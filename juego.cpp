#include "juego.h"
#include <iostream>
//Funcion para crear el juego
Juego crearJuego(const std::vector<Jugador>& jugadores, const Tablero& tablero, const Cartas_Chance& cartas_chance, const Cartas_Comunity& cartas_comunity){
    Juego juego;
    juego.jugadores = jugadores;
    juego.tablero = tablero;
    juego.cartas_chance = cartas_chance;
    juego.cartas_comunity = cartas_comunity;
    juego.turno = 0;
    juego.juego_activo = true;
    juego.turno_en_progreso = false;
    juego.tiradas_consecutivas = 0;
    return juego;
}

//Funciones para lanzar dados
std::pair<int, int> lanzardados(){ // Retorna una pareja de enteros
    //Numeros aleatorios entre 1 y 6
    int dado1 = rand() % 6 + 1; 
    int dado2 = rand() % 6 + 1;
    return std::make_pair(dado1, dado2); 
}
//Funciones para mover el jugador
void moverJugador(Juego& juego, int indiceJugador, std::pair<int, int> pasos){
    int total_pasos = pasos.first + pasos.second;
    juego.jugadores[indiceJugador].posicion += total_pasos;
    if(juego.jugadores[indiceJugador].posicion > 40){ // Si se pasa de 40, se reinicia a 1 
        juego.jugadores[indiceJugador].posicion -= 40;
        AgregarDinero(juego.jugadores[indiceJugador], 200);
        std::cout << juego.jugadores[indiceJugador].nombre << " paso por GO y cobra $200\n";
    }
}

