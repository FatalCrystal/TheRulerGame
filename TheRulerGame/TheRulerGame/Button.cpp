#include "Button.h"

Button::Button(sf::Sprite* _sprite, sf::Vector2f _position, std::function<void()> _onClick)
{
	SetSprite(_sprite);
	SetPosition(_position);
	m_OnClick = _onClick;
}

Button::Button(sf::Sprite* _sprite, float _posX, float _posY, std::function<void()> _onClick)
{
	SetSprite(_sprite);
	SetPosition(_posX, _posY);
	m_OnClick = _onClick;
}

Button::~Button()
{
}

void Button::SetPosition(sf::Vector2f _position)
{
	m_Position = _position;
	
	if (m_Sprite != nullptr)
	{
		m_Sprite->setPosition(m_Position);
	}
}

void Button::SetPosition(float _posX, float _posY)
{
	m_Position = sf::Vector2f(_posX, _posY);

	if (m_Sprite != nullptr)
	{
		m_Sprite->setPosition(m_Position);
	}
}

void Button::SetSprite(sf::Sprite* _sprite)
{
	m_Sprite = _sprite;

	if (m_Sprite != nullptr)
	{
		m_Sprite->setOrigin(m_Sprite->getGlobalBounds().width / 2, m_Sprite->getGlobalBounds().height / 2);
	}
}

sf::Vector2f Button::GetPosition() const
{
	return m_Position;
}

sf::Sprite* Button::GetSprite() const
{
	return m_Sprite;
}

void Button::ActivateOnClick()
{
	m_OnClick();
}

void Button::Render(sf::RenderWindow* _window)
{
	if (m_Sprite != nullptr)
	{
		_window->draw(*m_Sprite);
	}
}
