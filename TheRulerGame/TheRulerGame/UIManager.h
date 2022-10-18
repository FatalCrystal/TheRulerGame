#pragma once
#include <vector>
#include "Player.h"
#include "GameState.h"
#include "Button.h"

class UIManager
{
public:
	// GameData struct holds data necessary to pass into button lambdas
	// GameManager will construct one from the relevant variables and pass it into SetCurrentDisplay() to give the function access to their values
	struct GameData
	{
		float* BaseMoveSpeed;
		float* BaseFireDelay;
		float* PickupSpawnRate;
		float* TimerLength;
		float* Volume;
		std::string WinnerText;

		// Constructor
		GameData(float* _baseMoveSpeed, float* _baseFireDelay, float* _pickupSpawnRate, float* _timerLength, float* _volume, std::string _winnerText)
		{
			BaseMoveSpeed = _baseMoveSpeed;
			BaseFireDelay = _baseFireDelay;
			PickupSpawnRate = _pickupSpawnRate;
			TimerLength = _timerLength;
			Volume = _volume;
			WinnerText = _winnerText;
		};
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

	// Game state as of the previous frame
	GameState m_PreviousState = GameState::None;

public:
	// Constructor
	UIManager();
	// Destructor
	~UIManager();

	// Set current UI display mode
	void UpdateDisplayState(GameState* _state, UIManager::GameData _gameData);

	// Populate m_Textures with textures loaded from image files
	void LoadTextures();
	// On mouse click, check mouse position against button rects and activate clicked button
	void PollButtons(sf::RenderWindow *_window);
	// Per-frame processes, runs every frame
	void Update(GameState* _state, UIManager::GameData _gameData, float _timeRemaining);
	// Draw all UI elements to the screen, runs every frame
	void Render(sf::RenderWindow* _window);
};

