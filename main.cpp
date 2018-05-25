#include <string.h>
#include "Pieza.h"
#include <ncurses.h>

using namespace std;

char enteroACaracter(int);
void iniciarMatriz(Pieza**);
int* obtenerTotales(Pieza**);
int caracterAEntero(char);
void imprimirTab(Pieza**);


int main(int argc, char const *argv[]){
	initscr();

	Pieza** matriz = new Pieza*[7];

	start_color();

	iniciarMatriz(matriz);

	init_pair(1,COLOR_WHITE,COLOR_BLUE);
	init_pair(2,COLOR_WHITE,COLOR_YELLOW);
	init_pair(3,COLOR_BLACK,COLOR_RED);
	init_pair(4,COLOR_WHITE,COLOR_BLACK);

	int turnoJugada = 0;
	char jug1[100], jug2[100];
	do {
		move(20, 60);
		printw("%s%d","Ingrese el nombre del jugador ", turnoJugada + 1);
		move(21, 60);
		addstr("                               ");
		move(21, 60);
		char nombre[100];
		int contador = 0;
		noecho();
		char caracterN = getch();
		while(caracterN != '\n'){
			noecho();
				addch(caracterN);
				nombre[contador] = caracterN;
				contador++;
			caracterN = getch();
		}
		if (!turnoJugada) {
			strcpy(jug1, nombre);
		} else {
			strcpy(jug2, nombre);
		}
		turnoJugada++;
		refresh();
	}while(turnoJugada < 2);
	move(20, 60);
	addstr("                               ");
	move(21, 60);
	addstr("                               ");
	turnoJugada = 0;
	imprimirTab(matriz);
	do{
		int* totales = obtenerTotales(matriz);
		attrset (COLOR_PAIR(4));
		move(4, 70);
       	addstr("Lista de los Jugadores a competir: ");
		move(6, 70);
		addstr("                                                   ");
		move(6, 70);
		printw("%s%s%d",jug1, " ->MARINO<-: ", totales[0]);
		move(8, 70);
		addstr("                                                   ");
		move(8, 70);
		printw("%s%s%d",jug2, " ->CORONEL<-: ", totales[1]);
		move(25, 70);
		if (totales[0] == 0) {
			printw("%s%s%s", "Felicidades, ha Ganado ", jug2, " ->CORONEL<-");
			getch();
			break;
		} else if (totales[1] == 0) {
			printw("%s%s%s", "Felicidades, ha Ganado ", jug1, " ->MARINO<-");
			getch();
			break;
		}
		move(23, 70);
		if (turnoJugada) {
			printw("%s%s%s", "Es el turno de  ", jug2, " ->CORONEL<-");
		} else {
			printw("%s%s%s", "Es el turno de  ", jug1, " ->MARINO<-");
		}
		move(25, 70);
                addstr("Ingrese la posicion que movera seguido de la nueva posicion, por ejemplo: f6-e5");
		move(26, 70);
		char input[100];
		int contadorTeclas = 0;
		noecho();
		char caracter = getch();
		while(caracter != '\n'){
			noecho();
				addch(caracter);
				input[contadorTeclas] = caracter;
				contadorTeclas++;
			caracter = getch();
		}
		int fila = caracterAEntero(input[0]);
		int nuevaFila = caracterAEntero(input[3]);
		if ((matriz[(int)(input[1] - '0')][fila].esNegra() && !turnoJugada) || (!matriz[(int)(input[1] - '0')][fila].esNegra() && turnoJugada)) {
			attrset (COLOR_PAIR(3));
			move(24, 70);
	       	addstr("No te puedes ir a esa casilla!!!!");
		} else {
			if (!matriz[(int)(input[1] - '0')][fila].movimiento(nuevaFila,(int)(input[4] - '0') , matriz)){
				attrset (COLOR_PAIR(3));
				move(24, 70);
		       	addstr("Movimiento NO valido, intenta de nuevo!");
			} else {
				turnoJugada = !turnoJugada; move(24, 70); addstr("                                 ");
			}
		}
		imprimirTab(matriz);
		refresh();
	}while(true);
	return 0;
}

void iniciarMatriz(Pieza** matriz){
        for(int FILA = 0; FILA < 8; FILA++){
                matriz[FILA] = new Pieza[8];
                for(int COLUMNA = 0; COLUMNA < 8; COLUMNA++){
                        if(FILA < 3 || FILA > 4){
                                if((COLUMNA + FILA) % 2 == 0){
                                        matriz[FILA][COLUMNA] = Pieza(COLUMNA, FILA, FILA < 3 ? 0 : 1);
                                }else{
                                        matriz[FILA][COLUMNA] = Pieza();
                                }
                        }else{
                                matriz[FILA][COLUMNA] = Pieza();
                        }
                }
        }

}

void imprimirTab(Pieza** matriz){
	for(int FILA = 0; FILA < 8; FILA++){
		for(int COLUMNA = 0; COLUMNA < 8; COLUMNA++){
			int x = COLUMNA * 5;
			if (FILA == 0) {
				move(FILA * 5, COLUMNA * 7 + 7);
				printw("%c",enteroACaracter(COLUMNA));
			}
			for(int i = 0; i < 5; i++){
				move(FILA * 5 + i + 2, COLUMNA * 7 + 5);
				if((COLUMNA + FILA) % 2 == 0){
					attrset (COLOR_PAIR(1));
				}else{
					attrset (COLOR_PAIR(2));
				}
				if(matriz[FILA][COLUMNA].estaViva()){
					if(matriz[FILA][COLUMNA].esNegra()){
						attrset (COLOR_PAIR(3));
					}
					printw(" ***** ");
				}else{					
					printw("       ");
				}
			}
		}
		move(FILA * 5 + 4, 2);
		printw("%d",FILA);
	}
		move(10, 70);
}

int* obtenerTotales(Pieza** piezas) {
	int* totales = new int[2];
	totales[0] = 0;
	totales[1] = 0;
	for(int FILA = 0; FILA < 8; FILA++)
		for(int COLUMNA = 0; COLUMNA < 8; COLUMNA++){
			if (piezas[FILA][COLUMNA].estaViva()) {
				if (piezas[FILA][COLUMNA].esNegra()) {
					totales[1]++;
				} else {
					totales[0]++;
				}
			}
		}
	return totales;
}


int caracterAEntero(char x){
        char abc[9] = "abcdefgh";
        for(int LETRA = 0; LETRA < 8; LETRA++){
                if(abc[LETRA] == x){
                        return LETRA;
                }
        }
        return -1;
}
char enteroACaracter(int numero){
        char abc[9] = "abcdefgh";
        return abc[numero];
}

