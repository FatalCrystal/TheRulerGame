#include "GameObject.h"

GameObject::GameObject(sf::Shape* _shape, sf::Vector2f _position)
{
	SetShape(_shape);
	SetPosition(_position);
}

GameObject::GameObject(sf::Shape* _shape, float _posX, float _posY)
{
	SetShape(_shape);
	SetPosition(sf::Vector2f(_posX, _posY));
}

GameObject::~GameObject()
{
	delete m_Shape;
}

void GameObject::SetPosition(sf::Vector2f _position)
{
	m_Position = _position;

	if (m_Shape != nullptr)
	{
		m_Shape->setPosition(m_Position);
	}
}

void GameObject::SetShape(sf::Shape* _shape)
{
	m_Shape = _shape;
	m_Shape->setOrigin(m_Shape->getGlobalBounds().width / 2, m_Shape->getGlobalBounds().height / 2);
}

void GameObject::Render(sf::RenderWindow* _window)
{
	if (m_Shape != nullptr)
	{
		_window->draw(*m_Shape);
	}
}


