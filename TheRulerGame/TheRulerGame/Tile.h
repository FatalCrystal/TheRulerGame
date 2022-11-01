#pragma once
#include <SFML/Graphics.hpp>
#include "Utils.h"

// Enum for tile type
enum TileType
{
	TILE_GROUND,
	TILE_WALL,
};

class Tile
{
private:
	// Tile rect
	sf::RectangleShape* m_TileRect;

	// Tile rect size
	sf::Vector2f m_TileRectSize;
	// Tile rect origin
	sf::Vector2f m_TileRectOrigin;

	// Hold Enum
	TileType m_TileType;

	// Initialize variables
	void InitializeVaribles();
	void InitializeTileRect();

public:
	Tile(TileType _type);
	virtual ~Tile();

	sf::RectangleShape* GetTile() const { return m_TileRect; };
	sf::Vector2f GetTileRectSize() const { return m_TileRectSize; };
};

