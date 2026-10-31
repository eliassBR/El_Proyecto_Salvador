#pragma once

#include <SFML/Graphics.hpp>
#include <string>

enum class TipoMapa;

class Material
{
private:
    sf::Texture _textura;
    sf::Sprite _sprite;
    TipoMapa _mapaAsignado;     // 0 = Garage, 1 = Cocina, 2 = living
    bool _colisionable;

public:
    Material(
        const std::string& ruta,
        TipoMapa mapaAsignado,
        sf::Vector2f posicion,
        bool colisionable
    );

    void dibujar(
        sf::RenderWindow& ventana,
        TipoMapa mapaActual
    );

    sf::Sprite getposicion() const;
    sf::FloatRect getBounds() const;
    bool esColisionable() const;
    TipoMapa getMapaAsignado() const;
};

