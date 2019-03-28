//#include "libs.h"
//#include "AssetManager.h"
//
//b2Vec2 gravity(0.f, 9.8f);
//b2World world(gravity);
//
//void setWall(int x, int y, int w, int h)
//{
//	b2PolygonShape gr;
//	gr.SetAsBox(w / SCALE, h / SCALE);
//
//	b2BodyDef bdef;
//	bdef.position.Set(x / SCALE, y / SCALE);
//
//	b2Body *body_gr = world.CreateBody(&bdef);
//	body_gr->CreateFixture(&gr, 1);
//	body_gr->SetUserData((void*)"wall");
//}
//
//void setBox(int x, int y, int w, int h)
//{
//	b2PolygonShape shape;
//	shape.SetAsBox(w / SCALE, h / SCALE);
//
//	b2BodyDef bdef;
//	bdef.type = b2_dynamicBody;
//	bdef.position.Set(x / SCALE, y / SCALE);
//	b2Body *body = world.CreateBody(&bdef);
//	body->CreateFixture(&shape, 2);
//	body->SetUserData((void*)"box");
//}
//
//int falsemain()
//{
//	sf::RenderWindow window(sf::VideoMode(800, 600), "testing");
//	window.setFramerateLimit(60);
//
//	// init
//
//	sf::Texture t1, t2, t3;
//
//	t1.loadFromFile("images/ground.png");
//	t2.loadFromFile("images/player.png");
//	t3.loadFromFile("images/objects1.png");
//
//	t2.setSmooth(true); t3.setSmooth(true);
//
//	sf::Sprite sGround(t1), sPlayer(t2), sBox(t3);
//	sBox.setTextureRect(sf::IntRect(81, 0, 61, 61));
//	sBox.setOrigin(30, 30);
//
//	sPlayer.setTextureRect(sf::IntRect(0, 160, 32, 32));
//	sPlayer.setOrigin(16, 16);
//
//	sGround.setPosition(0, 320);
//
//	// map, objects
//	setWall(400, 490, 2000, 10);
//	setWall(55, 438, 64, 60);
//	setWall(710, 435, 100, 60);
//	setWall(-5, 0, 5, 600);
//	setWall(800, 0, 5, 600);
//
//	setBox(600, 100, 30, 30);
//	setBox(180, 100, 30, 30);
//	setBox(50, 100, 30, 30);
//
//	// player
//
//	b2BodyDef pbdef;
//	pbdef.position.Set(2, 2);
//	pbdef.type = b2_dynamicBody;
//
//	b2CircleShape pShape;
//	pShape.m_radius = 16 / SCALE;
//
//	b2Body *pBody = world.CreateBody(&pbdef);
//	pBody->CreateFixture(&pShape, 2);
//	pBody->SetUserData((void*)"player");
//
//
//	while (window.isOpen())
//	{
//		sf::Event evt;
//
//		while (window.pollEvent(evt))
//		{
//			if (evt.type == sf::Event::Closed) window.close();
//		}
//
//		world.Step(1 / 60.f, 8, 3);
//
//		bool onGround = false;
//		b2Vec2 pos = pBody->GetPosition();
//		pos.y += 17 / SCALE;
//		for (b2Body *it = world.GetBodyList(); it != 0; it = it->GetNext())
//			for (b2Fixture *itf = it->GetFixtureList(); itf != 0; itf = itf->GetNext())
//				if (itf->TestPoint(pos)) onGround = true;
//
//		b2Vec2 velocity = pBody->GetLinearVelocity();
//		float angelVel = pBody->GetAngularVelocity();
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) if (velocity.x < 20) pBody->ApplyForceToCenter(b2Vec2(-24, 0), 1);
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) if (velocity.x > -20) pBody->ApplyForceToCenter(b2Vec2(24, 0), 1);
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) if (onGround) pBody->ApplyLinearImpulseToCenter(b2Vec2(0, -24), 1);
//
//		window.clear(sf::Color(0, 153, 255));
//		window.draw(sGround);
//
//		for (b2Body *it = world.GetBodyList(); it != 0; it = it->GetNext())
//		{
//			if (it->GetUserData() == "box")
//			{
//				b2Vec2 pos = it->GetPosition();
//				float angle = it->GetAngle();
//				sBox.setPosition(pos.x * SCALE, pos.y * SCALE);
//				sBox.setRotation(angle * DEG);
//				window.draw(sBox);
//			}
//
//			if (it->GetUserData() == "player")
//			{
//				b2Vec2 pos = it->GetPosition();
//				float angle = it->GetAngle();
//				sPlayer.setPosition(pos.x * SCALE, pos.y * SCALE);
//				sPlayer.setRotation(angle * DEG);
//				window.draw(sPlayer);
//			}
//		}
//
//		window.display();
//	}
//
//	return 0;
//
//}

