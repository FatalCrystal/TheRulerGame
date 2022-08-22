#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

class Button
{
private:
	// Button position in screen space (affects position of sprite)
	sf::Vector2f m_Position = sf::Vector2f(0.0f, 0.0f);
	// Button's visual representation on the screen
	sf::Sprite* m_Sprite = nullptr;
	// The function called when the button is clicked by the user
	std::function<void()> m_OnClick = []() {};

public:
	// Constructor (vector position)
	Button(sf::Sprite* _sprite, sf::Vector2f _position, std::function<void()> _onClick);
	// Constructor (loose positions)
	Button(sf::Sprite* _sprite, float _posX, float _posY, std::function<void()> _onClick);
	// Destructor
	~Button();

	// Set position with vector, also affects sprite position
	void SetPosition(sf::Vector2f _position);
	// Set position with floats, also affects sprite position
	void SetPosition(float _posX, float _posY);
	// Set Sprite by pointer
	void SetSprite(sf::Sprite* _sprite);

	// Return position
	sf::Vector2f GetPosition() const;
	// Return sprite pointer
	sf::Sprite* GetSprite() const;

	// Activates the button's OnClick function
	void ActivateOnClick();

	// Renders the button to the window, runs every frame
	void Render(sf::RenderWindow* _window);

};

