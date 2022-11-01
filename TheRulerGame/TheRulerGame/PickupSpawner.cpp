#include "PickupSpawner.h" 
#include <random>
#include <iostream>
#include <time.h>
#include "Utils.h" 

// Pickup spawner
void PickupSpawner::SpawnPickups() 
{
	if (m_SpawnClock.getElapsedTime().asSeconds() > m_PickupSpawnDelay && m_PickUpVector.size() < m_MaxPickUps)
	{
		Pickup* NewPickUp = new Pickup;
		srand(time(NULL)); 
		NewPickUp->Type = (PickupType)(rand() % 3);
		m_SpawnClock.restart();

		switch (NewPickUp->Type)
		{

		case type_Laser:
			NewPickUp->Shape = sf::CircleShape(15);
			NewPickUp->Shape.setFillColor(sf::Color(250, 150, 100)); //ORANGE
			break;

		case type_Knockback:
			NewPickUp->Shape = sf::CircleShape(15);
			NewPickUp->Shape.setFillColor(sf::Color(100, 250, 50)); //green
			break;

		case type_AttackSpeed:
			NewPickUp->Shape = sf::CircleShape(15);
			NewPickUp->Shape.setFillColor(sf::Color(100, 250, 200)); //green
		}

		NewPickUp->Shape.setPosition(rand() % Utils::WinSizeX + 1, rand() % Utils::WinSizeY + 1); 
		m_PickUpVector.push_back(NewPickUp);
	};
} 
	
void PickupSpawner::RenderPickups(sf::RenderWindow* window)
{
	for (Pickup* CurrentPickUp : m_PickUpVector) 
	{
		window->draw(CurrentPickUp->Shape);
	}
}



