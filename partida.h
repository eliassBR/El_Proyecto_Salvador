
#ifndef PARTIDA_H
#define PARTIDA_H

#include <SFML/Graphics.hpp>
#include "personaje.h"
#include "material.h"

enum class TipoMapa
{
    NINGUNO,
    GARAGE,
    LIVING,
    HABITACION
};

class Partida
{
private:
    sf::RenderWindow& _ventana;

    sf::Texture _texturaFondo;
    sf::Sprite _spriteFondo;
    sf::Image _fondoColision;

    Personaje _personaje1;
    Material _auto;

    TipoMapa _mapaActual;
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
    // Constructor.
    Partida(sf::RenderWindow& ventana, TipoMapa tipoMapa);

    // Devuelve el sprite del auto.
    sf::Sprite getposicion_auto() const;

    // Carga el fondo y las colisiones del mapa.
    void cargarMapa(TipoMapa tipoMapa);

    // Comprueba si una posición tiene una pared.
    bool verificarColision(float x, float y) const;

    // Comprueba la colisión entre el personaje y el auto.
    bool colisionConMaterial1(const sf::Sprite& pos_personaje, const sf::Sprite& pos_objeto) const;

    // Calcula dónde aparece el personaje al cambiar de mapa.
    sf::Vector2f posicionDeAparicion(TipoMapa destino, TipoMapa origen) const;

    // Cambia al mapa indicado.
    void cambiarMapa(TipoMapa destino);

    // Actualiza el movimiento y los cambios de mapa.
    void actualizar(float dt);

    // Dibuja los elementos de la partida.
    void dibujar();
};

#endif
