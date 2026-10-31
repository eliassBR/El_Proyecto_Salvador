#include "partida.h"
#include <iostream>

// Constructor de Partida.
Partida::Partida(sf::RenderWindow& ventana, TipoMapa tipoMapa)
    : _ventana(ventana),
      _spriteFondo(_texturaFondo),
      _personaje1(_ventana),
      _auto(
          "assets/images/obj/autoGarageEditado.png",
          TipoMapa::GARAGE,
          {1000.f, 250.f},
          true
      ),
      _mapaActual(TipoMapa::NINGUNO),
      _puertaTocada(TipoMapa::NINGUNO),
      _bloqueoPuerta(false),
      _puertaDormitorio(
          {1126.f, 144.f},  //pos
          {110.f, 390.f}    //tam
      ),
      _puertaLivingDormitorio(
          {46.f, 155.f},  //pos
          {86.f, 372.f}   //tam
      ),
      _puertaLivingGarage(
          {1149.f, 155.f},  //pos
          {92.f, 379.f}     //tam
      ),
      _puertaGarage(
          {63.f, 67.f},     //pos
          {193.f, 500.f}    //tam
      )
{
    // Carga el mapa que se recibe como parámetro.
    cargarMapa(tipoMapa);
    if (_mapaActual == TipoMapa::HABITACION)
    {
        _personaje1.colocarPies(300.f, 550.f);
    }
}

// Devuelve el sprite del auto para poder consultar su posición.
sf::Sprite Partida::getposicion_auto() const
{
    return _auto.getposicion();
}

// Carga las imágenes correspondientes al mapa indicado.
// También carga su imagen de colisiones, que determina dónde puede caminar el personaje.
void Partida::cargarMapa(TipoMapa tipoMapa)
{
    std::string fondo;
    std::string colision;

    // Según el mapa recibido, se seleccionan sus archivos correspondientes.
    switch (tipoMapa)
    {
    case TipoMapa::HABITACION:
        fondo = "assets/images/backgrounds/fondoDormitorio.png";
        colision = "assets/images/backgrounds/fondoDormitorioColision.png";
        break;

    case TipoMapa::LIVING:
        fondo = "assets/images/backgrounds/fondoLiving.png";
        colision = "assets/images/backgrounds/fondoLivingColision.png";
        break;

    case TipoMapa::GARAGE:
        fondo = "assets/images/backgrounds/fondoGarage.png";
        colision = "assets/images/backgrounds/fondoGarageColision.png";
        break;

    default:
        std::cout << "Mapa sin configurar.\n";
        return;
    }

    // Se carga la imagen de fondo. Si ocurre un error, se informa y se interrumpe.
    if (!_texturaFondo.loadFromFile(fondo))
    {
        std::cout << "Error al cargar: " << fondo << '\n';
        return;
    }
    // Se carga la imagen que contiene las zonas transitables y las paredes.
    if (!_fondoColision.loadFromFile(colision))
    {
        std::cout << "Error al cargar: " << colision << '\n';
        return;
    }

    // Solo se actualiza el mapa actual cuando ambas imágenes se cargaron correctamente.
    _mapaActual = tipoMapa;
    _spriteFondo.setTexture(_texturaFondo, true);
}

// Comprueba si una coordenada corresponde a una puerta del mapa actual.
// Si encuentra una, guarda cuál es el mapa al que permite acceder.
bool Partida::dentroDePuerta(float x, float y) const
{
    const sf::Vector2f punto{x, y};

    // Se revisan las puertas según el mapa en el que se encuentra el personaje.
    switch (_mapaActual)
    {
    case TipoMapa::HABITACION:
        if (_puertaDormitorio.contains(punto))
        {
            _puertaTocada = TipoMapa::LIVING;
            return true;
        }
        break;
    case TipoMapa::LIVING:
        if (_puertaLivingDormitorio.contains(punto))
        {
            _puertaTocada = TipoMapa::HABITACION;
            return true;
        }

        if (_puertaLivingGarage.contains(punto))
        {
            _puertaTocada = TipoMapa::GARAGE;
            return true;
        }
        break;
    case TipoMapa::GARAGE:
        if (_puertaGarage.contains(punto))
        {
            _puertaTocada = TipoMapa::LIVING;
            return true;
        }
        break;

    default:
        break;
    }

    return false;
}

