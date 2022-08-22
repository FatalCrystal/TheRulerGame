#include "UIManager.h"
#include "Utils.h"

UIManager::UIManager()
{
	// m_Font.loadFromFile(".ttf");

	SetCurrentDisplay(UIDisplay::MainMenu, UIManager::GameData());
}

UIManager::~UIManager()
{
}

void UIManager::SetCurrentDisplay(UIDisplay _display, UIManager::GameData)
{
	// Set current display
	m_CurrentDisplay = _display;

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
	if (m_CurrentDisplay == UIDisplay::MainMenu)
	{
		// Play Button
		m_Buttons.push_back(new Button(nullptr, 0, 0, []() {}));
		// Options Button
		m_Buttons.push_back(new Button(nullptr, 0, 0, []() {}));
		// Quit Button
		m_Buttons.push_back(new Button(nullptr, 0, 0, []() {}));

		// Title Text
		m_TextLabels.push_back(new sf::Text("THE RULER GAME", m_Font, 50));
		m_TextLabels[0]->setOrigin(m_TextLabels[0]->getGlobalBounds().width / 2, m_TextLabels[0]->getGlobalBounds().height / 2);
		m_TextLabels[0]->setPosition(Utils::WinCenterX, 100);
		// Play Button Text
		m_TextLabels.push_back(new sf::Text("PLAY", m_Font, 30));
		m_TextLabels[1]->setOrigin(m_TextLabels[1]->getGlobalBounds().width / 2, m_TextLabels[1]->getGlobalBounds().height / 2);
		m_TextLabels[1]->setPosition(m_Buttons[0]->GetPosition());
		// Options Button Text
		m_TextLabels.push_back(new sf::Text("OPTIONS", m_Font, 30));
		m_TextLabels[2]->setOrigin(m_TextLabels[2]->getGlobalBounds().width / 2, m_TextLabels[2]->getGlobalBounds().height / 2);
		m_TextLabels[2]->setPosition(m_Buttons[1]->GetPosition());
		// Quit Button Text
		m_TextLabels.push_back(new sf::Text("QUIT", m_Font, 30));
		m_TextLabels[3]->setOrigin(m_TextLabels[3]->getGlobalBounds().width / 2, m_TextLabels[3]->getGlobalBounds().height / 2);
		m_TextLabels[3]->setPosition(m_Buttons[2]->GetPosition());
	}
	else if (m_CurrentDisplay == UIDisplay::Options)
	{
		// Buttons and text for the options screen
	}
	else if (m_CurrentDisplay == UIDisplay::Gameplay)
	{
		// Title Text
		m_TextLabels.push_back(new sf::Text("60", m_Font, 50));
		m_TextLabels[0]->setOrigin(m_TextLabels[0]->getGlobalBounds().width / 2, m_TextLabels[0]->getGlobalBounds().height / 2);
		m_TextLabels[0]->setPosition(Utils::WinCenterX, 50);
	}
	else if (m_CurrentDisplay == UIDisplay::EndScreen)
	{
		// Buttons and text for the end screen
	}
}

UIDisplay UIManager::GetCurrentDisplay() const
{
	return m_CurrentDisplay;
}

void UIManager::LoadTextures()
{
	// Load textures from files and add them to the vector
}

void UIManager::PollButtons()
{
	for (Button* CurrentButton : m_Buttons)
	{
		// If button rect contains mouse position, activate button's OnClick and break the loop 
		if (CurrentButton->GetSprite()->getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition()))
		{
			CurrentButton->ActivateOnClick();
			break;
		}
	}
}

void UIManager::Update(float _timeRemaining)
{
	// In gameplay display mode, update the timer text based on the remaining time
	if (m_CurrentDisplay == UIDisplay::Gameplay)
	{
		m_TextLabels[0]->setString(std::to_string(_timeRemaining));
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
