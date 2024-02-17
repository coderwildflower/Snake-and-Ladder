#include <SFML/Graphics.hpp>
#include <iostream>

#include "Dice.h"
#include "Button.h"
#include "Board.h"
#include "Player.h"

int main()
{
	// Create the main game window
	sf::RenderWindow window(sf::VideoMode(900, 900), "Snake and Ladder");

	Dice _dice;
	Button _diceRollBtn(450, 800, 100, 100, "ROLL", sf::Color::White, sf::Color::Cyan, sf::Color::Green, "");

	Board _board;
	_board.InitializeBoard(window);

	Player _player;
	_player.InitializePlayer();
	_player.playerPos = 0;

	bool canClick = true;

	//Main Game Loop ------------------------------------------------------------------------------------------
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
						//sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
						//std::cout << "Mouse Position: (" << mousePosition.x << ", " << mousePosition.y << ")" << std::endl;
					
					if (_diceRollBtn.isMouseOver(window))
					{
						int diceNumber = _dice.GetRandomNum();
						_player.MovePlayer(diceNumber);

						std::cout << diceNumber << std::endl;
						std::cout << _player.playerPos ;
						std::cout << "\n";

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

		//-------------------------------------------------------------------------------------------------

		window.clear();

		window.draw(_board.boardSprite);
		_diceRollBtn.UpdateColor(window);
		_diceRollBtn.RenderButton(window);
		window.draw(_player.playerSprite);

		window.display();
	}

	return 0;
}