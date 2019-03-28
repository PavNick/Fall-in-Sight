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
	AssetManager *manager;
	sf::Sprite pSprite;
	bool onGround;
	b2BodyDef pbdef;
	b2PolygonShape pShape;
	b2Body *pBody;
	b2Vec2 spawnPoint;
	b2World *world;
	PlayerState currentState;

	void initModel()
	{	
		// Physics

		pbdef.type = b2_dynamicBody;					//
		pbdef.userData = (void*)"player";				// Body setup
		pbdef.position.Set(spawnPoint.x, spawnPoint.y);	//

		pShape.SetAsBox(12.0f / SCALE, 18.0f / SCALE);	// Player shape setup

		pBody = world->CreateBody(&pbdef);				//
		pBody->CreateFixture(&pShape, 2.0f);			// Load shape in body and add to World
		pBody->SetUserData((void*)"player");			//

		// Visuals

		pSprite.setTexture(manager->GetTexture("player.png"));	// Load texture to Sprite
		pSprite.setTextureRect(sf::IntRect(0, 0, 12, 18));		// Cut texture for render
	}

public:
	Player(b2World *w, b2Vec2 &sp, AssetManager *man) : manager(man)
	{
		currentState = PlayerState::Stay;
		world = w;
		spawnPoint = sp;
		initModel();

	}

	void updateEvent(sf::Event *ev)
	{
		if (ev->type == sf::Event::KeyPressed)
		{
			switch (ev->key.code)
			{
			case sf::Keyboard::D:
				currentState = PlayerState::MoveRight;
			default:
				break;
			}
		}
	}

	void update(float deltaTime, sf::RenderWindow *window)
	{
		
	}
};