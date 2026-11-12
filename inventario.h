#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Inventario
{
private:

    /*-----------------------------------------------------
                        ALMACENAMIENTO
    -----------------------------------------------------*/

    std::vector<int> _objetos;

    int _slotSeleccionado;
    int _opcionSeleccionada;
    int _objetoEnUso;

    /*-----------------------------------------------------
                            ESTADOS
    -----------------------------------------------------*/

    bool _inventarioAbierto;
    bool _menuOpcionesAbierto;

    /*-----------------------------------------------------
                      CONTROL DE TECLADO
    -----------------------------------------------------*/

    bool _teclaEAnterior;
    bool _teclaEnterAnterior;
    bool _teclaEscapeAnterior;
    bool _teclaArribaAnterior;
    bool _teclaAbajoAnterior;

    bool _teclasNumericasAnteriores[5];

    /*-----------------------------------------------------
                            INTERFAZ
    -----------------------------------------------------*/

    sf::RenderWindow& _ventana;

    sf::RectangleShape _fondoInventario;
    sf::RectangleShape _slots[5];

    sf::RectangleShape _fondoOpciones;
    sf::RectangleShape _opciones[3];

    /*-----------------------------------------------------
                       FUNCIONES INTERNAS
    -----------------------------------------------------*/

    int cantidadOpciones() const;
    void ejecutarOpcion();

public:

    /*-----------------------------------------------------
                          CONSTRUCTOR
    -----------------------------------------------------*/

    Inventario(sf::RenderWindow& ventana);

    /*-----------------------------------------------------
                        ADMINISTRACIÓN
    -----------------------------------------------------*/

    bool agregarObjeto(int idObjeto);
    void quitarObjeto(int numeroSlot);
    bool tieneObjeto(int idObjeto) const;

    /*-----------------------------------------------------
                         FUNCIONAMIENTO
    -----------------------------------------------------*/

    void actualizar();
    void dibujar();

    /*-----------------------------------------------------
                           CONSULTAS
    -----------------------------------------------------*/

    bool estaAbierto() const;
    int getObjetoEnUso() const;
};
