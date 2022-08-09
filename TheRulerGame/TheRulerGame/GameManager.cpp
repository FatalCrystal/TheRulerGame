#include "GameManager.h"

GameManager::GameManager()
{
	m_Window = new sf::RenderWindow(sf::VideoMode(Utils::WinSizeX, Utils::WinSizeY), "The Ruler Game");
	m_Window->setFramerateLimit(Utils::FrameLimit);

    m_Objects.push_back(new GameObject(new sf::CircleShape(10), Utils::WinSizeX / 2, Utils::WinSizeY / 2));

	GameLoop();
}

GameManager::~GameManager()
{
	delete m_Window;
}

void GameManager::GameLoop()
{
	m_GameClock.restart();
	m_FrameClock.restart();

    while (m_Window->isOpen())
    {
        m_DeltaTime = m_FrameClock.getElapsedTime().asMilliseconds();

        sf::Event Event;
        while (m_Window->pollEvent(Event))
        {
            if (Event.type == sf::Event::Closed)
            {
                m_Window->close();
            }
        }

        Update();

        Render();

        m_FrameClock.restart();
    }
}

void GameManager::PlayerInput()
{

}

void GameManager::Update()
{
    for (GameObject* Object : m_Objects)
    {
        Object->Update(m_DeltaTime);
    }
}

void GameManager::Render()
{
	m_Window->clear();

    for (GameObject* Object : m_Objects)
    {
        Object->Render(m_Window);
    }

	m_Window->display();
}
