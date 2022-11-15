#include "PickupSpawner.h" 
#include <random>
#include <iostream>
#include <time.h>
#include "Utils.h" 

// Pickup spawner
void PickupSpawner::SpawnPickups(std::vector<Tile*>Walls)
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

		case type_Bomb:
			NewPickUp->Shape = sf::CircleShape(15);
			NewPickUp->Shape.setFillColor(sf::Color::Red); //red 
			break;

		case type_AttackSpeed:
			NewPickUp->Shape = sf::CircleShape(15);
			NewPickUp->Shape.setFillColor(sf::Color(100, 250, 20)); //green
			break;
		case type_Knockback:
			NewPickUp->Shape = sf::CircleShape(15);
			NewPickUp->Shape.setFillColor(sf::Color(100, 250, 50)); //green
			break;

		default: 
			break; 
		} 

		NewPickUp->Shape.setOrigin(NewPickUp->Shape.getRadius() / 2, NewPickUp->Shape.getRadius() / 2); 
		sf::Vector2f Position = sf::Vector2f(rand() % Utils::WinSizeX + 1, rand() % Utils::WinSizeY + 1);
		while (IntersectsWalls(Walls, Position, NewPickUp)) {
			Position = sf::Vector2f(rand() % Utils::WinSizeX + 1, rand() % Utils::WinSizeY + 1);
		}
		NewPickUp->Shape.setPosition(Position);
		m_PickUpVector.push_back(NewPickUp);
	};
}

bool PickupSpawner::IntersectsWalls(std::vector<Tile*> Walls, sf::Vector2f Position, Pickup* pickup)
{
	for (int i = 0; i < Walls.size(); i++)
	{
		if (Walls[i]->GetTile()->getGlobalBounds().contains(Position) || 
			Walls[i]->GetTile()->getGlobalBounds().contains(Position.x + pickup->Shape.getGlobalBounds().width, Position.y) ||
			Walls[i]->GetTile()->getGlobalBounds().contains(Position.x - pickup->Shape.getGlobalBounds().width, Position.y) ||
			Walls[i]->GetTile()->getGlobalBounds().contains(Position.x + pickup->Shape.getGlobalBounds().width, Position.y - pickup->Shape.getGlobalBounds().height) ||
			Walls[i]->GetTile()->getGlobalBounds().contains(Position.x - pickup->Shape.getGlobalBounds().width, Position.y + pickup->Shape.getGlobalBounds().height) ||
			Walls[i]->GetTile()->getGlobalBounds().contains(Position.x, Position.y + pickup->Shape.getGlobalBounds().height) ||
			Walls[i]->GetTile()->getGlobalBounds().contains(Position.x, Position.y - pickup->Shape.getGlobalBounds().height)) {
			
			printf("true");
			return true; 
		}
	}
	printf("false");
	return false;
}



void PickupSpawner::RenderPickups(sf::RenderWindow* window)
{
	for (Pickup* CurrentPickUp : m_PickUpVector) 
	{
		window->draw(CurrentPickUp->Shape);
	}
}



