#pragma once
#include <SFML/Graphics.hpp>
#include "box2D/box2D.h"
#include "Actor.h"

class ProcesarColision:public b2ContactListener
{
public:
	void BeginContact(b2Contact* contacto);
	bool colisiona = false;
};