//Aplicar la casilla en la que cayó el jugador
void aplicarCasilla(Juego& juego, int posicion, int indiceJugador){
    //Propiedad
    if(juego.tablero.casillas.at(posicion).funcion == "propiedad"){
        std::cout << "Ha caido en la propiedad: " << juego.tablero.casillas.at(posicion).nombre << std::endl;
        if(juego.tablero.casillas.at(posicion).propietario.empty()){
            mostrarCasilla(juego.tablero.casillas.at(posicion));// Muestro la casilla y si no tiene propietario sale el mensaje de quue se puede comprar
            std::string comando;
            std::cin >> comando;
            if(comando == "comprar"){
                ComprarPropiedad(juego.jugadores[indiceJugador], juego.tablero.casillas.at(posicion));
                std::cout << "Ha comprado la propiedad: " << juego.tablero.casillas.at(posicion).nombre << std::endl;
            } 
        } else if (juego.tablero.casillas.at(posicion).propietario != juego.jugadores[indiceJugador].nombre){
            for(int i = 0; i < (int)juego.jugadores.size(); i++){// Recorre jugadores 
                if(juego.jugadores[i].nombre == juego.tablero.casillas.at(posicion).propietario){ // Si el propietario coincide con el nombre del jugador
                    cobrarAlquiler(juego, i, indiceJugador, posicion);
                }
            }
        } else {
            std::cout << "Esta es tu propiedad.\n";
        }
    // Community Chest
    } else if(juego.tablero.casillas.at(posicion).funcion == "Community Chest"){
        std::cout << "Ha caido en Community Chest" << std::endl;
        sacarCartaComunity(juego, indiceJugador);
    // Chance
    } else if(juego.tablero.casillas.at(posicion).funcion == "Chance"){
        std::cout << "Ha caido en Chance" << std::endl;
        sacarCartaChance(juego, indiceJugador);
    //Income Tax
    } else if(juego.tablero.casillas.at(posicion).funcion == "Income Tax"){
        std::cout << "Ha caido en Income Tax" << std::endl;
        RetirarDinero(juego.jugadores[indiceJugador], 200);
    // Estacion
    } else if(juego.tablero.casillas.at(posicion).funcion == "estacion"){
        std::cout << "Ha caido en la estacion: " << juego.tablero.casillas.at(posicion).nombre << std::endl;
        if(juego.tablero.casillas.at(posicion).propietario.empty()){
            mostrarCasilla(juego.tablero.casillas.at(posicion));
            std::string comando;
            std::cin >> comando;
            if(comando == "comprar"){
                ComprarPropiedad(juego.jugadores[indiceJugador], juego.tablero.casillas.at(posicion));
                std::cout << "Ha comprado la estacion: " << juego.tablero.casillas.at(posicion).nombre << std::endl;
                std::cout << "Saldo: $" << juego.jugadores[indiceJugador].saldo << std::endl;
                mostrarCasilla(juego.tablero.casillas.at(posicion));
            } 
        } else if (juego.tablero.casillas.at(posicion).propietario != juego.jugadores[indiceJugador].nombre){
            for(int i = 0; i < (int)juego.jugadores.size(); i++){// Recorre jugadores 
                if(juego.jugadores[i].nombre == juego.tablero.casillas.at(posicion).propietario){ // Si el propietario coincide con el nombre del jugador
                    cobrarAlquiler(juego, i, indiceJugador, posicion);
                }
            }
        }
    //Jail
    } else if(juego.tablero.casillas.at(posicion).funcion == "jail"){
        std::cout << "Ha caido en la carcel" << std::endl;
        std::cout << "Solo estas de visita en la carcel." << std::endl;
    // Free Parking
    } else if(juego.tablero.casillas.at(posicion).funcion == "Free Parking"){
        std::cout << "Ha caido en Free Parking" << std::endl;
    //Go to Jail
    } else if(juego.tablero.casillas.at(posicion).funcion == "Go To Jail"){
        std::cout << "Ha caido en Go to Jail. Vas a la carcel!" << std::endl;
        juego.jugadores[indiceJugador].enCarcel = true;
        juego.jugadores[indiceJugador].turnosEnCarcel = 1;
        juego.jugadores[indiceJugador].posicion = 11;
    // Luxury Tax
    } else if(juego.tablero.casillas.at(posicion).funcion == "Luxury Tax"){
        std::cout << "Ha caido en Luxury Tax" << std::endl;
        juego.jugadores[indiceJugador].saldo -= 100;
    } else if (juego.tablero.casillas.at(posicion).funcion == "utilidad"){
        std::cout << "Ha caido en la utilidad " << juego.tablero.casillas.at(posicion).nombre << std::endl;
        if(juego.tablero.casillas.at(posicion).propietario.empty()){
            mostrarCasilla(juego.tablero.casillas.at(posicion));
            std::string comando;
            std::cin >> comando;
            if(comando == "comprar"){
                ComprarPropiedad(juego.jugadores[indiceJugador], juego.tablero.casillas.at(posicion));
                std::cout << "Ha comprado la utilidad: " << juego.tablero.casillas.at(posicion).nombre << std::endl;
                mostrarCasilla(juego.tablero.casillas.at(posicion));
            } else {
            }
        } else if (juego.tablero.casillas.at(posicion).propietario != juego.jugadores[indiceJugador].nombre){
            for(int i = 0; i < (int)juego.jugadores.size(); i++){// Recorre jugadores 
                if(juego.jugadores[i].nombre == juego.tablero.casillas.at(posicion).propietario){ // Si el propietario coincide con el nombre del jugador
                    cobrarAlquiler(juego, i, indiceJugador, posicion);
                }
            }
        }
    }
}

