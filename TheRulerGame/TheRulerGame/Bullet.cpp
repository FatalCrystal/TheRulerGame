 #include "Bullet.h"
#include <iostream>

Bullet::Bullet(sf::Vector2f _position, sf::Vector2f _direction, float _moveSpeed, float _bulletRadius, Player* _target) :
	m_BulletRadius(_bulletRadius), m_Direction(_direction), m_MoveSpeed(_moveSpeed), m_Target(_target) // Set bullet parameters
{
	// Create shape
	m_Shape = new sf::CircleShape(m_BulletRadius);
	// set origin in middle
	m_Shape->setOrigin(m_BulletRadius, m_BulletRadius);
	// Set the bullet position
	m_Shape->setPosition(_position);
}

Bullet::~Bullet()
{
	delete m_Shape;
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
