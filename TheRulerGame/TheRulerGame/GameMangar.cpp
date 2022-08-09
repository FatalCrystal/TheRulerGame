#include "GameMangar.h"

GameMangar::GameMangar()
{
	m_VideoMode.width = Utils::WinSizeX;
	m_VideoMode.height = Utils::WinSizeY;
	m_Window = new sf::RenderWindow();
	m_Window->setFramerateLimit(Utils::FrameLimit);
	
	m_Window->create(m_VideoMode, "TheRulerGame");

}

GameMangar::~GameMangar()
{
	delete m_Window;
}

void GameMangar::GameLoop()
{
	while (m_Window->isOpen())
	{
		Update();
		Render();
	}
}

void GameMangar::Render()
{
	m_Window->clear(sf::Color::White);

	m_Window->display();
}

void GameMangar::Update()
{

}
