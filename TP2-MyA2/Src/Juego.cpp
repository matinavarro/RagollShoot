#include "Juego.h"
#include "Actor.h"
#include "Ragdoll.h"
#include "ProcesarColision.h"

Juego::Juego(Vector2i resolucion, std::string titulo){
	//configuro los fps del juego
	fps = 60;
	tiempoFrame = 1.0f / fps;

	ventana1 = new RenderWindow(VideoMode(resolucion.x, resolucion.y), titulo);
	ventana1->setFramerateLimit(fps);

	ventana1->setVisible(true);
	
	evento1 = new Event;
	reloj1 = new Clock;
	tiempo1 = new Time;
	_tiempo = new Time;

	//configuro fuente para poder mostrar mensajes
	fuente.loadFromFile("../Src/Minecraft.ttf");
	textIngresar.setFont(fuente);
	textIngresar.setCharacterSize(26);
	textIngresar.setFillColor(Color::Yellow);
	textIngresar.setScale(0.02f, 0.02f);

	IniciaGame();
}

void Juego::IniciaGame() {//iniciamos juego
	iniciar_fisica();
	iniciar_img();
	set_camera();
	//elementos del mundo
	act_suelo = new Actor(bdy_suelo, fig_suelo);
	act_arma = new ActorSprite(bdy_arma, spCañon);
	act_base = new ActorSprite(bdy_base, spBcañon);
	act_molino = new ActorSprite(bdy_bol, spMolino);
	act_basemol = new ActorSprite(bdy_basebol, spBmolino);
	for (int i = 0; i < 3; i++) {
		act_caja[i] = new ActorSprite(bdy_caja[i], spBloque);
	}
	act_caja_m = new ActorSprite(bdy_caja_m, spCaja);
	for (int i = 0; i < 3; i++) {
		act_nube[i] = new ActorSprite(bdy_nube[i], spNube);
	}
	gameLoop();
}

void Juego::set_camera() {//contramos camara con esta funcion
	//vista de la ventana de juego menu y nivel 1
	if (escena == 1 || escena == 0) {
		camara1 = new View({ 19.f,19.f }, { 13.f, 13.f });
		camara1->move(33.f, 82.f);
		ventana1->setView(*camara1);
	}
	//en el caso que sea diferente al nivel 1 se mueve la camara
	else if (escena >1) {
		camara1 = new View({ 19.f,19.f }, { 13.f, 13.f });
		camara1->move(33.f + moverCamara.x, 82.f );
		ventana1->setView(*camara1);
	}
}

