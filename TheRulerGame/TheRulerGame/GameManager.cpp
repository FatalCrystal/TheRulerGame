#include "GameManager.h"

GameManager::GameManager()
{
	m_Window = new sf::RenderWindow(sf::VideoMode(Utils::WinSizeX, Utils::WinSizeY), "The Ruler Game");
	m_Window->setFramerateLimit(Utils::FrameLimit);

    m_PlayerOne = new Player(new sf::CircleShape(10), Utils::WinCenterX - 100, Utils::WinCenterY, "Player One", sf::Color::Red);
    m_PlayerTwo = new Player(new sf::CircleShape(10), Utils::WinCenterX + 100, Utils::WinCenterY, "Player One", sf::Color::Blue);

    m_Objects.push_back(m_PlayerOne);
    m_Objects.push_back(m_PlayerTwo);

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

        PlayerInput();

        Update();

        Render();

        m_FrameClock.restart();
    }
}

void GameManager::PlayerInput()
{
    sf::Vector2f PlayerOneVelocity = sf::Vector2f(0.0f, 0.0f);
    sf::Vector2f PlayerTwoVelocity = sf::Vector2f(0.0f, 0.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && m_PlayerOne->GetPosition().y > 0 + m_PlayerOne->GetMoveSpeed())
    {
        PlayerOneVelocity.y -= 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && m_PlayerOne->GetPosition().y < Utils::WinSizeY - m_PlayerOne->GetMoveSpeed())
    {
        PlayerOneVelocity.y += 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && m_PlayerOne->GetPosition().x > 0 + m_PlayerOne->GetMoveSpeed())
    {
        PlayerOneVelocity.x -= 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && m_PlayerOne->GetPosition().x < Utils::WinSizeX - m_PlayerOne->GetMoveSpeed())
    {
        PlayerOneVelocity.x += 1;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_PlayerTwo->GetPosition().y > 0 + m_PlayerTwo->GetMoveSpeed())
    {
        PlayerTwoVelocity.y -= 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_PlayerTwo->GetPosition().y < Utils::WinSizeY - m_PlayerTwo->GetMoveSpeed())
    {
        PlayerTwoVelocity.y += 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_PlayerTwo->GetPosition().x > 0 + m_PlayerTwo->GetMoveSpeed())
    {
        PlayerTwoVelocity.x -= 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_PlayerTwo->GetPosition().x < Utils::WinSizeX - m_PlayerTwo->GetMoveSpeed())
    {
        PlayerTwoVelocity.x += 1;
    }

    m_PlayerOne->SetPosition(m_PlayerOne->GetPosition() + (Utils::Normalize(PlayerOneVelocity) * m_PlayerOne->GetMoveSpeed()));
    m_PlayerTwo->SetPosition(m_PlayerTwo->GetPosition() + (Utils::Normalize(PlayerTwoVelocity) * m_PlayerTwo->GetMoveSpeed()));

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
