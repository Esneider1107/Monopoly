#ifndef CARTAESPECIAL   
#define CARTAESPECIAL   

#include <string>
#include <vector>
#include "tablero.h"
#include "jugador.h"
#include <queue>

struct Carta{
    std::string descripcion;
    std::string tipo;
    std::string accion;
    int monto;
    int monto_casa;
    int monto_hotel;
    int casilla_destino;        
    int multiplicador;          
    int casillas_movimiento;
};
struct Cartas_Comunity{
    std::queue<Carta> cartas_comunity;
};

struct Cartas_Chance{
    std::queue<Carta> cartas_chance;
};

Cartas_Comunity crearCartasComunity();

Cartas_Chance crearCartaChance();

void AplicarCarta(Jugador& juagdor, const Carta& carta);

void ObtenerCarta(const Carta& carta);

void ColocarAlFinal(const Carta& carta);

#endif