void Juego::iniciar_fisica(){
	
	// Inicializamos el mundo con la gravedad por defecto de la tierra
	mundo1 = new b2World(b2Vec2(0.0f, 9.81f));

	//colisiones
	colisionador = new ProcesarColision();
	mundo1->SetContactListener(colisionador);
	//identificamos cuerpo
	idCaja_m = new int;
	*idCaja_m = 1;
	idSuelo = new int;
	*idSuelo = 2;

	//creo e inicializo el suelo
	bdydef_suelo.type = b2_staticBody;
	bdydef_suelo.position = b2Vec2(52.f + moverCamara.x, 107.5f);
	
	bdy_suelo = mundo1->CreateBody(&bdydef_suelo);
	
	b2PolygonShape shp_suelo;
	shp_suelo.SetAsBox(9.f, 0.3f);
	
	fixdef_suelo.shape = &shp_suelo;
	fixdef_suelo.restitution = 0.f;
	fixdef_suelo.density = 1.f;
	fix_suelo = bdy_suelo->CreateFixture(&fixdef_suelo);
	//desigamos identificador 
	b2BodyUserData& dataSuelo = bdy_suelo->GetUserData();
	dataSuelo.pointer = (uintptr_t)idSuelo;

	//creo e inicializo el cañon
	bdydef_arma.type = b2_staticBody;
	bdydef_arma.position = b2Vec2(47.1f + moverCamara.x, 105.4f);

	bdy_arma = mundo1->CreateBody(&bdydef_arma);

	b2PolygonShape shp_arma;
	shp_arma.SetAsBox(1.2f, 0.7f);

	fixdef_arma.shape = &shp_arma;
	fixdef_arma.density = 1.f;
	fixdef_arma.restitution = 0.1f;
	fixdef_arma.friction = 0.3f;

	fix_arma = bdy_arma->CreateFixture(&fixdef_arma);

	//creo e inicializo la base del cañon
	bdydef_base.type = b2_staticBody;
	bdydef_base.position = b2Vec2(47.f + moverCamara.x, 106.2f);

	bdy_base = mundo1->CreateBody(&bdydef_base);

	b2PolygonShape shp_base;
	shp_base.SetAsBox(0.9f, 0.8f);

	fixdef_base.shape = &shp_base;
	fixdef_base.density = 1.f;
	fixdef_base.restitution = 0.1f;
	fixdef_base.friction = 0.3f;

	fix_base = bdy_base->CreateFixture(&fixdef_base);

		//creo e inicializo la bola
		bdydef_bol.type = b2_dynamicBody;
		bdydef_bol.position = b2Vec2(83.f, 99.8f);

		bdy_bol = mundo1->CreateBody(&bdydef_bol);

		b2PolygonShape shp_bol;
		shp_bol.SetAsBox(0.4f, 2.f);

		fixdef_bol.shape = &shp_bol;
		fixdef_bol.density = 1.f;
		fixdef_bol.restitution = 0.1f;
		fixdef_bol.friction = 0.1f;

		fix_bol = bdy_bol->CreateFixture(&fixdef_bol);

		//creo e inicializo la base de la bola
		bdydef_basebol.type = b2_staticBody;
		bdydef_basebol.position = b2Vec2(83.f, 97.f);

		bdy_basebol = mundo1->CreateBody(&bdydef_basebol);

		b2PolygonShape shp_basebol;
		shp_basebol.SetAsBox(0.8f, 0.5f);

		fixdef_basebol.shape = &shp_basebol;
		fixdef_basebol.density = 1.f;
		fixdef_basebol.restitution = 0.2f;
		fixdef_basebol.friction = 0.1f;

		fix_basebol = bdy_basebol->CreateFixture(&fixdef_basebol);

		//Uno con resortes de la base y la bola
		jntdef_bol.Initialize(bdy_basebol, bdy_bol, b2Vec2(bdy_basebol->GetPosition().x, bdy_bol->GetPosition().y - 3.f), //cabeza - torso
			b2Vec2(bdy_bol->GetPosition().x, bdy_basebol->GetPosition().y - 0.1f));

		jntdef_bol.damping = 0.5f;
		jntdef_bol.stiffness = 2.f;
		jntdef_bol.length = 5.f;
		jntdef_bol.collideConnected = true;
		jnt_bol = (b2DistanceJoint*)mundo1->CreateJoint(&jntdef_bol);

	//creo e inicializo el obstaculo fijo
	for (int i = 0; i < 3; i++) {
		bdydef_caja[i].type = b2_staticBody;
		bdydef_caja[0].position = b2Vec2(54.f + moverCamara.x, 98.5f + moverCamara.y);
		bdydef_caja[1].position = b2Vec2(54.9f + moverCamara.x, 98.5f + moverCamara.y);
		bdydef_caja[2].position = b2Vec2(55.8f + moverCamara.x, 98.5f + moverCamara.y);
		bdy_caja[i] = mundo1->CreateBody(&bdydef_caja[i]);

		b2PolygonShape shp_caja;
		shp_caja.SetAsBox(0.5f, 0.45f);

		fixdef_caja[i].shape = &shp_caja;
		fixdef_caja[i].density = 0.5f;
		fixdef_caja[i].restitution = 0.01f;
		fixdef_caja[i].friction = 0.1f;

		fix_caja[i] = bdy_caja[i]->CreateFixture(&fixdef_caja[i]);
	}

	//creo e inicializo el obstaculo mobil
	bdydef_caja_m.type = b2_dynamicBody;
	bdydef_caja_m.position = b2Vec2(55.f + moverCamara.x, 97.f + moverCamara.y);

	bdy_caja_m = mundo1->CreateBody(&bdydef_caja_m);

	b2PolygonShape shp_caja_m;
	shp_caja_m.SetAsBox(0.5f, 0.5f);

	fixdef_caja_m.shape = &shp_caja_m;
	fixdef_caja_m.density = 1.f;
	fixdef_caja_m.restitution = 0.1f;
	fixdef_caja_m.friction = 0.3f;

	fix_caja_m = bdy_caja_m->CreateFixture(&fixdef_caja_m);
	//desigamos identificador 
	b2BodyUserData& dataCaja = bdy_caja_m->GetUserData();
	dataCaja.pointer = (uintptr_t)idCaja_m;

		//creo e inicializo el obstaculo fijo
	for (int i = 0; i < 3; i++) {
		bdydef_nube[i].type = b2_staticBody;
		bdydef_nube[0].position = b2Vec2(51.f, 97.f);
		bdydef_nube[1].position = b2Vec2(47.7f, 100.f);
		bdydef_nube[2].position = b2Vec2(54.f, 103.f);

		bdy_nube[i] = mundo1->CreateBody(&bdydef_nube[i]);

		b2PolygonShape shp_nube;
		shp_nube.SetAsBox(0.8f, 0.6f);

		fixdef_nube[i].shape = &shp_nube;
		fixdef_nube[i].density = 1.f;
		fixdef_nube[i].restitution = 0.1f;
		fixdef_nube[i].friction = 0.3f;

		fix_nube[i] = bdy_nube[i]->CreateFixture(&fixdef_nube[i]);
	}
}

