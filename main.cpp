#include <string.h>
#include "Pieza.h"
#include <ncurses.h>

using namespace std;

void imprimirTab(Pieza**);
int caracterAEntero(char);
char enteroACaracter(int);
void iniciarMatriz(Pieza**);
int* obtenerTotales(Pieza**);
int main(int argc, char const *argv[]){
	initscr();
	Pieza** matriz = new Pieza*[7];
	start_color();
	iniciarMatriz(matriz);
	init_pair(1,COLOR_WHITE,COLOR_RED);
	init_pair(2,COLOR_WHITE,COLOR_GREEN);
	init_pair(3,COLOR_BLACK,COLOR_RED);
	init_pair(4,COLOR_WHITE,COLOR_BLACK);
	int turno = 0;
	char jugador1[100], jugador2[100];
	do {
		move(20, 60);
		printw("%s%d","Ingrese el nombre del jugador ", turno + 1);
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
		if (!turno) {
			strcpy(jugador1, nombre);
		} else {
			strcpy(jugador2, nombre);
		}
		turno++;
		refresh();
	}while(turno < 2);
	move(20, 60);
	addstr("                               ");
	move(21, 60);
	addstr("                               ");
	turno = 0;
	imprimirTab(matriz);
	do{
		int* totales = obtenerTotales(matriz);
		attrset (COLOR_PAIR(4));
		move(4, 70);
       	addstr("--------JUGADORES--------");
		move(6, 70);
		addstr("                                                   ");
		move(6, 70);
		printw("%s%s%d",jugador1, " (PIEZAS BLANCAS): ", totales[0]);
		move(8, 70);
		addstr("                                                   ");
		move(8, 70);
		printw("%s%s%d",jugador2, " (PIEZAS NEGRAS): ", totales[1]);
		move(25, 70);
		if (totales[0] == 0) {
			printw("%s%s%s", "HA GANADO ", jugador2, " (PIEZAS NEGRAS)");
			getch();
			break;
		} else if (totales[1] == 0) {
			printw("%s%s%s", "HA GANADO ", jugador1, " (PIEZAS BLANCAS)");
			getch();
			break;
		}
		move(23, 70);
		if (turno) {
			printw("%s%s%s", "Es el turno de  ", jugador2, " (PIEZAS NEGRAS)");
		} else {
			printw("%s%s%s", "Es el turno de  ", jugador1, " (PIEZAS BLANCAS)");
		}
		move(25, 70);
		addstr("Ingrese la poscion a mover seguido de la nueva posicion. Ejemplo: f6-e5");
		move(26, 70);
		char input[100];
		int contadorTeclas = 0;
		noecho();
		char caracter = getch();
		while(caracter != '\n'){
			noecho();
			// if(caracter >= 48 && caracter <= 57){
				addch(caracter);
				input[contadorTeclas] = caracter;
				contadorTeclas++;
			// }
			caracter = getch();
		}
		int fila = caracterAEntero(input[0]);
		int nuevaFila = caracterAEntero(input[3]);
		if ((matriz[(int)(input[1] - '0')][fila].esNegra() && !turno) || (!matriz[(int)(input[1] - '0')][fila].esNegra() && turno)) {
			attrset (COLOR_PAIR(3));
			move(24, 70);
	       	addstr("CASILLA ERRONEA");
		} else {
			if (!matriz[(int)(input[1] - '0')][fila].mover(nuevaFila,(int)(input[4] - '0') , matriz)){
				attrset (COLOR_PAIR(3));
				move(24, 70);
		       	addstr("ERROR MOVIMIENTO INVALIDO");
			} else {
				turno = !turno;
				move(24, 70);
				addstr("                                 ");
			}
		}
		imprimirTab(matriz);
		refresh();
	}while(true);
	return 0;
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
int caracterAEntero(char x){
	char letras[9] = "abcdefgh";
	for(int LETRA = 0; LETRA < 8; LETRA++){
		if(letras[LETRA] == x){
			return LETRA;
		}
	} 
	return -1;
}
char enteroACaracter(int numero){
	char letras[9] = "abcdefgh";
	return letras[numero];
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
