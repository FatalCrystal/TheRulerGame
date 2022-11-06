#include "SceneManager.h"
#include <vector>

// Enum to hold different pickup states
enum PickupType
 {
	type_Laser,
	type_AttackSpeed,
	type_Bomb,
	type_Knockback,
	type_None
};

// Struct to determine base pickup parameters
struct Pickup
{
	// Pickup shape
	sf::CircleShape Shape;
	// Pickup type
	PickupType Type; 
};

class PickupSpawner {
private:
	// How many pickups allowed on screen
	int m_MaxPickUps = 5;

	sf::Clock m_SpawnClock = sf::Clock();

public:
	// Vector to hold spawned pickups
	std::vector<Pickup*> m_PickUpVector = {};
	// Delay between pickup spawn
	float m_PickupSpawnDelay = 10;

	PickupSpawner() {};
	~PickupSpawner() {};

	void SpawnPickups(std::vector<Tile*>Walls); 
	bool IntersectsWalls(std::vector<Tile*>Walls, sf::Vector2f Position);
	void SetSpawnAmount(float _spawnAmount) { m_MaxPickUps = _spawnAmount; };
	void RenderPickups(sf::RenderWindow* Window);

	void fKnockback();

};