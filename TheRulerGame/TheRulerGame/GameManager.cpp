#include "GameManager.h"

GameManager::GameManager()
{
	m_Window = new sf::RenderWindow(sf::VideoMode(Utils::WinSizeX, Utils::WinSizeY), "The Ruler Game");
	m_Window->setFramerateLimit(Utils::FrameLimit);

    m_UIManager = new UIManager();

    m_PlayerOne = new Player(new sf::CircleShape(10, 3), Utils::WinCenterX - 100, Utils::WinCenterY, "Player One", sf::Color::Red);
    m_PlayerTwo = new Player(new sf::CircleShape(10, 3), Utils::WinCenterX + 100, Utils::WinCenterY, "Player Two", sf::Color::Blue);

    m_PlayerOne->SetEnemy(m_PlayerTwo);
    m_PlayerTwo->SetEnemy(m_PlayerOne);

    m_Objects.push_back(m_PlayerOne);
    m_Objects.push_back(m_PlayerTwo);

	GameLoop();
}

GameManager::~GameManager()
{

}

void GameManager::GameLoop()
{
	m_GameClock.restart();
	m_FrameClock.restart();

    while (m_Window->isOpen())
    {
        m_DeltaTime = (float)m_FrameClock.getElapsedTime().asMilliseconds();

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
    float PlayerOneAngle = 0.0f;
    float PlayerTwoAngle = 0.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        m_PlayerOne->Shoot(&m_Projectiles);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
    {
        m_PlayerTwo->Shoot(&m_Projectiles);
    }
    
    // PLAYER ONE ROTATION AND MOVEMENT

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        PlayerOneAngle -= m_PlayerOne->GetRotationSpeed();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        PlayerOneAngle += m_PlayerOne->GetRotationSpeed();
    }

    m_PlayerOne->SetDirection(Utils::Rotate(m_PlayerOne->GetDirection(), PlayerOneAngle * (float)(3.1415926536 / 180)));
    m_PlayerOne->GetShape()->rotate(PlayerOneAngle);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        m_PlayerOne->SetPosition(m_PlayerOne->GetPosition() + (Utils::Normalize(m_PlayerOne->GetDirection()) * m_PlayerOne->GetMoveSpeed()));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        m_PlayerOne->SetPosition(m_PlayerOne->GetPosition() + (Utils::Normalize(m_PlayerOne->GetDirection()) * -m_PlayerOne->GetMoveSpeed()));
    }

    // PLAYER TWO ROTATION AND MOVEMENT

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        PlayerTwoAngle -= m_PlayerTwo->GetRotationSpeed();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        PlayerTwoAngle += m_PlayerTwo->GetRotationSpeed();
    }

    m_PlayerTwo->SetDirection(Utils::Rotate(m_PlayerTwo->GetDirection(), PlayerTwoAngle * (float)(3.1415926536 / 180)));
    m_PlayerTwo->GetShape()->rotate(PlayerTwoAngle);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        m_PlayerTwo->SetPosition(m_PlayerTwo->GetPosition() + (Utils::Normalize(m_PlayerTwo->GetDirection()) * m_PlayerTwo->GetMoveSpeed()));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        m_PlayerTwo->SetPosition(m_PlayerTwo->GetPosition() + (Utils::Normalize(m_PlayerTwo->GetDirection()) * -m_PlayerTwo->GetMoveSpeed()));
    }
  
}

void GameManager::Update()
{
    for (GameObject* Object : m_Objects)
    {
        Object->Update(m_DeltaTime);
    }

    for (Bullet* Projectile : m_Projectiles)
    {
        Projectile->Update();
    }

    m_PlayerOne->Update(&m_Projectiles);
    m_PlayerTwo->Update(&m_Projectiles);

    m_UIManager->Update(m_TimerLength - m_GameClock.getElapsedTime().asSeconds());
}

void GameManager::Render()
{
	m_Window->clear();

    for (GameObject* Object : m_Objects)
    {
        Object->Render(m_Window);
    }

    for (Bullet* Projectile : m_Projectiles)
    {
        Projectile->Render(m_Window);
    }

    m_UIManager->Render(m_Window);

	m_Window->display();
}
