#include "SFML/Graphics.hpp"
#include <vector>

enum PickupType
 {
	type_Laser,
	type_Knockback,
	type_None
};

struct Pickup
{
	sf::CircleShape Shape; 
	PickupType Type; 
};

class PickupSpawner {
private:
	int m_MaxPickUps = 5;
	sf::Clock m_SpawnClock = sf::Clock();

public:
	std::vector<Pickup*> m_PickUpVector = {};
	float m_PickupSpawnDelay = 10;

	PickupSpawner();
	~PickupSpawner();

	void SpawnPickups(); 
	void RenderPickups(sf::RenderWindow* Window);
};