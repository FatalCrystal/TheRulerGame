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
    PickupType PlayerOnePickup = PickupType::type_None;
    PickupType PlayerTwoPickup = PickupType::type_None;

    if (m_GameState == GameState::Gameplay)
    {
        m_PlayerOne->WallCollisions(m_SceneManager, m_Window, &m_Projectiles);
        m_PlayerTwo->WallCollisions(m_SceneManager, m_Window, &m_Projectiles);

        m_PlayerOne->PlayerInput(&m_Projectiles, sf::Keyboard::Space, sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D);
        m_PlayerTwo->PlayerInput(&m_Projectiles, sf::Keyboard::RControl, sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right);

        PickUps.SpawnPickups(m_SceneManager.GetWalls()); 

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

        PlayerOnePickup = m_PlayerOne->GetPickup();
        PlayerTwoPickup = m_PlayerTwo->GetPickup();
    }

    float TimeRemaining = m_TimerLength - m_GameClock.getElapsedTime().asSeconds();

    m_UIManager->Update(&m_GameState, UIManager::GameData(&m_BaseMoveSpeed, &m_BaseFireDelay, nullptr, &m_TimerLength, &m_Volume, &PickUps.m_PickupSpawnDelay, PlayerOnePickup, PlayerTwoPickup, WinnerText), TimeRemaining);
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
