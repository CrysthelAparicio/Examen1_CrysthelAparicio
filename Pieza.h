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
	bool movimiento(int,int,Pieza**&);
	
	void CambiarColor(bool);
	void setViva(bool);
	void setX(int);
        void setY(int);

	
	int getX();
	int getY();


};

#endif
