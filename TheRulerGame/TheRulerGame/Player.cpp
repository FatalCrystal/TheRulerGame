#include "Player.h"
#include "Collision.h"

Player::Player(std::string _spritePath, sf::Vector2f _position, std::string _name) :
	m_Name(_name) // Set player name
{
	// Load player texture
	m_Texture.loadFromFile("Resources/Textures/" + _spritePath);
	// Set player sprite
	SetSprite(new sf::Sprite(m_Texture));

	// Load texture for crown
	m_CrownTexture.loadFromFile("Resources/Textures/Crown.png");
	//Create sprite for crown
	m_CrownSprite = new sf::Sprite(m_CrownTexture);
	// Assign sprite origin
	m_CrownSprite->setOrigin(m_CrownSprite->getGlobalBounds().width / 2, m_CrownSprite->getGlobalBounds().height / 2);

	// Set the player audio parameters
	SetAudio();
	// Set player initial position
	SetPosition(_position);
	
	// Create player bounding box shape
	m_BoundingBoxShape = new sf::RectangleShape();
}

Player::~Player()
{
	delete m_BoundingBoxShape;
	delete m_CrownSprite;
	delete m_Sprite;
}

// Set players enemy
void Player::SetEnemy(Player* _enemy)
{
	m_Enemy = _enemy;
}

// Set player sprite and its origin 
void Player::SetSprite(sf::Sprite* _sprite)
{
	m_Sprite = _sprite;
	m_Sprite->setOrigin(m_Sprite->getGlobalBounds().width / 2, m_Sprite->getGlobalBounds().height / 2);
}

// Set player position 
void Player::SetPosition(sf::Vector2f _position)
{
	m_Position = _position;

	if (m_Sprite != nullptr)
	{
		m_Sprite->setPosition(m_Position);
	}
}

// Set the direction of the player
void Player::SetDirection(sf::Vector2f _direction)
{
	m_Direction = _direction;
}

// Set the player movespeed
void Player::SetMoveSpeed(float _moveSpeed)
{
	m_MoveSpeed = _moveSpeed;
}

// Set attack cool down
void Player::SetAttackCooldown(float _attackCooldown)
{
	m_AttackCooldownDuration = _attackCooldown;
}

// Set the speed at which the player rotates in game
void Player::SetRotationSpeed(float _rotationSpeed)
{
	m_RotationSpeed = _rotationSpeed;
}

// Set pickup
void Player::SetPickup(PickupType _pickup)
{
	m_CurrentPickup = _pickup;
	m_PickupTimer.restart();
}

// Set whether the player has the crown
void Player::SetCrown(bool _hasCrown)
{
	m_HasCrown = _hasCrown;

	/*if (m_HasCrown)
	{
		m_Shape->setOutlineColor(sf::Color::Yellow);
	}
	else
	{
		m_Shape->setOutlineColor(m_Color);
	}*/
}

// Set audio files for the players to use
void Player::SetAudio()
{
	// Check if sound buffer is loaded
	if (!m_PlayerShootSB.loadFromFile("Resources/Sounds/Shoot.wav"))
	{
		std::cout << "Error Shoot.wav not loaded" << std::endl;
	}

	if (!m_PlayerHitSB.loadFromFile("Resources/Sounds/Hit.wav"))
	{
		std::cout << "Error Hit.wav not loaded" << std::endl;
	}
	
	if (!m_PlayerCrownSwitchSB.loadFromFile("Resources/Sounds/Crown_Switch.wav"))
	{
		std::cout << "Error Crown_Switch.wav not loaded" << std::endl;
	}
	
	if (!m_PlayerPickUpSB.loadFromFile("Resources/Sounds/Powerup.wav"))
	{
		std::cout << "Error Powerup.wav not loaded" << std::endl;
	}

	// Set buffer to sound veriable
	m_PlayerShootSound.setBuffer(m_PlayerShootSB);
	m_PlayerHitSound.setBuffer(m_PlayerHitSB);
	m_PlayerCrownSwitchSound.setBuffer(m_PlayerCrownSwitchSB);
	m_PlayerPickUpSound.setBuffer(m_PlayerPickUpSB);
}

