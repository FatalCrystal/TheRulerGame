#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

static class Collision
{
private:

public:
	static void XCollision(sf::Shape* _objA, sf::FloatRect _objB)
	{
		sf::Vector2f entityACenter = {
			(_objA->getGlobalBounds().left + _objA->getGlobalBounds().width / 2.f),
			(_objA->getGlobalBounds().top + _objA->getGlobalBounds().height / 2.f)
		};

		sf::Vector2f entityBCenter = {
			(_objB.left + _objB.width / 2.f),
			(_objB.top + _objB.height / 2.f)
		};

		if (entityACenter.x <= entityBCenter.x)
		{
			float offSet = -(_objA->getGlobalBounds().left + _objA->getGlobalBounds().width - _objB.left);
			_objA->move(offSet, 0);
		}

		if (entityACenter.x >= entityBCenter.x)
		{
			float offSet = (_objB.left + _objB.width - _objA->getGlobalBounds().left);
			_objA->move(offSet, 0);
		}
	}


	static void YCollision(sf::Shape* _objA, sf::FloatRect _objB)
	{
		sf::Vector2f entityACenter = {
			(_objA->getGlobalBounds().left + _objA->getGlobalBounds().width / 2.f),
			(_objA->getGlobalBounds().top + _objA->getGlobalBounds().height / 2.f)
		};

		sf::Vector2f entityBCenter = {
			(_objB.left + _objB.width / 2.f),
			(_objB.top + _objB.height / 2.f)
		};

		if (entityACenter.y <= entityBCenter.y)
		{
			float offSet = -(_objA->getGlobalBounds().top + _objA->getGlobalBounds().height - _objB.top);
			_objA->move(0, offSet);
		}

		if (entityACenter.y >= entityBCenter.y)
		{
			float offSet = (_objB.top + _objB.height - _objA->getGlobalBounds().top);
			_objA->move(0, offSet);
		}
	}

};
