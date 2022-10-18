#include "PickUpSpawn.H" 
#include <random>
#include <iostream>
#include <time.h>
#include "Utils.h" 
// a spawner that spawns 3 different shapes on the map 

void PickUpSpawn::SpawnPickUps() {


	if (SpawnClock.getElapsedTime().asSeconds() > 10 && PickUpVector.size() < 5) { //if 10 seconds have paased and less than 5 pickups on screen
		PickUp* NewPickUp = new PickUp;     //make a new pickup 
		srand(time(NULL)); 
		NewPickUp->Type = (PickupType)(rand() % 2);      //randomize the pickup 
		std::cout << "it works fart";  // check 
		SpawnClock.restart();     //restart clock 

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

		case type_AOE:
			NewPickUp->Shape = sf::CircleShape(15);
			NewPickUp->Shape.setFillColor(sf::Color(255, 0, 0)); //green 





			break;
		}
		NewPickUp->Shape.setPosition(rand() % Utils::WinSizeX + 1, rand() % Utils::WinSizeY + 1);  //ON The screen m ap 
		PickUpVector.push_back(NewPickUp);




	};
} 
	
void PickUpSpawn::RenderPickUps(sf::RenderWindow* window)
{
	for (PickUp* CurrentPickUp : PickUpVector) {     
		window->draw(CurrentPickUp->Shape);

	}
}



