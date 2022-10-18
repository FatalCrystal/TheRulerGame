#include "SFML/Graphics.hpp"
#include <vector>

enum PickupType
 {
	type_Laser, type_Knockback, type_None
};

struct PickUp //instance 
{
	sf::CircleShape Shape; 
	PickupType Type; 
};

class PickUpSpawn {

public: 
	sf::Clock SpawnClock; 
	void SpawnPickUps(); 
	  int MaxPickUps = 5; 
	  PickupType Type = type_None; //declared 
	  void RenderPickUps(sf::RenderWindow* Window); 
	  std::vector<PickUp*> PickUpVector; 

	//PickupType.Laser
};