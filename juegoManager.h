#pragma once

#include <SFML/Graphics.hpp>
#include <optional>
#include "partida.h"
#include "menu.h"

enum EstadoJuego
{
    PORTADA,
    JUGANDO,
    PAUSA,
    CARGAR_PARTIDA,
    AJUSTES
};

class JuegoManager
{
private:
    sf::RenderWindow& _ventana;
    Menu _menu;
    Partida _partida;
    EstadoJuego _estado;

public:
    explicit JuegoManager(sf::RenderWindow& ventana);
    void ejecutar();
};
