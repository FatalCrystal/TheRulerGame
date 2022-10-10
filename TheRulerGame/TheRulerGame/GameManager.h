#pragma once
#include "Bullet.h"
#include "Player.h"
#include "UIManager.h"
#include "SceneManager.h"
#include <vector>

class GameManager
{
private:
	// Main render window
	sf::RenderWindow* m_Window = nullptr;
	// UI Manager
	UIManager* m_UIManager = nullptr;

	SceneManager sceneManager;

	// Contains all objects in the game
	std::vector<GameObject*> m_Objects = {};
	// Contains all projectiles in the game
	std::vector<Bullet*> m_Projectiles = {};

	// Player One
	Player* m_PlayerOne = nullptr;
	// Player Two
	Player* m_PlayerTwo = nullptr;

	// Time elapsed between each frame
	float m_DeltaTime = 0.0f;

	// Total duration of game timer
	float m_TimerLength = 60;
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

