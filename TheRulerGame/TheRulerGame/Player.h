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
	sf::Texture m_Texture;
	sf::Sprite* m_Sprite;
	// The other player
	Player* m_Enemy = nullptr;

	// Clock to track attack cooldown
	sf::Clock m_AttackCooldown = sf::Clock();
	// Duration of attack cooldown
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
	Player(std::string _spritePath, sf::Vector2f _position, std::string _name);
	// Destructor
	~Player();

	// Set enemy
	void SetEnemy(Player* _enemy);
	// Set shape
	void SetSprite(sf::Sprite* _sprite);
	// Set position
	void SetPosition(sf::Vector2f _position);
	// Set direction
	void SetDirection(sf::Vector2f _direction);
	// Set movement speed
	void SetMoveSpeed(float _moveSpeed);
	// Set attack cooldown duration
	void SetAttackCooldown(float _attackCooldown);
	// Set rotation speed
	void SetRotationSpeed(float _rotationSpeed);
	// Set the current pickup held by the player (can be none)
	void SetPickup(Pickup _pickup);
	// Set whether or not the player holds the crown
	void SetCrown(bool _hasCrown);

	// Return sprite pointer
	sf::Sprite* GetSprite() const;
	// Return name
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

	// Fire a projectile
	void Shoot(std::vector<Bullet*>* _projectiles);
	// Per-frame processing, runs every frame (after object update)
	void Update(std::vector<Bullet*>* _projectiles);
	// Renders the object to the window, runs every frame
	void Render(sf::RenderWindow* _window);
};

