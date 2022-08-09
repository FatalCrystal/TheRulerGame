#pragma once
#include "Utils.h"
#include "SFML/Window.hpp"

class GameMangar
{
private:
	// Main window render window
	sf::RenderWindow* m_Window;

	// Video mode for the main render window
	sf::VideoMode m_VideoMode;

public:

	// Constructor
	GameMangar();

	// Destructor
	~GameMangar();

	// Main SFML game loop
	void GameLoop();

	// Handles all game redering
	void Render();

	// Handles all game update function 
	void Update();
};

