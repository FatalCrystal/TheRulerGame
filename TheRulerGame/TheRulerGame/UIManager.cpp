#include "UIManager.h"
#include "Utils.h"
#include <iostream>

UIManager::UIManager()
{
	m_Font.loadFromFile("Resources/Fonts/arial.ttf");

	m_Textures.push_back(sf::Texture());
	m_Textures[0].loadFromFile("Resources/Textures/Button.png");

	m_Textures.push_back(sf::Texture());
	m_Textures[1].loadFromFile("Resources/Textures/IncButton.png");

	m_Textures.push_back(sf::Texture());
	m_Textures[2].loadFromFile("Resources/Textures/DecButton.png");
}

UIManager::~UIManager()
{
}

void UIManager::UpdateDisplayState(GameState* _state, UIManager::GameData _gameData)
{

	// Delete data at existing button pointers
	for (Button* CurrentButton : m_Buttons)
	{
		delete CurrentButton;
	}

	// Empty button vector
	m_Buttons.clear();

	// Delete data at existing text pointers
	for (sf::Text* CurrentText : m_TextLabels)
	{
		delete CurrentText;
	}

	// Empty text vector
	m_TextLabels.clear();

	// Create new buttons and text labels based on the new UI display mode
	if (*_state == GameState::MainMenu)
	{
		// Play Button
		m_Buttons.push_back(new Button(new sf::Sprite(m_Textures[0]), Utils::WinCenterX, 300, [=]()
			{
				*_state = GameState::Gameplay;
				std::cout << "Starting Game" << std::endl;
			}));

		// Options Button
		m_Buttons.push_back(new Button(new sf::Sprite(m_Textures[0]), Utils::WinCenterX, 470, [=]()
			{
				*_state = GameState::Options;
				std::cout << "Entering Options Screen" << std::endl;
			}));

		// Quit Button
		m_Buttons.push_back(new Button(new sf::Sprite(m_Textures[0]), Utils::WinCenterX, 640, [=]()
			{
				*_state = GameState::Exiting;
				std::cout << "Exiting Game" << std::endl;
			}));

		// Title Text
		m_TextLabels.push_back(new sf::Text("THE RULER GAME", m_Font, 50));
		m_TextLabels[0]->setOrigin(m_TextLabels[0]->getGlobalBounds().width / 2, m_TextLabels[0]->getGlobalBounds().height / 2);
		m_TextLabels[0]->setPosition(Utils::WinCenterX, 100);
		// Play Button Text
		m_TextLabels.push_back(new sf::Text("PLAY", m_Font, 30));
		m_TextLabels[1]->setOrigin(m_TextLabels[1]->getGlobalBounds().width / 2, m_TextLabels[1]->getGlobalBounds().height / 2);
		m_TextLabels[1]->setPosition(m_Buttons[0]->GetPosition() - sf::Vector2f(0, 8));
		// Options Button Text
		m_TextLabels.push_back(new sf::Text("OPTIONS", m_Font, 30));
		m_TextLabels[2]->setOrigin(m_TextLabels[2]->getGlobalBounds().width / 2, m_TextLabels[2]->getGlobalBounds().height / 2);
		m_TextLabels[2]->setPosition(m_Buttons[1]->GetPosition() - sf::Vector2f(0, 8));
		// Quit Button Text
		m_TextLabels.push_back(new sf::Text("QUIT", m_Font, 30));
		m_TextLabels[3]->setOrigin(m_TextLabels[3]->getGlobalBounds().width / 2, m_TextLabels[3]->getGlobalBounds().height / 2);
		m_TextLabels[3]->setPosition(m_Buttons[2]->GetPosition() - sf::Vector2f(0, 8));

		// Player 1 Text
		m_TextLabels.push_back(new sf::Text("PLAYER ONE", m_Font, 30));
		m_TextLabels[4]->setOrigin(m_TextLabels[4]->getGlobalBounds().width / 2, m_TextLabels[4]->getGlobalBounds().height / 2);
		m_TextLabels[4]->setPosition(200, Utils::WinCenterY + 150);
		m_TextLabels[4]->setFillColor(sf::Color::Red);
		// Player 1 WS
		m_TextLabels.push_back(new sf::Text("W/S - Move Forward/Back", m_Font, 20));
		m_TextLabels[5]->setOrigin(m_TextLabels[5]->getGlobalBounds().width / 2, m_TextLabels[5]->getGlobalBounds().height / 2);
		m_TextLabels[5]->setPosition(200, Utils::WinCenterY + 190);
		m_TextLabels[5]->setFillColor(sf::Color::Red);
		// Player 1 AD
		m_TextLabels.push_back(new sf::Text("A/D - Rotate Left/Right", m_Font, 20));
		m_TextLabels[6]->setOrigin(m_TextLabels[6]->getGlobalBounds().width / 2, m_TextLabels[6]->getGlobalBounds().height / 2);
		m_TextLabels[6]->setPosition(200, Utils::WinCenterY + 220);
		m_TextLabels[6]->setFillColor(sf::Color::Red);
		// Player 1 Space
		m_TextLabels.push_back(new sf::Text("Space - Shoot", m_Font, 20));
		m_TextLabels[7]->setOrigin(m_TextLabels[7]->getGlobalBounds().width / 2, m_TextLabels[7]->getGlobalBounds().height / 2);
		m_TextLabels[7]->setPosition(200, Utils::WinCenterY + 250);
		m_TextLabels[7]->setFillColor(sf::Color::Red);
		// Player 1 E
		m_TextLabels.push_back(new sf::Text("E - Special Ability", m_Font, 20));
		m_TextLabels[8]->setOrigin(m_TextLabels[8]->getGlobalBounds().width / 2, m_TextLabels[8]->getGlobalBounds().height / 2);
		m_TextLabels[8]->setPosition(200, Utils::WinCenterY + 280);
		m_TextLabels[8]->setFillColor(sf::Color::Red);

		// Player 2 Text
		m_TextLabels.push_back(new sf::Text("PLAYER TWO", m_Font, 30));
		m_TextLabels[9]->setOrigin(m_TextLabels[9]->getGlobalBounds().width / 2, m_TextLabels[9]->getGlobalBounds().height / 2);
		m_TextLabels[9]->setPosition(Utils::WinSizeX - 200, Utils::WinCenterY + 150);
		m_TextLabels[9]->setFillColor(sf::Color::Cyan);
		// Player 2 UD
		m_TextLabels.push_back(new sf::Text("Up/Down - Move Forward/Back", m_Font, 20));
		m_TextLabels[10]->setOrigin(m_TextLabels[10]->getGlobalBounds().width / 2, m_TextLabels[10]->getGlobalBounds().height / 2);
		m_TextLabels[10]->setPosition(Utils::WinSizeX - 200, Utils::WinCenterY + 190);
		m_TextLabels[10]->setFillColor(sf::Color::Cyan);
		// Player 2 LR
		m_TextLabels.push_back(new sf::Text("Left/Right - Rotate Left/Right", m_Font, 20));
		m_TextLabels[11]->setOrigin(m_TextLabels[11]->getGlobalBounds().width / 2, m_TextLabels[11]->getGlobalBounds().height / 2);
		m_TextLabels[11]->setPosition(Utils::WinSizeX - 200, Utils::WinCenterY + 220);
		m_TextLabels[11]->setFillColor(sf::Color::Cyan);
		// Player 2 CTRL
		m_TextLabels.push_back(new sf::Text("CTRL - Shoot", m_Font, 20));
		m_TextLabels[12]->setOrigin(m_TextLabels[12]->getGlobalBounds().width / 2, m_TextLabels[12]->getGlobalBounds().height / 2);
		m_TextLabels[12]->setPosition(Utils::WinSizeX - 200, Utils::WinCenterY + 250);
		m_TextLabels[12]->setFillColor(sf::Color::Cyan);
		// Player 2 Shift
		m_TextLabels.push_back(new sf::Text("Shift - Special Ability", m_Font, 20));
		m_TextLabels[13]->setOrigin(m_TextLabels[13]->getGlobalBounds().width / 2, m_TextLabels[13]->getGlobalBounds().height / 2);
		m_TextLabels[13]->setPosition(Utils::WinSizeX - 200, Utils::WinCenterY + 280);
		m_TextLabels[13]->setFillColor(sf::Color::Cyan);
	}
	else if (*_state == GameState::Options)
	{
		// Buttons and text for the options screen

		// Increase Movement Speed
		m_Buttons.push_back(new Button(new sf::Sprite(m_Textures[1]), Utils::WinCenterX + 200, 200, [=]()
			{
				*_gameData.BaseMoveSpeed += 0.5f;
				std::cout << "Increased base movement speed from " << *_gameData.BaseMoveSpeed - 0.5f << " to " << *_gameData.BaseMoveSpeed << std::endl;
			}));

		// Decrease Movement Speed
		m_Buttons.push_back(new Button(new sf::Sprite(m_Textures[2]), Utils::WinCenterX - 200, 200, [=]()
			{
				*_gameData.BaseMoveSpeed -= 0.5f;
				std::cout << "Decreased base movement speed from " << *_gameData.BaseMoveSpeed + 0.5f << " to " << *_gameData.BaseMoveSpeed << std::endl;
			}));

		// Increase Fire Rate (Decrease Fire Delay)
		m_Buttons.push_back(new Button(new sf::Sprite(m_Textures[1]), Utils::WinCenterX + 170, 300, [=]()
			{
				*_gameData.BaseFireDelay -= 0.05f;
				std::cout << "Increased base fire rate from " << 1.0f / (* _gameData.BaseFireDelay + 0.5f) << " to " << 1.0f / *_gameData.BaseFireDelay << std::endl;
			}));

		// Decrease Fire Rate (Increase Fire Delay)
		m_Buttons.push_back(new Button(new sf::Sprite(m_Textures[2]), Utils::WinCenterX - 170, 300, [=]()
			{
				*_gameData.BaseFireDelay += 0.05f;
				std::cout << "Decreased base fire rate from " << 1.0f / (*_gameData.BaseFireDelay - 0.5f) << " to " << 1.0f / *_gameData.BaseFireDelay << std::endl;
			}));

		// Increase Spawn Rate (Decrease Spawn Delay)
		m_Buttons.push_back(new Button(new sf::Sprite(m_Textures[1]), Utils::WinCenterX + 185, 400, [=]()
			{
				*_gameData.PickupSpawnDelay -= 1.0f;
				std::cout << "Increased pickup spawn rate" << std::endl;
			}));

		// Decrease Spawn Rate (Increase Spawn Delay)
		m_Buttons.push_back(new Button(new sf::Sprite(m_Textures[2]), Utils::WinCenterX - 185, 400, [=]()
			{
				*_gameData.PickupSpawnDelay += 1.0f;
				std::cout << "Decreased pickup spawn rate" << std::endl;
			}));

		// Increase Timer Duration
		m_Buttons.push_back(new Button(new sf::Sprite(m_Textures[1]), Utils::WinCenterX + 170, 500, [=]()
			{
				*_gameData.TimerLength += 1.0f;
				std::cout << "Increased timer duration from " << *_gameData.TimerLength - 1.0f << " to " << *_gameData.TimerLength << std::endl;
			}));

		// Decrease Timer Duration
		m_Buttons.push_back(new Button(new sf::Sprite(m_Textures[2]), Utils::WinCenterX - 170, 500, [=]()
			{
				*_gameData.TimerLength -= 1.0f;
				std::cout << "Decreased timer duration from " << *_gameData.TimerLength + 1.0f << " to " << *_gameData.TimerLength << std::endl;
			}));

		// Increase Volume
		m_Buttons.push_back(new Button(new sf::Sprite(m_Textures[1]), Utils::WinCenterX + 170, 600, [=]()
			{
				*_gameData.Volume += 5.0f;
				std::cout << "Increased audio volume from " << *_gameData.Volume - 5.0f << " to " << *_gameData.Volume << std::endl;
			}));

		// Decrease Volume
		m_Buttons.push_back(new Button(new sf::Sprite(m_Textures[2]), Utils::WinCenterX - 170, 600, [=]()
			{
				*_gameData.Volume -= 5.0f;
				std::cout << "Decreased audio volume from " << *_gameData.Volume + 5.0f << " to " << *_gameData.Volume << std::endl;
			}));

		// Back to Main Menu
		m_Buttons.push_back(new Button(new sf::Sprite(m_Textures[0]), Utils::WinCenterX, 670, [=]()
			{
				*_state = GameState::MainMenu;
				std::cout << "Returning to Main Menu" << std::endl;
			}));

		// Movement Speed Text
		m_TextLabels.push_back(new sf::Text("Base Movement Speed", m_Font, 30));
		m_TextLabels[0]->setOrigin(m_TextLabels[0]->getGlobalBounds().width / 2, m_TextLabels[0]->getGlobalBounds().height / 2);
		m_TextLabels[0]->setPosition(Utils::WinCenterX, 200);

		// Fire Rate Text
		m_TextLabels.push_back(new sf::Text("Base Fire Rate", m_Font, 30));
		m_TextLabels[1]->setOrigin(m_TextLabels[1]->getGlobalBounds().width / 2, m_TextLabels[1]->getGlobalBounds().height / 2);
		m_TextLabels[1]->setPosition(Utils::WinCenterX, 300);

		// Pickup Spawn Rate Text
		m_TextLabels.push_back(new sf::Text("Pickup Spawn Rate", m_Font, 30));
		m_TextLabels[2]->setOrigin(m_TextLabels[2]->getGlobalBounds().width / 2, m_TextLabels[2]->getGlobalBounds().height / 2);
		m_TextLabels[2]->setPosition(Utils::WinCenterX, 400);

		// Timer Length Text
		m_TextLabels.push_back(new sf::Text("Timer Duration", m_Font, 30));
		m_TextLabels[3]->setOrigin(m_TextLabels[3]->getGlobalBounds().width / 2, m_TextLabels[3]->getGlobalBounds().height / 2);
		m_TextLabels[3]->setPosition(Utils::WinCenterX, 500);

		// Volume Text
		m_TextLabels.push_back(new sf::Text("Audio Volume", m_Font, 30));
		m_TextLabels[4]->setOrigin(m_TextLabels[4]->getGlobalBounds().width / 2, m_TextLabels[4]->getGlobalBounds().height / 2);
		m_TextLabels[4]->setPosition(Utils::WinCenterX, 600);

		// Options Text
		m_TextLabels.push_back(new sf::Text("OPTIONS", m_Font, 50));
		m_TextLabels[5]->setOrigin(m_TextLabels[5]->getGlobalBounds().width / 2, m_TextLabels[5]->getGlobalBounds().height / 2);
		m_TextLabels[5]->setPosition(Utils::WinCenterX, 70);

		// Return Text
		m_TextLabels.push_back(new sf::Text("RETURN", m_Font, 30));
		m_TextLabels[6]->setOrigin(m_TextLabels[6]->getGlobalBounds().width / 2, m_TextLabels[6]->getGlobalBounds().height / 2);
		m_TextLabels[6]->setPosition(Utils::WinCenterX, 660);
	}
	else if (*_state == GameState::Gameplay)
	{
		// Timer Text
		m_TextLabels.push_back(new sf::Text("60", m_Font, 50));
		m_TextLabels[0]->setOrigin(m_TextLabels[0]->getGlobalBounds().width / 2, m_TextLabels[0]->getGlobalBounds().height / 2);
		m_TextLabels[0]->setPosition(Utils::WinCenterX, 50);

		// Player One Pickup Text
		m_TextLabels.push_back(new sf::Text("Pickup: ", m_Font, 30));
		m_TextLabels[1]->setOrigin(m_TextLabels[1]->getGlobalBounds().width / 2, m_TextLabels[1]->getGlobalBounds().height / 2);
		m_TextLabels[1]->setPosition(250, 50);
		m_TextLabels[1]->setFillColor(sf::Color::Red);

		// Player Two Pickup Text
		m_TextLabels.push_back(new sf::Text("Pickup: ", m_Font, 30));
		m_TextLabels[2]->setOrigin(m_TextLabels[2]->getGlobalBounds().width / 2, m_TextLabels[2]->getGlobalBounds().height / 2);
		m_TextLabels[2]->setPosition(Utils::WinSizeX - 250, 50);
		m_TextLabels[2]->setFillColor(sf::Color::Cyan);
	}
	else if (*_state == GameState::EndScreen)
	{
		// Return to Main Menu Button
		m_Buttons.push_back(new Button(new sf::Sprite(m_Textures[0]), Utils::WinCenterX, 700, [=]()
		{
			*_state = GameState::MainMenu;
			std::cout << "Returning to Main Menu" << std::endl;
		}));

		// Game Over Text
		m_TextLabels.push_back(new sf::Text("GAME OVER", m_Font, 50));
		m_TextLabels[0]->setOrigin(m_TextLabels[0]->getGlobalBounds().width / 2, m_TextLabels[0]->getGlobalBounds().height / 2);
		m_TextLabels[0]->setPosition(Utils::WinCenterX, 70);

		// Winner Text
		m_TextLabels.push_back(new sf::Text(_gameData.WinnerText, m_Font, 42));
		m_TextLabels[1]->setOrigin(m_TextLabels[1]->getGlobalBounds().width / 2, m_TextLabels[1]->getGlobalBounds().height / 2);
		m_TextLabels[1]->setPosition(Utils::WinCenterX, 150);

		// Return to Main Menu Text
		m_TextLabels.push_back(new sf::Text("RETURN", m_Font, 30));
		m_TextLabels[2]->setOrigin(m_TextLabels[2]->getGlobalBounds().width / 2, m_TextLabels[2]->getGlobalBounds().height / 2);
		m_TextLabels[2]->setPosition(Utils::WinCenterX, 690);
	}
}

