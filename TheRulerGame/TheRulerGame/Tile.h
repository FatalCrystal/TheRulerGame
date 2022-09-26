#pragma once
#include <SFML/Graphics.hpp>

enum TileType
{
	TILE_GROUND,
	TILE_WALL,
};

class Tile
{
private:
	sf::RectangleShape* m_TileRect;

	sf::Vector2f m_TileRectSize;
	sf::Vector2f m_TileRectOrigin;

	TileType m_TileType;

	void InitializeVaribles();
	void InitializeTileRect(TileType _type);

public:
	Tile(TileType _type);
	virtual ~Tile();

	sf::RectangleShape* GetTile();
	sf::Vector2f GetTileRectSize();
};

