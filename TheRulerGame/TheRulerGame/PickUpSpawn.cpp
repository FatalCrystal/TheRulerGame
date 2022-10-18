#include "PickUpSpawn.H" 
#include <random>
#include <iostream>
#include <time.h>
#include "Utils.h" 
// a spawner that spawns 3 different shapes on the map 

void PickUpSpawn::SpawnPickUps() {


	if (SpawnClock.getElapsedTime().asSeconds() > 10 && PickUpVector.size() < 5) {
		PickUp* NewPickUp = new PickUp;
		srand(time(NULL)); 
		NewPickUp->Type = (PickupType)(rand() % 2);
		std::cout << "hgi"; 
		SpawnClock.restart(); 

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
		}
		NewPickUp->Shape.setPosition(rand() % Utils::WinSizeX + 1, rand() % Utils::WinSizeY + 1); 
		PickUpVector.push_back(NewPickUp);




	};
} 
	
void PickUpSpawn::RenderPickUps(sf::RenderWindow* window)
{
	for (PickUp* CurrentPickUp : PickUpVector) {
		window->draw(CurrentPickUp->Shape);

	}
}