void Juego::iniciar_img() {
	//cargo sprtie para fondo del juego
	txFondo = new Texture;
	spFondo = new Sprite;
	txFondo->loadFromFile("../Src/fondo_cielo.png");
	spFondo->setTexture(*txFondo);
	spFondo->setPosition(45.5 + moverCamara.x, 94);
	spFondo->setScale(0.006, 0.008);

	//cargo sprtie para boton de Reset
	txReset = new Texture;
	spReset = new Sprite;
	txReset->loadFromFile("../Src/restart.png");
	spReset->setTexture(*txReset);
	spReset->setPosition(56 + moverCamara.x, 94.8);
	spReset->setScale(0.007, 0.009);

	//cargo sprtie para boton de Start
	txInicio[0] = new Texture;
	spInicio[0] = new Sprite;
	txInicio[0]->loadFromFile("../Src/start.png");
	spInicio[0]->setTexture(*txInicio[0]);
	spInicio[0]->setPosition(50, 100);
	spInicio[0]->setScale(0.01, 0.013);

	//cargo sprtie para boton de Salir
	txInicio[1] = new Texture;
	spInicio[1] = new Sprite;
	txInicio[1]->loadFromFile("../Src/salir.png");
	spInicio[1]->setTexture(*txInicio[1]);
	spInicio[1]->setPosition(50, 102);
	spInicio[1]->setScale(0.01, 0.013);

	//cargo sprtie para boton de Titulo Juego
	txInicio[2] = new Texture;
	spInicio[2] = new Sprite;
	txInicio[2]->loadFromFile("../Src/titulo.png");
	spInicio[2]->setTexture(*txInicio[2]);
	spInicio[2]->setPosition(47, 96);
	spInicio[2]->setScale(0.02, 0.025);

	//cargo sprite cartel ganador
	txInicio[3] = new Texture;
	spInicio[3] = new Sprite;
	txInicio[3]->loadFromFile("../Src/ganaste.png");
	spInicio[3]->setTexture(*txInicio[3]);
	spInicio[3]->setPosition(115, 98);
	spInicio[3]->setScale(0.02, 0.025);

	//cargo sprite cartel perdedor
	txInicio[4] = new Texture;
	spInicio[4] = new Sprite;
	txInicio[4]->loadFromFile("../Src/perdiste.png");
	spInicio[4]->setTexture(*txInicio[4]);
	spInicio[4]->setPosition(49 + moverCamara.x, 98);
	spInicio[4]->setScale(0.02, 0.025);

	//cargo sprite cartel proximo nivel
	txInicio[5] = new Texture;
	spInicio[5] = new Sprite;
	txInicio[5]->loadFromFile("../Src/level.png");
	spInicio[5]->setTexture(*txInicio[5]);
	spInicio[5]->setPosition(47, 98);
	spInicio[5]->setScale(0.02, 0.025);

	//inicializo las figuras de los actores
	//nube
	txNube = new Texture;
	spNube = new Sprite;
	txNube->loadFromFile("../Src/nube.png");
	spNube->setTexture(*txNube);
	//suelo
	fig_suelo = new RectangleShape;
	fig_suelo->setFillColor(Color::Green);
	//cañon
	txCañon = new Texture;
	spCañon = new Sprite;
	txCañon->loadFromFile("../Src/cañon.png");
	spCañon->setTexture(*txCañon);
	//base Cañon
	txBcañon = new Texture;
	spBcañon = new Sprite;
	txBcañon->loadFromFile("../Src/pie_cañon.png");
	spBcañon->setTexture(*txBcañon);
	//obstaculo fijo
	txBloque = new Texture;
	spBloque = new Sprite;
	txBloque->loadFromFile("../Src/bloque.png");
	spBloque->setTexture(*txBloque);
	//obstaculo mobil
	txCaja = new Texture;
	spCaja = new Sprite;
	txCaja->loadFromFile("../Src/caja.png");
	spCaja->setTexture(*txCaja);
	//molino
	txMolino = new Texture;
	spMolino = new Sprite;
	txMolino->loadFromFile("../Src/bola.png");
	spMolino->setTexture(*txMolino);
	//base de molino
	txBmolino = new Texture;
	spBmolino= new Sprite;
	txBmolino->loadFromFile("../Src/soporte.png");
	spBmolino->setTexture(*txBmolino);
}

