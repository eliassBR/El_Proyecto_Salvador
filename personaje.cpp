#include "personaje.h"
#include "partida.h"
#include <iostream>


/*-----------------------------------------------------
                    CONSTRUCTOR
-----------------------------------------------------*/

Personaje::Personaje(sf::RenderWindow& ventana)
    : _ventana(ventana),
      _textura("assets/images/sprites/spriteP1caminando.png"),
      _sprite(_textura),
      _velocidad(200.f),
      _vida(100),
      _fila(0),
      _columna(0),
      _frameActual(0),
      _cantFrames(3),
      _ancho(362),
      _alto(362),
      _contador(0.f),
      _cuadrosPorFrame(0.15f),
      _limiteIzq(50.f),
      _limiteDer(1000.f),
      _limiteArriba(100.f),
      _limiteAbajo(500.f),
      _inventario(ventana)
{
    _sprite.setTextureRect(sf::IntRect(
        {_columna * _ancho, _fila * _alto},
        {_ancho, _alto}
    ));

    _sprite.setPosition({400.f, 200.f});
    _sprite.setScale({0.64f, 0.96f});
}


/*-----------------------------------------------------
                         MOVIMIENTO
-----------------------------------------------------*/

void Personaje::setLimites(float izq, float der, float arriba, float abajo)
{
    _limiteIzq = izq;
    _limiteDer = der;
    _limiteArriba = arriba;
    _limiteAbajo = abajo;
}


void Personaje::colocarPies(float x, float y)
{
    _sprite.setPosition({
        x - (_ancho * _sprite.getScale().x) / 2.f,
        y - (_alto * _sprite.getScale().y)
    });
}


bool Personaje::puedePisar(float x, float y, const Partida& partida) const
{
    const float PIES_IZQ = 60.f;
    const float PIES_DER = 258.f;
    const float PIES_Y = 320.f;

    float escalaX = _sprite.getScale().x;
    float escalaY = _sprite.getScale().y;

    float izquierda = x + PIES_IZQ * escalaX;
    float derecha = x + PIES_DER * escalaX;
    float piesY = y + PIES_Y * escalaY;


    // Comprobación de colisiones con las paredes.
    for (float px = izquierda; px < derecha; px += 10.f)
    {
        if (partida.verificarColision(px, piesY))
        {
            return false;
        }
    }

        if (partida.verificarColision(derecha, piesY))
    {
        return false;
    }


    /*
    // Comprobación de colisiones con los objetos del catálogo.
    sf::Sprite spritePersonaje = _sprite;
    spritePersonaje.setPosition({x, y});

    if (partida.colisionConMaterial1(spritePersonaje, spritePersonaje))
    {
        return false;
    }
    */


    // Comprobación de colisiones con los objetos del catálogo (solo los pies).
    // Se arma una caja fina en los pies del personaje y se compara solo esa.
    const float ALTO_PIES = 10.f;

    sf::FloatRect cajaPies(
        {izquierda, piesY - ALTO_PIES},
        {derecha - izquierda, ALTO_PIES}
    );

    if (partida.colisionConObjetos(cajaPies))
    {
        return false;
    }

    return true;

}


void Personaje::caminar(const Partida& partida)
{
    static sf::Clock relojInterno;
    float dt = relojInterno.restart().asSeconds();

    if (dt > 0.05f)
    {
        dt = 0.05f;
    }


    // El inventario se actualiza siempre, para poder abrirlo y cerrarlo.
    _inventario.actualizar();


    // Con el inventario abierto, el personaje no se mueve.
    if (_inventario.estaAbierto())
    {
        _frameActual = 0;
        _contador = 0.f;
        _columna = 0;

        _sprite.setTextureRect(sf::IntRect(
            {_columna * _ancho, _fila * _alto},
            {_ancho, _alto}
        ));

        return;
    }


    // Variables de movimiento.
    float dx = 0.f;
    float dy = 0.f;
    bool enMovimiento = false;


    // Movimiento hacia arriba.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        dy = -_velocidad * dt;
        _fila = 1;
        enMovimiento = true;
    }

    // Movimiento hacia abajo.
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) ||
             sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        dy = _velocidad * dt;
        _fila = 3;
        enMovimiento = true;
    }

    // Movimiento hacia la izquierda.
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
             sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        dx = -_velocidad * dt;
        _fila = 2;
        enMovimiento = true;
    }

    // Movimiento hacia la derecha.
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
             sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        dx = _velocidad * dt;
        _fila = 0;
        enMovimiento = true;
    }


    // Posición actual del personaje.
    float x = _sprite.getPosition().x;
    float y = _sprite.getPosition().y;


    // Movimiento horizontal.
    if (dx != 0.f && puedePisar(x + dx, y, partida))
    {
        x += dx;
    }


    // Movimiento vertical.
    if (dy != 0.f && puedePisar(x, y + dy, partida))
    {
        y += dy;
    }


    // Aplicar la posición definitiva.
    _sprite.setPosition({x, y});


    // Actualización de la animación.
    if (enMovimiento)
    {
        _contador += dt;

        if (_contador >= 0.11f)
        {
            _contador = 0.f;
            _frameActual = (_frameActual + 1) % _cantFrames;
        }
    }
    else
    {
        _frameActual = 0;
        _contador = 0.f;
    }


    // Actualización del cuadro de animación.
    _columna = _frameActual;

    _sprite.setTextureRect(sf::IntRect(
        {_columna * _ancho, _fila * _alto},
        {_ancho, _alto}
    ));
}


/*-----------------------------------------------------
                         ANIMACIÓN
-----------------------------------------------------*/

void Personaje::setFila(int fila)
{
    _fila = fila;
}


/*-----------------------------------------------------
                         INVENTARIO
-----------------------------------------------------*/

bool Personaje::agregarObjeto(int idObjeto)
{
    return _inventario.agregarObjeto(idObjeto);
}


bool Personaje::tieneObjeto(int idObjeto) const
{
    return _inventario.tieneObjeto(idObjeto);
}


/*-----------------------------------------------------
                    CONSULTAS Y DIBUJADO
-----------------------------------------------------*/

sf::FloatRect Personaje::getBounds() const
{
    return _sprite.getGlobalBounds();
}


void Personaje::dibujar()
{
    _ventana.draw(_sprite);
    _inventario.dibujar();
}
