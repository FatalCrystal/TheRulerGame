#include "PickUps.h"


void PickUps::SpawnPickups()
{

	MaxPickUps = 10; 

	if (this->SpawnTimer < this->SpawnTimerMax)
		this->SpawnTimer += 1.f; 
	else
	{
		if (this->Vpickups.size() < this->MaxPickUps)
		{
			this->Vpickups.push_back(PickUps()); 
			this->SpawnTimer = 0.f;     // no mroe spawn if 10 pickups 
		}
		
	}
}




PickUps::PickUps()
{
	/*srand(static_cast<unsigned>(time(0))); 
	this->shape.setRadius(static_cast<float>(rand() % 10 + 10)); */
	this->shape.setFillColor(sf::Color::Cyan);
	this->shape.setRadius(10.0f);

}

PickUps::~PickUps()
{
}

void PickUps::RenderPickUps(sf::RenderWindow* _window)
{
	_window->draw(shape);
}


