#ifndef CARTAESPECIAL   
#define CARTAESPECIAL   

#include <string>
#include <vector>
#include "tablero.h"
#include "jugador.h"
#include <queue>
#include <fstream>
#include <sstream>

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

typedef struct Carta Carta;


struct Cartas_Comunity{
    std::queue<Carta> cartas_comunity;
};

struct Cartas_Chance{
    std::queue<Carta> cartas_chance;
};



std::vector<Carta> leerCartasComunidadDesdeTxt(const std::string& nombreArchivo);
std::vector<Carta> leerCartasChanceDesdeTxt(const std::string& nombreArchivo);

Cartas_Comunity crearCartasComunity(std::vector<Carta> cartas_comunity);

Cartas_Chance crearCartasChance(std::vector<Carta> cartas_chance);

void AplicarCarta(Tablero& tablero, Jugador& jugador, const Carta& carta, std::vector<Jugador>& jugadores);

Carta ObtenerCartaComunity(const Cartas_Comunity& cartas_comunity);
Carta ObtenerCartaChance(const Cartas_Chance& cartas_chance);

void ColocarAlFinalCartasComunity(Cartas_Comunity& cartas_comunity, Carta carta);

void ColocarAlFinalCartasChance(Cartas_Chance& cartas_chance, Carta carta);

#endif