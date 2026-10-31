#include "MENU.h"

Menu::Menu(sf::RenderWindow& ventana) : _ventana(ventana),
    _texturaPortada("assets/images/ui/portadaJuego.png"),
    _spritePortada(_texturaPortada),
    _fuente("assets/fonts/arial.ttf"),
    _opcionJugar(_fuente,"JUGAR"),
    _opcionCargar(_fuente,"CARGAR JUEGO"),
    _opcionAjustes(_fuente,"AJUSTES"),
    _opcionSalir(_fuente,"SALIR"),
    _opcSeleccionada(1)
{
    _opcionJugar.setCharacterSize(40);
    _opcionJugar.setPosition({555,350});
    _opcionJugar.setFillColor(sf::Color::White);

    _opcionCargar.setCharacterSize(40);
    _opcionCargar.setPosition({465,420});
    _opcionCargar.setFillColor(sf::Color::Yellow);

    _opcionAjustes.setCharacterSize(40);
    _opcionAjustes.setPosition({545,490});
    _opcionAjustes.setFillColor(sf::Color::Yellow);

    _opcionSalir.setCharacterSize(40);
    _opcionSalir.setPosition({570,560});
    _opcionSalir.setFillColor(sf::Color::Yellow);

}

void Menu::cambiarSeleccion(sf::Keyboard::Key tecla)
{
    switch(_opcSeleccionada)
    {
    case 1:
        if (tecla == sf::Keyboard::Key::Down)
        {
            _opcionJugar.setFillColor(sf::Color::Yellow);
            _opcionCargar.setFillColor(sf::Color::White);
            _opcSeleccionada = 2;
        }
        else if (tecla == sf::Keyboard::Key::Up)
        {
            _opcionJugar.setFillColor(sf::Color::Yellow);
            _opcionSalir.setFillColor(sf::Color::White);
            _opcSeleccionada =4;
        }
        break;
    case 2:
        if (tecla == sf::Keyboard::Key::Down)
        {
            _opcionCargar.setFillColor(sf::Color::Yellow);
            _opcionAjustes.setFillColor(sf::Color::White);
            _opcSeleccionada = 3;
        }
        else if (tecla == sf::Keyboard::Key::Up)
        {
            _opcionCargar.setFillColor(sf::Color::Yellow);
            _opcionJugar.setFillColor(sf::Color::White);
            _opcSeleccionada = 1;
        }
        break;
    case 3:
        if (tecla == sf::Keyboard::Key::Down)
        {
            _opcionAjustes.setFillColor(sf::Color::Yellow);
            _opcionSalir.setFillColor(sf::Color::White);
            _opcSeleccionada = 4;
        }
        else if (tecla == sf::Keyboard::Key::Up)
        {
            _opcionAjustes.setFillColor(sf::Color::Yellow);
            _opcionCargar.setFillColor(sf::Color::White);
            _opcSeleccionada = 2;
        }
        break;
    case 4:
        if (tecla == sf::Keyboard::Key::Down)
        {
            _opcionSalir.setFillColor(sf::Color::Yellow);
            _opcionJugar.setFillColor(sf::Color::White);
            _opcSeleccionada = 1;
        }
        else if (tecla == sf::Keyboard::Key::Up)
        {
            _opcionSalir.setFillColor(sf::Color::Yellow);
            _opcionAjustes.setFillColor(sf::Color::White);
            _opcSeleccionada = 3;
        }
        break;
    }
}

int Menu::getOpcSeleccionada()
{
    return _opcSeleccionada;
}

void Menu::dibujarPortada()
{
    _ventana.draw(_spritePortada);
    _ventana.draw(_opcionJugar);
    _ventana.draw(_opcionCargar);
    _ventana.draw(_opcionAjustes);
    _ventana.draw(_opcionSalir);

}
