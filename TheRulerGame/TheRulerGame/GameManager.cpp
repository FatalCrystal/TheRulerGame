#include "GameManager.h"

GameManager::GameManager()
{
	m_Window = new sf::RenderWindow(sf::VideoMode(Utils::WinSizeX, Utils::WinSizeY), "The Ruler Game");
	m_Window->setFramerateLimit(Utils::FrameLimit);

    m_UIManager = new UIManager();

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
            if (Event.type == sf::Event::Closed || m_GameState == GameState::Exiting)
            {
                m_Window->close();
            }

            if (Event.type == sf::Event::MouseButtonPressed && Event.mouseButton.button == sf::Mouse::Button::Left)
            {
                m_UIManager->PollButtons(m_Window);
            }
        }

        if (m_GameState != m_PreviousGameState)
        {
            ChangeGameState();
        }

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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
    {
        m_PlayerOne->SpecialAttack();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
    {
        m_PlayerTwo->SpecialAttack();
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
    m_PlayerOne->GetSprite()->rotate(PlayerOneAngle);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        m_PlayerOne->SetPosition(sf::Vector2f(m_PlayerOne->GetPosition() + (Utils::Normalize(m_PlayerOne->GetDirection()) * m_PlayerOne->GetMoveSpeed())));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        m_PlayerOne->SetPosition(sf::Vector2f(m_PlayerOne->GetPosition() + (Utils::Normalize(m_PlayerOne->GetDirection()) * -m_PlayerOne->GetMoveSpeed())));
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
    m_PlayerTwo->GetSprite()->rotate(PlayerTwoAngle);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        m_PlayerTwo->SetPosition(sf::Vector2f(m_PlayerTwo->GetPosition() + (Utils::Normalize(m_PlayerTwo->GetDirection()) * m_PlayerTwo->GetMoveSpeed())));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        m_PlayerTwo->SetPosition(sf::Vector2f(m_PlayerTwo->GetPosition() + (Utils::Normalize(m_PlayerTwo->GetDirection()) * -m_PlayerTwo->GetMoveSpeed())));
    }
  
}

void GameManager::ChangeGameState()
{
    if (m_GameState == GameState::Gameplay)
    {

        m_SceneManager.LoadRandomScene();

        m_PlayerOne = new Player("RedTank.png", sf::Vector2f(Utils::WinCenterX - 100, Utils::WinCenterY), "Player One");
        m_PlayerTwo = new Player("BlueTank.png", sf::Vector2f(Utils::WinCenterX + 100, Utils::WinCenterY), "Player Two");

        m_PlayerOne->SetEnemy(m_PlayerTwo);
        m_PlayerTwo->SetEnemy(m_PlayerOne);

        m_Objects.push_back(m_PlayerOne);
        m_Objects.push_back(m_PlayerTwo);

        for (int i = m_Objects.size() - 2; i < m_Objects.size(); i++)
        {
            ((Player*)m_Objects[i])->SetMoveSpeed(m_BaseMoveSpeed);
            ((Player*)m_Objects[i])->SetAttackCooldown(m_BaseFireDelay);
        }

        m_GameClock.restart();
    }
    else if (m_PreviousGameState == GameState::Gameplay)
    {
        for (GameObject* CurrentObject : m_Objects)
        {
            delete CurrentObject;
            CurrentObject = nullptr;
        }
        for (Bullet* CurrentBullet : m_Projectiles)
        {
            delete CurrentBullet;
            CurrentBullet = nullptr;
        }

        m_Objects.clear();
        m_Projectiles.clear();
        m_PlayerOne = nullptr;
        m_PlayerTwo = nullptr;
    }

    m_PreviousGameState = m_GameState;
}

void GameManager::Update()
{
    std::string WinnerText;
    if (m_GameState == GameState::Gameplay)
    {
        PlayerInput();

        PickUps.SpawnPickups(); 


        for (GameObject* Object : m_Objects)
        {
            Object->Update(m_DeltaTime);
        }

        for (Bullet* Projectile : m_Projectiles)
        {
            Projectile->Update();
        }

        m_PlayerOne->Update(&m_Projectiles, &PickUps.m_PickUpVector);
        m_PlayerTwo->Update(&m_Projectiles, &PickUps.m_PickUpVector); 
        
        if (m_GameClock.getElapsedTime().asSeconds() >= m_TimerLength)
        {
            if (m_PlayerOne->HasCrown())
            {
                WinnerText = "THE WINNER IS PLAYER ONE (RED)!";
            }
            else if (m_PlayerTwo->HasCrown())
            {
                WinnerText = "THE WINNER IS PLAYER TWO (BLUE)!";
            }
            else
            {
                WinnerText = "IT'S A TIE!";
            }

            m_GameState = GameState::EndScreen;
            ChangeGameState();
        }
    }

    float TimeRemaining = m_TimerLength - m_GameClock.getElapsedTime().asSeconds();
    m_UIManager->Update(&m_GameState, UIManager::GameData(&m_BaseMoveSpeed, &m_BaseFireDelay, nullptr, &m_TimerLength, &m_Volume, &PickUps.m_PickupSpawnDelay, WinnerText), TimeRemaining);
}

void GameManager::Render()
{

	m_Window->clear();
    
    m_SceneManager.RenderLevel(m_Window);

    PickUps.RenderPickups(m_Window); 

    for (GameObject* Object : m_Objects)
    {
        if (Object == m_PlayerOne || Object == m_PlayerTwo)
        {
            ((Player*)Object)->Render(m_Window);
        }
        else
        {
            Object->Render(m_Window);
        }
    }

    for (Bullet* Projectile : m_Projectiles)
    {
        Projectile->Render(m_Window);
    }

    m_UIManager->Render(m_Window);

	m_Window->display();
}
