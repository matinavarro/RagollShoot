#include "ProcesarColision.h"

void ProcesarColision::BeginContact(b2Contact* contacto) 
{
	b2Fixture* aux1 = contacto->GetFixtureA();//designamos a un aux ficture el contacto del primero cuerpo a colisionar
	int* cuerpoAData = (int*)aux1->GetBody()->GetUserData().pointer;//obtenemos el dato que identifica el cuerpo
	int cuerpoA = cuerpoAData != nullptr ? *cuerpoAData : 0;
	b2Fixture* aux2 = contacto->GetFixtureB();//designamos a un aux ficture el contacto del segundo cuerpo a colisionar
	int* cuerpoBData = (int*)aux2->GetBody()->GetUserData().pointer;//obtenemos el dato que identifica el cuerpo
	int cuerpoB = cuerpoBData != nullptr ? *cuerpoBData : 0;

// caja movible contra el suelo
if ((cuerpoA == 1 && cuerpoB == 2) || (cuerpoA == 2 && cuerpoB == 1)){ //condicionante para detectar colision
	colisiona = true;//colisiona es igual a verdadero y ejecuta en juego las acciones a realizar
	}

}