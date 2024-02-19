#include <SFML/Graphics.hpp>
#include <iostream>

#include "Dice.h"
#include "Button.h"
#include "Board.h"
#include "Player.h"

int main()
{
	// Create the main game window ---------------------------------------------------------------------------
	sf::RenderWindow window(sf::VideoMode(900, 900), "Snake and Ladder");
	sf::Clock gameClock;
	window.setFramerateLimit(60);
	//--------------------------------------------------------------------------------------------------------

	Dice _dice;
	_dice.InitializeDice();

	Button _diceRollBtn(400, 750, 100, 100, 414 ,767, "ROLL", sf::Color::White, sf::Color::Cyan, sf::Color::Green, "assets/textures/Dice_static.png");
	_diceRollBtn.btnSprite.setTextureRect((sf::IntRect(0, 0, 128.67, 69))); //x,y,w,h to show single image from texture grid

	Board _board;
	_board.InitializeBoard(window);

	Player _player;
	_player.InitializePlayer();

	bool canClick = true;

	//Main Game Loop ------------------------------------------------------------------------------------------
	while (window.isOpen())
	{
		_dice.RollDice(gameClock);

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
					if (_diceRollBtn.isMouseOver(window))
					{
					
						int diceNumber = _dice.GetRandomNum();
						_player.MovePlayer(diceNumber);

						std::cout << diceNumber;
						std::cout << "\n";
						std::cout << _player.playerPos;
						std::cout << "\n\n";

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

		// ----------------------------------------------------------------------------------------------------

		window.clear(sf::Color(55, 80, 82,255));


		window.draw(_board.boardSprite);
		_diceRollBtn.UpdateColor(window);
		_diceRollBtn.RenderButton(window);
		window.draw(_player.playerSprite);
		window.draw(_dice.diceAnimSprite);

		window.display();
	}

	return 0;
}