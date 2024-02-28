#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>

#include "Dice.h"
#include "Button.h"
#include "Board.h"
#include "Player.h"
#include "PlayerSwitch.h"
#include "Sound.h"

int main()
{
	// Create the main game window ---------------------------------------------------------------------------
	sf::RenderWindow window(sf::VideoMode(900, 900), "Snake and Ladder");
	window.setFramerateLimit(60);
	float elaspedTime = 0;
	float deltaTime = 0;
	sf::Clock gameClock;

	// Create DIce Object--------------------------
	Dice _dice;
	_dice.InitializeDice();
	int diceNumber = 0;

	//Create Dice Roll Button------------------
	Button _diceRollBtn(400, 750, 100, 100, 414, 767, "", sf::Color::White, sf::Color::Cyan, sf::Color::Green, "");

	//Create Snake and Ladder board----------------
	Board _board;
	_board.InitializeBoard(window);

	Sound _sound;
	_sound.loadAllAudio();

	//Setup total players --------------------------
	PlayerManager _manager;
	_manager.SetPlayer(4);
	int turn = _manager.playerTurn = 0;
	for (int i = 0; i < 4; i++)
	{
		_manager.players[i].InitializePlayer(i);
	}
	_manager.SetTurnArrow(turn);
	_manager.displayArrow = true;

	float percent = 0.f;

	bool canClick = true;
	bool isRolling = false;
	bool ClimborFall = false;

	//Main Game Loop ------------------------------------------------------------------------------------------
	while (window.isOpen())
	{
		deltaTime = gameClock.restart().asSeconds();
		sf::Event event;

		_manager.AnimateArrow(deltaTime);

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
						_sound.PlayDiceRoll();
						_manager.displayArrow = false;
						isRolling = true;
						canClick = false;

						diceNumber = _dice.GetRandomNum(); //get random number
						//_dice.RollDice(elaspedTime);
						_dice.diceAnimSprite.setTextureRect(_dice.diceFace[diceNumber - 1]); //set the dice face to the given number
						_manager.players[turn].setPos(diceNumber);//set the position of the player

						std::cout << diceNumber << ": Dice Number";
						std::cout << "\n";
						std::cout << _manager.players[turn].playerPosIndex << ": Position of Player" << turn + 1;
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

			percent = elaspedTime / 0.5f;
			percent = std::min(percent, 1.f); //limit percant from 0 to 1

			//First Move normally according to dice roll number-----------------------
			sf::Vector2f tempPos = BoardCellPosition[_manager.players[turn].playerPosIndex - 1];
			_manager.players[turn].playerSprite.setPosition(_manager.players[turn].lerp(_manager.players[turn].startPlayerPosition, tempPos, percent));

			if (percent > 0.99f && !ClimborFall)
			{
				_manager.players[turn].playerSprite.setPosition(tempPos); //snap current pos to final pos at the end of percantage
				_manager.players[turn].startPlayerPosition = tempPos;

				elaspedTime = 0.00f;
				percent = 0;

				_manager.players[turn].finalPlayerPosition = _manager.players[turn].finalPos(_board); //set x and y of target cell

				if (_manager.players[turn].foundLadder) // check if snake or ladder is found
				{
					_sound.PlayLadder();
					ClimborFall = true;
				}
				else if (_manager.players[turn].foundSnake)
				{
					_sound.PlaySnake();
					ClimborFall = true;
				}
				else {
					canClick = true;
					isRolling = false;

					turn++; //switch turn
					if (turn > 3) turn = 0;
					_manager.SetTurnArrow(turn);
					_manager.displayArrow = true;
				}

			}

			//Then Climb or Fall if any snake or ladder is encountered
			if (ClimborFall)
			{
				_manager.players[turn].playerSprite.setPosition(_manager.players[turn].lerp(_manager.players[turn].startPlayerPosition, _manager.players[turn].finalPlayerPosition, percent));
				if (percent > 0.99f)
				{
					_manager.players[turn].playerSprite.setPosition(_manager.players[turn].finalPlayerPosition);
					_manager.players[turn].startPlayerPosition = _manager.players[turn].finalPlayerPosition;

					//reset
					elaspedTime = 0.00f;
					percent = 0;
					canClick = true;
					isRolling = false;
					ClimborFall = false;

					turn++; // //switch turn
					if (turn > 3) turn = 0;
					_manager.SetTurnArrow(turn);
					_manager.displayArrow = true;
				}
			}
		}

		// ----------------------------------------------------------------------------------------------------

		window.clear();

		window.draw(_board.bgSprite);
		window.draw(_board.boardSprite);
		_diceRollBtn.UpdateColor(window);
		_diceRollBtn.RenderButton(window);
		window.draw(_dice.diceAnimSprite);
		if (_manager.displayArrow) window.draw(_manager.arrowSprite);

		for (int i = 0; i < 4; i++) //draw 4 players
		{
			window.draw(_manager.players[i].playerSprite);
		}

		window.display();
	}

	return 0;
}