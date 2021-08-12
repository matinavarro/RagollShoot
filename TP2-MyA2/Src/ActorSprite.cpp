#include "ActorSprite.h"

ActorSprite::ActorSprite(b2Body* cuerpo, Sprite* figura) : bdy_actor(cuerpo), fig_actor(figura) { //constructor recibe un cuerpo y un sprite
	posicion = bdy_actor->GetPosition();

	dimensiones.upperBound = b2Vec2(-FLT_MAX, -FLT_MAX);//tomamos las dimensionas mas bajas o negativas del cuerpo
	dimensiones.lowerBound = b2Vec2(FLT_MAX, FLT_MAX);//tomamos las dimensiones mas altas del cuerpo

	//obtenemos dimensiones del fixture
	for (b2Fixture* f = bdy_actor->GetFixtureList(); f; f = f->GetNext()) {
		dimensiones = f->GetAABB(0);//le pasamos el elemento 0 ya que siempre va a leer el primer fixture
	}

	fig_actor->setOrigin(fig_actor->getTexture()->getSize().x / 2.f, fig_actor->getTexture()->getSize().y / 2.f);//tomamos la figura del centro
	fig_actor->setPosition(posicion.x, posicion.y);//seteamos posicion
	fig_actor->setRotation(rad2deg(bdy_actor->GetAngle()));//vemos cada vez que dibujamos en que angulo esta para convertirlo a radianes

	fig_actor->setScale(dimensiones.GetExtents().x *2.5/ fig_actor->getTexture()->getSize().x, dimensiones.GetExtents().y *2.5/ fig_actor->getTexture()->getSize().y);//escalamos dimensiones de la figura
}

//convertimos grados en radianes, ya que SFML usa grados y box2d radianes
float ActorSprite::rad2deg(float radianes) {
	return radianes * 180 / 3.14f;
}

//dibujamos el cuerpo con sprite
void ActorSprite::dibujar(RenderWindow& ventana) {
	posicion = bdy_actor->GetPosition();
	fig_actor->setPosition(posicion.x, posicion.y);
	fig_actor->setRotation(rad2deg(bdy_actor->GetAngle()));//vemos cada vez que dibujamos en que angulo esta para convertirlo a radianes
	ventana.draw(*fig_actor);//dibujamos figura
}