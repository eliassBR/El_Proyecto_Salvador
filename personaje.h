#pragma once

#include <SFML/Graphics.hpp>

class Partida;

class Personaje
{
private:
    sf::RenderWindow& _ventana;
    sf::Texture _textura;
    sf::Sprite _sprite;

    float _velocidad;

    int _fila;
    int _columna;
    int _frameActual;
    int _cantFrames;
    int _ancho;
    int _alto;

    float _contador;
    float _cuadrosPorFrame;

    float _limiteIzq;
    float _limiteDer;
    float _limiteArriba;
    float _limiteAbajo;

public:
    Personaje(sf::RenderWindow& ventana);

    void setLimites(
        float izq,
        float der,
        float arriba,
        float abajo
    );

    void setFila(int fila);
    void colocarPies(float x, float y);

    bool puedePisar(
        float x,
        float y,
        const Partida& partida
    ) const;

    void caminar(const Partida& partida);
    sf::FloatRect getBounds() const;
    void dibujar();
};
