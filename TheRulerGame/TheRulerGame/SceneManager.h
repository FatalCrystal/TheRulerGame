#pragma once
#include "Utils.h"
#include "Tile.h"
#include <fstream>

class SceneManager
{
private:
	char levelArray[Utils::WinSizeX][Utils::WinSizeY];

	std::vector<Tile*> levelGroundTiles;
	std::vector<Tile*> levelWallTiles;

public:
	SceneManager();
	~SceneManager();

	void LoadRandomScene();
	void LoadScene(std::string _filePath);
	void RenderLevel(sf::RenderTarget* _window);
	std::vector<Tile*> GetWalls();
};

