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
	float playerScale;			// player scale
	sf::IntRect playerRect;		// player rect

	// TESTING

	void setWall(int x, int y, int w, int h)
	{
		b2PolygonShape gr;
		gr.SetAsBox(w / SCALE, h / SCALE);

		b2FixtureDef wallfdef;
		wallfdef.friction = 0.3f;
		wallfdef.density = 1.0f;
		wallfdef.shape = &gr;

		b2BodyDef bdef;
		bdef.position.Set(x / SCALE, y / SCALE);

		b2Body *body_gr = world->CreateBody(&bdef);
		body_gr->CreateFixture(&wallfdef);
		body_gr->SetUserData((void*)"wall");
	}

	void initModel()
	{	
		// -----Physics

		playerScale = 5;
		playerRect = sf::IntRect(0, 0, 12, 22);

		// Body setup

		pbdef.type = b2_dynamicBody;
		pbdef.userData = (void*)"player";
		pbdef.position.Set(spawnPoint.x, spawnPoint.y);
		pbdef.fixedRotation = true;
		
		b2FixtureDef fdef;
		fdef.density = 1.8f;
		fdef.friction = 5.6f;

		// Player shape setup

		pShape.SetAsBox((playerRect.width * playerScale) / SCALE, (playerRect.height * playerScale) / SCALE);
		fdef.shape = &pShape;
		

		// Load shape in body and add to World

		pBody = world->CreateBody(&pbdef);
		pBody->CreateFixture(&fdef);
		pBody->SetUserData((void*)"player");

		// -----Visuals

		pSprite.setTexture(manag->GetTexture("player.png"));	// Load texture to Sprite
		pSprite.setTextureRect(playerRect);		// Cut texture for render
		pSprite.setScale(playerScale, playerScale);
		pSprite.setOrigin(pSprite.getTextureRect().width / 2, pSprite.getTextureRect().height / 2);
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
				break;
			}
		}
		else if (ev->type == sf::Event::KeyReleased) currentState = PlayerState::Stay;
	}

	void setStay() { currentState = PlayerState::Stay; }

	void update(float deltaTime) // update gametick
	{
		bool onGround = false;
		b2Vec2 pos = pBody->GetPosition();
		pos.y += pSprite.getTextureRect().height * playerScale / SCALE + 0.2;
		for (b2Body *it = world->GetBodyList(); it != 0; it = it->GetNext())
			if (it->GetUserData() != "player") for (b2Fixture *itf = it->GetFixtureList(); itf != 0; itf = itf->GetNext())
				if (itf->TestPoint(pos)) onGround = true;

		b2Vec2 velocity = pBody->GetLinearVelocity();

		switch (currentState)
		{
		case PlayerState::MoveRight:
			if (velocity.x > -1) pBody->ApplyLinearImpulseToCenter(b2Vec2(20, 0), 1);	// Force					
			pSprite.setTextureRect(sf::IntRect(playerRect.width, playerRect.left, -playerRect.width, playerRect.height));
			break;
		case PlayerState::MoveLeft:
			if (velocity.x < 1) pBody->ApplyLinearImpulseToCenter(b2Vec2(-20, 0), 1);
			pSprite.setTextureRect(playerRect);
			break;
		case PlayerState::Jump:
			if (onGround) pBody->ApplyLinearImpulseToCenter(b2Vec2(0, -240), 1);
			break;
		default:
			break;
		}
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