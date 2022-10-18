#include "Tile.h"

void Tile::InitializeVaribles()
{
	m_TileRectSize = sf::Vector2f(20.f, 20.f);
	m_TileRectOrigin = m_TileRectSize / 2.f;
}

void Tile::InitializeTileRect(TileType _type)
{
	m_TileRect = new sf::RectangleShape();
	m_TileRect->setSize(m_TileRectSize);
	m_TileRect->setOrigin(m_TileRectOrigin);

	sf::Color tempColor;

	switch (_type)
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

Tile::Tile(TileType _type)
{
	m_TileType = _type;
	InitializeVaribles();
	InitializeTileRect(_type);
}

Tile::~Tile()
{
	delete m_TileRect;
}

sf::RectangleShape* Tile::GetTile()
{
	return m_TileRect;
}

sf::Vector2f Tile::GetTileRectSize()
{
	return m_TileRectSize;
}