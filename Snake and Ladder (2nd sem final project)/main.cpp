#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>

#include "Dice.h"
#include "Button.h"
#include "Board.h"
#include "Player.h"
#include "PlayerSwitch.h"

int main()
{
	// Create the main game window ---------------------------------------------------------------------------
	sf::RenderWindow window(sf::VideoMode(900, 900), "Snake and Ladder");
	window.setFramerateLimit(60);
	float elaspedTime = 0;
	float deltaTime = 0;
	sf::Clock gameClock;
	
	// Create DIce Object---------------
	Dice _dice;
	_dice.InitializeDice();
	int diceNumber = 0;

	//Create Dice Roll Button--------------
	Button _diceRollBtn(400, 750, 100, 100, 414, 767, "", sf::Color::White, sf::Color::Cyan, sf::Color::Green, "");
	//_diceRollBtn.btnSprite.setTextureRect((sf::IntRect(0, 0, 128.67, 69))); //x,y,w,h to show single image from texture grid

	//Create Snake and Ladder board----------------
	Board _board;
	_board.InitializeBoard(window);

	//Setup total players ----------------------
	PlayerManager manager;
	manager.SetPlayer(4);
	int turn = manager.playerTurn = 0;
	for (int i = 0; i < 4; i++)
	{
		manager.players[i].InitializePlayer(i);
	}

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

						diceNumber = _dice.GetRandomNum(); //get random number
						//_dice.RollDice(elaspedTime);
						_dice.diceAnimSprite.setTextureRect(_dice.diceFace[diceNumber - 1]); //set the dice face to the given number
						manager.players[turn].setPos(diceNumber);//set the position of the player
						  
						std::cout << diceNumber << ": Dice Number";
						std::cout << "\n";
						std::cout << manager.players[turn].playerPosIndex << ": Position of Player" << turn+1;
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
			sf::Vector2f tempPos = BoardCellPosition[manager.players[turn].playerPosIndex - 1];
			manager.players[turn].playerSprite.setPosition(manager.players[turn].lerp(manager.players[turn].startPlayerPosition, tempPos, percent));

			if (percent > 0.99f && !canClimb)
			{
				manager.players[turn].playerSprite.setPosition(tempPos); //snap current pos to final pos at the end of percantage
				manager.players[turn].startPlayerPosition = tempPos;

				elaspedTime = 0.00f;
				percent = 0;

				manager.players[turn].finalPlayerPosition = manager.players[turn].finalPos(_board); //set x and y of target cell
				if (manager.players[turn].foundSnakeorLadder) canClimb = true; // check if snake or ladder is found
				else {
					canClick = true;
					isRolling = false;

					turn++;
					if (turn > 3) turn = 0;
				}

			}

			//Then Climb or Fall if any snake or ladder is encountered
			if (canClimb)
			{
				manager.players[turn].playerSprite.setPosition(manager.players[turn].lerp(manager.players[turn].startPlayerPosition, manager.players[turn].finalPlayerPosition, percent));
				if (percent > 0.99f)
				{
					manager.players[turn].playerSprite.setPosition(manager.players[turn].finalPlayerPosition);
					manager.players[turn].startPlayerPosition = manager.players[turn].finalPlayerPosition;

					//reset
					elaspedTime = 0.00f;
					percent = 0;
					canClick = true;
					isRolling = false;
					canClimb = false;

					turn++;
					if (turn > 3) turn = 0;
				}
			}

		
		}

		// ----------------------------------------------------------------------------------------------------

		window.clear(sf::Color(54, 54, 54, 255));

		window.draw(bgSprite);
		window.draw(_board.boardSprite);
		_diceRollBtn.UpdateColor(window);
		_diceRollBtn.RenderButton(window);

		for (int i = 0; i < 4; i++) //draw 4 players
		{
			window.draw(manager.players[i].playerSprite);
		}
	
		window.draw(_dice.diceAnimSprite);

		window.display();

	}

	return 0;
}