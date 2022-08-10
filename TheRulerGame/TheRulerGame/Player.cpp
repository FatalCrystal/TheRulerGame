#include "Player.h"

Player::Player(sf::Shape* _shape, sf::Vector2f _position, std::string _name, sf::Color _color)
{
	SetShape(_shape);
	SetPosition(_position);
	m_Name = _name;
	m_Shape->setFillColor(_color);
}

Player::Player(sf::Shape* _shape, float _posX, float _posY, std::string _name, sf::Color _color)
{
	SetShape(_shape);
	SetPosition(_posX, _posY);
	m_Name = _name;
	m_Shape->setFillColor(_color);
}

Player::~Player()
{
}

void Player::SetMoveSpeed(float _moveSpeed)
{
	m_MoveSpeed = _moveSpeed;
}

void Player::SetPickup(Pickup _pickup)
{
	m_CurrentPickup = _pickup;
}

void Player::SetCrown(bool _hasCrown)
{
	m_HasCrown = _hasCrown;
}

float Player::GetMoveSpeed() const
{
	return m_MoveSpeed;
}

Pickup Player::GetPickup() const
{
	return m_CurrentPickup;
}

bool Player::HasCrown() const
{
	return m_HasCrown;
}
