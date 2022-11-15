#include "PickupSpawner.h" 
#include <random>
#include <iostream>
#include <time.h>
#include "Utils.h" 

PickupSpawner::PickupSpawner()
{
	m_AttackSpeedTexture.loadFromFile("Resources/Textures/AttackSpeed.png");
	m_LaserTexture.loadFromFile("Resources/Textures/Laser.png");
	m_KnockbackTexture.loadFromFile("Resources/Textures/Knockback.png");
	m_BombTexture.loadFromFile("Resources/Textures/Bomb.png");
}

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
			NewPickUp->Sprite = sf::Sprite(m_LaserTexture);
			NewPickUp->Sprite.setOrigin(0.5f, 0.5f);
			break;

		case type_Bomb:
			NewPickUp->Sprite = sf::Sprite(m_BombTexture);
			NewPickUp->Sprite.setOrigin(0.5f, 0.5f);
			break;

		case type_AttackSpeed:
			NewPickUp->Sprite = sf::Sprite(m_AttackSpeedTexture);
			NewPickUp->Sprite.setOrigin(0.5f, 0.5f);
			break;
		case type_Knockback:
			NewPickUp->Sprite = sf::Sprite(m_KnockbackTexture);
			NewPickUp->Sprite.setOrigin(0.5f, 0.5f);
			break;

		default: 
			break; 
		} 

		sf::Vector2f Position = sf::Vector2f(rand() % Utils::WinSizeX + 1, rand() % Utils::WinSizeY + 1);
		while (IntersectsWalls(Walls, Position)) {
			Position = sf::Vector2f(rand() % Utils::WinSizeX + 1, rand() % Utils::WinSizeY + 1);
		}
		NewPickUp->Sprite.setPosition(rand() % Utils::WinSizeX + 1, rand() % Utils::WinSizeY + 1); 
		m_PickUpVector.push_back(NewPickUp);
	};
}
bool PickupSpawner::IntersectsWalls(std::vector<Tile*> Walls, sf::Vector2f Position)
{
	for (int i = 0; i < Walls.size(); i++)
	{
		if (Walls[i]->GetTile()->getGlobalBounds().contains(Position)) {

			return true; 
		}
	}

	return false;
}



void PickupSpawner::RenderPickups(sf::RenderWindow* window)
{
	for (Pickup* CurrentPickUp : m_PickUpVector) 
	{
		window->draw(CurrentPickUp->Sprite);
	}
}