// Verifica si una coordenada del mapa representa una pared.
// Devuelve true si hay colisión y false si el personaje puede pasar.
bool Partida::verificarColision(float x, float y) const
{
    const auto tamano = _fondoColision.getSize();

    // Si la coordenada está fuera de los límites de la imagen,     se considera una colisión para impedir que el personaje salga del mapa.
    if (x < 0.f || y < 0.f ||
        x >= tamano.x || y >= tamano.y)
    {
        return true;
    }

    // Primero se detectan las cajas de las puertas.       La puerta es transitable aunque tenga píxeles negros en la imagen de colisiones.
    if (dentroDePuerta(x, y))
    {
        return false;
    }

    // Se obtiene el color del píxel correspondiente a la posición consultada.
    const sf::Color color = _fondoColision.getPixel({
        static_cast<unsigned int>(x),
        static_cast<unsigned int>(y)
    });

    // Negro: pared, por lo tanto no se puede avanzar.
    if (color == sf::Color::Black)
    {
        return true;
    }

    // Los demás colores, incluido el verde, representan zonas transitables.
    return false;
}

// Comprueba si el personaje está tocando el auto.  // Solo considera la colisión cuando el auto está habilitado y se encuentra en el mismo mapa que el personaje.
bool Partida::colisionConMaterial1(const sf::Sprite& pos_personaje, const sf::Sprite& pos_objeto) const
{
    if (!_auto.esColisionable() || _auto.getMapaAsignado() != _mapaActual)
    {
        return false;
    }

    // Compara los rectángulos que ocupan el personaje y el objeto.     // Si se superponen, existe una colisión.
    return pos_personaje.getGlobalBounds().findIntersection(pos_objeto.getGlobalBounds()).has_value();
}

// Determina en qué coordenadas debe aparecer el personaje cuando pasa de un mapa a otro.   // Las posiciones dependen tanto del mapa de destino como del de origen.
sf::Vector2f Partida::posicionDeAparicion(TipoMapa destino, TipoMapa origen) const
{
    // Dormitorio -> Living.
    if (origen == TipoMapa::HABITACION &&
        destino == TipoMapa::LIVING)
    {
        return {250.f, 560.f};
    }

    // Garage -> Living.
    if (origen == TipoMapa::GARAGE &&
        destino == TipoMapa::LIVING)
    {
        return {980.f, 560.f};
    }

    // Living -> Dormitorio.
    if (origen == TipoMapa::LIVING &&
        destino == TipoMapa::HABITACION)
    {
        return {980.f, 560.f};
    }

    // Living -> Garage.
    if (origen == TipoMapa::LIVING &&
        destino == TipoMapa::GARAGE)
    {
        return {400.f, 560.f};
    }

    // Posición predeterminada si no coincide ninguna combinación.
    return {300.f, 550.f};
}

// Realiza el cambio de escenario.  // Guarda el mapa de origen, carga el destino y coloca al personaje en la posición de aparición correspondiente.
void Partida::cambiarMapa(TipoMapa destino)
{
    const TipoMapa origen = _mapaActual;

    cargarMapa(destino);

    // Si el mapa no se pudo cargar, no se modifica la posición del personaje.
    if (_mapaActual != destino)
    {
        return;
    }

    // Se calcula la posición de aparición según los mapas involucrados.
    const sf::Vector2f aparicion = posicionDeAparicion(destino, origen);

    _personaje1.colocarPies(aparicion.x, aparicion.y);

    // Evita que el personaje vuelva a activar la puerta inmediatamente después de aparecer en el nuevo mapa.
    _bloqueoPuerta = true;
}

// Actualiza el estado de la partida.   // Controla el movimiento del personaje y determina si debe cambiar de mapa.
void Partida::actualizar(float dt)
{
    (void)dt;

    // Se reinicia la puerta detectada antes de procesar el movimiento.
    _puertaTocada = TipoMapa::NINGUNO;

    // Actualiza el movimiento del personaje y verifica las colisiones.
    _personaje1.caminar(*this);

    // Si el personaje ya no está tocando una puerta    // se permite detectar una nueva.
    if (_puertaTocada == TipoMapa::NINGUNO)
    {
        _bloqueoPuerta = false;
    }
    // Si hay una puerta detectada y no está bloqueada  // se realiza el cambio al mapa correspondiente.
    else if (!_bloqueoPuerta &&
             _puertaTocada != _mapaActual)
    {
        cambiarMapa(_puertaTocada);
    }
}

void Partida::dibujar()
{
    _ventana.draw(_spriteFondo);
    _auto.dibujar(_ventana, _mapaActual);
    _personaje1.dibujar();
}
