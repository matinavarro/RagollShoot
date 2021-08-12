#pragma once
#include <SFML/Graphics.hpp>
#include "box2D/box2D.h"

using namespace sf;
	
class Actor {
public:
	Actor(b2Body* cuerpo, RectangleShape* figura);
	float rad2deg(float radianes);
	void dibujar(RenderWindow &ventana);

private:
	b2Body* bdy_actor;
	RectangleShape * fig_actor;
	b2AABB dimensiones;
	b2Vec2 posicion;

};