// Handles wall collisions
void Player::WallCollisions(SceneManager _scene, sf::RenderWindow* _window, std::vector<Bullet*>* _projectiles)
{
	// Bool to check if player is colliding with wall
	bool colliding = false;

	// Set player bounding box float rect
	m_PlayerBoundingBox = m_Sprite->getGlobalBounds();
	// Set bounding box shape for nex position to a little bigger the player 
	m_BoundingBoxShape->setSize(sf::Vector2f(25, 25));
	// Make shape invis
	m_BoundingBoxShape->setFillColor(sf::Color::Transparent);
	// Set shape to player position
	m_BoundingBoxShape->setPosition(GetPosition().x - m_Sprite->getTextureRect().width / 2, GetPosition().y - m_Sprite->getTextureRect().height / 2);

	// Set float rect to hold bounding box
	m_PlayerNextPos = m_BoundingBoxShape->getGlobalBounds();
	// Move float rect to slightly infront of the player
	m_PlayerNextPos.left += m_Direction.x;
	m_PlayerNextPos.top += m_Direction.y;

	// Loop through the walls
	for (auto &wall : _scene.GetWalls())
	{
		// Float rect for wall bounding box
		sf::FloatRect wallBounds = wall->GetTile()->getGlobalBounds();

		// If not colliding restrict movement
		if (!colliding)
		{
			m_CanMoveForward = true;
			m_CanMoveBack = true;
		}

		// Check if wall bounding box intersects with the players next position bounding box
		if (wallBounds.intersects(m_PlayerNextPos))
		{
			// Bottom Player collision with Top wall collision
			if (m_PlayerBoundingBox.top < wallBounds.top + wallBounds.height
				&& m_PlayerBoundingBox.top + m_PlayerBoundingBox.height < wallBounds.top + wallBounds.height
				&& m_PlayerBoundingBox.left < wallBounds.left + wallBounds.width
				&& m_PlayerBoundingBox.left + m_PlayerBoundingBox.width > wallBounds.left)
			{
				colliding = true;
				if (m_Sprite->getRotation() > 90.f && m_Sprite->getRotation() < 270.f)
				{
					m_CanMoveForward = false;
					m_CanMoveBack = true;
				}
			}
			// Top Player collision with Bottom wall collision
			if (m_PlayerBoundingBox.top > wallBounds.top
				&& m_PlayerBoundingBox.top + m_PlayerBoundingBox.height > wallBounds.top + wallBounds.height
				&& m_PlayerBoundingBox.left < wallBounds.left + wallBounds.width
				&& m_PlayerBoundingBox.left + m_PlayerBoundingBox.width > wallBounds.left)
			{
				colliding = true;
				if (m_Sprite->getRotation() < 90.f || m_Sprite->getRotation() > 270.f)
				{
					m_CanMoveForward = false;
					m_CanMoveBack = true;
				}
			}
			// Left Player collision with Right wall collision
			if (m_PlayerBoundingBox.left < wallBounds.left
				&& m_PlayerBoundingBox.left + m_PlayerBoundingBox.width < wallBounds.left + wallBounds.width
				&& m_PlayerBoundingBox.top > wallBounds.top + wallBounds.height
				&& m_PlayerBoundingBox.top + m_PlayerBoundingBox.height > wallBounds.top)
			{
				colliding = true;
				if (m_Sprite->getRotation() < 180.f && m_Sprite->getRotation() > 0.f)
				{
					m_CanMoveForward = false;
					m_CanMoveBack = true;
				}
			}
			// Right Player collision with Left wall collision
			if (m_PlayerBoundingBox.left > wallBounds.left
				&& m_PlayerBoundingBox.left + m_PlayerBoundingBox.width > wallBounds.left + wallBounds.width
				&& m_PlayerBoundingBox.top < wallBounds.top + wallBounds.height
				&& m_PlayerBoundingBox.top + m_PlayerBoundingBox.height > wallBounds.top)
			{
				colliding = true;
				if (m_Sprite->getRotation() < 360.f && m_Sprite->getRotation() > 180.f)
				{
					m_CanMoveForward = false;
					m_CanMoveBack = true;
				}
			}
		}

		// Set bullet counter
		int Counter = 0;
		// Loop through bullets
		for (Bullet* Projectile : *_projectiles)
		{
			// If bullets intersect with wall remove bullet and play sound
			if (Projectile->GetShape()->getGlobalBounds().intersects(wallBounds))
			{
				m_PlayerHitSound.play();

				delete _projectiles->at(Counter);
				_projectiles->erase(_projectiles->begin() + Counter);
				Counter -= 1;
			}
			Counter += 1;
		}
	}
}

// Handles shooting
void Player::Shoot(std::vector<Bullet*>* _projectiles)
{
	if (m_AttackCooldown.getElapsedTime().asSeconds() > m_AttackCooldownDuration)
	{
		m_PlayerShootSound.play();
		_projectiles->push_back(new Bullet(m_Position, m_Direction, m_BulletSpeed, m_BulletRadius, m_Enemy));
		m_AttackCooldown.restart();
	}
}

void Player::SpecialAttack()
{
	switch (m_CurrentPickup)
	{
	case type_Laser:
		// Laser attack code goes here
		std::cout << m_Name << " used Laser!" << std::endl;
		break;

	case type_Knockback:
		// Knockback attack code goes here
		std::cout << m_Name << " used Knockback!" << std::endl;
		break;

	default:
		break;
	}
}

