#include "Inventario.h"
#include <iostream>

/*-----------------------------------------------------
                        CONSTRUCTOR
-----------------------------------------------------*/

Inventario::Inventario(sf::RenderWindow& ventana)
    : _objetos(5, 0),
      _slotSeleccionado(0),
      _opcionSeleccionada(0),
      _objetoEnUso(0),
      _inventarioAbierto(false),
      _menuOpcionesAbierto(false),
      _teclaEAnterior(false),
      _teclaEnterAnterior(false),
      _teclaEscapeAnterior(false),
      _teclaArribaAnterior(false),
      _teclaAbajoAnterior(false),
      _ventana(ventana),
      _fondoInventario({520.f, 130.f}),
      _fondoOpciones({190.f, 118.f})
{
    for (int i = 0; i < 5; i++)
    {
        _teclasNumericasAnteriores[i] = false;
    }

    // Fondo del inventario.
    _fondoInventario.setFillColor(sf::Color(30, 30, 30, 230));
    _fondoInventario.setPosition({350.f, 20.f});

    // Los cinco slots.
    for (int i = 0; i < 5; i++)
    {
        _slots[i].setSize({80.f, 80.f});
        _slots[i].setPosition({365.f + i * 100.f, 45.f});
        _slots[i].setFillColor(sf::Color(75, 75, 75));
        _slots[i].setOutlineThickness(3.f);
        _slots[i].setOutlineColor(sf::Color::White);
    }

    // Fondo del menú de opciones (debajo del inventario).
    _fondoOpciones.setFillColor(sf::Color(30, 30, 30, 240));
    _fondoOpciones.setPosition({515.f, 160.f});

    // Las tres opciones.
    for (int i = 0; i < 3; i++)
    {
        _opciones[i].setSize({160.f, 25.f});
        _opciones[i].setPosition({530.f, 170.f + i * 32.f});
        _opciones[i].setFillColor(sf::Color(80, 80, 80));
    }
}

/*-----------------------------------------------------
                      ADMINISTRACIÓN
-----------------------------------------------------*/

// Agrega un objeto al primer slot vacío. Devuelve false si no hay lugar.
bool Inventario::agregarObjeto(int idObjeto)
{
    if (idObjeto <= 0)
    {
        return false;
    }

    for (int i = 0; i < 5; i++)
    {
        if (_objetos[i] == 0)
        {
            _objetos[i] = idObjeto;
            return true;
        }
    }

    std::cout << "Inventario lleno.\n";
    return false;
}


// Quita el objeto del slot indicado.
void Inventario::quitarObjeto(int numeroSlot)
{
    if (numeroSlot < 0 || numeroSlot >= 5)
    {
        return;
    }

    // Si el objeto en uso era ese, ya no está en uso.
    if (_objetos[numeroSlot] == _objetoEnUso)
    {
        _objetoEnUso = 0;
    }

    _objetos[numeroSlot] = 0;
}


// Comprueba si el inventario contiene un objeto.
bool Inventario::tieneObjeto(int idObjeto) const
{
    for (int i = 0; i < 5; i++)
    {
        if (_objetos[i] == idObjeto)
        {
            return true;
        }
    }

    return false;
}


/*-----------------------------------------------------
                      FUNCIONES INTERNAS
-----------------------------------------------------*/

// Seleccionar, soltar y cancelar. Si el slot está vacío, ninguna.
int Inventario::cantidadOpciones() const
{
    if (_objetos[_slotSeleccionado] == 0)
    {
        return 0;
    }

    return 3;
}


void Inventario::ejecutarOpcion()
{
    int objeto = _objetos[_slotSeleccionado];

    if (objeto == 0)
    {
        _menuOpcionesAbierto = false;
        return;
    }

    // Opción 0: seleccionar.
    if (_opcionSeleccionada == 0)
    {
        _objetoEnUso = objeto;
        std::cout << "Objeto seleccionado: " << objeto << '\n';
    }

    // Opción 1: soltar.
    else if (_opcionSeleccionada == 1)
    {
        quitarObjeto(_slotSeleccionado);
        std::cout << "Objeto soltado.\n";
    }

    // Opción 2: cancelar (no hace nada).

    _menuOpcionesAbierto = false;
}


/*-----------------------------------------------------
                       FUNCIONAMIENTO
-----------------------------------------------------*/

