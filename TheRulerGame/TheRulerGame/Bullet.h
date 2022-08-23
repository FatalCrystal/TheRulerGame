#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Player;

class Bullet
{
private:
	// Shape
	sf::CircleShape* m_Shape;
	// Player that can be damaged by the bullet
	Player* m_Target;
	// Movement direction
	sf::Vector2f m_Direction;
	// Movement Speed
	float m_MoveSpeed;

public:
	// Constructor
	Bullet(sf::Vector2f _position, sf::Vector2f _direction, float _moveSpeed, Player* _target);
	// Destructor
	~Bullet();

	// Return Target
	Player* GetTarget() const;

	// Per-frame processing, runs every frame
	void Update();
	// Render shape to screen, runs every frame
	void Render(sf::RenderTarget* _window);
};

