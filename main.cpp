#include "cartaEspecial.h"
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

void mostrarEstadoJugador(const Jugador& jugador) {
    std::cout << "\n--- Estado de " << jugador.nombre << " ---" << std::endl;
    std::cout << "Posicion: Casilla " << jugador.posicion << std::endl;
    std::cout << "Saldo: $" << jugador.saldo << std::endl;
    std::cout << "En carcel: " << (jugador.enCarcel ? "Si" : "No") << std::endl;
    if(jugador.tiene_salir_carcel) {
        std::cout << "Tiene carta de salir de carcel" << std::endl;
    }
    if(jugador.multiplicador_alquiler > 1) {
        std::cout << "Multiplicador de alquiler: x" << jugador.multiplicador_alquiler << std::endl;
    }
    std::cout << "------------------------\n" << std::endl;
}

void probarCarta(Tablero& tablero, Jugador& jugador, const Carta& carta, std::vector<Jugador>& jugadores) {
    std::cout << "\n========================================" << std::endl;
    std::cout << "CARTA: " << carta.descripcion << std::endl;
    std::cout << "Tipo: " << carta.tipo << " | Accion: " << carta.accion << std::endl;
    std::cout << "========================================" << std::endl;
    
    std::cout << "\nAntes de aplicar la carta:" << std::endl;
    mostrarEstadoJugador(jugador);
    
    AplicarCarta(tablero, jugador, carta, jugadores);
    
    std::cout << "\nDespues de aplicar la carta:" << std::endl;
    mostrarEstadoJugador(jugador);
    
    std::cout << "\nPresiona Enter para continuar...";
    std::cin.get();
}

