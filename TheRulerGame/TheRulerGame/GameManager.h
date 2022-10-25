#pragma once
#include "UIManager.h"
#include <vector>

class GameManager
{
private:
	// Main render window
	sf::RenderWindow* m_Window = nullptr;
	// UI Manager
	UIManager* m_UIManager = nullptr;

	GameState m_GameState = GameState::MainMenu;
	GameState m_PreviousGameState = GameState::None;
	SceneManager m_SceneManager;

	// Contains all objects in the game
	std::vector<GameObject*> m_Objects = {};
	// Contains all projectiles in the game
	std::vector<Bullet*> m_Projectiles = {};

	// Player One
	Player* m_PlayerOne = nullptr;
	// Player Two
	Player* m_PlayerTwo = nullptr;

	float m_BaseMoveSpeed = 5.0f;
	float m_BaseFireDelay = 0.2f;
	// float m_PickupSpawnRate;
	float m_Volume = 100.0f;

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

	void ChangeGameState();

	// Handles all game update function 
	void Update();
	// Handles all game redering
	void Render();
};

