#include "juegoManager.h"

int main()
{
    sf::RenderWindow ventana(sf::VideoMode({1280, 720}), "El Proyecto Salvador");
    ventana.setFramerateLimit(60);

    JuegoManager juego(ventana);
    juego.ejecutar();

    return 0;
}
