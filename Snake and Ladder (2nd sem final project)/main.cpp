#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>

#include "Dice.h"
#include "Button.h"
#include "Board.h"
#include "Player.h"

int main()
{
	// Create the main game window ---------------------------------------------------------------------------
	sf::RenderWindow window(sf::VideoMode(900, 900), "Snake and Ladder");
	window.setFramerateLimit(60);
	float elaspedTime = 0;
	float deltaTime = 0;
	sf::Clock gameClock;
	//--------------------------------------------------------------------------------------------------------

	Dice _dice;
	_dice.InitializeDice();
	int diceNumber = 0;

	Button _diceRollBtn(400, 750, 100, 100, 414, 767, "", sf::Color::White, sf::Color::Cyan, sf::Color::Green, "");
	_diceRollBtn.btnSprite.setTextureRect((sf::IntRect(0, 0, 128.67, 69))); //x,y,w,h to show single image from texture grid

	Board _board;
	_board.InitializeBoard(window);

	Player _player;
	_player.InitializePlayer();
	_player.startPlayerPosition.x = 20;
	_player.startPlayerPosition.y = 700;
	float percent = 0.f;

	bool canClick = true;
	bool isRolling = false;
	bool canClimb = false;

	//Main Game Loop ------------------------------------------------------------------------------------------
	while (window.isOpen())
	{
		deltaTime = gameClock.restart().asSeconds();
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
						isRolling = true;
						canClick = false;

						diceNumber = _dice.GetRandomNum();
						//_dice.RollDice(elaspedTime);
						_dice.diceAnimSprite.setTextureRect(_dice.diceFace[diceNumber - 1]);

						_player.setPos(1);
						  
						std::cout << diceNumber << ": Dice Number";
						std::cout << "\n";
						std::cout << _player.playerPosIndex << ": Player Position";
						std::cout << "\n\n";
					}
				}

			case sf::Event::MouseButtonReleased:
				//canClick = true;
				break;

			default:
				break;
			}

		}

		if (isRolling)
		{
			elaspedTime += deltaTime;

			percent = elaspedTime / 0.3f;
			percent = std::min(percent, 1.f); //limit percant from 0 to 1

			//First Move normally according to dice roll number-----------------------
			sf::Vector2f tempPos = BoardCellPosition[_player.playerPosIndex - 1];
			_player.playerSprite.setPosition(_player.lerp(_player.startPlayerPosition, tempPos, percent)); 

			if (percent > 0.99f && !canClimb)
			{
				_player.playerSprite.setPosition(tempPos);
				_player.startPlayerPosition = tempPos;

				elaspedTime = 0.00f;
				percent = 0;

				_player.finalPlayerPosition = _player.finalPos(_board); //set x and y of target cell
				if (_player.foundSnakeorLadder) canClimb = true; // check if snake or ladder is found
				else {
					canClick = true;
					isRolling = false;
				}

			}

			//Then Climb or Fall if any snake or ladder is encountered
			if (canClimb)
			{
				_player.playerSprite.setPosition(_player.lerp(_player.startPlayerPosition, _player.finalPlayerPosition, percent));
				if (percent > 0.99f)
				{
					_player.playerSprite.setPosition(_player.finalPlayerPosition);
					_player.startPlayerPosition = _player.finalPlayerPosition;

					//reset
					elaspedTime = 0.00f;
					percent = 0;
					canClick = true;
					isRolling = false;
					canClimb = false;
				}
			}

		}

		// ----------------------------------------------------------------------------------------------------

		window.clear(sf::Color(54, 54, 54, 255));

		window.draw(_board.boardSprite);
		_diceRollBtn.UpdateColor(window);
		_diceRollBtn.RenderButton(window);
		window.draw(_player.playerSprite);
		window.draw(_dice.diceAnimSprite);

		window.display();

	}

	return 0;
}