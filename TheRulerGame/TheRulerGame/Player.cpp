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

void Player::SetDirection(sf::Vector2f _direction)
{
	m_Direction = _direction;
}

void Player::SetMoveSpeed(float _moveSpeed)
{
	m_MoveSpeed = _moveSpeed;
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
}

sf::Vector2f Player::GetDirection() const
{
	return m_Direction;
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
