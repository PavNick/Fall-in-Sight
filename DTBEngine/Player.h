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
	AssetManager *manager;		// Assets (textures, sounds)
	sf::Sprite pSprite;			// Sprite for draw
	bool onGround;				// Check intersects ground
	b2BodyDef pbdef;			// Body definitions
	b2PolygonShape pShape;		// Body shape
	b2Body *pBody;				// Body
	b2Vec2 spawnPoint;			// Point spawn on map
	b2World *world;				// Pointer to main gameworld
	PlayerState currentState;	// player current state

	void initModel()
	{	
		// -----Physics

		// Body setup

		pbdef.type = b2_dynamicBody;
		pbdef.userData = (void*)"player";
		pbdef.position.Set(spawnPoint.x, spawnPoint.y);

		// Player shape setup

		pShape.SetAsBox(12.0f / SCALE, 18.0f / SCALE);

		// Load shape in body and add to World

		pBody = world->CreateBody(&pbdef);
		pBody->CreateFixture(&pShape, 2.0f);
		pBody->SetUserData((void*)"player");

		// -----Visuals

		pSprite.setTexture(manager->GetTexture("player.png"));	// Load texture to Sprite
		pSprite.setTextureRect(sf::IntRect(0, 0, 12, 18));		// Cut texture for render
	}

public:
	Player(b2World *w, b2Vec2 &sp, AssetManager *man) : manager(man) // Constructor
	{
		currentState = PlayerState::Stay;
		world = w;
		spawnPoint = sp;
		initModel();
		// todo
	}

	void updateEvent(sf::Event *ev) // For moving, shooting and more
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

	void update(float deltaTime) // update gametick
	{
		
	}

	void draw(sf::RenderWindow *window) // render player on display
	{

	}
};