#include "material.h"
#include "partida.h"
#include <iostream>

Material::Material(
    const std::string& ruta,
    TipoMapa mapaAsignado,
    sf::Vector2f posicion,
    bool colisionable
)
    : _textura(),
      _sprite(_textura),
      _mapaAsignado(mapaAsignado),
      _colisionable(colisionable)
{
    if (!_textura.loadFromFile(ruta))
    {
        std::cout << "No se pudo cargar el material: "
                  << ruta << '\n';
    }

    _sprite.setTexture(_textura);
    _sprite.setPosition(posicion);
}

void Material::dibujar(
    sf::RenderWindow& ventana,
    TipoMapa mapaActual
)
{
    // El objeto solo aparece en su mapa asignado.
    if (_mapaAsignado == mapaActual)
        ventana.draw(_sprite);
}

sf::Sprite Material::getposicion() const
{
    return _sprite;
}

sf::FloatRect Material::getBounds() const
{
    return _sprite.getGlobalBounds();
}

bool Material::esColisionable() const
{
    return _colisionable;
}

TipoMapa Material::getMapaAsignado() const
{
    return _mapaAsignado;
}
