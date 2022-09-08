#pragma once

#include <vector>
#include "gameTile.h"

class Board
{
public:

	static const int boardXSize = 15;
	static const int boardYSize = 15;

	gameTile* tiles[boardXSize][boardYSize];

	Board();
	~Board();

	void BoardSetup();
	void BoardDraw(sf::RenderWindow* window);
	void BoardUpdate(GameObject* obj);

	void ProccesObjectMovement(GameObject* _obj);

	void ProcessObjectDirState(GameObject* _obj);

	sf::Vector2f ProcessLerp(sf::Vector2f _vec2A, sf::Vector2f _vec2B, float _fAlpha);

	sf::Vector2f m_BoardPosition;

	std::vector<GameObject*> m_vecPtrObject;

	char boardMap[15][15];
};