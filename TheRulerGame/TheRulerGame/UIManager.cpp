#include "UIManager.h"
#include "Utils.h"
#include <iostream>

UIManager::UIManager()
{
	m_Font.loadFromFile("arial.ttf");
	m_Textures.push_back(sf::Texture());
	m_Textures[0].loadFromFile("Button.png");
}

UIManager::~UIManager()
{
}

void UIManager::UpdateDisplayState(GameState* _state, UIManager::GameData)
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
	}
	else if (*_state == GameState::Options)
	{
		// Buttons and text for the options screen
	}
	else if (*_state == GameState::Gameplay)
	{
		// Title Text
		m_TextLabels.push_back(new sf::Text("60", m_Font, 50));
		m_TextLabels[0]->setOrigin(m_TextLabels[0]->getGlobalBounds().width / 2, m_TextLabels[0]->getGlobalBounds().height / 2);
		m_TextLabels[0]->setPosition(Utils::WinCenterX, 50);
	}
	else if (*_state == GameState::EndScreen)
	{
		// Buttons and text for the end screen
	}
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

void UIManager::Update(GameState* _state, float _timeRemaining)
{
	if (*_state != m_PreviousState)
	{
		m_PreviousState = *_state;
		UpdateDisplayState(_state, GameData());
	}

	// In gameplay display mode, update the timer text based on the remaining time
	if (*_state == GameState::Gameplay)
	{
		m_TextLabels[0]->setString(std::to_string((int)_timeRemaining));
		m_TextLabels[0]->setOrigin(m_TextLabels[0]->getGlobalBounds().width / 2, m_TextLabels[0]->getGlobalBounds().height / 2);
		m_TextLabels[0]->setPosition(Utils::WinCenterX, 50);
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
