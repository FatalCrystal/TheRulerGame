#include "Player.h"

Player::Player(std::string _spritePath, sf::Vector2f _position, std::string _name)
{
	m_Texture.loadFromFile("Resources/Textures/" + _spritePath);
	SetSprite(new sf::Sprite(m_Texture));
	SetAudio();
	SetPosition(_position);
	m_Name = _name;
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

void Player::SetPickup(Pickup _pickup)
{
	m_CurrentPickup = _pickup;
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

Pickup Player::GetPickup() const
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

void Player::Update(std::vector<Bullet*>* _projectiles)
{
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
		_window->draw(*m_Sprite);
	}
}
