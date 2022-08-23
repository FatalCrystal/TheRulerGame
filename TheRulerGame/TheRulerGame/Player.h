#pragma once
#include "GameObject.h"
#include "Bullet.h"

enum class Pickup
{
	None,
};

class Player : public GameObject
{
private:
	// Name of the player (for debug and UI)
	std::string m_Name = "Player";
	// Shape color
	sf::Color m_Color = sf::Color::White;
	Player* m_Enemy = nullptr;

	sf::Clock m_AttackCooldown = sf::Clock();
	float m_AttackCooldownDuration = 0.2f;

	// Direction the player is facing
	sf::Vector2f m_Direction = sf::Vector2f(0.0f, -1.0f);
	// Player movement velocity
	float m_MoveSpeed = 5.0f;
	// Player rotation speed
	float m_RotationSpeed = 3.0f;

	// Pickup currently held by the player (can be none)
	Pickup m_CurrentPickup = Pickup::None;
	// Whether or not the player is currently holding the crown
	bool m_HasCrown = false;

public:
	// Constructor with vector position
	Player(sf::Shape* _shape, sf::Vector2f _position, std::string _name, sf::Color _color);
	// Constructor with X and Y positions
	Player(sf::Shape* _shape, float _posX, float _posY, std::string _name, sf::Color _color);
	// Destructor
	~Player();

	// Set enemy
	void SetEnemy(Player* _enemy);
	// Set shape
	void SetShape(sf::Shape* _shape);
	// Set direction
	void SetDirection(sf::Vector2f _direction);
	// Set movement speed
	void SetMoveSpeed(float _moveSpeed);
	// Set rotation speed
	void SetRotationSpeed(float _rotationSpeed);
	// Set the current pickup held by the player (can be none)
	void SetPickup(Pickup _pickup);
	// Set whether or not the player holds the crown
	void SetCrown(bool _hasCrown);

	std::string GetName() const;
	// Return direction
	sf::Vector2f GetDirection() const;
	// Return movement speed
	float GetMoveSpeed() const;
	// Return rotation speed
	float GetRotationSpeed() const;
	// Return current pickup (can be none)
	Pickup GetPickup() const;
	// Return whether or not the player holds the crown
	bool HasCrown() const;

	void Shoot(std::vector<Bullet*>* _projectiles);
	void Update(std::vector<Bullet*>* _projectiles);
};

