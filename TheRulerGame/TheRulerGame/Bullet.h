#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Player;

class Bullet
{
private:
	// Shape
	sf::Shape* m_Shape;
	// Player that can be damaged by the bullet
	Player* m_Target;
	// Movement direction
	sf::Vector2f m_Direction;
	// Movement Speed
	float m_MoveSpeed;
	// Bullet size
	float m_BulletRadius;

public:
	// Constructor
	Bullet(sf::Vector2f _position, sf::Vector2f _direction, float _moveSpeed, float _bulletRadius, Player* _target);
	// Destructor
	~Bullet();

	// Return Target
	Player* GetTarget() const { return m_Target; };
	// Return the shape of the bullet
	sf::Shape* GetShape();

	// Per-frame processing, runs every frame
	void Update();
	// Render shape to screen, runs every frame
	void Render(sf::RenderTarget* _window);
};

