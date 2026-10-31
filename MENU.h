#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <SFML/Graphics.hpp>

class Menu
{
private:
    sf::RenderWindow& _ventana;
    sf::Texture _texturaPortada;
    sf::Sprite _spritePortada;
    sf::Font _fuente;
    sf::Text _opcionJugar;
    sf::Text _opcionCargar;
    sf::Text _opcionAjustes;
    sf::Text _opcionSalir;
    int _opcSeleccionada;

public:
    Menu(sf::RenderWindow& ventana);
    int getOpcSeleccionada();
    void dibujarPortada();
    void cambiarSeleccion(sf::Keyboard::Key tecla);


};

#endif // MENU_H_INCLUDED
