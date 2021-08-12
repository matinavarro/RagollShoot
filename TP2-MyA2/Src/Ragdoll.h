#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Actor.h"

using namespace sf;
class Ragdoll
{
public:
	Ragdoll(Vector2f posicion, b2World  & mundo1);
	void Dibujar(RenderWindow& ventana);
	void aplicar_fuerza(Vector2f posicion_m);
	float rad2deg(float radianes);

private:
	RectangleShape* fig_rag[6];
	Actor* act_rag[6];

	b2Body* bdy_rag[6];
	b2BodyDef bdydef_rag[6];
	b2Fixture* fix_rag[6];
	b2FixtureDef fixdef_rag[6];

	//declaro los Resortes
	b2DistanceJoint* jnt_rag[5];
	b2DistanceJointDef jntdef_rag[5];

};