//Funcion para cobrar alquiler
void cobrarAlquiler(Juego& juego, int indiceJugadorPropietario, int indiceJugadorQPaga, int pos){
    // Referencias para mayor legibilidad
    Jugador& propietario = juego.jugadores[indiceJugadorPropietario];
    Jugador& jugadorQuePaga = juego.jugadores[indiceJugadorQPaga];
    Casilla& propiedad = juego.tablero.casillas[pos];

    // Verificación básica
    if (propiedad.propietario.empty() || propiedad.propietario != propietario.nombre) {
        std::cout << "Esta casilla no pertenece a " << propietario.nombre << ".\n";
        return;
    }

    // Determinar el monto base del alquiler
    int nivel = propiedad.nivel_propiedad;
    int montoBase = 0;
    if (propiedad.alquiler.find(nivel) != propiedad.alquiler.end()) {
        montoBase = propiedad.alquiler[nivel];
    } else {
        std::cout << "No se encontró un valor de alquiler para este nivel.\n";
        return;
    }

    // Aplicar multiplicadores (por ventaja o color)
    int multiplicador = 1;
    if (jugadorQuePaga.multiplicador_alquiler > 1) {
        multiplicador = jugadorQuePaga.multiplicador_alquiler;
        jugadorQuePaga.multiplicador_alquiler = 1;
    } else if (!propiedad.color.empty()) {
        int total_color = 0, total_propietario = 0;
        for (const auto& c : juego.tablero.casillas) {
            if (c.second.color == propiedad.color) {
                total_color++;
                if (c.second.propietario == propietario.nombre)
                    total_propietario++;
            }
        }
        if (total_color > 0 && total_color == total_propietario)
            multiplicador = 2;
    }

    int montoFinal = montoBase * multiplicador;

    // Verificar si el jugador puede pagar
    if (jugadorQuePaga.saldo >= montoFinal) {
        RetirarDinero(jugadorQuePaga, montoFinal);
        AgregarDinero(propietario, montoFinal);
        std::cout << jugadorQuePaga.nombre << " pagó $" << montoFinal  << " de alquiler a " << propietario.nombre << " por caer en " << propiedad.nombre << ".\n";
        return;
    }

    // Si no puede pagar, ofrecer venta de propiedades
    std::cout << jugadorQuePaga.nombre << " no tiene suficiente dinero para pagar el alquiler.\n";

    // Recolectar propiedades del jugador
    std::vector<int> indicesPropiedades;
    for (const auto& it : juego.tablero.casillas) {
        if (it.second.propietario == jugadorQuePaga.nombre)
            indicesPropiedades.push_back(it.first);
    }

    if (indicesPropiedades.empty()) {
        std::cout << "No tienes propiedades para vender. Estás en bancarrota.\n";
        jugadorQuePaga.EnBancarrota = true;
        return;
    }

    std::cout << "Tienes las siguientes propiedades:\n";
    for (int idx : indicesPropiedades)
        std::cout << "- " << juego.tablero.casillas[idx].nombre << " (Valor: $"  << juego.tablero.casillas[idx].precio << ")\n";

    std::cout << "Digite el nombre de la propiedad que desea vender: ";
    std::string nombrePropiedad;
    std::cin.ignore();
    std::getline(std::cin, nombrePropiedad);

    bool propiedadVendida = false;
    for (int idx : indicesPropiedades) {
        Casilla& c = juego.tablero.casillas[idx];
        if (c.nombre == nombrePropiedad) {
            VenderPropiedad(jugadorQuePaga, c);
            propiedadVendida = true;
        }
    }

    if (!propiedadVendida) {
        std::cout << "Propiedad no encontrada o nombre inválido.\n";
        return;
    }

    // Intentar pagar nuevamente
    if (jugadorQuePaga.saldo >= montoFinal) {
        RetirarDinero(jugadorQuePaga, montoFinal);
        AgregarDinero(propietario, montoFinal);
        std::cout << jugadorQuePaga.nombre << " vendió una propiedad y pagó $" << montoFinal << " de alquiler a " << propietario.nombre << " por caer en " << propiedad.nombre << ".\n";
    } else {
        std::cout << jugadorQuePaga.nombre << " aún no tiene suficiente dinero para pagar el alquiler. " << "Queda en bancarrota.\n";
        jugadorQuePaga.EnBancarrota = true;
    }
}


// Funciones para sacar carta chance 
void sacarCartaChance(Juego& juego, int indiceJugador){
    Carta carta = ObtenerCartaChance(juego.cartas_chance);
    mostrarCarta(carta);
    AplicarCarta(juego.tablero, juego.jugadores[indiceJugador], carta, juego.jugadores);
    if(carta.accion != "salir_carcel"){ // Si la carta es salir de la carcel, el jugador la conserva
        ColocarAlFinalCartasChance(juego.cartas_chance, carta);
    }
    juego.cartas_chance.cartas_chance.pop();
}
// Funciones para sacar carta comunity
void sacarCartaComunity(Juego& juego, int indiceJugador){
    Carta carta = ObtenerCartaComunity(juego.cartas_comunity);
    mostrarCarta(carta);
    AplicarCarta(juego.tablero, juego.jugadores[indiceJugador], carta, juego.jugadores);
    if(carta.accion != "salir_carcel"){ // Si la carta es salir de la carcel, el jugador la conserva
        ColocarAlFinalCartasComunity(juego.cartas_comunity, carta);
    }
    juego.cartas_comunity.cartas_comunity.pop();
}
//Funcion para guardar el estado actual del juego en el historial
void guardarEstadoHistorial(Juego& juego){
    Historial historial;
    historial.jugadores = juego.jugadores;
    historial.tablero = juego.tablero;
    historial.cartas_chance = juego.cartas_chance;
    historial.cartas_comunity = juego.cartas_comunity;
    historial.turno = juego.turno;
    juego.historial.push(historial);
}

