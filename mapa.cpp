
#include "mapa.h"
#include <iostream>
#include <utility>

/*-----------------------------------------------------
                    CLASE: Mapa
-----------------------------------------------------*/

Mapa::Mapa() {}

void Mapa::cargarObjetos(TipoMapa tipoMapa)
{
    // 1. Vaciamos el catálogo del mapa anterior para liberar la memoria de los objetos viejos.
    _colisionables.clear();
    _texturas.clear();

    // 2. Dependiendo del mapa al que entra el personaje, creamos sus objetos sólidos correspondientes.
    switch (tipoMapa)
    {
    case TipoMapa::HABITACION:

        break;

       case TipoMapa::LIVING:
    {
        // ------------------------------------
        // OBJETO 1: EL MUEBLE
        // ------------------------------------

        // Cargar textura.
        auto texturaMueble = std::make_unique<sf::Texture>("assets/images/obj/muebleLiving.png");

        // Guardar la textura.
        const sf::Texture& referenciaMueble = *texturaMueble;
        _texturas.push_back(std::move(texturaMueble));

        // Crear el mueble.
        auto mueble = std::make_unique<ObjetoMapa>(referenciaMueble,sf::Vector2f(500.f, 340.f));

        // Establecer escala.
        mueble->setScale({0.40f, 0.40f});

        // Solo la base del mueble es sólida (en píxeles de la imagen 414x457).
        mueble->setCajaColision(sf::FloatRect({20.f, 330.f}, {374.f, 120.f}));

        // Agregar al catálogo.
        _colisionables.push_back(std::move(mueble));

        break;
    }

    case TipoMapa::GARAGE:
    {
        // ------------------------------------
        // OBJETO 1: LA MESA
        // ------------------------------------

        // Cargar textura.
        auto texturaMesa = std::make_unique<sf::Texture>(
                               "assets/images/obj/mesaGarage.png"
                           );

        // Guardar la textura.
        const sf::Texture& referenciaMesa = *texturaMesa;
        _texturas.push_back(std::move(texturaMesa));

        // Crear la mesa y agregarla al catálogo.
        auto mesa = std::make_unique<ObjetoMapa>(referenciaMesa,sf::Vector2f(780.f, 300.f));

        // Agregar al catálogo.
        _colisionables.push_back(std::move(mesa));

        break;
    }

    case TipoMapa::NINGUNO:

        break;

    default:
        std::cout << "Advertencia: Cargando un mapa sin objetos o catálogo no configurado.\n";
        break;
    }
}

const std::vector<std::unique_ptr<Colision>>& Mapa::getColisionables() const
{
    return _colisionables;
}
