#include "partida.h"
#include <iostream>

/*-----------------------------------------------------
                    CONSTRUCTOR
-----------------------------------------------------*/

Partida::Partida(sf::RenderWindow& ventana, TipoMapa tipoMapa)
    : _ventana(ventana),
      _personaje1(_ventana),
      _spriteFondo(_texturaFondo),
      _mapaActual(TipoMapa::NINGUNO),
      _puertaTocada(TipoMapa::NINGUNO),
      _bloqueoPuerta(false),
      _puertaDormitorio(
          {1126.f, 144.f},
          {110.f, 390.f}
      ),
      _puertaLivingDormitorio(
          {46.f, 155.f},
          {86.f, 372.f}
      ),
      _puertaLivingGarage(
          {1149.f, 155.f},
          {92.f, 379.f}
      ),
      _puertaGarage(
          {63.f, 67.f},
          {193.f, 500.f}
      )
{
    cargarMapa(tipoMapa);

    if (_mapaActual == TipoMapa::HABITACION)
    {
        _personaje1.colocarPies(100.f, 550.f);
    }
}


/*-----------------------------------------------------
            SISTEMA DE MAPAS Y COLISIONES
-----------------------------------------------------*/

// Carga las imágenes correspondientes al mapa indicado.
void Partida::cargarMapa(TipoMapa tipoMapa)
{
    std::string fondo;
    std::string colision;

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

    // Carga la imagen de fondo.
    if (!_texturaFondo.loadFromFile(fondo))
    {
        std::cout << "Error al cargar: " << fondo << '\n';
        return;
    }

    // Carga la imagen de colisiones.
    if (!_fondoColision.loadFromFile(colision))
    {
        std::cout << "Error al cargar: " << colision << '\n';
        return;
    }

    // Actualiza el mapa actual.
    _mapaActual = tipoMapa;
    _spriteFondo.setTexture(_texturaFondo, true);

    // Carga los objetos correspondientes al nuevo mapa.
    _mapaCatalogo.cargarObjetos(tipoMapa);
}


// Comprueba si una coordenada corresponde a una puerta.
bool Partida::dentroDePuerta(float x, float y) const
{
    const sf::Vector2f punto{x, y};

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


// Verifica si una coordenada representa una pared.
bool Partida::verificarColision(float x, float y) const
{
    const auto tamano = _fondoColision.getSize();

    if (x < 0.f || y < 0.f ||
        x >= tamano.x || y >= tamano.y)
    {
        return true;
    }

    if (dentroDePuerta(x, y))
    {
        return false;
    }

    const sf::Color color = _fondoColision.getPixel({
        static_cast<unsigned int>(x),
        static_cast<unsigned int>(y)
    });

    if (color == sf::Color::Black)
    {
        return true;
    }

    return false;
}

/*------------------------*/

// Comprueba si el personaje colisiona con algún objeto del catálogo.
bool Partida::colisionConMaterial1(
    const sf::Sprite& pos_personaje,
    const sf::Sprite& pos_objeto
) const
{
    // El segundo parámetro se conserva por compatibilidad
    // con las llamadas anteriores, pero ya no necesitamos un objeto individual.
    (void)pos_objeto;

    // Recorremos todos los objetos del mapa actual.
    for (const auto& objeto : _mapaCatalogo.getColisionables())
    {
        if (pos_personaje.getGlobalBounds()
                .findIntersection(objeto->getBounds()).has_value())
        {
            return true;
        }
    }

    return false;
}

bool Partida::colisionConObjetos(const sf::FloatRect& caja) const
{
    for (const auto& objeto : _mapaCatalogo.getColisionables())
    {
        if (caja.findIntersection(objeto->getBounds()).has_value())
        {
            return true;
        }
    }

    return false;
}

/*-----------------------------------------------------
                  SISTEMA DE PUERTAS
-----------------------------------------------------*/

// Determina dónde aparece el personaje al cambiar de mapa.
sf::Vector2f Partida::posicionDeAparicion(
    TipoMapa destino,
    TipoMapa origen
) const
{
    if (origen == TipoMapa::HABITACION &&
        destino == TipoMapa::LIVING)
    {
        return {250.f, 560.f};
    }

    if (origen == TipoMapa::GARAGE &&
        destino == TipoMapa::LIVING)
    {
        return {980.f, 560.f};
    }

    if (origen == TipoMapa::LIVING &&
        destino == TipoMapa::HABITACION)
    {
        return {960.f, 560.f};
    }

    if (origen == TipoMapa::LIVING &&
        destino == TipoMapa::GARAGE)
    {
        return {200.f, 600.f};
    }

    return {300.f, 550.f};
}


// Realiza el cambio de escenario.
void Partida::cambiarMapa(TipoMapa destino)
{
    const TipoMapa origen = _mapaActual;

    cargarMapa(destino);

    std::cout << "Mapa después del cambio: "
              << static_cast<int>(_mapaActual) << '\n';

    if (_mapaActual != destino)
    {
        return;
    }

    const sf::Vector2f aparicion =
        posicionDeAparicion(destino, origen);

    _personaje1.colocarPies(aparicion.x, aparicion.y);

    _bloqueoPuerta = true;
}


/*-----------------------------------------------------
                ACTUALIZACIÓN Y DIBUJO
-----------------------------------------------------*/

// Actualiza el estado de la partida.
void Partida::actualizar(float dt)
{
    (void)dt;

    _puertaTocada = TipoMapa::NINGUNO;

    _personaje1.caminar(*this);

    if (_puertaTocada == TipoMapa::NINGUNO)
    {
        _bloqueoPuerta = false;
    }
    else if (!_bloqueoPuerta &&
             _puertaTocada != _mapaActual)
    {
        cambiarMapa(_puertaTocada);
    }
}


// Dibuja los elementos de la partida.
void Partida::dibujar()
{
    _ventana.draw(_spriteFondo);

    // Dibuja todos los objetos del catálogo.
    for (const auto& objeto : _mapaCatalogo.getColisionables())
    {
        if (const auto* objetoMapa =
                dynamic_cast<const ObjetoMapa*>(objeto.get()))
        {
            objetoMapa->draw(_ventana);
        }
    }

    // Dibuja al personaje.
    _personaje1.dibujar();
}
