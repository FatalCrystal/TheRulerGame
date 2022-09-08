#include "gameTile.h"

gameTile::gameTile(sf::String spriteFilePath, sf::Vector2f TilePosition, bool m_impassable)
{
	m_TileTexture = new sf::Texture();
	m_TileTexture->loadFromFile(spriteFilePath);

	m_pTileSprite = new sf::Sprite();

	m_pTileSprite->setTexture(*m_TileTexture);

	m_TilePosition = TilePosition;


	m_pTileSprite->setOrigin(sf::Vector2f(m_pTileSprite->getGlobalBounds().width / 2, m_pTileSprite->getGlobalBounds().height / 2));

	UpdateSprite();
}


gameTile::~gameTile()
{
	delete m_TileTexture;
	delete m_pTileSprite;
}
