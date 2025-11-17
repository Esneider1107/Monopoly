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
    juego.aplicarcasilla_despues_carta = false;
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

//Aplicar la casilla en la que cayo el jugador
void aplicarCasilla(Juego& juego, int posicion, int indiceJugador){
    //Propiedad
    if(juego.tablero.casillas.at(posicion).funcion == "propiedad"){
        std::cout << "Ha caido en la propiedad: " << juego.tablero.casillas.at(posicion).nombre << std::endl;
        if(juego.tablero.casillas.at(posicion).propietario.empty()){
            mostrarCasilla(juego.tablero.casillas.at(posicion));// Muestro la casilla y si no tiene propietario sale el mensaje de quue se puede comprar
            std::string comando;
            std::cin >> comando;
            if(comando == "comprar" || comando == "Comprar"){
                ComprarPropiedad(juego.jugadores[indiceJugador], juego.tablero.casillas.at(posicion));
                std::cout << "Ha comprado la propiedad: " << juego.tablero.casillas.at(posicion).nombre << std::endl;
            } else {
                std::cout << "No ha comprado nada" << std::endl;
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
        std::cout << "Ha caido en Go to Jail. Vas a la carcel" << std::endl;
        juego.jugadores[indiceJugador].enCarcel = true;
        juego.jugadores[indiceJugador].turnosEnCarcel = 3;
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
    //Verificar si es del propietario
    if (propiedad.propietario.empty()) {
            std::cout << "Esta casilla no tiene dueño " << propietario.nombre << ".\n";
            return;
        }
    int montoBase = 0;
    int nivel = 0;
    if(propiedad.hipotecada){
        std::cout << "La propiedad esta hipotecada asi que no tiene que pagar.\n";
        return;
    }

    //Logica para las utilidades (servicios)
    if(propiedad.funcion == "utilidad"){
        int contador_utilidades = 0;
        for (const auto& it : juego.tablero.casillas) {
            if (it.second.funcion == "utilidad" && it.second.propietario == propietario.nombre) {
                contador_utilidades++;
            }
        }
        if (jugadorQuePaga.multiplicador_alquiler == 1){
            int tirada = juego.ultimoValorDados; 
            if (contador_utilidades == 1) {
                montoBase = 4 * tirada;  // 4x el valor de los dados
            } else if (contador_utilidades >= 2) {
                montoBase = 10 * tirada; // 10x el valor de los dados
            }
            std::cout << "Utilidad: " << propiedad.nombre << "\n";
            std::cout << "Propietario tiene " << contador_utilidades << " utilidad(es)\n";
            std::cout << "Multiplicador: " << (contador_utilidades == 1 ? "4x" : "10x") << " dados\n";
            std::cout << "Dados: " << tirada << "  Alquiler: $" << montoBase << "\n";
        }
    }
    
    //Logica para las estaciones
    else if(propiedad.funcion == "estacion"){
        int contador_estaciones = 0; // contador de las estaciones del propietario
        for(const auto& it : juego.tablero.casillas){ // Itera sobre las casillas
            if(it.second.funcion == "estacion" && it.second.propietario == propietario.nombre){ // Busca si tiene estaciones
                contador_estaciones++; 
            }
        }
        nivel = contador_estaciones;
        if (propiedad.alquiler.find(nivel) != propiedad.alquiler.end()) { // Si find no encuentra nivel va a devolver end
            montoBase = propiedad.alquiler[nivel];
        } else {
            std::cout << "No se encontro un valor de alquiler para este nivel de estacion.\n";
            return;
        }
        std::cout << "Estacion: " << propiedad.nombre << "\n";
        std::cout << "Propietario tiene " << contador_estaciones << " estacion(es)\n";
        std::cout << "Alquiler base: $" << montoBase << "\n";
    }
    
    //Logica propiedades normales
    else if(propiedad.funcion == "propiedad"){
        nivel = propiedad.nivel_propiedad;
        if (propiedad.alquiler.find(nivel) != propiedad.alquiler.end()) { // Si find no encuentra nivel va a devolver end
            montoBase = propiedad.alquiler[nivel];
        } else {
            std::cout << "No se encontro un valor de alquiler para este nivel.\n";
            return;
        }
        std::cout << "Propiedad: " << propiedad.nombre << " [" << propiedad.color << "]\n";
        if (nivel == 0) {
            std::cout << "Sin construcciones\n";
        } else if (nivel <= 4) {
            std::cout << "Con " << nivel << " casa(s)\n";
        } else {
            std::cout << "Con hotel\n";
        }
        std::cout << "Alquiler base: $" << montoBase << "\n";
    }

    // Aplicar multiplicadores (por ventaja o color)
    int multiplicador = 1;
    if (jugadorQuePaga.multiplicador_alquiler > 1) {
        multiplicador = jugadorQuePaga.multiplicador_alquiler;
        jugadorQuePaga.multiplicador_alquiler = 1;
    } else if (!propiedad.color.empty() && propiedad.funcion == "propiedad" && nivel == 0) {  // Tiene que ser propiedad y no puede tener casas
        int total_color = 0, total_propietario = 0;
        for (const auto& c : juego.tablero.casillas) {
            if (c.second.color == propiedad.color && c.second.funcion == "propiedad") { // Si es del mismo color y propiedad
                total_color++;
                if (c.second.propietario == propietario.nombre) // Si es del mismo propietario
                    total_propietario++;
            }
        }
        if (total_color > 0 && total_color == total_propietario) // Si es tiene todas del mismo color
            multiplicador = 2;
    }

    int montoFinal = montoBase * multiplicador;
    std::cout << "Monto final a pagar: $" << montoFinal << "\n\n";

// Verificar si el jugador puede pagar
if (jugadorQuePaga.saldo >= montoFinal) {
    RetirarDinero(jugadorQuePaga, montoFinal);
    AgregarDinero(propietario, montoFinal);
    std::cout << jugadorQuePaga.nombre << " pago $" << montoFinal << " de alquiler a " << propietario.nombre << ".\n";
    return;
}

std::cout << "\n" << jugadorQuePaga.nombre << " no tiene suficiente dinero ($" << jugadorQuePaga.saldo << " de $" << montoFinal << ").\n";

// Recolectar propiedades del jugador
std::vector<int> indicesPropiedades; 
for (const auto& it : juego.tablero.casillas) { // Recorre las propiedades
    if (it.second.propietario == jugadorQuePaga.nombre) // Si es del jugador
        indicesPropiedades.push_back(it.first); 
}

if (indicesPropiedades.empty()) {
    std::cout << "No tienes propiedades. Estas en bancarrota.\n";
    jugadorQuePaga.EnBancarrota = true;
    return;
}

// Mostrar opciones
std::cout << "\nTus propiedades:\n";
for (int idx : indicesPropiedades) { // Recorre las propiedades
    Casilla& c = juego.tablero.casillas[idx];
    std::cout << "- " << c.nombre;
    
    if (c.nivel_propiedad == 5) {
        std::cout << " [Hotel] (Venta: $" << c.precio_hotel / 2 << ")";
    } else if (c.nivel_propiedad > 0) {
        std::cout << " [" << c.nivel_propiedad << " casa(s)] (Venta casa: $" << c.precio_casa / 2 << ")";
    } else {
        std::cout << " [Sin construcciones] (Venta: $" << c.precio / 2 << ")";
    }
    std::cout << "\n";
}

std::cout << "\n¿Que deseas vender?\n";
std::cout << "1) Hotel\n";
std::cout << "2) Casa\n";
std::cout << "3) Hipotecar\n";
std::cout << "Opcion: ";

//Pide la opcion que va a elegir
std::string opcion;
std::cin >> opcion;
std::getline(std::cin, opcion);
//Pide el nombre de la propiedad
std::cout << "Nombre de la propiedad: ";
std::string nombrePropiedad;
std::getline(std::cin, nombrePropiedad);

// Buscar la propiedad
Casilla* propiedadSeleccionada = nullptr;
int posPropiedad = 0;

for(auto& it : juego.tablero.casillas){ //itera en las casillas
    if(it.second.nombre == nombrePropiedad && it.second.propietario == jugadorQuePaga.nombre){ // busca la propiedad con el nombre y q sea del propietario
        propiedadSeleccionada = &it.second;
        posPropiedad = it.first;
        break;
    }
}

if(propiedadSeleccionada == nullptr){
    std::cout << "No se encontro la propiedad o no es tuya.\n";
    // Reintentar
    cobrarAlquiler(juego, indiceJugadorPropietario, indiceJugadorQPaga, pos);
    return;
}

bool ventaExitosa = false;
bool hipotecaExitosa = false;


//  VENDER HOTEL
if(opcion == "Hotel" || opcion == "hotel"){
    if(propiedadSeleccionada->nivel_propiedad != 5){ 
        std::cout << "Esta propiedad no tiene hotel.\n";
    } else {
        // Verificar venta pareja: debes vender de las propiedades con MaS construcciones
        std::vector<Casilla*> propiedadesMismoColor;
        for(auto& it : juego.tablero.casillas){ //itera en las casillas
            if(it.second.color == propiedadSeleccionada->color &&  it.second.funcion == "propiedad"){ // Busca las propeidades del mismo color
                propiedadesMismoColor.push_back(&it.second);
            }
        }
        
        // Encontrar el nivel maximo en el grupo
        int nivelMaximo = 0;
        for(auto* prop : propiedadesMismoColor){ //  Itera en las propiedades del jugador del mismo color
            if(prop->nivel_propiedad > nivelMaximo){
                nivelMaximo = prop->nivel_propiedad; // Escoge la que mas casas tenga
            }
        }
        
        // Solo puedes vender si esta propiedad tiene el nivel maximo
        if(propiedadSeleccionada->nivel_propiedad < nivelMaximo){
            std::cout << "Debes vender parejo. Vende primero de las propiedades con mas construcciones:\n";
            for(auto* prop : propiedadesMismoColor){ // Itera en las propiedades del jugador del mismo color
                if(prop->nivel_propiedad == nivelMaximo){ 
                    std::cout << "  - " << prop->nombre << ": " << prop->nivel_propiedad << (prop->nivel_propiedad == 5 ? " (hotel)" : " casa(s)") << "\n"; // Imprime las propiedades
                }
            }
        } else {
            ventaExitosa = VenderHotel(jugadorQuePaga, *propiedadSeleccionada);
        }
    }
}

// VENDER CASA 
else if(opcion == "Casa" || opcion == "casa"){
    if(propiedadSeleccionada->nivel_propiedad == 0){ // Verifica si tiene casas
        std::cout << "Esta propiedad no tiene casas.\n";
    } else if(propiedadSeleccionada->nivel_propiedad == 5){
        std::cout << "Debes vender el hotel primero (opcion 1).\n"; // Verifica si tiene hotel
    } else {
        // Verificar venta pareja
        std::vector<Casilla*> propiedadesMismoColor;
        for(auto& it : juego.tablero.casillas){
            if(it.second.color == propiedadSeleccionada->color && it.second.funcion == "propiedad"){  // Escoge las propiedades del mismo color 
                propiedadesMismoColor.push_back(&it.second);
            }
        }
        
        int nivelMaximo = 0;
        //Escoge el nivel maximo de las propieades (# casas)
        for(auto* prop : propiedadesMismoColor){
            if(prop->nivel_propiedad > nivelMaximo){
                nivelMaximo = prop->nivel_propiedad;
            }
        }
        
        if(propiedadSeleccionada->nivel_propiedad < nivelMaximo){
            std::cout << "Debes vender parejo. Vende primero de las propiedades con mas construcciones:\n";
            for(auto* prop : propiedadesMismoColor){
                if(prop->nivel_propiedad == nivelMaximo){
                    std::cout << "  - " << prop->nombre << ": " << prop->nivel_propiedad << (prop->nivel_propiedad == 5 ? " (hotel)" : " casa(s)") << "\n";
                }
            }
        } else {
            ventaExitosa = VenderCasa(jugadorQuePaga, *propiedadSeleccionada);
        }
    }
}

//  VENDER PROPIEDAD COMPLETA 
else if(opcion == "Hipotecar" || opcion == "hipotecar"){
    if(propiedadSeleccionada->nivel_propiedad > 0){
        std::cout << "Debes vender todas las construcciones antes de vender la propiedad.\n";
    } else {
        hipotecaExitosa = HipotecarPropiedad(jugadorQuePaga, *propiedadSeleccionada);
        if(hipotecaExitosa){
            std::cout << "Has Hipotecado la propiedad" << propiedadSeleccionada->nombre << " por $" << propiedadSeleccionada->precio / 2 << "\n";
        }
    }
}

if(!ventaExitosa || !hipotecaExitosa){
    std::cout << "No se pudo completar la venta. Intenta de nuevo.\n";
    cobrarAlquiler(juego, indiceJugadorPropietario, indiceJugadorQPaga, pos);
    return;
}

// VERIFICAR SI AHORA PUEDE PAGAR
std::cout << "\nSaldo actual: $" << jugadorQuePaga.saldo << "\n";

if (jugadorQuePaga.saldo >= montoFinal) {
    RetirarDinero(jugadorQuePaga, montoFinal);
    AgregarDinero(propietario, montoFinal);
    std::cout << jugadorQuePaga.nombre << " pago $" << montoFinal << " de alquiler a " << propietario.nombre << ".\n";
} else {
    std::cout << "Aun necesitas $" << (montoFinal - jugadorQuePaga.saldo) << " mas.\n";
    std::cout << "¿Vender algo mas? (s/n): ";
    char respuesta;
    std::cin >> respuesta;
    if (respuesta == 's' || respuesta == 'S') {
        cobrarAlquiler(juego, indiceJugadorPropietario, indiceJugadorQPaga, pos);
    } else {
        std::cout << jugadorQuePaga.nombre << " queda en bancarrota.\n";
        jugadorQuePaga.EnBancarrota = true;
    }
}
}

// Funciones para sacar carta chance 
void sacarCartaChance(Juego& juego, int indiceJugador){
    Carta carta = ObtenerCartaChance(juego.cartas_chance);
    juego.cartas_chance.cartas_chance.pop();
    mostrarCarta(carta);
    AplicarCarta(juego.tablero, juego.jugadores[indiceJugador], carta, juego.jugadores);
    if(carta.accion != "salir_carcel"){ // Si la carta es salir de la carcel, el jugador la conserva
        ColocarAlFinalCartasChance(juego.cartas_chance, carta);
    }
    if(carta.accion == "mover_casilla" || carta.accion == "mover_estacion" || carta.accion == "mover_servicio"){
        juego.aplicarcasilla_despues_carta = true;
    }
}
// Funciones para sacar carta comunity
void sacarCartaComunity(Juego& juego, int indiceJugador){
    Carta carta = ObtenerCartaComunity(juego.cartas_comunity);
    juego.cartas_comunity.cartas_comunity.pop();
    mostrarCarta(carta);
    AplicarCarta(juego.tablero, juego.jugadores[indiceJugador], carta, juego.jugadores);
    if(carta.accion != "salir_carcel"){ // Si la carta es salir de la carcel, el jugador la conserva
        ColocarAlFinalCartasComunity(juego.cartas_comunity, carta);
    }
    if(carta.accion == "mover_casilla" || carta.accion == "mover_estacion" || carta.accion == "mover_servicio"){
        juego.aplicarcasilla_despues_carta = true;
    }
}
//Funcion para guardar el estado actual del juego en el historial
void guardarEstadoHistorial(Juego& juego){
    Historial historial;
    historial.jugadores = juego.jugadores;
    historial.tablero = juego.tablero;
    historial.cartas_chance = juego.cartas_chance;
    historial.cartas_comunity = juego.cartas_comunity;
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
    if(jugadorActual.enCarcel && jugadorActual.turnosEnCarcel > 0){
        // Tiene carta para salir de la carcel
        if(jugadorActual.tiene_salir_carcel){
            std::cout << jugadorActual.nombre << " usa la carta para salir de la carcel.\n";
            jugadorActual.enCarcel = false;
            jugadorActual.turnosEnCarcel = 0;
            jugadorActual.tiene_salir_carcel = false;
        }
        else {
            // Esta en carcel y debe decidir si paga o no
            std::cout << jugadorActual.nombre << " esta en la carcel.\n";
            std::cout << "Escriba 'salir' para pagar 50 y salir, o 'x' para saltar el turno.\n";
            std::string comando;
            std::cin >> comando;
            if(comando == "salir"){
                if(jugadorActual.saldo >= 50){
                    jugadorActual.enCarcel = false;
                    jugadorActual.turnosEnCarcel = 0;
                    RetirarDinero(jugadorActual, 50);
                    std::cout << jugadorActual.nombre << " ha salido de la carcel.\n";
                } else {
                    std::cout << "No tienes suficiente dinero para pagar.\n";
                }
            } 
            // De cualquier forma, si esta en carcel sigue sin tirar
            if(jugadorActual.enCarcel && jugadorActual.turnosEnCarcel > 0){
                jugadorActual.turnosEnCarcel--;
                std::cout << "Turnos restantes en carcel: " << jugadorActual.turnosEnCarcel << "\n";
                pasarturno(juego);
                juego.turno_en_progreso = false;
                if(jugadorActual.turnosEnCarcel == 0){
                    jugadorActual.enCarcel = false;
                    jugadorActual.turnosEnCarcel = 0;
                    RetirarDinero(jugadorActual, 50);
                    std::cout << jugadorActual.nombre << " ha salido de la carcel y le toco pagar 50.\n";
                }
                return;
            }
        }
    }
    //Guarda los dados obtenidos
    std::pair<int, int>dados = lanzardados();
    juego.ultimoValorDados = dados.first + dados.second;
    std::cout << jugadorActual.nombre << " lanza: " << dados.first << " + " << dados.second  << " = " << (dados.first + dados.second) << "\n";
    // Devuelve si es par o no 
    bool esDoble = (dados.first == dados.second);
    //Si es doble acualiza dadopar como verdadero para que pueda lanzar otra vez
    if(esDoble && !jugadorActual.enCarcel){
        juego.tiradas_consecutivas++; 
        std::cout << "DOBLES\n";
        // Si tiene 3 pares consecutivos va a la carcel
        if(juego.tiradas_consecutivas >= 3){
            std::cout << "Tres dobles seguidos Vas a la carcel.\n";
            jugadorActual.enCarcel = true;
            jugadorActual.turnosEnCarcel = 3;
            jugadorActual.posicion = 11;
            pasarturno(juego);
            juego.turno_en_progreso = false;
            return;
        } else if(juego.tiradas_consecutivas == 2 && jugadorActual.enCarcel == true){
            std::cout << "Dos dobles seguidos Sales de la carcel.\n";
            jugadorActual.enCarcel = false;
            jugadorActual.turnosEnCarcel = 0;
            pasarturno(juego);
            juego.turno_en_progreso = false;
            return;
        }
        
        jugadorActual.DadoPar = true;
        std::cout << "Puedes tirar de nuevo\n";
        
    } else {
        jugadorActual.DadoPar = false;
        juego.tiradas_consecutivas = 0;
    }

    moverJugador(juego, indiceJugador, dados);

    std::cout << jugadorActual.nombre << " se mueve a la casilla " << jugadorActual.posicion << " (" << juego.tablero.casillas.at(jugadorActual.posicion).nombre << ")\n\n";

    aplicarCasilla(juego, jugadorActual.posicion, indiceJugador);

    if(juego.aplicarcasilla_despues_carta){
        aplicarCasilla(juego, jugadorActual.posicion, indiceJugador);
        juego.aplicarcasilla_despues_carta = false;
    }

    if(jugadorActual.EnBancarrota){
        std::cout << "\n" << jugadorActual.nombre << " ha quedado en bancarrota.\n";
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

void comprar_casa(Juego& juego, int indiceJugador){
    mostrarInfoJugador(juego.tablero, juego.jugadores[juego.turno]);
    std::cout << "Ingrese el nombre de la propiedad donde desea comprar una casa: \n";
    std::string nombrePropiedad;
    std::cin.ignore();
    std::getline(std::cin, nombrePropiedad);
    Casilla* propiedad_selecionada = nullptr;
    int posicionPropiedad = 0;
    for(auto& it : juego.tablero.casillas){
        if(it.second.nombre == nombrePropiedad){
            propiedad_selecionada = &it.second;
            posicionPropiedad = it.first;
        }
    }
    if(propiedad_selecionada == nullptr){
        std::cout << "No se encontro la propiedad: " << nombrePropiedad << "\n";
        return;
    }
    if(propiedad_selecionada->funcion != "propiedad"){
        std::cout << "No puedes construir casas en estaciones o utilidades.\n";
        return;
    }
    if(propiedad_selecionada->hipotecada){
        std::cout << "La propiedad esta hipotecada.\n";
        return;
    }
    std::vector<Casilla*> propiedadesMismoColor;
    for(auto& it : juego.tablero.casillas){
        if(it.second.color == propiedad_selecionada->color && it.second.funcion == "propiedad"){
            propiedadesMismoColor.push_back(&it.second);
        }
    }

    bool tieneMonopolio = true;
    for(auto* prop : propiedadesMismoColor){
        if(prop->propietario != juego.jugadores[indiceJugador].nombre){
            tieneMonopolio = false;
        }
    }
    if(!tieneMonopolio){
        std::cout << "Necesitas tener todas las propiedades del color "  << propiedad_selecionada->color << " para construir.\n";
        return;
    }
    int nivelMinimo = propiedad_selecionada->nivel_propiedad;
    for(auto* prop : propiedadesMismoColor){
        if(prop->nivel_propiedad < nivelMinimo){
            nivelMinimo = prop->nivel_propiedad;
        }
    }
    if(propiedad_selecionada->nivel_propiedad > nivelMinimo){
        std::cout << "No puedes construir aqui. Debes construir parejo.\n";
        std::cout << "Propiedades del color " << propiedad_selecionada->color << ":\n";
        for(auto* prop : propiedadesMismoColor){
            std::cout << "  - " << prop->nombre << ": " << prop->nivel_propiedad << " casa(s)\n";
        }
        std::cout << "Construye primero en las propiedades con menos casas.\n";
        return;
    }
    ComprarCasa(juego.jugadores[indiceJugador], *propiedad_selecionada);
    std::cout << "\n¡Casa comprada exitosamente\n";
    std::cout << "Propiedad: " << propiedad_selecionada->nombre << "\n";
    std::cout << "Nivel actual: " << propiedad_selecionada->nivel_propiedad << " casa(s)\n";
    std::cout << "Costo: $" << propiedad_selecionada->precio_casa << "\n";
    std::cout << "Saldo restante: $" << juego.jugadores[indiceJugador].saldo << "\n";
    
}

void comprar_hotel(Juego& juego, int indiceJugador){
    mostrarInfoJugador(juego.tablero, juego.jugadores[juego.turno]);
    std::cout << "Ingrese el nombre de la propiedad donde desea comprar el hotel: \n";
    std::string nombrePropiedad;
    std::cin.ignore();
    std::getline(std::cin, nombrePropiedad);
    Casilla* propiedadSeleccionada = nullptr;
    
    for(auto& it : juego.tablero.casillas){
        if(it.second.nombre == nombrePropiedad){
            propiedadSeleccionada = &it.second;
        }
    }
    if(propiedadSeleccionada == nullptr){
        std::cout << "No se encontro la propiedad: " << nombrePropiedad << "\n";
        return;
    }
    
    if(propiedadSeleccionada->funcion != "propiedad"){
        std::cout << "No puedes construir hoteles en estaciones o utilidades.\n";
        return;
    }
    if(propiedadSeleccionada->hipotecada){
        std::cout << "La propiedad esta hipotecada.\n";
        return;
    }
    // Verificar monopolio y construccion pareja
    std::vector<Casilla*> propiedadesMismoColor;
    for(auto& it : juego.tablero.casillas){
        if(it.second.color == propiedadSeleccionada->color && it.second.funcion == "propiedad"){
            propiedadesMismoColor.push_back(&it.second);
        }
    }

    // Todas las propiedades del color deben tener 4 casas o un hotel
    for(auto* prop : propiedadesMismoColor){
        if(prop->nivel_propiedad < 4){
            std::cout << "Todas las propiedades del color " << propiedadSeleccionada->color  << " deben tener 4 casas antes de comprar hoteles.\n";
            return;
        }
    }
    ComprarHotel(juego.jugadores[indiceJugador], *propiedadSeleccionada);
    std::cout << "\n¡Hotel comprado exitosamente\n";
    std::cout << "Propiedad: " << propiedadSeleccionada->nombre << "\n";
    std::cout << "Costo: $" << propiedadSeleccionada->precio_hotel << "\n";
    std::cout << "Saldo restante: $" << juego.jugadores[indiceJugador].saldo << "\n";
}

void hipotecar_propiedad(Juego& juego, int indiceJugador){
    std::cout << "Tus propiedades que puedes hipotecar:\n";
    for(auto& it : juego.tablero.casillas){
        if(it.second.propietario == juego.jugadores[indiceJugador].nombre && !it.second.hipotecada){
            std::cout << it.second.nombre << "\n";
        }
    }
    std::cout << "Ingrese el nombre de la propiedad que desea hipotecar: \n";
    std::string nombrePropiedad;
    std::cin.ignore();
    std::getline(std::cin, nombrePropiedad);
    Casilla* propiedad_selecionada = nullptr;
    int posicionPropiedad = 0;
    for(auto& it : juego.tablero.casillas){
        if(it.second.nombre == nombrePropiedad){
            propiedad_selecionada = &it.second;
            posicionPropiedad = it.first;
        }
    }
    if(propiedad_selecionada == nullptr){
        std::cout << "No se encontro la propiedad: " << nombrePropiedad << "\n";
        return;
    }
    if(propiedad_selecionada->nivel_propiedad > 0){
        std::cout << "Debes vender todas las construcciones antes de hipotecar la propiedad.\n";
        return;
    }
    if(propiedad_selecionada->propietario != juego.jugadores[indiceJugador].nombre){
        std::cout << "No eres el propietario.\n";
        return;
    }
    if(propiedad_selecionada->hipotecada){
        std::cout << "La propiedad ya esta hipotecada.\n";
        return;
    }
    HipotecarPropiedad(juego.jugadores[indiceJugador], *propiedad_selecionada);
    std::cout << "\nPropiedad hipotecada exitosamente\n";
}

void deshipotecar_propiedad(Juego& juego, int indiceJugador){
    std::cout << "Tus propiedades que puedes hipotecar:\n";
    for(auto& it : juego.tablero.casillas){
        if(it.second.hipotecada && it.second.propietario == juego.jugadores[indiceJugador].nombre){
            std::cout << it.second.nombre << "\n";
        }
    }
    std::cout << "Ingrese el nombre de la propiedad que desea deshipotecar: \n";
    std::string nombrePropiedad;
    std::cin.ignore();
    std::getline(std::cin, nombrePropiedad);
    Casilla* propiedad_selecionada = nullptr;
    int posicionPropiedad = 0;
    for(auto& it : juego.tablero.casillas){
        if(it.second.nombre == nombrePropiedad){
            propiedad_selecionada = &it.second;
            posicionPropiedad = it.first;
        }
    }
    if(propiedad_selecionada == nullptr){
        std::cout << "No se encontro la propiedad: " << nombrePropiedad << "\n";
        return;
    }
    if(!propiedad_selecionada->hipotecada){
        std::cout << "La propiedad no esta hipotecada.\n";
        return;
    }
    if(propiedad_selecionada->propietario != juego.jugadores[indiceJugador].nombre){
        std::cout << "No eres el propietario.\n";
        return;
    }
    deshipotecarPropiedad(juego.jugadores[indiceJugador], *propiedad_selecionada);
    std::cout << "\nPropiedad deshipotecada exitosamente\n";
}