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
    
    for (auto* i : m_ProjectilesOne)
    {
        delete i;
    }
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
        m_AttackDirOne.x = 0;
        m_AttackDirOne.y = -1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && m_PlayerOne->GetPosition().y < Utils::WinSizeY - m_PlayerOne->GetMoveSpeed())
    {
        PlayerOneVelocity.y += 1;
        m_AttackDirOne.x = 0;
        m_AttackDirOne.y = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && m_PlayerOne->GetPosition().x > 0 + m_PlayerOne->GetMoveSpeed())
    {
        PlayerOneVelocity.x -= 1;
        m_AttackDirOne.x = -1;
        m_AttackDirOne.y = 0;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && m_PlayerOne->GetPosition().x < Utils::WinSizeX - m_PlayerOne->GetMoveSpeed())
    {
        PlayerOneVelocity.x += 1;
        m_AttackDirOne.x = 1;
        m_AttackDirOne.y = 0;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_PlayerTwo->GetPosition().y > 0 + m_PlayerTwo->GetMoveSpeed())
    {
        PlayerTwoVelocity.y -= 1;
        m_AttackDirTwo.x = 0;
        m_AttackDirTwo.y = -1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_PlayerTwo->GetPosition().y < Utils::WinSizeY - m_PlayerTwo->GetMoveSpeed())
    {
        PlayerTwoVelocity.y += 1;
        m_AttackDirTwo.x = 0;
        m_AttackDirTwo.y = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_PlayerTwo->GetPosition().x > 0 + m_PlayerTwo->GetMoveSpeed())
    {
        PlayerTwoVelocity.x -= 1;
        m_AttackDirTwo.x = -1;
        m_AttackDirTwo.y = 0;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_PlayerTwo->GetPosition().x < Utils::WinSizeX - m_PlayerTwo->GetMoveSpeed())
    {
        PlayerTwoVelocity.x += 1;
        m_AttackDirTwo.x = 1;
        m_AttackDirTwo.y = 0;
    }

    m_PlayerOne->SetPosition(m_PlayerOne->GetPosition() + (Utils::Normalize(PlayerOneVelocity) * m_PlayerOne->GetMoveSpeed()));
    m_PlayerTwo->SetPosition(m_PlayerTwo->GetPosition() + (Utils::Normalize(PlayerTwoVelocity) * m_PlayerTwo->GetMoveSpeed()));

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_CanAttackOne == true)
    {
        m_ProjectilesOne.push_back(new Bullet(m_PlayerOne->GetPosition().x, m_PlayerOne->GetPosition().y, m_AttackDirOne.x, m_AttackDirOne.y, m_BulletSpeed));
    }


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && m_CanAttackTwo == true)
    {
        m_ProjectilesTwo.push_back(new Bullet(m_PlayerTwo->GetPosition().x, m_PlayerTwo->GetPosition().y, m_AttackDirTwo.x, m_AttackDirTwo.y, m_BulletSpeed));
    }

}

void GameManager::Update()
{
    for (GameObject* Object : m_Objects)
    {
        Object->Update(m_DeltaTime);
    }

    if (m_AttackCDOne < m_AttackCDMaxOne)
    {
        m_AttackCDOne += 0.5f;
    }

    if (m_AttackCDOne >= m_AttackCDMaxOne)
    {
        m_CanAttackOne = true;
        m_AttackCDOne = 0.f;
    }
    else
    {
        m_CanAttackOne = false;
    }

    if (m_AttackCDTwo < m_AttackCDMaxTwo)
    {
        m_AttackCDTwo += 0.5f;
    }

    if (m_AttackCDTwo >= m_AttackCDMaxTwo)
    {
        m_CanAttackTwo = true;
        m_AttackCDTwo = 0.f;
    }
    else
    {
        m_CanAttackTwo = false;
    }

    unsigned counterOne = 0;
    for (auto* bullet : m_ProjectilesOne)
    {
        bullet->Update();

        if (bullet->GetBounds().intersects(m_PlayerTwo->GetShape()->getGlobalBounds()))
        {
            m_PlayerTwo->SetCrown(false);
            m_PlayerOne->SetCrown(true);

            std::cout << "Player One Has Crown" << std::endl;

            delete m_ProjectilesOne.at(counterOne);
            m_ProjectilesOne.erase(m_ProjectilesOne.begin() + counterOne);
            --counterOne;
        }

        if (bullet->GetBounds().top + bullet->GetBounds().height < 0)
        {
            delete m_ProjectilesOne.at(counterOne);
            m_ProjectilesOne.erase(m_ProjectilesOne.begin() + counterOne);
            --counterOne;
        }

        ++counterOne;
    }

    unsigned counterTwo = 0;
    for (auto* bullet : m_ProjectilesTwo)
    {
        bullet->Update();

        if (bullet->GetBounds().intersects(m_PlayerOne->GetShape()->getGlobalBounds()))
        {
            m_PlayerTwo->SetCrown(true);
            m_PlayerOne->SetCrown(false);

            std::cout << "Player Two Has Crown" << std::endl;

            delete m_ProjectilesTwo.at(counterTwo);
            m_ProjectilesTwo.erase(m_ProjectilesTwo.begin() + counterTwo);
            --counterTwo;
        }

        if (bullet->GetBounds().top + bullet->GetBounds().height < 0)
        {
            delete m_ProjectilesTwo.at(counterTwo);
            m_ProjectilesTwo.erase(m_ProjectilesTwo.begin() + counterTwo);
            --counterTwo;
        }

        ++counterTwo;
    }
}

void GameManager::Render()
{
	m_Window->clear();

    for (GameObject* Object : m_Objects)
    {
        Object->Render(m_Window);
    }

    for (auto* bullet : m_ProjectilesOne)
    {
        bullet->Render(m_Window);
    }

    for (auto* bullet : m_ProjectilesTwo)
    {
        bullet->Render(m_Window);
    }

	m_Window->display();
}
