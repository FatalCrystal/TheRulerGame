#pragma once
#include "GameObject.h"

enum class Pickup
{
	None,
};

class Player : public GameObject
{
private:
	std::string m_Name = "Player";
	float m_MoveSpeed = 5.0f;

	Pickup m_CurrentPickup = Pickup::None;
	bool m_HasCrown = false;

public:
	// Constructor with vector position
	Player(sf::Shape* _shape, sf::Vector2f _position, std::string _name, sf::Color _color);
	// Constructor with X and Y positions
	Player(sf::Shape* _shape, float _posX, float _posY, std::string _name, sf::Color _color);
	// Destructor
	~Player();

	// Set movement speed
	void SetMoveSpeed(float _moveSpeed);
	// Set the current pickup held by the player (can be none)
	void SetPickup(Pickup _pickup);
	// Set whether or not the player holds the crown
	void SetCrown(bool _hasCrown);

	// Return movement speed
	float GetMoveSpeed() const;
	// Return current pickup (can be none)
	Pickup GetPickup() const;
	// Return whether or not the player holds the crown
	bool HasCrown() const;
};

