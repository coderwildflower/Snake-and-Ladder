#include <SFML/Graphics.hpp>
#include <iostream>

#include "Dice.h"
#include "Button.h"

int main()
{
	Dice _dice;
	Button _diceRollBtn(450, 800, 100, 100, "ROLL", sf::Color::White, sf::Color::Cyan, sf::Color::Green,"");

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