float Juego::deg2rad(float grados) {
	//formula para convertir grados a radianes
	return grados * 3.14f / 100;
}

void Juego::gameLoop() {
	//bucle del juego
	while (ventana1->isOpen()) {
		*tiempo1 = reloj1->getElapsedTime();
		if (tiempo2 + tiempoFrame < tiempo1->asSeconds()) {
			tiempo2 = tiempo1->asSeconds();
			ventana1->clear();
			Colision();
			procesar_eventos();
			actualizar_fisica();
			Dibujar();
			ventana1->display();
		}
	}
}

void Juego::actualizar_fisica() {
	//creo la fisica del juego
	mundo1->Step(tiempoFrame, 8, 8);
	mundo1->ClearForces();
	mundo1->DebugDraw();
}

void Juego::Dibujar() {
	//fondo
	ventana1->draw(*spFondo);
	switch (escena)
	{
	case 0:
		for (int i = 0; i < 3; i++) {
			ventana1->draw(*spInicio[i]);
		}
		break;
	case 1:
		// textos - Boton Reset
		textIngresar.setString("Nivel 1 - Ragdolls: " + to_string(5 - cant_rag));
		textIngresar.setPosition(46, 95);
		ventana1->draw(textIngresar);
		ventana1->draw(*spReset);
		//dibujo los actores
		act_arma->dibujar(*ventana1);
		act_base->dibujar(*ventana1);
		for (int i = 0; i < 3; i++) {
			act_caja[i]->dibujar(*ventana1);
		}
		act_caja_m->dibujar(*ventana1);
		//dibujo nubes sprites
		act_suelo->dibujar(*ventana1);
		for (int i = 0; i < 3; i++) {
			act_nube[i]->dibujar(*ventana1);
		}
		//dibujo los ragdolls
		for (int i = 0; i < cant_rag; i++) {
			rag_3[i]->Dibujar(*ventana1);
		}
		//condicion ganador
		if (gameOver == false && escena == 1) {
			ventana1->draw(*spInicio[5]);
			*_tiempo = reloj1->getElapsedTime();//colocamos pantalla de inicio por un lapso de tiempo
		}
		else if (cant_rag >=5 && gameOver ==true){
			ventana1->draw(*spInicio[4]);
		}
		break;
	case 2:
		// textos- Boton Reset
		textIngresar.setString("Nivel 2 - Ragdolls: " + to_string(5 - cant_rag));
		textIngresar.setPosition(46 + moverCamara.x, 95);
		ventana1->draw(textIngresar);
		ventana1->draw(*spReset);
		//dibujo los actores
		act_arma->dibujar(*ventana1);
		act_base->dibujar(*ventana1);
		act_suelo->dibujar(*ventana1);
		for (int i = 0; i < 3; i++) {
			act_caja[i]->dibujar(*ventana1);
		}
		act_caja_m->dibujar(*ventana1);
		act_molino->dibujar(*ventana1);
		act_basemol->dibujar(*ventana1);
		//dibujo los ragdolls
		for (int i = 0; i < cant_rag; i++) {
			rag_3[i]->Dibujar(*ventana1);
		}
		if (cant_rag >= 5) {
			ventana1->draw(*spInicio[4]);
		}
		break;
	case 3:
		ventana1->draw(*spReset);
		ventana1->draw(*spInicio[3]);
		break;
	default:
		break;
	}
}

