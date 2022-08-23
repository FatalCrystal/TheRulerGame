#pragma once
#include <cstdlib>.rand(); 
#include <SFML/Graphics.hpp>

enum PickUpType {

	type_Bomb, 
	type_Laser
};
class PickUps
{
	std::vector<PickUps> Vpickups; //container 
 
	sf::CircleShape shape;  //visual representation of the pickups for now 

public: 

	float SpawnTimer;
	float SpawnTimerMax;
	int MaxPickUps;

//	std::vector<PickUps> 
	
	void SpawnPickups(); 

	void RenderPickUps(sf::RenderWindow* _window);
	


	PickUps(); 

	~PickUps();

};

