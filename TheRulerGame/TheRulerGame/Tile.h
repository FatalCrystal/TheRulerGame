#pragma once
#include <SFML/Graphics.hpp>

// Define tyle types
enum TileType
{
	TILE_GROUND,
	TILE_WALL,
};

class Tile
{
private:
	// Define tile shape
	sf::RectangleShape* m_TileRect;
	// Define tile size
	sf::Vector2f m_TileRectSize;
	// Define tile origin
	sf::Vector2f m_TileRectOrigin;

	// Veriable to hold tilr type
	TileType m_TileType;

	// Functions to initialize tile veriables 
	void InitializeVaribles();
	void InitializeTileRect(TileType _type);

public:
	// Constructor
	Tile(TileType _type);
	//Destructor
	virtual ~Tile();
	// Getters
	sf::RectangleShape* GetTile();
	sf::Vector2f GetTileRectSize();
};

