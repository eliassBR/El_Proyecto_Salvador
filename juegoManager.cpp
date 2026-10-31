#include "juegoManager.h"

JuegoManager::JuegoManager(sf::RenderWindow& ventana)
    : _ventana(ventana),
      _menu(ventana),
      _partida(ventana, TipoMapa::HABITACION),
      _estado(PORTADA)
{
}

void JuegoManager::ejecutar()
{
    sf::Clock reloj;

    while (_ventana.isOpen())
    {
        const float dt = reloj.restart().asSeconds();

        while (const std::optional evento = _ventana.pollEvent())
        {
            if (evento->is<sf::Event::Closed>())
                _ventana.close();

            if (const auto* tecla =
                    evento->getIf<sf::Event::KeyPressed>())
            {
                if (_estado == PORTADA)
                {
                    if (tecla->code == sf::Keyboard::Key::Down ||
                        tecla->code == sf::Keyboard::Key::Up)
                    {
                        _menu.cambiarSeleccion(tecla->code);
                    }

                    if (tecla->code == sf::Keyboard::Key::Enter)
                    {
                        const int opc =
                            _menu.getOpcSeleccionada();

                        if (opc == 1)
                            _estado = JUGANDO;

                        if (opc == 2)
                            _estado = CARGAR_PARTIDA;

                        if (opc == 3)
                            _estado = AJUSTES;

                        if (opc == 4)
                            _ventana.close();
                    }
                }
                else if (_estado == JUGANDO &&
                         tecla->code == sf::Keyboard::Key::Escape)
                {
                    _estado = PAUSA;
                }
                else if (_estado == PAUSA &&
                         tecla->code == sf::Keyboard::Key::Escape)
                {
                    _estado = JUGANDO;
                }
            }
        }

        if (_estado == JUGANDO)
            _partida.actualizar(dt);

        _ventana.clear();

        switch (_estado)
        {
        case PORTADA:
            _menu.dibujarPortada();
            break;

        case JUGANDO:
            _partida.dibujar();
            break;

        case PAUSA:
            // Mantiene el juego pausado hasta pulsar Escape.
            _partida.dibujar();
            break;

        default:
            break;
        }

        _ventana.display();
    }
}
