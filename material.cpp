#include "partida.h"
#include "material.h"
#include <iostream>

/*-----------------------------------------------------
                    CLASE HIJA: MapaObjeto
-----------------------------------------------------*/

ObjetoMapa::ObjetoMapa(const sf::Texture& texture, sf::Vector2f position)
    : _sprite(texture),
      // Por defecto, la caja es toda la textura.
      _cajaColision(sf::FloatRect({0.f, 0.f}, sf::Vector2f(texture.getSize())))
{
    // La textura ya se asignó arriba gracias al constructor de inicialización (:).
    // Ahora solo acomodamos su posición en el mundo.
    _sprite.setPosition(position);
}

/*
ObjetoMapa::ObjetoMapa(const sf::Texture& texture, sf::Vector2f position, sf::FloatRect localCollisionBox)
    : _sprite(texture)
{
    // La textura ya se asignó arriba gracias al constructor de inicialización (:).
    // Ahora solo acomodamos su posición en el mundo.
    _sprite.setPosition(position);

    // Calculamos la caja de colisión absoluta en el mundo sumando la posición del objeto
    _cajaColision = sf::FloatRect(
        sf::Vector2f(position.x + localCollisionBox.position.x, position.y + localCollisionBox.position.y),
        localCollisionBox.size
    );
}
*/

sf::FloatRect ObjetoMapa::getBounds() const
{
    const sf::Vector2f pos = _sprite.getPosition();
    const sf::Vector2f esc = _sprite.getScale();

    return sf::FloatRect(
        {pos.x + _cajaColision.position.x * esc.x,
         pos.y + _cajaColision.position.y * esc.y},
        {_cajaColision.size.x * esc.x,
         _cajaColision.size.y * esc.y}
    );
}

void ObjetoMapa::setScale(sf::Vector2f escala)
{
    _sprite.setScale(escala);
}

void ObjetoMapa::setCajaColision(sf::FloatRect cajaLocal)
{
    _cajaColision = cajaLocal;
}

/*
sf::FloatRect ObjetoMapa::getBounds() const
{
    return _cajaColision;
}
*/

void ObjetoMapa::draw(sf::RenderWindow& window) const
{
    window.draw(_sprite); // Corregido: mSprite cambiado por tu variable real '_sprite'
}
