#ifndef PARTIDA_H
#define PARTIDA_H

#include <SFML/Graphics.hpp>
#include "personaje.h"
#include "mapa.h"

class Partida
{
private:

    /*-----------------------------------------------------
                    ATRIBUTOS GENERALES
    -----------------------------------------------------*/

    sf::RenderWindow& _ventana;
    Personaje _personaje1;

    /*-----------------------------------------------------
                       SISTEMA DE MAPAS
    -----------------------------------------------------*/

    sf::Texture _texturaFondo;
    sf::Sprite _spriteFondo;
    sf::Image _fondoColision;

    TipoMapa _mapaActual;

    // Catálogo de objetos correspondientes al mapa actual.
    Mapa _mapaCatalogo;

    // Carga el fondo y las colisiones del mapa.
    void cargarMapa(TipoMapa tipoMapa);


    /*-----------------------------------------------------
                        SISTEMA DE PUERTAS
    -----------------------------------------------------*/

    mutable TipoMapa _puertaTocada;
    bool _bloqueoPuerta;

    // Áreas de detección de las puertas.
    sf::FloatRect _puertaDormitorio;
    sf::FloatRect _puertaLivingDormitorio;
    sf::FloatRect _puertaLivingGarage;
    sf::FloatRect _puertaGarage;

    // Comprueba si una posición está dentro de una puerta.
    bool dentroDePuerta(float x, float y) const;


public:

    /*-----------------------------------------------------
                     CONSTRUCTOR
    -----------------------------------------------------*/

    Partida(sf::RenderWindow& ventana, TipoMapa tipoMapa);


    /*-----------------------------------------------------
                SISTEMA DE MAPAS Y COLISIONES
    -----------------------------------------------------*/

    // Comprueba si una posición tiene una pared.
    bool verificarColision(float x, float y) const;

    // Cambia al mapa indicado.
    void cambiarMapa(TipoMapa destino);

    // Comprueba la colisión del personaje con los objetos del catálogo.
    bool colisionConMaterial1(
        const sf::Sprite& pos_personaje,
        const sf::Sprite& pos_objeto
    ) const;

    // Comprueba si una caja (por ejemplo, los pies del personaje) choca con algún objeto del catálogo.
    bool colisionConObjetos(const sf::FloatRect& caja) const;

    // Calcula dónde aparece el personaje al cambiar de mapa.
    sf::Vector2f posicionDeAparicion(
        TipoMapa destino,
        TipoMapa origen
    ) const;


    /*-----------------------------------------------------
                    ACTUALIZACIÓN Y DIBUJO
    -----------------------------------------------------*/

    // Actualiza el movimiento y los cambios de mapa.
    void actualizar(float dt);

    // Dibuja los elementos de la partida.
    void dibujar();
};

#endif
