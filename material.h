#pragma once

#include <SFML/Graphics.hpp>
#include <string>

/*-----------------------------------------------------
                    CLASE PADRE: Collidable
-----------------------------------------------------*/

class Colision {
public:
    virtual ~Colision() = default;

    // Cada objeto sabrá devolver su propia caja de colisión
    virtual sf::FloatRect getBounds() const = 0;
};

/*-----------------------------------------------------
                    CLASE HIJA: MATERIAL
-----------------------------------------------------*/

class ObjetoMapa : public Colision
{
private:

    sf::Sprite _sprite;

    // Caja de colisión relativa a la textura original (sin escala).
    sf::FloatRect _cajaColision;

public:
    // Constructor que inicializa el objeto con su textura, posición en el mapa y caja sólida relativa
    ObjetoMapa(const sf::Texture& texture, sf::Vector2f position);
    virtual ~ObjetoMapa() override = default;

    // Implementación obligatoria del método de la clase padre

    void setScale(sf::Vector2f escala);

    // Define la caja sólida en píxeles de la textura original.
    void setCajaColision(sf::FloatRect cajaLocal);

    // Devuelve la caja de colisión en coordenadas del mundo.
    sf::FloatRect getBounds() const override;

    // Permite dibujar el sprite del objeto en la ventana del juego
    void draw(sf::RenderWindow& window) const;


};