void Inventario::actualizar()
{
    bool teclaE      = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E);
    bool teclaEnter  = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter);
    bool teclaEscape = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape);
    bool teclaArriba = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);
    bool teclaAbajo  = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down);


    // Abrir o cerrar el inventario.
    if (teclaE && !_teclaEAnterior)
    {
        _inventarioAbierto = !_inventarioAbierto;
        _menuOpcionesAbierto = false;
    }

    _teclaEAnterior = teclaE;


    // Si está cerrado, actualizamos las teclas anteriores para que
    // no se dispare nada apenas se abra.
    if (!_inventarioAbierto)
    {
        _teclaEnterAnterior = teclaEnter;
        _teclaEscapeAnterior = teclaEscape;
        _teclaArribaAnterior = teclaArriba;
        _teclaAbajoAnterior = teclaAbajo;

        for (int i = 0; i < 5; i++)
        {
            _teclasNumericasAnteriores[i] = false;
        }

        return;
    }


    // Selección directa de los cinco slots.
    const sf::Keyboard::Key teclasSlots[5] =
    {
        sf::Keyboard::Key::Num1,
        sf::Keyboard::Key::Num2,
        sf::Keyboard::Key::Num3,
        sf::Keyboard::Key::Num4,
        sf::Keyboard::Key::Num5
    };

    for (int i = 0; i < 5; i++)
    {
        bool tecla = sf::Keyboard::isKeyPressed(teclasSlots[i]);

        if (tecla && !_teclasNumericasAnteriores[i])
        {
            _slotSeleccionado = i;
            _menuOpcionesAbierto = false;
        }

        _teclasNumericasAnteriores[i] = tecla;
    }


    // Abrir el menú de opciones o confirmar una opción.
    if (teclaEnter && !_teclaEnterAnterior)
    {
        if (!_menuOpcionesAbierto)
        {
            if (_objetos[_slotSeleccionado] != 0)
            {
                _menuOpcionesAbierto = true;
                _opcionSeleccionada = 0;
            }
        }
        else
        {
            ejecutarOpcion();
        }
    }

    _teclaEnterAnterior = teclaEnter;


    // Recorrer las opciones.
    if (_menuOpcionesAbierto)
    {
        if (teclaArriba && !_teclaArribaAnterior)
        {
            _opcionSeleccionada--;

            if (_opcionSeleccionada < 0)
            {
                _opcionSeleccionada = cantidadOpciones() - 1;
            }
        }

        if (teclaAbajo && !_teclaAbajoAnterior)
        {
            _opcionSeleccionada++;

            if (_opcionSeleccionada >= cantidadOpciones())
            {
                _opcionSeleccionada = 0;
            }
        }
    }

    _teclaArribaAnterior = teclaArriba;
    _teclaAbajoAnterior = teclaAbajo;


    // Escape: cierra el menú de opciones, o el inventario.
    if (teclaEscape && !_teclaEscapeAnterior)
    {
        if (_menuOpcionesAbierto)
        {
            _menuOpcionesAbierto = false;
        }
        else
        {
            _inventarioAbierto = false;
        }
    }

    _teclaEscapeAnterior = teclaEscape;
}


/*-----------------------------------------------------
                           DIBUJADO
-----------------------------------------------------*/

void Inventario::dibujar()
{
    if (!_inventarioAbierto)
    {
        return;
    }

    _ventana.draw(_fondoInventario);

    for (int i = 0; i < 5; i++)
    {
        if (i == _slotSeleccionado)
        {
            _slots[i].setOutlineColor(sf::Color::Yellow);
        }
        else
        {
            _slots[i].setOutlineColor(sf::Color::White);
        }

        _ventana.draw(_slots[i]);
    }

    if (_menuOpcionesAbierto)
    {
        _ventana.draw(_fondoOpciones);

        int cantidad = cantidadOpciones();

        for (int i = 0; i < cantidad; i++)
        {
            if (i == _opcionSeleccionada)
            {
                _opciones[i].setFillColor(sf::Color(180, 150, 50));
            }
            else
            {
                _opciones[i].setFillColor(sf::Color(80, 80, 80));
            }

            _ventana.draw(_opciones[i]);
        }
    }
}


/*-----------------------------------------------------
                          CONSULTAS
-----------------------------------------------------*/

bool Inventario::estaAbierto() const
{
    return _inventarioAbierto;
}


int Inventario::getObjetoEnUso() const
{
    return _objetoEnUso;
}
