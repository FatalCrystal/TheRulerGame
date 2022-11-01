#include "Tile.h"

Tile::Tile(TileType _type) :
	m_TileType(_type)
{
	InitializeVaribles();
	InitializeTileRect();
}

Tile::~Tile()
{
	delete m_TileRect;
}

void Tile::InitializeVaribles()
{
	m_TileRectSize = sf::Vector2f(Utils::WinSizeX / 40, Utils::WinSizeY / 40);
	m_TileRectOrigin = m_TileRectSize / 2.f;
}

void Tile::InitializeTileRect()
{
	m_TileRect = new sf::RectangleShape();
	m_TileRect->setSize(m_TileRectSize);
	m_TileRect->setOrigin(m_TileRectOrigin);

	// Set tile color depending on tile type
	sf::Color tempColor;

	switch (m_TileType)
	{
	case TILE_GROUND:
		tempColor.r = 207.0f;
		tempColor.g = 182.0f;
		tempColor.b = 189.0f;
		m_TileRect->setFillColor(tempColor);
		break;

	case TILE_WALL:
		tempColor.r = 66.0f;
		tempColor.g = 43.0f;
		tempColor.b = 50.0f;
		m_TileRect->setFillColor(tempColor);
		break;

	default:
		break;
	}
}

