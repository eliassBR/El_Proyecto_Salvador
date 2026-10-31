#include "personaje.h"
#include "partida.h"
#include "material.h"
#include <iostream>

Personaje::Personaje(sf::RenderWindow& ventana)
    : _ventana(ventana),
      _textura("assets/images/sprites/spriteP1caminando.png"),
      _sprite(_textura),
      _velocidad(200.f),
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
      _limiteAbajo(500.f)
{
    _sprite.setTextureRect(sf::IntRect({_columna*_ancho,_fila*_alto}, {_ancho,_alto}));
    _sprite.setPosition({400.f, 200.f});
    _sprite.setScale({0.64f, 0.96f});
}

void Personaje::setLimites(float izq, float der, float arriba, float abajo)
{
    _limiteIzq = izq;
    _limiteDer = der;
    _limiteArriba = arriba;
    _limiteAbajo = abajo;
}

void Personaje::setFila(int fila)
{
    _fila = fila;
}

void Personaje::colocarPies(float x, float y)
{
    _sprite.setPosition({x - (_ancho * _sprite.getScale().x) / 2.f, y - (_alto * _sprite.getScale().y)});
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

    // Se revisa un punto cada 10 píxeles a lo largo de los pies
    for (float px = izquierda; px < derecha; px += 10.f)
    {
        if (partida.verificarColision(px, piesY))
        {
            return false;
        }
    }

    return !partida.verificarColision(derecha, piesY);
}

void Personaje::caminar(const Partida& partida)
{
    sf::Vector2f posicionAnterior = _sprite.getPosition();
    static sf::Clock relojInterno;
    float dt = relojInterno.restart().asSeconds();

    if (dt > 0.05f)
    {
        dt = 0.05f;
    }

    // MANDATORIO: Creamos dx y dy acá arriba para que las líneas 182 y 186 funcionen
    float dx = 0.f;
    float dy = 0.f;
    bool enMovimiento = false;


    // ARRIBA: Tecla W o Flecha Arriba
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        dy = -_velocidad * dt;
        _fila = 1;
        enMovimiento = true;
    }
    // ABAJO: S o flecha abajo
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        dy = _velocidad * dt;
        _fila = 3;
        enMovimiento = true;
    }
    // IZQUIERDA: A o flecha izquierda
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        dx = -_velocidad * dt;
        _fila = 2;
        enMovimiento = true;
    }
    // DERECHA: D o flecha derecha
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        dx = _velocidad * dt;
        _fila = 0;
        enMovimiento = true;
    }

    /*    limitarMovimiento(); */


    // Filtramos la posición: Solo se aplican dx e dy si caen en zona blanca
    float x = _sprite.getPosition().x;
    float y = _sprite.getPosition().y;

     // Movimiento horizontal
    if (dx != 0.f && puedePisar(x + dx, y, partida))
    {
        _sprite.setPosition({x + dx, y});
        x += dx;
    }

    // Movimiento vertical
    if (dy != 0.f && puedePisar(x, y + dy, partida))
    {
        _sprite.setPosition({x, y + dy});
        y += dy;
    }

    // Aplicar la posición definitiva
    _sprite.setPosition({x, y});

    // Animación
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

    // Colisión con el auto (en el lugar original)
    //sf::Sprite spriteAuto = partida.getposicion_auto();
    sf::Sprite spriteAuto = partida.getposicion_auto();

    /*if (partida.colisionConMaterial1(_sprite,spriteAuto,))
    {
        std::cout << "¡¡¡ COLISIÓN DETECTADA !!!" << std::endl;
        _sprite.setPosition(posicionAnterior);
    }*/


    if (partida.colisionConMaterial1(_sprite, spriteAuto))
    {
        std::cout << "¡¡¡ COLISIÓN DETECTADA !!!" << std::endl;
        _sprite.setPosition(posicionAnterior);
    }

 std::cout << "Personaje en: " << _sprite.getPosition().x << ", " << _sprite.getPosition().y << std::endl;
std::cout << "Auto en: " << spriteAuto.getPosition().x << ", " << spriteAuto.getPosition().y << std::endl;


    _columna = _frameActual;
    _sprite.setTextureRect(sf::IntRect({_columna * _ancho, _fila * _alto}, {_ancho, _alto}));
}


sf::FloatRect Personaje::getBounds()const
{
    return _sprite.getGlobalBounds();
}


void Personaje::dibujar()
{
    _ventana.draw(_sprite);
}
