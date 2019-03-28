#pragma once

#include "libs.h"
#include "AssetManager.h"
#include "Animator.h"

enum PlayerState { 
	Stay = 0,		// no move
	MoveRight,		// moving right
	MoveLeft,		// moving left
	MoveUp,			// moving up (ladder)
	MoveDown,		// moving down (ladder, platform)
	Jump			// jumping
};

class Player
{
	AssetManager *manag;		// Assets (textures, sounds)
	sf::Sprite pSprite;			// Sprite for draw
	bool onGround;				// Check intersects ground
	b2BodyDef pbdef;			// Body definitions
	b2PolygonShape pShape;		// Body shape
	b2Body *pBody;				// Body
	b2Vec2 spawnPoint;			// Point spawn on map
	b2World *world;				// Pointer to main gameworld
	PlayerState currentState;	// player current state

	// TESTING

	void setWall(int x, int y, int w, int h)
	{
		b2PolygonShape gr;
		gr.SetAsBox(w / SCALE, h / SCALE);

		b2BodyDef bdef;
		bdef.position.Set(x / SCALE, y / SCALE);

		b2Body *body_gr = world->CreateBody(&bdef);
		body_gr->CreateFixture(&gr, 1);
		body_gr->SetUserData((void*)"wall");
	}

	void initModel()
	{	
		// -----Physics

		// Body setup

		pbdef.type = b2_dynamicBody;
		pbdef.userData = (void*)"player";
		pbdef.position.Set(spawnPoint.x, spawnPoint.y);
		

		// Player shape setup

		pShape.SetAsBox((10.0f * 5) / SCALE, (15.0f * 5) / SCALE);
		

		// Load shape in body and add to World

		pBody = world->CreateBody(&pbdef);
		pBody->CreateFixture(&pShape, 2.8f);
		pBody->SetUserData((void*)"player");

		// -----Visuals

		pSprite.setTexture(manag->GetTexture("player.png"));	// Load texture to Sprite
		pSprite.setTextureRect(sf::IntRect(0, 0, 10, 15));		// Cut texture for render
		pSprite.setScale(5, 5);
		pSprite.setOrigin(5, 7.5);
	}

public:
	Player(b2World *w, b2Vec2 &sp, AssetManager &man) : manag(&man) // Constructor
	{
		currentState = PlayerState::Stay;
		world = w;
		spawnPoint = sp;
		initModel();
		// todo

		// test

		setWall(0, 500, 800, 10);

	}

	void updateEvent(sf::Event *ev) // For moving, shooting and more
	{
		if (ev->type == sf::Event::KeyPressed)
		{
			switch (ev->key.code)
			{
			case sf::Keyboard::D:
				currentState = PlayerState::MoveRight;
				break;
			case sf::Keyboard::A:
				currentState = PlayerState::MoveLeft;
				break;
			case sf::Keyboard::W:
				currentState = PlayerState::MoveUp;
				break;
			case sf::Keyboard::S:
				currentState = PlayerState::MoveDown;
				break;
			case sf::Keyboard::Space:
				currentState = PlayerState::Jump;
				break;
			default:
				currentState = PlayerState::Stay;
				break;
			}
		}
	}

	void setStay() { currentState = PlayerState::Stay; }

	void update(float deltaTime) // update gametick
	{
		bool onGround = true;
		/*
		b2Vec2 pos = pBody->GetPosition();
		pos.y += 16 / SCALE;
		for (b2Body *it = world->GetBodyList(); it != 0; it = it->GetNext())
			for (b2Fixture *itf = it->GetFixtureList(); itf != 0; itf = itf->GetNext())
				if (itf->TestPoint(pos)) onGround = true;*/

		b2Vec2 velocity = pBody->GetLinearVelocity();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) if (velocity.x < 200) pBody->ApplyForceToCenter(b2Vec2(-2400, 0), 1);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) if (velocity.x > -200) pBody->ApplyForceToCenter(b2Vec2(2400, 0), 1);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) if (onGround) pBody->ApplyForceToCenter(b2Vec2(0, -240), 1);

		if (velocity.x > 0)
		{
			pBody->SetLinearVelocity(b2Vec2(pBody->GetLinearVelocity().x - 0.5, pBody->GetLinearVelocity().y));
		}


		//switch (currentState)
		//{
		//case PlayerState::MoveRight:
		//	if (velocity.x > -20) pBody->ApplyForceToCenter(b2Vec2(24, 0), 1);	// Force
		//	pSprite.setTextureRect(sf::IntRect(0, 0, 10, 15));					// Visual
		//	break;
		//case PlayerState::MoveLeft:
		//	if (velocity.x < 20) pBody->ApplyForceToCenter(b2Vec2(-24, 0), 1);
		//	pSprite.setTextureRect(sf::IntRect(10, 0, -10, 15));
		//	break;
		//case PlayerState::Jump:
		//	if (onGround) pBody->ApplyLinearImpulseToCenter(b2Vec2(0, -15), 1);
		//	break;
		//default:
		//	break;
		//}
		//setStay();
	}

	void draw(sf::RenderWindow *window) // render player on display
	{
		for (b2Body *it = world->GetBodyList(); it != 0; it = it->GetNext())
		{
			if (it->GetUserData() == "player")
			{
				b2Vec2 pos = it->GetPosition();
				pSprite.setPosition(pos.x * SCALE, pos.y * SCALE);
				window->draw(pSprite);
			}
		}
	}
};