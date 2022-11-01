#pragma once
#include "GameObject.h"
#include "Bullet.h"
#include "SFML/Audio.hpp"
#include "PickupSpawner.h"
#include "SceneManager.h"

class Player : public GameObject
{
private:
	// Name of the player (for debug and UI)
	std::string m_Name = "Player";
	sf::Texture m_Texture;
	sf::Texture m_CrownTexture;
	
	sf::Sprite* m_Sprite;
	sf::Sprite* m_CrownSprite;
	
	// Shape used for player bounding box
	sf::RectangleShape* m_BoundingBoxShape;
	
	// The other player
	Player* m_Enemy = nullptr;
	
	// Clock to track attack cooldown
	sf::Clock m_AttackCooldown;
	// Duration of attack cooldown
	float m_AttackCooldownDuration = 1.f;

	// Hold player next position bounding box
	sf::FloatRect m_PlayerNextPos;
	// Holds player current bounding box
	sf::FloatRect m_PlayerBoundingBox;

	// Direction the player is facing
	sf::Vector2f m_Direction = sf::Vector2f(0.0f, -1.0f);
	// Player movement velocity
	float m_MoveSpeed = 5.0f;
	// Player rotation speed
	float m_RotationSpeed = 3.0f;

	// Pickup currently held by the player (can be none)
	PickupType m_CurrentPickup = type_None; 
	// Timer which counts down to pickup disappearing
	sf::Clock m_PickupTimer = sf::Clock();
	// Duration of Pickup Timer
	float m_PickupTimerDuration = 10.0f;
	// Whether or not the player is currently holding the crown
	bool m_HasCrown = false;
	// Whether or not the player can move
	bool m_CanMoveForward = true;
	bool m_CanMoveBack = true;

	// Bullet size
	float m_BulletRadius = 5.f;
	// Bullet speed
	float m_BulletSpeed = 10.f;

	// Load sound data for shooting
	sf::Sound m_PlayerShootSound;
	sf::Sound m_PlayerHitSound;
	sf::Sound m_PlayerCrownSwitchSound;
	sf::Sound m_PlayerPickUpSound;

	sf::SoundBuffer m_PlayerShootSB;
	sf::SoundBuffer m_PlayerHitSB;
	sf::SoundBuffer m_PlayerCrownSwitchSB;
	sf::SoundBuffer m_PlayerPickUpSB;

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
	void SetPickup(PickupType _pickup);
	// Set whether or not the player holds the crown
	void SetCrown(bool _hasCrown);
	// Initializes audio data
	void SetAudio();
	// Wall collisions
	void WallCollisions(SceneManager _scene, sf::RenderWindow* _window, std::vector<Bullet*>* _projectiles);

	// Return sprite pointer
	sf::Sprite* GetSprite() const { return m_Sprite; };
	// Return name
	std::string GetName() const { return m_Name; };
	// Return direction
	sf::Vector2f GetDirection() const { return m_Direction; };
	// Return item pickup sound
	sf::Sound GetPickUpSound() const { return m_PlayerPickUpSound; };
	// Return Hit sound
	sf::Sound GetHitSound() const { return m_PlayerHitSound; };
	// Return movement speed
	float GetMoveSpeed() const { return m_MoveSpeed; };
	// Return rotation speed
	float GetRotationSpeed() const { return m_RotationSpeed; };
	// Return current pickup (can be none)
	PickupType GetPickup() const { return m_CurrentPickup; };
	// Return whether or not the player holds the crown
	bool HasCrown() const { return m_HasCrown; };

	// Fire a projectile
	void Shoot(std::vector<Bullet*>* _projectiles);
	
	// Use special attack
	void SpecialAttack();
	void PlayerInput(std::vector<Bullet*>* _projectiles, sf::Keyboard::Key _shoot, sf::Keyboard::Key _up, sf::Keyboard::Key _special, sf::Keyboard::Key _left, sf::Keyboard::Key _right);
	// Per-frame processing, runs every frame (after object update)
	void Update(std::vector<Bullet*>* _projectiles, std::vector<Pickup*>* _pickups);
	// Renders the object to the window, runs every frame
	void Render(sf::RenderWindow* _window);
};

