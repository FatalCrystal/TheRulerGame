#include <SFML/Graphics.hpp>
#include "GameObject.h"

class gameTile
{
private:

	sf::Sprite* m_pTileSprite;
	sf::Texture* m_TileTexture;
	sf::Vector2f m_TilePosition;

public:

	gameTile(sf::String spriteFilePath, sf::Vector2f m_TilePosition, bool m_impassable);
	~gameTile();

	sf::Sprite* GetSprite() { return m_pTileSprite; };
	void UpdateSprite() { m_pTileSprite->setPosition(m_TilePosition); };

	sf::Vector2i m_TileGridPosition;

	//Whats in the gameTile rn code
	bool m_impassable = false; // check if you can go through or not
	GameObject* m_currentOccupent;
};

