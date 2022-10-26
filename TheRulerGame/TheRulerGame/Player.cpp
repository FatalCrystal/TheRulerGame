#include "Player.h"

Player::Player(std::string _spritePath, sf::Vector2f _position, std::string _name)
{
	m_Texture.loadFromFile("Resources/Textures/" + _spritePath);
	SetSprite(new sf::Sprite(m_Texture));

	m_CrownTexture.loadFromFile("Resources/Textures/Crown.png");
	m_CrownSprite = new sf::Sprite(m_CrownTexture);
	m_CrownSprite->setOrigin(m_CrownSprite->getGlobalBounds().width / 2, m_CrownSprite->getGlobalBounds().height / 2);

	SetAudio();
	SetPosition(_position);
	m_Name = _name;
	
	m_BoundingBoxShape = new sf::RectangleShape();
}

Player::~Player()
{
}

void Player::SetEnemy(Player* _enemy)
{
	m_Enemy = _enemy;
}

void Player::SetSprite(sf::Sprite* _sprite)
{
	m_Sprite = _sprite;
	m_Sprite->setOrigin(m_Sprite->getGlobalBounds().width / 2, m_Sprite->getGlobalBounds().height / 2);
}

void Player::SetPosition(sf::Vector2f _position)
{
	m_Position = _position;

	if (m_Sprite != nullptr)
	{
		m_Sprite->setPosition(m_Position);
	}
}

void Player::SetDirection(sf::Vector2f _direction)
{
	m_Direction = _direction;
}

void Player::SetMoveSpeed(float _moveSpeed)
{
	m_MoveSpeed = _moveSpeed;
}

void Player::SetAttackCooldown(float _attackCooldown)
{
	m_AttackCooldownDuration = _attackCooldown;
}

void Player::SetRotationSpeed(float _rotationSpeed)
{
	m_RotationSpeed = _rotationSpeed;
}

void Player::SetPickup(PickupType _pickup)
{
	m_CurrentPickup = _pickup;
	m_PickupTimer.restart();
}

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

void Player::SetAudio()
{
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

	m_PlayerShootSound.setBuffer(m_PlayerShootSB);
	m_PlayerHitSound.setBuffer(m_PlayerHitSB);
	m_PlayerCrownSwitchSound.setBuffer(m_PlayerCrownSwitchSB);
	m_PlayerPickUpSound.setBuffer(m_PlayerPickUpSB);
}

void Player::WallCollisions(SceneManager _scene, sf::RenderWindow* _window)
{
	bool colliding = false;

	m_PlayerBoundingBox = m_Sprite->getGlobalBounds();

	m_BoundingBoxShape->setSize(sf::Vector2f(25, 25));
	m_BoundingBoxShape->setFillColor(sf::Color::Transparent);
	m_BoundingBoxShape->setPosition(GetPosition().x - m_Sprite->getTextureRect().width / 2, GetPosition().y - m_Sprite->getTextureRect().height / 2);

	
	m_PlayerNextPos = m_BoundingBoxShape->getGlobalBounds();
	m_PlayerNextPos.left += m_Direction.x;
	m_PlayerNextPos.top += m_Direction.y;

	

	for (auto &wall : _scene.GetWalls())
	{
		sf::FloatRect wallBounds = wall->GetTile()->getGlobalBounds();

		if (!colliding)
		{
			m_CanMoveForward = true;
			m_CanMoveBack = true;
		}

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
	}
}

sf::Sprite* Player::GetSprite() const
{
	return m_Sprite;
}

std::string Player::GetName() const
{
	return m_Name;
}

sf::Vector2f Player::GetDirection() const
{
	return m_Direction;
}

sf::Sound Player::GetPickUpSound() const
{
	return m_PlayerPickUpSound;
}

sf::Sound Player::GetHitSound() const
{
	return m_PlayerHitSound;
}

float Player::GetMoveSpeed() const
{
	return m_MoveSpeed;
}

float Player::GetRotationSpeed() const
{
	return m_RotationSpeed;
}

PickupType Player::GetPickup() const
{	
	return m_CurrentPickup;
}

bool Player::HasCrown() const
{
	return m_HasCrown;
}

void Player::Shoot(std::vector<Bullet*>* _projectiles)
{
	if (m_AttackCooldown.getElapsedTime().asSeconds() > m_AttackCooldownDuration)
	{
		m_PlayerShootSound.play();
		_projectiles->push_back(new Bullet(m_Position, m_Direction, 10.0f, m_Enemy));
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

void Player::PlayerInput(std::vector<Bullet*>* _projectiles, sf::Keyboard::Key _shoot, sf::Keyboard::Key _up, sf::Keyboard::Key _down, sf::Keyboard::Key _left, sf::Keyboard::Key _right)
{
	float PlayerAngle = 0.0f;

	// Player one Shoot
	if (sf::Keyboard::isKeyPressed(_shoot))
	{
		Shoot(_projectiles);
	}

	// PLAYER ONE ROTATION AND MOVEMENT

	if (sf::Keyboard::isKeyPressed(_left))
	{
		PlayerAngle -= m_RotationSpeed;
	}
	if (sf::Keyboard::isKeyPressed(_right))
	{
		PlayerAngle += m_RotationSpeed;
	}

	SetDirection(Utils::Rotate(m_Direction, PlayerAngle * (float)(3.1415926536 / 180)));
	m_Sprite->rotate(PlayerAngle);

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

	std::cout << m_Sprite->getRotation() << std::endl;
	
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
