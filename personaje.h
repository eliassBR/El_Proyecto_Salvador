#pragma once

#include <SFML/Graphics.hpp>
#include "Inventario.h"

class Partida;

class Personaje
{
private:

    /*-----------------------------------------------------
                    ATRIBUTOS DEL PERSONAJE
    -----------------------------------------------------*/

    sf::RenderWindow& _ventana;
    sf::Texture _textura;
    sf::Sprite _sprite;

    float _velocidad;
    int _vida;

    /*-----------------------------------------------------
                    ATRIBUTOS DE ANIMACIÓN
    -----------------------------------------------------*/

    int _fila;
    int _columna;
    int _frameActual;
    int _cantFrames;
    int _ancho;
    int _alto;

    float _contador;
    float _cuadrosPorFrame;

    /*-----------------------------------------------------
                    LÍMITES DEL MAPA
    -----------------------------------------------------*/

    float _limiteIzq;
    float _limiteDer;
    float _limiteArriba;
    float _limiteAbajo;

    /*-----------------------------------------------------
                    CLASE : OBJ _INVENTARIO
    -----------------------------------------------------*/

    Inventario _inventario;

    /*-----------*/

public:

    /*-----------------------------------------------------
                    CONSTRUCTOR
    -----------------------------------------------------*/

    Personaje(sf::RenderWindow& ventana);

    /*-----------------------------------------------------
                    MOVIMIENTO
    -----------------------------------------------------*/

    void setLimites(float izq, float der, float arriba, float abajo);
    void colocarPies(float x, float y);
    bool puedePisar(float x, float y, const Partida& partida) const;
    void caminar(const Partida& partida);

    /*-----------------------------------------------------
                    ANIMACIÓN
    -----------------------------------------------------*/

    void setFila(int fila);

    /*-----------------------------------------------------
                    INVENTARIO
    -----------------------------------------------------*/

    bool agregarObjeto(int idObjeto);
    bool tieneObjeto(int idObjeto) const;

    /*-----------------------------------------------------
                    CONSULTAS Y DIBUJADO
    -----------------------------------------------------*/

    sf::FloatRect getBounds() const;
    void dibujar();
};