void Juego::Colision() {
	//detecto colision de la caja contra el suelo para establecer condicion de ganador
	if (colisionador->colisiona == true) {
		gameOver = false;
		if (_tiempo->asSeconds() >= 7) {
			moverCamara.x += 33.f;//movemos la camara 
			moverCamara.y += 2.f;//movemos la camara para generar movimento de objetos 
			escena++;//aumentamos nivel
			cant_rag = 0;//reiniciamos contador de ragdol
			IniciaGame();//reiniciamos el juego
		}
	}
}

void Juego::procesar_eventos() {

	while (ventana1->pollEvent(*evento1)) {
		//obtengo la ubicacion del del mouse y la convierto de pixel a coordenadas
		mousePos = Mouse::getPosition(*ventana1);
		mousePos_Cord = ventana1->mapPixelToCoords(mousePos);

		switch (evento1->type) {
		case Event::Closed:
			ventana1->close();
			break;
		case Event::MouseButtonPressed:
			if (cant_rag < 5 && escena != 0) {//si disparo 5 ragdolls termina el juego

				//con la posicion del raton disparo el ragdoll
				rag_3[cant_rag] = new Ragdoll({ bdy_arma->GetPosition().x + 1.f,bdy_arma->GetPosition().y - 2.f }, *mundo1);//configuro la posicion del mouse para la direccion del disparo
				rag_3[cant_rag]->aplicar_fuerza({ mousePos_Cord.x - bdy_arma->GetPosition().x,mousePos_Cord.y - bdy_arma->GetPosition().y });//aplico la fuerza al disparo
				cant_rag++;//incremento para poder condicionar el juego
			}
			if (evento1->mouseButton.button == Mouse::Button::Left) {
				if (spReset->getGlobalBounds().contains(mousePos_Cord.x, mousePos_Cord.y)) {
					ventana1->close();
					new Juego({ 800,600 }, "TPFINAL,Matias Navarro"); //Si presiono boton Restart se reinicia
				}
			}
			if (evento1->mouseButton.button == Mouse::Button::Left && escena == 0) {
				if (spInicio[0]->getGlobalBounds().contains(mousePos_Cord.x, mousePos_Cord.y)) {//Si presiono boton Start inicia juego
					escena =1;
				}
			}
			if (evento1->mouseButton.button == Mouse::Button::Left && escena == 0) {
				if (spInicio[1]->getGlobalBounds().contains(mousePos_Cord.x, mousePos_Cord.y)) {//Si presiono boton Salir se cierra el juego
					ventana1->close();
				}
			}
			break;
		case Event::MouseMoved:
			bdy_arma->SetTransform(bdy_arma->GetPosition(), atan2f(mousePos_Cord.y - bdy_arma->GetPosition().y, mousePos_Cord.x - bdy_arma->GetPosition().x));//obtengo las coodrdenadas del raton
			break;
		case Event::KeyPressed:
			if (Keyboard::isKeyPressed(Keyboard::Escape)) {// ESCAPE para otra opcion en caso de cerrar juego
				ventana1->close();
				break;
			}
			break;

		}
	}
}

