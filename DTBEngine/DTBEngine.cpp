#include "libs.h"
#include "AssetManager.h"
#include "Player.h"

b2Vec2 gravity(0.0f, 10.0f);
b2World world(gravity);

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "main");
	window.setFramerateLimit(60);

	// init

	AssetManager manager;
	sf::Sprite tet(manager.GetTexture("player.png"));
	b2Vec2 spawn(50 / SCALE, 50 / SCALE);
	Player pl(&world, spawn, manager);

	sf::Clock clock;
	float dtime = 0;

	while (window.isOpen())
	{
		sf::Event evt;
		dtime = clock.getElapsedTime().asSeconds();
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

