#ifndef HISTORIAL_H
#define HISTORIAL_H
//libreriras necesarias
#include <string>
#include <vector>
#include "tablero.h"
#include "jugador.h"
#include "cartaEspecial.h"
#include <queue>
#include <stack>

//Definicion estructura Historial
struct Historial{
    std::vector<Jugador> jugadores;
    Tablero tablero;
    Cartas_Chance cartas_chance;
    Cartas_Comunity cartas_comunity;
    int turno;
};
//Definicion estructura Juego
struct Juego{ 
    std::vector<Jugador> jugadores;
    Tablero tablero;
    Cartas_Chance cartas_chance;
    Cartas_Comunity cartas_comunity;
    int turno;
    std::stack<Historial> historial;
    int ultimoValorDados;
    bool juego_activo;
    bool turno_en_progreso;  
    int tiradas_consecutivas;
    bool aplicarcasilla_despues_carta;
};

typedef struct Juego Juego;
typedef struct Historial Historial;

//Funcion para crear el juego
Juego crearJuego(const std::vector<Jugador>& jugadores, const Tablero& tablero, const Cartas_Chance& cartas_chance, const Cartas_Comunity& cartas_comunity); // Pre: vector de jugadores - tablero - cartas chance y cartas comunity -----> Post: Juego iniciado
//Funciones para lanzar dados
std::pair<int, int> lanzardados(); // Pre: Nada -----> Post: Dos numeros enteros
//Funciones para mover al jugador
void moverJugador(Juego& juego, int indiceJugador, std::pair<int, int> pasos); // Pre: Juego - jugador a mover - la cantidad de pasos a mover -----> Post: El jugador estara en una nueva posicion (La suma de los pasos)
void pasarturno(Juego& juego); // Pre: Juego -----> Post: Se pasa al siguiente jugador
//Funcion para aplicar la casilla en la que cayó el jugador
void aplicarCasilla(Juego& juego, int posicion, int indiceJugador); // Pre: Juego - jugador - posicion de la casilla -----> Post: El jugador hara lo que la casilla le diga o le de la opcion 
//Funcion para cobrar alquiler
void cobrarAlquiler(Juego& juego, int indiceJugadorPropietario, int indiceJugadorQPaga, int pos); // Pre: Juego - jugador a cobrar - jugador a pagar - la propeidad donde cayo  -----> Post: Se le restara lo que cueste el alquiler al que cayo en una propiedad y al dueño se le sumara
//Funcion para sacar carta chance
void sacarCartaChance(Juego& juego, int indiceJugador); // Pre: Juego y jugador -----> Post: Saca una carta de la cola de cartas chance, la aplica y la mete al final 
//Funcion para sacar carta comunity
void sacarCartaComunity(Juego& juego, int indiceJugador); // Pre: Juego y jugador -----> Post: Saca una carta de la cola de cartas comunity, la aplica y la mete al final 
//Funcion para guardar el estado actual del juego en el historial
void guardarEstadoHistorial(Juego& juego); // Pre: Juego -----> Post: Se añade en la pila el ultimo turno (Estado del juego)
//Funcion para deshacer la ultima accion
void DeshacerUltimaAccion(Juego& juego); // Pre: Juego  -----> Post: Elimina el turno anterior de la partida
// Funcion para una tirada (jugada)
void ejecutarTirada(Juego& juego);// Pre: Juego  -----> Post: Ejecuta el flujo de una jugada
//Funcion para comprar casa con usuario
void comprar_casa(Juego& juego, int indiceJugador); // Pre: Juego y jugador  -----> Post: Se verifica que pueda comprar casa en una propiedad y se sube de nivel
//Funcion para comprar casa con usuario
void comprar_hotel(Juego& juego, int indiceJugador); // Pre: Juego y jugador -----> Post: Se verifica que pueda comprar hotel en una propiedad y se sube de nivel
//Funcion para Hipotecar una propiedad
void hipotecar_propiedad(Juego& juego, int indiceJugador); // Pre: Juego y jugador  -----> Post: Buscar casa e hipotecar
//Funcion para deshipotecar una propiedad
void deshipotecar_propiedad(Juego& juego, int indiceJugador); // Pre: Juego y jugador  -----> Post: Buscar casa y deshipotecar

#endif