#ifndef MAPA_H_INCLUDED
#define MAPA_H_INCLUDED

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "material.h"

enum class TipoMapa { NINGUNO, HABITACION, LIVING, GARAGE };

/*-----------------------------------------------------
                    CLASE: Mapa
-----------------------------------------------------*/

class Mapa
{
private:
    // Guarda las texturas para que sigan existiendo mientras se usan.
    std::vector<std::unique_ptr<sf::Texture>> _texturas;

    // El catálogo: guardamos punteros inteligentes a Colision.
    // Esto nos permite meter cualquier objeto derivado (como ObjetoMapa) de forma dinámica.
    std::vector<std::unique_ptr<Colision>> _colisionables;

public:
    Mapa();
    ~Mapa() = default;

    // Se encarga de limpiar el catálogo anterior y rellenarlo con los objetos del mapa seleccionado.
    void cargarObjetos(TipoMapa tipoMapa);

    // Permite que otras clases (como Partida) puedan consultar la lista de objetos sólidos actuales.
    const std::vector<std::unique_ptr<Colision>>& getColisionables() const;
};

#endif // MAPA_H_INCLUDED
