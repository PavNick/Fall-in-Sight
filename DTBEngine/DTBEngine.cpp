#include "libs.h"
#include "AssetManager.h"
#include "Player.h"

b2Vec2 gravity(0.0f, 9.0f);
b2World world(gravity);

void setWall(int x, int y, int w, int h)
{
	b2PolygonShape gr;
	gr.SetAsBox(w / SCALE, h / SCALE);

	b2FixtureDef wallfdef;
	//wallfdef.friction = 0.3f;
	wallfdef.density = 1.0f;
	wallfdef.shape = &gr;

	b2BodyDef bdef;
	bdef.position.Set(x / SCALE, y / SCALE);

	b2Body *body_gr = world.CreateBody(&bdef);
	body_gr->CreateFixture(&wallfdef);
	body_gr->SetUserData((void*)"wall");
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 640), "main");
	window.setFramerateLimit(60);

	// init

	AssetManager manager;
	b2Vec2 spawn(50 / SCALE, 50 / SCALE);
	Player pl(&world, spawn, manager);

	// testroom

	setWall(0, 0, 800, 16);
	setWall(0, 16, 16, 600 - 16);
	setWall(0, 600 - 16, 800, 16);
	setWall(800 - 16, 16, 16, 600 - 16);

	// tsr

	sf::Clock clock;
	sf::Time dtime;

	while (window.isOpen())
	{
		sf::Event evt;
		dtime = clock.getElapsedTime();
		clock.restart();
		while (window.pollEvent(evt))
		{
			if (evt.type == sf::Event::Closed) window.close();
			pl.updateEvent(&evt);
		}

		world.Step(1 / 60.f, 8, 3);

		pl.update(dtime);

		window.clear(sf::Color(0, 153, 255));
		pl.draw(&window);

		window.display();
	}

	return 0;
	
}

