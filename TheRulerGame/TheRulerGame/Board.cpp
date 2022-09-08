#include "Board.h"

Board::Board()
{
	m_BoardPosition = sf::Vector2f(400, 400);

	for (int i = 0; i < boardXSize; i++)
	{
		for (int j = 0; j < boardYSize; j++)
		{

			tiles[i][j] = new gameTile("Images/gameTile.png", sf::Vector2f((i * 64) + 112, (j * 64) + 112), false);

			tiles[i][j]->m_TileGridPosition.x = (i * 64) + 112;
			tiles[i][j]->m_TileGridPosition.y = (i * 64) + 112;
		}
	}



}

Board::~Board()
{
	for (int i = 0; i < boardXSize; i++)
	{
		for (int j = 0; j < boardYSize; j++)
		{
			delete tiles[i][j];
		}
	}
}

void Board::BoardSetup()
{

	char boardMap[15][15] =
	{

	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'x', ' ', ' ', 'x', ' ', ' '}, //1
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'x', ' ', ' ', 'x', ' ', ' ' },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'x', ' ', ' ' },
	{ ' ', ' ', ' ', 'x', 'x', ' ', ' ', ' ', ' ', 'x', ' ', ' ', 'x', ' ', ' ' },
	{ ' ', ' ', ' ', ' ', 'x', ' ', ' ', 'x', 'x', 'x', ' ', ' ', 'x', ' ', ' ' },
	{ ' ', ' ', ' ', ' ', 'x', ' ', ' ', ' ', ' ', 'x', ' ', ' ', 'x', ' ', ' ' },
	{ ' ', ' ', 'x', 'x', 'x', ' ', ' ', ' ', ' ', 'x', ' ', ' ', 'x', ' ', ' ' },
	{ ' ', ' ', ' ', ' ', 'x', ' ', ' ', ' ', ' ', 'x', ' ', ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ', 'x', ' ', 'x', 'x', ' ', 'x', ' ', 'x', 'x', 'x', 'x' },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'x', ' ', 'x', ' ', ' ', ' ' }, //10
	{ ' ', ' ', 'x', 'x', 'x', 'x', 'x', ' ', ' ', 'x', ' ', ' ', ' ', ' ', ' ' },
	{ ' ', ' ', 'x', ' ', ' ', ' ', ' ', ' ', ' ', 'x', ' ', ' ', 'x', 'x', 'x' },
	{ ' ', ' ', 'x', ' ', ' ', ' ', ' ', ' ', ' ', 'x', ' ', ' ', ' ', ' ', 'x' },
	{ ' ', ' ', 'x', ' ', 'x', 'x', 'x', 'x', 'x', 'x', ' ', ' ', ' ', ' ', 'x' },
	{ 'y', ' ', 'x', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'x', 'x' },
	};

	sf::Texture* ImpassableTex = new sf::Texture();
	sf::Texture* Goal = new sf::Texture();

	for (int i = 0; i < boardXSize; i++)
	{
		for (int j = 0; j < boardYSize; j++)
		{
			if (boardMap[i][j] == 'x')
			{
				tiles[i][j]->m_impassable = true;
				tiles[i][j]->GetSprite()->setTexture(*ImpassableTex);
			}
			if (boardMap[i][j] == 'y')
			{
				tiles[i][j]->m_impassable = false;
				tiles[i][j]->GetSprite()->setTexture(*Goal);
			}
		}
	};

	ImpassableTex->loadFromFile("Images/Tile.png");


}

void Board::BoardDraw(sf::RenderWindow* window)
{
	for (int i = 0; i < boardXSize; i++)
	{
		for (int j = 0; j < boardYSize; j++)
		{
			window->draw(*tiles[i][j]->GetSprite());
		}
	}
}





sf::Vector2f Board::ProcessLerp(sf::Vector2f _vec2A, sf::Vector2f _vec2B, float _fAlpha)
{
	return _vec2A * _fAlpha + _vec2B * (1.0f - _fAlpha);
}
