#pragma once
#include <vector>
#include "Button.h"

// UI display modes
enum class UIDisplay
{
	MainMenu,
	Gameplay,
	EndScreen,
	Options,
	None,
};

class UIManager
{
	// GameData struct holds data necessary to pass into button lambdas
	// GameManager will construct one from the relevant variables and pass it into SetCurrentDisplay() to give the function access to their values
	struct GameData
	{
		// Data needed for button lambdas goes here

		//Constructor
		GameData() {};
	};

private:
	// Vector containing all existing buttons
	std::vector<Button*> m_Buttons = {};
	// Vector containing all existing text labels
	std::vector<sf::Text*> m_TextLabels = {};
	
	// Font used for drawing text
	sf::Font m_Font = {};
	// Vector containing textures used for button sprites
	std::vector<sf::Texture> m_Textures = {};

	// Current UI display mode
	UIDisplay m_CurrentDisplay = UIDisplay::MainMenu;

public:
	// Constructor
	UIManager();
	// Destructor
	~UIManager();

	// Set current UI display mode
	void SetCurrentDisplay(UIDisplay _display, UIManager::GameData _gameData);

	// Return current UI display mode
	UIDisplay GetCurrentDisplay() const;

	// Populate m_Textures with textures loaded from image files
	void LoadTextures();
	// On mouse click, check mouse position against button rects and activate clicked button
	void PollButtons();
	// Per-frame processes, runs every frame
	void Update(float _timeRemaining);
	// Draw all UI elements to the screen, runs every frame
	void Render(sf::RenderWindow* _window);
};

