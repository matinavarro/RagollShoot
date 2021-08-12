#pragma once
#include <SFML/Graphics.hpp>
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <SFML/Audio.hpp>
#include "Box2D\Box2D.h"
#include "Actor.h"
#include "ActorSprite.h"
#include "Ragdoll.h"
#include "ProcesarColision.h"
#include <string>
#include <iostream> 


using namespace sf;
using namespace std;

class Juego
{
private:
	int alto, ancho;
	RenderWindow* ventana1;//ventana
	View *camara1;//camara
	Event *evento1;//evento
	Time* tiempo1;//tiempo 
	Clock *reloj1;//reloj
	Time* _tiempo;//time para controlar visualizacion de carteles informativos
	float fps, tiempoFrame, tiempo2;// Tiempo de frame
	Vector2f moverCamara;//movemos camara
	int cant_rag = 0;//total de ragdolls que permito disparar
	int escena = 0;//controlamos distintos eventos que se muestran en pantalla
	bool gameOver = true;//condicion ganador controlado por booleanos
	bool controlTiempo = false;


	Vector2i mousePos;//posicion del raton
	Vector2f mousePos_Cord;//posicion del raton en coordenadas

	Texture* txFondo;//textura del fondo
	Sprite* spFondo;//sprite del fondo
	Texture* txNube;//textura del obstaculo nube
	Sprite* spNube;//sprite del obstaculo nube
	Texture* txReset;//Textura Boton Reset
	Sprite* spReset;//Sprite Botono Reset
	Texture* txInicio[6];//Textura Boton y carteles de [0]Start , [1]Salir , [2]Titulo juego, [3]ganador, [4]perdedor y [5]perdedor
	Sprite* spInicio[6];//Sprite Boton y carteles de [0]Start , [1]Salir , [2]Titulo juego,[3]ganador, [4]perdedor y [5]perdedor
	Texture* txCaja;//textura del obstaculo caja
	Sprite* spCaja;//sprite del obstaculo caja
	Texture* txBloque;//textura del obstaculo caja
	Sprite* spBloque;//sprite del obstaculo caja
	Texture* txCañon;//textura del obstaculo caja
	Sprite* spCañon;//sprite del obstaculo caja
	Texture* txBcañon;//textura del obstaculo caja
	Sprite* spBcañon;//sprite del obstaculo caja
	Texture* txPiso;//textura del obstaculo caja
	Sprite* spPiso;//sprite del obstaculo caja
	Texture* txMolino;//textura del obstaculo molino
	Sprite* spMolino;//sprite del obstaculo molino
	Texture* txBmolino;//textura del obstaculo base molino
	Sprite* spBmolino;//sprite del obstaculo base molino

	Font fuente;//cargamos fuente
	Text textIngresar;//textos mostrado en pantalla

	Actor* act_suelo;//suelo
	ActorSprite* act_arma;//cañon
	ActorSprite* act_base;//base del cañon
	ActorSprite* act_molino;//cañon
	ActorSprite* act_basemol;//base del cañon
	ActorSprite* act_caja[3];//obstaculo fijo
	ActorSprite* act_caja_m;//obstaculo mobil
	ActorSprite* act_nube[3];//obstaculo nube

	Ragdoll* rag_3[5];

	//Resortes para mouse y cañon
	b2DistanceJoint* jnt_rag;
	b2DistanceJointDef jntdef_rag;

	RectangleShape* fig_suelo;
	RectangleShape* fig_arma;
	RectangleShape* fig_base;
	RectangleShape* fig_caja;
	RectangleShape* fig_caja_m;

	b2World* mundo1;

	//Suelo
	b2Body* bdy_suelo;
	b2BodyDef bdydef_suelo;
	b2Fixture* fix_suelo;
	b2FixtureDef fixdef_suelo;

	//cañon
	b2Body* bdy_arma;
	b2BodyDef bdydef_arma;
	b2Fixture* fix_arma;
	b2FixtureDef fixdef_arma;

	//base del cañon
	b2Body* bdy_base;
	b2BodyDef bdydef_base;
	b2Fixture* fix_base;
	b2FixtureDef fixdef_base;
	
	//obstaculo fijo
	b2Body* bdy_caja[3];
	b2BodyDef bdydef_caja[3];
	b2Fixture* fix_caja[3];
	b2FixtureDef fixdef_caja[3];

	//obstaculo mobil
	b2Body* bdy_caja_m;
	b2BodyDef bdydef_caja_m;
	b2Fixture* fix_caja_m;
	b2FixtureDef fixdef_caja_m;

	//obstaculo nubes
	b2Body* bdy_nube[3];
	b2BodyDef bdydef_nube[3];
	b2Fixture* fix_nube[3];
	b2FixtureDef fixdef_nube[3];

	//bola
	b2Body* bdy_bol;
	b2BodyDef bdydef_bol;
	b2Fixture* fix_bol;
	b2FixtureDef fixdef_bol;

	//base de la bola
	b2Body* bdy_basebol;
	b2BodyDef bdydef_basebol;
	b2Fixture* fix_basebol;
	b2FixtureDef fixdef_basebol;

	//Resortes bola colgante
	b2DistanceJoint* jnt_bol;
	b2DistanceJointDef jntdef_bol;

	//procesador de colisiones
	ProcesarColision* colisionador;
	int* idCaja_m;
	int* idSuelo;

public:
	Juego(Vector2i resolucion, string titulo);
	void set_camera();
	void iniciar_fisica();
	void iniciar_img();
	void IniciaGame();
	float deg2rad(float grados);
	bool colisiona=true;


	void gameLoop();
	void Dibujar();
	void Colision();
	void actualizar_fisica();
	void procesar_eventos();
};