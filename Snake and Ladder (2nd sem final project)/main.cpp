#include <SFML/Graphics.hpp>
#include <iostream>

#include "Dice.h"

class Button {

private:
	sf::RectangleShape shape;
	sf::Text btnText;
	sf::Font textFont;
	sf::Color btnIdleColor = sf::Color::White;
	sf::Color btnHoverColor;
	sf::Color btnClickColor;
	sf::Texture btnTexture;
	sf::Sprite btnSprite;

	//Constructor
public:
	Button(float posX, float posY, float width, float height, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color clickColor, std::string imagePath = "") {

		shape.setSize(sf::Vector2f(width, height));
		shape.setPosition(sf::Vector2f(posX, posY));
		shape.setFillColor(btnIdleColor);
		btnHoverColor = hoverColor;
		btnClickColor = clickColor;

		textFont.loadFromFile("assets/OpenSans-Regular.ttf");
		btnText.setFont(textFont);
		btnText.setString(text);
		btnText.setCharacterSize(15);
		btnText.setFillColor(sf::Color::Black);

		//centre align the text inside the button
		btnText.setPosition(shape.getPosition().x + (shape.getSize().x / 2 - btnText.getGlobalBounds().width / 2),
			shape.getPosition().y + (shape.getSize().y / 2 - btnText.getGlobalBounds().height / 2));

		if (!imagePath.empty())
		{
			if (!btnTexture.loadFromFile(imagePath))
				std::cerr << "Failed to load texture!" << std::endl;

			btnSprite.setTexture(btnTexture);
			btnSprite.setPosition(posX, posY);
			btnSprite.setScale(width / btnTexture.getSize().x / 2, height / btnTexture.getSize().y / 2);
		}
	};

	//check if mouse is inside button or not
	bool isMouseOver(sf::RenderWindow& window)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		sf::FloatRect buttonRect = shape.getGlobalBounds();
		if (buttonRect.contains(sf::Vector2f(mousePos)))
			return true;
		else {
			shape.setFillColor(btnIdleColor);
			return false;
		}
	}

	void UpdateColor(sf::RenderWindow& window)
	{
		if (isMouseOver(window))
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				shape.setFillColor(btnClickColor);
			}
			else shape.setFillColor(btnHoverColor);
		}
	}

	void RenderButton(sf::RenderWindow& window)
	{
		window.draw(shape);
		window.draw(btnText);
		window.draw(btnSprite);
	}
};


int main()
{
	Dice _dice;
	Button _diceRollBtn(450, 800, 100, 100, "ROLL", sf::Color::White, sf::Color::Cyan, sf::Color::Green);

	// Create the main game window
	sf::RenderWindow window(sf::VideoMode(900, 900), "Snake and Ladder");

	//Set all gameobject's texutre and its height and width -------------------------------------------------------------------
	sf::Texture boardTexture;
	sf::Sprite board;

	float boardWidth = 700;
	float boardHeight = 700;

	boardTexture.loadFromFile("assets/textures/board.png");

	//board sprite setup in scene ---------------------
	boardTexture.setSmooth(true);
	board.setTexture(boardTexture);
	board.setScale(boardWidth / board.getLocalBounds().width, boardHeight / board.getLocalBounds().height);
	board.setPosition(450 - boardWidth / 2, 20);
	bool canClick = true;
	// ------------------------------------------------------------------------------------------------------------------------

	//Main Game Loop
	while (window.isOpen())
	{
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				
			case sf::Event::Closed:
				window.close();
				break;

				
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left && canClick)
				{
					//Dice Roll Button
					if (_diceRollBtn.isMouseOver(window))
					{
						int diceNumber = _dice.GetRandomNum();
						std::cout << diceNumber;
						canClick = false;
					}
				}

			case sf::Event::MouseButtonReleased:
				canClick = true;
					break;

			
			default:
				break;
			}
		}
	
		//--------------------------------------------------------------------------------------------
		_diceRollBtn.UpdateColor(window);
		window.clear();
		window.draw(board);
		_diceRollBtn.RenderButton(window);
		window.display();
	}

	return 0;
}