#pragma once
#include "Player.h"
#include <vector>

class GameManager
{
private:
	// Main render window
	sf::RenderWindow* m_Window = nullptr;

	// Contains all objects in the game
	std::vector<GameObject*> m_Objects = {};
	Player* m_PlayerOne = nullptr;
	Player* m_PlayerTwo = nullptr;

	// Time elapsed between each frame
	float m_DeltaTime = 0.0f;

	// Measures time elapsed since game start
	sf::Clock m_GameClock = sf::Clock();
	// Measures time elapsed since last frame
	sf::Clock m_FrameClock = sf::Clock();

public:
	// Constructor
	GameManager();
	// Destructor
	~GameManager();

	// Main SFML game loop
	void GameLoop();
	// Handles keyboard input for both players
	void PlayerInput();

	// Handles all game update function 
	void Update();
	// Handles all game redering
	void Render();
};

