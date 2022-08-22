#include "GameManager.h"

GameManager::GameManager()
{
	m_Window = new sf::RenderWindow(sf::VideoMode(Utils::WinSizeX, Utils::WinSizeY), "The Ruler Game");
	m_Window->setFramerateLimit(Utils::FrameLimit);

    m_PlayerOne = new Player(new sf::CircleShape(10), Utils::WinCenterX - 100, Utils::WinCenterY, "Player One", sf::Color::Red);
    m_PlayerTwo = new Player(new sf::CircleShape(10), Utils::WinCenterX + 100, Utils::WinCenterY, "Player One", sf::Color::Blue);

    m_Objects.push_back(m_PlayerOne);
    m_Objects.push_back(m_PlayerTwo);

    m_AttackCDOne.restart();

    m_AttackCDTwo.restart();

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
    float playerOneAngle = (3.1415926536 / 180) * (m_PlayerOne->GetShape()->getRotation());
    float playerTwoAngle = (3.1415926536 / 180) * (m_PlayerTwo->GetShape()->getRotation());

    sf::Vector2f PlayerOneVelocity = sf::Vector2f(0.0f, 0.0f);
    sf::Vector2f PlayerTwoVelocity = sf::Vector2f(0.0f, 0.0f);

    PlayerOneVelocity.y = 1.f * -sin(playerOneAngle);
    PlayerOneVelocity.x = 1.f * cos(playerOneAngle);

    PlayerTwoVelocity.y = 1.f * -sin(playerTwoAngle);
    PlayerTwoVelocity.x = 1.f * cos(playerTwoAngle);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_AttackCDOne.getElapsedTime().asMilliseconds() >= m_AttackCDMaxOne)
    {
        m_AttackCDOne.restart();
        m_ProjectilesOne.push_back(new Bullet(m_PlayerOne->GetPosition().x, m_PlayerOne->GetPosition().y, PlayerOneVelocity.x, PlayerOneVelocity.y, m_BulletSpeed));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && m_AttackCDTwo.getElapsedTime().asMilliseconds() >= m_AttackCDMaxTwo)
    {
        m_AttackCDTwo.restart();
        m_ProjectilesTwo.push_back(new Bullet(m_PlayerTwo->GetPosition().x, m_PlayerTwo->GetPosition().y, PlayerTwoVelocity.x, PlayerTwoVelocity.y, m_BulletSpeed));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        m_PlayerOne->SetPosition(m_PlayerOne->GetPosition() + (Utils::Normalize(PlayerOneVelocity) * m_PlayerOne->GetMoveSpeed()));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        m_PlayerOne->SetPosition(m_PlayerOne->GetPosition() + (Utils::Normalize(-PlayerOneVelocity) * m_PlayerOne->GetMoveSpeed()));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        m_PlayerOne->GetShape()->rotate(playerRotationSpeed);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        m_PlayerOne->GetShape()->rotate(-playerRotationSpeed);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        m_PlayerTwo->SetPosition(m_PlayerTwo->GetPosition() + (Utils::Normalize(PlayerTwoVelocity) * m_PlayerTwo->GetMoveSpeed()));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        m_PlayerTwo->SetPosition(m_PlayerTwo->GetPosition() + (Utils::Normalize(-PlayerTwoVelocity) * m_PlayerTwo->GetMoveSpeed()));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        m_PlayerTwo->GetShape()->rotate(playerRotationSpeed);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        m_PlayerTwo->GetShape()->rotate(-playerRotationSpeed);
    }


  
}

void GameManager::Update()
{
    for (GameObject* Object : m_Objects)
    {
        Object->Update(m_DeltaTime);
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
