#ifndef PIEZA_H
#define PIEZA_H

#include <string>

using std::string;

class Pieza{
private:
	int x,y;
	bool Negra, General, viva;
public:
	Pieza();
	Pieza(int,int,bool);
	bool esNegra();
	bool esGeneral();
	bool estaViva();
	void CambiarColor(bool);
	void setViva(bool);
	int getX();
	int getY();
	void setX(int);
	void setY(int);
	bool movimiento(int,int,Pieza**&);
};

#endif
