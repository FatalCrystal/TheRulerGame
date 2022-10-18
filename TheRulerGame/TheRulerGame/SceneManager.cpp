#include "SceneManager.h"
#include <ctime>
#include <iostream>

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::LoadRandomScene()
{
	srand((unsigned)time(0));

	int loadedLevel = std::rand() % 2;
	
	std::cout << loadedLevel;

	std::fstream loadFileStream;
	std::string loadFileString;
	std::string loadFilePath;

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

	int lineCount = 0;

	loadFileStream.open(loadFilePath, std::ios::in);

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

	for (int x = 0; x < Utils::WinSizeX; x++)
	{
		for (int y = 0; y < Utils::WinSizeY; y++)
		{
			if (levelArray[y][x] == 'X')
			{
				Tile* newTile = new Tile(TileType::TILE_WALL);
				newTile->GetTile()->setPosition(sf::Vector2f(x * newTile->GetTileRectSize().x, y * newTile->GetTileRectSize().y));

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

void SceneManager::LoadScene(std::string _filePath)
{
	std::fstream loadFileStream;
	std::string loadFileString;

	int lineCount = 0;

	loadFileStream.open(_filePath, std::ios::in);

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

	for (int x = 0; x < Utils::WinSizeX; x++)
	{
		for (int y = 0; y < Utils::WinSizeY; y++)
		{
			if (levelArray[y][x] == 'X')
			{
				Tile* newTile = new Tile(TileType::TILE_WALL);
				newTile->GetTile()->setPosition(sf::Vector2f(x * newTile->GetTileRectSize().x, y * newTile->GetTileRectSize().y));

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

std::vector<Tile*> SceneManager::GetWalls()
{
	return levelWallTiles;
}