std::string UIManager::PickupTypeToName(PickupType _pickupType)
{
	switch (_pickupType)
	{
	case PickupType::type_AttackSpeed:
		return "Attack Speed";
		break;

	case PickupType::type_Bomb:
		return "Bomb";
		break;

	case PickupType::type_Knockback:
		return "Knockback";
		break;

	case PickupType::type_Laser:
		return "Laser";
		break;

	case PickupType::type_None:
		return "None";
		break;

	default:
		break;
	}

	return "test";
}

void UIManager::LoadTextures()
{
	// Load textures from files and add them to the vector
}

void UIManager::PollButtons(sf::RenderWindow* _window)
{
	for (Button* CurrentButton : m_Buttons)
	{
		// If button rect contains mouse position, activate button's OnClick and break the loop 
		if (CurrentButton->GetSprite() != nullptr && CurrentButton->GetSprite()->getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*_window)))
		{
			std::cout << "Button Clicked" << std::endl;
			CurrentButton->ActivateOnClick();
			break;
		}
	}
}

void UIManager::Update(GameState* _state, UIManager::GameData _gameData, float _timeRemaining)
{
	if (*_state != m_PreviousState)
	{
		m_PreviousState = *_state;
		UpdateDisplayState(_state, _gameData);
	}

	// In gameplay display mode, update the timer text based on the remaining time
	if (*_state == GameState::Gameplay)
	{
		m_TextLabels[0]->setString(std::to_string((int)_timeRemaining));
		m_TextLabels[0]->setOrigin(m_TextLabels[0]->getGlobalBounds().width / 2, m_TextLabels[0]->getGlobalBounds().height / 2);
		m_TextLabels[0]->setPosition(Utils::WinCenterX, 50);

		m_TextLabels[1]->setString("Pickup: " + PickupTypeToName(_gameData.PlayerOnePickup));
		m_TextLabels[1]->setOrigin(m_TextLabels[1]->getGlobalBounds().width / 2, m_TextLabels[1]->getGlobalBounds().height / 2);
		m_TextLabels[1]->setPosition(250, 50);

		m_TextLabels[2]->setString("Pickup: " + PickupTypeToName(_gameData.PlayerTwoPickup));
		m_TextLabels[2]->setOrigin(m_TextLabels[2]->getGlobalBounds().width / 2, m_TextLabels[2]->getGlobalBounds().height / 2);
		m_TextLabels[2]->setPosition(Utils::WinSizeX - 250, 50);
	}
}

void UIManager::Render(sf::RenderWindow* _window)
{
	// Render all buttons
	for (Button* CurrentButton : m_Buttons)
	{
		CurrentButton->Render(_window);
	}

	// Render all text
	for (sf::Text* CurrentText : m_TextLabels)
	{
		_window->draw(*CurrentText);
	}
}
