#pragma once
#include "Utils.h"
#include "Tile.h"
#include <fstream>

class SceneManager
{
private:
	// Level array to determine level size 
	char levelArray[41][41];

	// Game tiles Stored in vectors to build level
	std::vector<Tile*> levelGroundTiles;
	std::vector<Tile*> levelWallTiles;

public:
	// Constructor
	SceneManager();
	// Destructor
	~SceneManager();
	// Function to load a randomly selected level
	void LoadRandomScene();
	// Function to load a selected level
	void LoadScene(std::string _filePath);
	// Function to render level tiles
	void RenderLevel(sf::RenderTarget* _window);
	// Getters
	std::vector<Tile*> GetWalls() const;
	std::vector<Tile*> GetGround() const;
	void ClearTiles();
};

