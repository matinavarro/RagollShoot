#include "Actor.h"

Actor::Actor(b2Body* cuerpo, RectangleShape* figura) : bdy_actor(cuerpo), fig_actor(figura) {

	posicion = bdy_actor->GetPosition();
	dimensiones.upperBound = b2Vec2(-FLT_MAX, -FLT_MAX);//tomamos las dimensionas mas bajas o negativas del cuerpo
	dimensiones.lowerBound = b2Vec2(FLT_MAX, FLT_MAX);//tomamos las dimensiones mas altas del cuerpo

	//obtenemos dimensiones del fixture
	for (b2Fixture* f = bdy_actor->GetFixtureList(); f; f = f->GetNext()) {
		dimensiones = f->GetAABB(0);//le pasamos el elemento 0 ya que siempre va a leer el primer fixture
	}
	fig_actor->setSize({ dimensiones.GetExtents().x * 2, dimensiones.GetExtents().y * 2 });//seteamos las dimensiones de la figura 
	fig_actor->setOrigin(fig_actor->getSize().x / 2.f, fig_actor->	getSize().y / 2.f);
	fig_actor->setPosition(posicion.x, posicion.y);//seteamos posicion
	fig_actor->setRotation(rad2deg(bdy_actor->GetAngle()));

}
//convertimos grados en radianes, ya que SFML usa grados y box2d radianes
float Actor::rad2deg(float radianes){
	return radianes * 180 / 3.14f;
}

//funcion para dibujar
void Actor::dibujar(RenderWindow &ventana){
	posicion = bdy_actor->GetPosition();
	fig_actor->setPosition(posicion.x, posicion.y);
	fig_actor->setRotation(rad2deg(bdy_actor->GetAngle()));//vemos cada vez que dibujamos en que angulo esta para convertirlo a radianes
	ventana.draw(*fig_actor);
}
