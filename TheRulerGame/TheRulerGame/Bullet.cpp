#include "Bullet.h"
#include <iostream>

Bullet::Bullet(sf::Vector2f _position, sf::Vector2f _direction, float _moveSpeed, Player* _target)
{
	m_Shape = new sf::CircleShape(5);
	m_Direction = _direction;
	m_MoveSpeed = _moveSpeed;
	m_Shape->setOrigin(5, 5);
	m_Shape->setPosition(_position);
	m_Target = _target;
}

Bullet::~Bullet()
{
}

Player* Bullet::GetTarget() const
{
	return m_Target;
}

sf::Shape* Bullet::GetShape()
{
	return m_Shape;
}


void Bullet::Update()
{
	m_Shape->move(m_MoveSpeed * m_Direction);
}

void Bullet::Render(sf::RenderTarget* _window)
{
	_window->draw(*m_Shape);
}