// Handles player input and movement
void Player::PlayerInput(std::vector<Bullet*>* _projectiles, sf::Keyboard::Key _shoot, sf::Keyboard::Key _up, sf::Keyboard::Key _down, sf::Keyboard::Key _left, sf::Keyboard::Key _right)
{
	float PlayerAngle = 0.0f;

	// Player Shoot
	if (sf::Keyboard::isKeyPressed(_shoot))
	{
		Shoot(_projectiles);
	}

	// PLAYER ROTATION AND MOVEMENT

	if (sf::Keyboard::isKeyPressed(_left))
	{
		PlayerAngle -= m_RotationSpeed;
	}
	if (sf::Keyboard::isKeyPressed(_right))
	{
		PlayerAngle += m_RotationSpeed;
	}

	// Set direction vector
	SetDirection(Utils::Rotate(m_Direction, PlayerAngle * (float)(3.1415926536 / 180)));
	// Rotate sprite
	m_Sprite->rotate(PlayerAngle);

	// If player can move equals true move
	if (m_CanMoveForward == true && sf::Keyboard::isKeyPressed(_up))
	{
		SetPosition(sf::Vector2f(m_Position + m_Direction * m_MoveSpeed));
	}
	if (m_CanMoveBack == true && sf::Keyboard::isKeyPressed(_down))
	{
		SetPosition(sf::Vector2f(m_Position + m_Direction * -m_MoveSpeed));
	}
}

void Player::Update(std::vector<Bullet*>* _projectiles, std::vector<Pickup*>* _pickups)
{
	if (m_CurrentPickup != type_None && m_PickupTimer.getElapsedTime().asSeconds() >= m_PickupTimerDuration)
	{
		SetPickup(type_None);
	}

	for (int i = 0; i < _pickups->size(); i++)
	{
		if (m_Sprite->getGlobalBounds().intersects(_pickups->at(i)->Shape.getGlobalBounds()))
		{
			SetPickup(_pickups->at(i)->Type);
			std::cout << _pickups->at(i)->Type; 

			delete _pickups->at(i);
			_pickups->erase(_pickups->begin() + i);
			i -= 1;

			break;
		}
	}
	
	int Counter = 0;
	for (Bullet* Projectile : *_projectiles)
	{
		if (Projectile->GetTarget() == this && Projectile->GetShape()->getGlobalBounds().intersects(m_Sprite->getGlobalBounds()))
		{
			m_PlayerHitSound.play();
			std::cout << "Hit " << m_Name << std::endl;
			if (m_HasCrown || (!m_HasCrown && !m_Enemy->HasCrown()))
			{
				m_PlayerCrownSwitchSound.play();
				SetCrown(false);
				m_Enemy->SetCrown(true);

				std::cout << m_Enemy->GetName() << " takes the Crown " << std::endl;
			}

			delete _projectiles->at(Counter);
			_projectiles->erase(_projectiles->begin() + Counter);
			Counter -= 1;
		}
		Counter += 1;
	}
}

void Player::XCollision(sf::FloatRect _objA, sf::FloatRect _objB)
{

}

void Player::MovePlayer(sf::Vector2f _velocity, std::vector<Tile*> _wallColl)
{
	// Current rect before movement
	sf::FloatRect CurrentRect = m_Sprite->getGlobalBounds();

	// Future rect IF movement was applied (Both X and Y)
	sf::FloatRect PredictedRect = sf::FloatRect(CurrentRect.left + _velocity.x, CurrentRect.top, CurrentRect.width, CurrentRect.height);

	while (CheckCollisionsPredictive(PredictedRect, _wallColl))
	{
		_velocity.x -= 0.1;
		PredictedRect = sf::FloatRect(CurrentRect.left + _velocity.x, CurrentRect.top, CurrentRect.width, CurrentRect.height);
	}
	
	PredictedRect = sf::FloatRect(CurrentRect.left, CurrentRect.top + _velocity.y, CurrentRect.width, CurrentRect.height);

	while (CheckCollisionsPredictive(PredictedRect, _wallColl))
	{
		_velocity.y -= 0.1;
		PredictedRect = sf::FloatRect(CurrentRect.left, CurrentRect.top + _velocity.y, CurrentRect.width, CurrentRect.height);
	}

	SetPosition(m_Position + _velocity);
}

bool Player::CheckCollisionsPredictive(sf::FloatRect _objA, std::vector<Tile*> _wallColl)
{
	for (auto i = 0; i < _wallColl.size(); i++)
	{
		if (_objA.intersects(_wallColl[i]->GetTile()->getGlobalBounds()))
		{
			return true;
		}
	}
	return false;
}

void Player::YCollision(sf::FloatRect _objA, sf::FloatRect _objB)
{
	if (_objA.intersects(_objB))
	{
		
	}
}

void Player::Render(sf::RenderWindow* _window)
{
	if (m_Sprite != nullptr)
	{
		if (m_HasCrown)
		{
			m_CrownSprite->setPosition(m_Position);
			_window->draw(*m_CrownSprite);
		}
		_window->draw(*m_Sprite);
	}

	_window->draw(*m_BoundingBoxShape);
}
