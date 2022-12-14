#pragma once
#include <SFML/Graphics.hpp>
#include "Utils.h"

class GameObject
{
protected:
	// Object position in screen space (affects position of shape)
	sf::Vector2f m_Position = sf::Vector2f(0.0f, 0.0f);
	// Object's visual representation on the screen
	sf::Shape* m_Shape = nullptr;

public:
	// Default constructor
	GameObject() {};
	// Constructor with vector position
	GameObject(sf::Shape* _shape, sf::Vector2f _position);
	// Constructor with X and Y positions
	GameObject(sf::Shape* _shape, float _posX, float _posY);
	// Destructor
	~GameObject();

	// Set position with vector, also affects shape position
	void SetPosition(sf::Vector2f _position);
	// Set Shape by pointer, origin is automatically centered
	void SetShape(sf::Shape* _shape);

	// Return position
	sf::Vector2f GetPosition() const { return m_Position; };
	// Return shape pointer
	sf::Shape* GetShape() const { return m_Shape; };

	// Renders the object to the window, runs every frame
	void Render(sf::RenderWindow* _window);
};