int main() {
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
    #endif

    std::cout << "=== PROBANDO TAD DE CARTAS ESPECIALES ===\n" << std::endl;

    // Crear tablero básico
    std::vector<Casilla> casillas = leerCasillasDesdeTxt("casillas.txt");
    Tablero tablero = crearTablero(casillas);

    // Crear jugadores de prueba
    std::vector<Jugador> jugadores;
    
    Jugador jugador1;
    jugador1.nombre = "Alice";
    jugador1.posicion = 7;
    jugador1.saldo = 1500;
    jugador1.enCarcel = false;
    jugador1.turnosEnCarcel = 0;
    jugador1.tiene_salir_carcel = false;
    jugador1.multiplicador_alquiler = 1;
    
    Jugador jugador2;
    jugador2.nombre = "Bob";
    jugador2.posicion = 15;
    jugador2.saldo = 1200;
    jugador2.enCarcel = false;
    jugador2.turnosEnCarcel = 0;
    jugador2.tiene_salir_carcel = false;
    jugador2.multiplicador_alquiler = 1;
    
    Jugador jugador3;
    jugador3.nombre = "Charlie";
    jugador3.posicion = 22;
    jugador3.saldo = 1800;
    jugador3.enCarcel = false;
    jugador3.turnosEnCarcel = 0;
    jugador3.tiene_salir_carcel = false;
    jugador3.multiplicador_alquiler = 1;
    
    jugadores.push_back(jugador1);
    jugadores.push_back(jugador2);
    jugadores.push_back(jugador3);

    // Cargar cartas desde archivos
    std::cout << "Cargando cartas de Comunidad..." << std::endl;
    auto cartasComunidadVec = leerCartasComunidadDesdeTxt("Cartas_comunity.txt");
    
    std::cout << "Cargando cartas de Chance..." << std::endl;
    auto cartasChanceVec = leerCartasChanceDesdeTxt("Cartas_Chance.txt");

    if (cartasComunidadVec.empty()) {
        std::cerr << "No se cargaron cartas de Comunidad" << std::endl;
        return 1;
    } else {
        std::cout << "Se cargaron " << cartasComunidadVec.size() << " cartas de Comunidad" << std::endl;
    }
    
    if (cartasChanceVec.empty()) {
        std::cerr << "No se cargaron cartas de Chance" << std::endl;
        return 1;
    } else {
        std::cout << "Se cargaron " << cartasChanceVec.size() << " cartas de Chance" << std::endl;
    }

    // Crear mazos usando tus structs
    Cartas_Comunity mazoComunidad;
    for(const auto& carta : cartasComunidadVec) {
        mazoComunidad.cartas_comunity.push(carta);
    }

    Cartas_Chance mazoChance;
    for(const auto& carta : cartasChanceVec) {
        mazoChance.cartas_chance.push(carta);
    }

    std::cout << "\n=== Mazos creados exitosamente ===" << std::endl;

    // Menú de pruebas
    int opcion;
    do {
        std::cout << "\n========================================" << std::endl;
        std::cout << "MENU DE PRUEBAS" << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "1. Probar carta de Comunidad" << std::endl;
        std::cout << "2. Probar carta de Chance" << std::endl;
        std::cout << "3. Ver estado de todos los jugadores" << std::endl;
        std::cout << "4. Probar varias cartas seguidas (Comunidad)" << std::endl;
        std::cout << "5. Probar varias cartas seguidas (Chance)" << std::endl;
        std::cout << "6. Reiniciar estado del jugador 1" << std::endl;
        std::cout << "7. Ver cartas restantes en mazos" << std::endl;
        std::cout << "0. Salir" << std::endl;
        std::cout << "Opcion: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch(opcion) {
            case 1: {
                if(mazoComunidad.cartas_comunity.empty()) {
                    std::cout << "\nNo hay mas cartas en el mazo de Comunidad" << std::endl;
                    std::cin.get();
                    break;
                }
                Carta carta = ObtenerCartaComunity(mazoComunidad);
                probarCarta(tablero, jugadores[0], carta, jugadores);
                mazoComunidad.cartas_comunity.pop();
                ColocarAlFinalCartasComunity(mazoComunidad, carta);
                break;
            }
            case 2: {
                if(mazoChance.cartas_chance.empty()) {
                    std::cout << "\nNo hay mas cartas en el mazo de Chance" << std::endl;
                    std::cin.get();
                    break;
                }
                Carta carta = ObtenerCartaChance(mazoChance);
                probarCarta(tablero, jugadores[0], carta, jugadores);
                mazoChance.cartas_chance.pop();
                ColocarAlFinalCartasChance(mazoChance, carta);
                break;
            }
            case 3: {
                std::cout << "\n=== ESTADO DE TODOS LOS JUGADORES ===" << std::endl;
                for(const auto& j : jugadores) {
                    mostrarEstadoJugador(j);
                }
                std::cout << "\nPresiona Enter para continuar...";
                std::cin.get();
                break;
            }
            case 4: {
                std::cout << "\nCuantas cartas quieres probar? ";
                int n;
                std::cin >> n;
                std::cin.ignore();
                
                for(int i = 0; i < n && !mazoComunidad.cartas_comunity.empty(); i++) {
                    Carta carta = ObtenerCartaComunity(mazoComunidad);
                    probarCarta(tablero, jugadores[0], carta, jugadores);
                    mazoComunidad.cartas_comunity.pop();
                    ColocarAlFinalCartasComunity(mazoComunidad, carta);
                }
                break;
            }
            case 5: {
                std::cout << "\nCuantas cartas quieres probar? ";
                int n;
                std::cin >> n;
                std::cin.ignore();
                
                for(int i = 0; i < n && !mazoChance.cartas_chance.empty(); i++) {
                    Carta carta = ObtenerCartaChance(mazoChance);
                    probarCarta(tablero, jugadores[0], carta, jugadores);
                    mazoChance.cartas_chance.pop();
                    ColocarAlFinalCartasChance(mazoChance, carta);
                }
                break;
            }
            case 6: {
                jugadores[0].posicion = 7;
                jugadores[0].saldo = 1500;
                jugadores[0].enCarcel = false;
                jugadores[0].turnosEnCarcel = 0;
                jugadores[0].tiene_salir_carcel = false;
                jugadores[0].multiplicador_alquiler = 1;
                std::cout << "\nJugador reiniciado!" << std::endl;
                std::cin.get();
                break;
            }
            case 7: {
                std::cout << "\nCartas en mazo de Comunidad: " << mazoComunidad.cartas_comunity.size() << std::endl;
                std::cout << "Cartas en mazo de Chance: " << mazoChance.cartas_chance.size() << std::endl;
                std::cout << "\nPresiona Enter para continuar...";
                std::cin.get();
                break;
            }
            case 0:
                std::cout << "\nSaliendo..." << std::endl;
                break;
            default:
                std::cout << "\nOpcion invalida" << std::endl;
                std::cin.get();
        }
    } while(opcion != 0);

    return 0;
}