#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Bullet
{
private:
	sf::CircleShape bullet;

	sf::Vector2f moveDirection;

	float moveSpeed;

public:
	Bullet(float _posX, float _posY, float _moveDirX, float _moveDirY, float _moveSpeed);
	~Bullet();

	const sf::FloatRect GetBounds() const;

	void Update();
	void Render(sf::RenderTarget* _window);
};

