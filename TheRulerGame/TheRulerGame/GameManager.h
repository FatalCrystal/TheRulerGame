#pragma once
#include "Bullet.h"
#include "Player.h"
#include <vector>

class GameManager
{
private:
	// Main render window
	sf::RenderWindow* m_Window = nullptr;

	// Contains all objects in the game
	std::vector<GameObject*> m_Objects = {};
	std::vector<Bullet*> m_ProjectilesOne;
	std::vector<Bullet*> m_ProjectilesTwo;

	Player* m_PlayerOne = nullptr;
	Player* m_PlayerTwo = nullptr;

	// Time elapsed between each frame
	float m_DeltaTime = 0.0f;

	float m_AttackCDOne;
	float m_AttackCDMaxOne = 10.f;

	float m_AttackCDTwo;
	float m_AttackCDMaxTwo = 10.f;

	float m_BulletSpeed = 10;

	sf::Vector2f m_AttackDirOne = sf::Vector2f(0.f, -1.f);
	sf::Vector2f m_AttackDirTwo = sf::Vector2f(0.f, -1.f);

	bool m_CanAttackOne;
	bool m_CanAttackTwo;

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

