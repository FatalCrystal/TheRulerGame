#include "SceneManager.h"
#include <ctime>
#include <iostream>

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

// Handles random scene assignment
void SceneManager::LoadRandomScene()
{
	// Set seed for random assignment
	srand((unsigned)time(0));

	// Generate number based on how many scenes we have
	int loadedLevel = std::rand() % 2;
	
	// Show level loaded in console
	std::cout << loadedLevel;

	// String to hold level file path
	std::string loadFilePath;

	// Switch case to determine level loaded
	switch (loadedLevel)
	{
	case 0:
		loadFilePath = "Resources/Levels/Level1.txt";
		break;
	case 1:
		loadFilePath = "Resources/Levels/Level2.txt";
		break;
	default:
		break;
	}

	// Run Level loading code
	LoadScene(loadFilePath);
}

// Handles loading of level taking in a string for level file location
void SceneManager::LoadScene(std::string _filePath)
{
	// Fstream to read from file
	std::fstream loadFileStream;

	// String to hold info from file
	std::string loadFileString;

	// file line count
	int lineCount = 0;

	// Open file and load file into fstream
	loadFileStream.open(_filePath, std::ios::in);

	// Get line put each char into level array then increment line when line is at end then close file
	if (loadFileStream.is_open())
	{
		while (std::getline(loadFileStream, loadFileString))
		{
			for (int i = 0; i < loadFileString.size(); i++)
			{
				levelArray[lineCount][i] = loadFileString[i];
			}

			lineCount++;
		}

		loadFileStream.close();
	}

	// Take level array and what ever char is in the array spot change tile 
	for (int x = 0; x < 41; x++)
	{
		for (int y = 0; y < 41; y++)
		{
			if (levelArray[y][x] == 'X')
			{
				// Create new tile
				Tile* newTile = new Tile(TileType::TILE_WALL);
				// Set tile position
				newTile->GetTile()->setPosition(sf::Vector2f(x * newTile->GetTileRectSize().x, y * newTile->GetTileRectSize().y));
				// Add tiles to vector for rendering and collisions
				levelWallTiles.push_back(newTile);
			}
			if (levelArray[y][x] == 'O')
			{
				Tile* newTile = new Tile(TileType::TILE_GROUND);
				newTile->GetTile()->setPosition(sf::Vector2f(x * newTile->GetTileRectSize().x, y * newTile->GetTileRectSize().y));

				levelGroundTiles.push_back(newTile);
			}
		}
	}
}

// Draw all level tiles
void SceneManager::RenderLevel(sf::RenderTarget* _window)
{
	for (auto i = 0; i < levelGroundTiles.size(); i++)
	{
		_window->draw(*levelGroundTiles[i]->GetTile());
	}
	for (auto i = 0; i < levelWallTiles.size(); i++)
	{
		_window->draw(*levelWallTiles[i]->GetTile());
	}
}

// Wall getter 
std::vector<Tile*> SceneManager::GetWalls()
{
	return levelWallTiles;
}
