#include "juego.h"
#include <ctime>
#include <iostream>
#include <vector>

std::vector<Jugador> inicializarJugadores(){
    std::cout << "Ingrese el numero de jugadores (2 - 4): " << std::endl;
    std::vector<Jugador> jugadores;
    int numJugadores;
    std::cin >> numJugadores;
    if(numJugadores < 2 || numJugadores > 4){
        std::cout << "[Error] El numero de jugadores es invalido. Reinicie el juego.\n";
        exit(1);
    } 
    for(int i = 0; i < numJugadores; i++){
        std::string nombre;
        std::cout << "Ingrese el nombre del jugador " << i + 1 << ": ";
        std::cin >> nombre;
        Jugador jugador = crearJugador(nombre);
        jugadores.push_back(jugador);
    }
    return jugadores;
}

int main(){
    srand(time(NULL));
    std::cout <<  "=============================================\n"
    "            BIENVENIDO A MONOPOLY C++        \n"
    "=============================================\n"
    "Domina las calles, negocia, invierte y evita la bancarrota.\n"
    "Que comience la partida!\n";
    std::vector<Jugador> jugadores = inicializarJugadores();
    std::vector<Casilla> casillas = leerCasillasDesdeTxt("Casillas.txt");
    Tablero tablero = crearTablero(casillas);
    Cartas_Chance cartas_chance = crearCartasChance(leerCartasChanceDesdeTxt("Cartas_Chance.txt"));
    Cartas_Comunity cartas_comunity = crearCartasComunity(leerCartasComunidadDesdeTxt("Cartas_comunity.txt"));
    Juego juego = crearJuego(jugadores, tablero, cartas_chance, cartas_comunity);
    while(juego.juego_activo){
        std::cout << "\n--- TURNO DE " << juego.jugadores[juego.turno].nombre << " ---\n";
       std::cout << "\n---------------------------------------------\n"
        "Opciones del turno:\n"
        "  1) Jugar     -> Tirar dados y avanzar\n"
        "  2) Info      -> Consultar su informacion\n"
        "  3) Tablero   -> Ver el estado del tablero\n"
        "  4) Deshacer  -> Revertir la ultima accion\n"
        "---------------------------------------------\n"
        "Escriba un comando: ";
        std::string comando;
        std::cin >> comando;
        if(comando == "Jugar" || comando == "jugar"){
            ejecutarTirada(juego);
        } else if(comando == "Info" || comando == "info"){
            mostrarInfoJugador(juego.tablero, juego.jugadores[juego.turno]);
        } else if(comando == "Tablero" || comando == "tablero"){
            mostrarTablero(juego.tablero, juego.jugadores);
        } else if(comando == "Deshacer" || comando == "deshacer"){
            DeshacerUltimaAccion(juego);
        } else {
            std::cout << "[Error] Comando no reconocido. Intente nuevamente.\n";
        }
        if(juego.jugadores[juego.turno].saldo <= 0 && juego.jugadores[juego.turno].EnBancarrota == true){
            std::cout << juego.jugadores[juego.turno].nombre << " ha quedado en bancarrota y abandona la partida.\n";
            juego.jugadores.erase(juego.jugadores.begin() + juego.turno);
            if(juego.turno >= juego.jugadores.size()) juego.turno = 0;
        }
        if(juego.jugadores.size() == 1){
            std::cout << juego.jugadores[0].nombre << " es el ganador del juego! Felicidades!\n";
            std::cout << "=============================================\n"
    "               FIN DE LA PARTIDA             \n"
    "=============================================\n";
            juego.juego_activo = false;
        }
    }
    return 0;
}

