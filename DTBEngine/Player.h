#pragma once

#include "libs.h"
#include "AssetManager.h"
#include "Animator.h"

#define WALK_POWER 1.2f
#define JUMP_POWER 3.32f

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
		pbdef.linearDamping = 3.1f;
		pbdef.gravityScale = 1.5f;
		
		b2FixtureDef fdef;
		fdef.density = 8.0f;;

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

	void updateAnimation(sf::Time &time)
	{

	}

	void update(sf::Time &deltaTime) // update gametick
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
			if (velocity.x < 1.1 * deltaTime.asMicroseconds()) pBody->ApplyForceToCenter(b2Vec2(WALK_POWER * deltaTime.asMicroseconds(), 0), 1);	// Force					
			pSprite.setTextureRect(sf::IntRect(playerRect.width, playerRect.left, -playerRect.width, playerRect.height));
			break;
		case PlayerState::MoveLeft:
			if (velocity.x > -1.1 * deltaTime.asMicroseconds()) pBody->ApplyForceToCenter(b2Vec2(-WALK_POWER * deltaTime.asMicroseconds(), 0), 1);
			pSprite.setTextureRect(playerRect);
			break;
		case PlayerState::Jump:
			if (onGround) pBody->ApplyForceToCenter(b2Vec2(0, -JUMP_POWER * deltaTime.asMicroseconds()), 1);
			break;
		case PlayerState::Stay:
			//pBody->SetAngularDamping(0.5f);
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