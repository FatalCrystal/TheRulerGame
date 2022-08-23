#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Player;

class Bullet
{
private:
	// Shape
	sf::Shape* m_Shape = nullptr;
	// Player that can be damaged by the bullet
	Player* m_Target = nullptr;
	// Movement direction
	sf::Vector2f m_Direction = {};
	// Movement Speed
	float m_MoveSpeed = 0.0f;

public:
	// Constructor
	Bullet(sf::Vector2f _position, sf::Vector2f _direction, float _moveSpeed, Player* _target);
	// Destructor
	~Bullet();

	// Return Target
	Player* GetTarget() const;
	sf::Shape* GetShape();

	// Per-frame processing, runs every frame
	void Update();
	// Render shape to screen, runs every frame
	void Render(sf::RenderTarget* _window);
};

