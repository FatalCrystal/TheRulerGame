#pragma once
#include "Bullet.h"
#include "Player.h"
#include "UIManager.h"
#include <vector>

class GameManager
{
private:
	// Main render window
	sf::RenderWindow* m_Window = nullptr;
	// UI Manager
	UIManager* m_UIManager = nullptr;

	// Contains all objects in the game
	std::vector<GameObject*> m_Objects = {};
	std::vector<Bullet*> m_ProjectilesOne;
	std::vector<Bullet*> m_ProjectilesTwo;

	Player* m_PlayerOne = nullptr;
	Player* m_PlayerTwo = nullptr;

	// Time elapsed between each frame
	float m_DeltaTime = 0.0f;

	sf::Clock m_AttackCDOne;
	sf::Int32 m_AttackCDMaxOne = 200;

	sf::Clock m_AttackCDTwo;
	sf::Int32 m_AttackCDMaxTwo = 200;

	float m_BulletSpeed = 10;

	bool m_CanAttackOne;
	bool m_CanAttackTwo;

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

