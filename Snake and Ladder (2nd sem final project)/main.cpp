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
	Button(float posX, float posY, float width, float height, std::string text,sf::Color idleColor, sf::Color hoverColor, sf::Color clickColor, std::string imagePath = "") {

		shape.setSize(sf::Vector2f(width, height));
		shape.setPosition(sf::Vector2f(posX, posY));
		shape.setFillColor(this->btnIdleColor);

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
		sf::Vector2f btnSize = shape.getSize();
		sf::Vector2f btnPos = shape.getPosition();

		if (mousePos.x >= btnPos.x && mousePos.x <= btnPos.x + btnSize.x &&
			mousePos.y >= btnPos.y && mousePos.y <= btnPos.y + btnSize.y)
			return true;
	}

	void SetIdleColor() {
		shape.setFillColor(btnIdleColor);
	}

	void SetHoverColor() {
		shape.setFillColor(btnHoverColor);
	}

	void SetclickColor() {
		shape.setFillColor(btnClickColor);
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
	Button _diceRollBtn(450,800,100,100,"ROLL",sf::Color::White, sf::Color::Cyan,sf::Color::Green);

	// Create the main game window
	sf::RenderWindow window(sf::VideoMode(900, 900), "Snake and Ladder");

	//Set all gameobjects texutre and its height and width -------------------------------------------------------------------
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

	 // ------------------------------------------------------------------------------------------------------------------------

	 //Main Game Loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			//Mouse position and click handler ---------------------------------------------------------
			if (_diceRollBtn.isMouseOver(window))
			{
				_diceRollBtn.SetHoverColor();
				if (event.type == sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					std::cout<<_dice.GetRandomNum();
					_diceRollBtn.SetclickColor();
				}
			}
			else _diceRollBtn.SetIdleColor();
			
		}


		//--------------------------------------------------------------------------------------------
		window.clear();
		window.draw(board);
		_diceRollBtn.RenderButton(window);
		window.display();
	}

	return 0;
}