//Funcion para deshacer la ultima accion
void DeshacerUltimaAccion(Juego& juego){
    if(!juego.historial.empty()){
        Historial historial = juego.historial.top();
        juego.jugadores = historial.jugadores;
        juego.tablero = historial.tablero;
        juego.cartas_chance = historial.cartas_chance;
        juego.cartas_comunity = historial.cartas_comunity;
        juego.turno = historial.turno;
        juego.historial.pop();
        std::cout << "La ultima accion ha sido revertida.\n";
    } else {
        std::cout << "[Aviso] No hay acciones para deshacer.\n";
    }
}
//Funcion para pasar el turno
void pasarturno(Juego& juego){
    juego.turno++;
    if(juego.turno >= (int)juego.jugadores.size()){ // Si se pasa del ultimo jugador, vuelve al primero
        juego.turno = 0;
    }
    juego.turno_en_progreso = false;  
    juego.tiradas_consecutivas = 0;
}

// Ejecutar UNA SOLA tirada
void ejecutarTirada(Juego& juego){
    //Verifica si el turno todavia no se acaba para guardar en el historial
    if(!juego.turno_en_progreso){ 
        guardarEstadoHistorial(juego);
        juego.turno_en_progreso = true;
        juego.tiradas_consecutivas = 0; // Reiniciar al inicio del turno
    }
    
    int indiceJugador = juego.turno; 
    Jugador& jugadorActual = juego.jugadores[indiceJugador];
    
    //verificar si esta en bancarrota
    if(jugadorActual.EnBancarrota){ 
        std::cout << "\n" << jugadorActual.nombre << " esta en bancarrota.\n";
        pasarturno(juego);
        juego.turno_en_progreso = false;
        return;
    }
    
    std::cout << "\nPosicion actual: Casilla " << jugadorActual.posicion << "\n";
    std::cout << "Saldo: $" << jugadorActual.saldo << "\n\n";
    
    //Guarda los dados obtenidos
    std::pair<int, int>dados = lanzardados();
    std::cout << jugadorActual.nombre << " lanza: " << dados.first << " + " << dados.second  << " = " << (dados.first + dados.second) << "\n";
    // Devuelve si es par o no 
    bool esDoble = (dados.first == dados.second);
    //Si es doble acualiza dadopar como verdadero para que pueda lanzar otra vez
    if(esDoble){
        juego.tiradas_consecutivas++; 
        std::cout << "DOBLES!\n";
        // Si tiene 3 pares consecutivos va a la carcel
        if(juego.tiradas_consecutivas >= 3){
            std::cout << "Tres dobles seguidos! Vas a la carcel.\n";
            jugadorActual.enCarcel = true;
            jugadorActual.turnosEnCarcel = 0;
            jugadorActual.posicion = 11;
            pasarturno(juego);
            juego.turno_en_progreso = false;
            return;
        }
        
        jugadorActual.DadoPar = true;
        std::cout << "Puedes tirar de nuevo!\n";
        
    } else {
        jugadorActual.DadoPar = false;
        juego.tiradas_consecutivas = 0;
    }

    moverJugador(juego, indiceJugador, dados);

    std::cout << jugadorActual.nombre << " se mueve a la casilla " << jugadorActual.posicion << " (" << juego.tablero.casillas.at(jugadorActual.posicion).nombre << ")\n\n";

    aplicarCasilla(juego, jugadorActual.posicion, indiceJugador);

    if(jugadorActual.EnBancarrota){
        std::cout << "\n" << jugadorActual.nombre << " ha quedado en bancarrota.\n";
        pasarturno(juego);
        juego.turno_en_progreso = false;
        return;
    }

    if(jugadorActual.enCarcel){
        jugadorActual.DadoPar = false;
        pasarturno(juego);
        juego.turno_en_progreso = false;
        return;
    }
    // Si no tiene par el jugador ya termina su turno
    if(!jugadorActual.DadoPar){
        std::cout << "\n========== FIN DEL TURNO ==========\n";
        pasarturno(juego);
        juego.turno_en_progreso = false;
    } else { // de lo contrario sigue tirando
        std::cout << "\n--- Puedes volver a tirar (comando 'Jugar') ---\n";
    }
}
