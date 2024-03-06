#include <SFML/Graphics.hpp> //graphisc library
#include <iostream>
#include <algorithm> //for min function
#include <string>

//custom headers
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
	bool isGameover = false;

	// Create DIce Object--------------------------
	Dice _dice;
	_dice.InitializeDice();
	int diceNumber = 0;

	//Create Dice Roll Button-------------------
	bool canPlay = false;
	Button _diceRollBtn(400, 750, 100, 100, 414, 767, "", sf::Color::White, sf::Color::Cyan, sf::Color::Green, "");

	Button PlayBtn(350, 300, 200, 50, 414, 767, "PLAY", sf::Color::White, sf::Color::Cyan, sf::Color::Green, "assets/textures/button.png");
	Button OptionsBtn(350, 400, 200, 50, 414, 767, "OPTIONS", sf::Color::White, sf::Color::Cyan, sf::Color::Green, "assets/textures/button.png");
	Button ExitBtn(350, 500, 200, 50, 414, 767, "QUIT", sf::Color::White, sf::Color::Cyan, sf::Color::Green, "assets/textures/button.png");

	//Create Snake and Ladder board----------------
	Board _board;
	_board.InitializeBoard();

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
	int count = 0;

	float percent = 0.f;

	bool canClick = true;
	bool diceRolled = false;
	bool ClimborFall = false;

	//Main Game Loop ------------------------------------------------------------------------------------------
	while (window.isOpen())
	{
		if (!isGameover)
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
						if (PlayBtn.isMouseOver(window))
						{
							canPlay = true;
						}

						if (ExitBtn.isMouseOver(window))
						{
							window.close();
						}

						if (_diceRollBtn.isMouseOver(window))
						{
							_sound.PlayDiceRoll();
							_manager.displayArrow = false;
							diceRolled = true;
							canClick = false;

							diceNumber = _dice.GetRandomNum(); //get random number
							_dice.diceAnimSprite.setTextureRect(_dice.diceFace[diceNumber - 1]); //set the dice face to the given number
							_manager.players[turn].setPos(diceNumber);//add the dice number to player index to find the target cell 
							if (_manager.players[turn].playerPosIndex >= 98)
							{
								//win game
								//show player name
								isGameover = true;
								std::cout << "CONGRATULATIONS!!! PLAYER " << turn << " WON THE GAME!!!" << std::endl;
								_sound.PlayVictory();
							}

							std::cout << diceNumber << ": Dice Number";
							std::cout << "\n";
							std::cout << _manager.players[turn].playerPosIndex << ": Position of Player" << turn + 1;
							std::cout << "\n\n";
						}
					}

			
				default:
					break;
				}

			}

			if (diceRolled)
			{
				ShowWinnerName("p");
				//First Move normally according to dice roll number---------------------------------
				while (count < diceNumber && !ClimborFall)
				{
					elaspedTime += deltaTime;
					percent = elaspedTime / 0.3f;
					percent = std::min(percent, 1.f);  //limit percant from 0 to 1

					sf::Vector2f tempPos = BoardCellPosition[_manager.players[turn].currentIndex];
					_manager.players[turn].playerSprite.setPosition(_manager.players[turn].lerp(_manager.players[turn].startPlayerPosition, tempPos, percent));

					if (percent > 0.8f)
					{
						_manager.players[turn].playerSprite.setPosition(tempPos); //snap current pos to final pos at the end of percantage
						_sound.PlayPlyaerMove();

						//reset percantage
						elaspedTime = 0.00f;
						percent = 0;

						count++;
						_manager.players[turn].currentIndex++;
						_manager.players[turn].startPlayerPosition = tempPos; //once reached to target cell assign the target cell to the startpos so it lerps from prev pos
					}


					if (count == diceNumber) //check sbake and ladder on last index
					{
					
						_manager.players[turn].finalPlayerPosition = _manager.players[turn].finalPos(_board); //set snake or ladder pos

						if (_manager.players[turn].foundLadder)
						{
							_sound.PlayLadder();
							ClimborFall = true;
							_manager.players[turn].currentIndex = _manager.players[turn].playerPosIndex;
						}
						else if (_manager.players[turn].foundSnake)
						{
							_sound.PlaySnake();
							ClimborFall = true;
							_manager.players[turn].currentIndex = _manager.players[turn].playerPosIndex;
						}
						else {
							canClick = true;
							diceRolled = false;

							if (diceNumber != 6)
							{
								turn++; //switch turn
								if (turn > 3) turn = 0;
							}
						
							_manager.SetTurnArrow(turn);
							_manager.displayArrow = true;
						}
						count = 0;

					}

					goto Render; // render screen in each loop
				}


				//Then Climb or Fall if any snake or ladder is encountered
				if (ClimborFall)
				{
					elaspedTime += deltaTime;
					percent = elaspedTime / 0.4f;
					percent = std::min(percent, 1.f);

					_manager.players[turn].playerSprite.setPosition(_manager.players[turn].lerp(_manager.players[turn].startPlayerPosition, _manager.players[turn].finalPlayerPosition, percent));
					if (percent > 0.99f)
					{
						_manager.players[turn].playerSprite.setPosition(_manager.players[turn].finalPlayerPosition);
						_manager.players[turn].startPlayerPosition = _manager.players[turn].finalPlayerPosition;

						//reset all values
						elaspedTime = 0.00f;
						percent = 0;
						canClick = true;
						diceRolled = false;
						ClimborFall = false;

						if (diceNumber != 6)
						{
							turn++; //switch turn
							if (turn > 3) turn = 0;
						}

						_manager.SetTurnArrow(turn);
						_manager.displayArrow = true;
					}

				}
			}
			// ----------------------------------------------------------------------------------------------------
		}
	Render:
		window.clear();
		window.draw(_board.bgSprite);

		if (!canPlay)
		{
			PlayBtn.UpdateColor(window);
			PlayBtn.RenderButton(window);
			OptionsBtn.UpdateColor(window);
			OptionsBtn.RenderButton(window);
			ExitBtn.UpdateColor(window);
			ExitBtn.RenderButton(window);
		}

		if (canPlay)
		{

			window.draw(_board.boardSprite);
			_diceRollBtn.UpdateColor(window);
			_diceRollBtn.RenderButton(window);
			for (int i = 0; i < 4; i++) //draw 4 players
			{
				window.draw(_manager.players[i].playerSprite);
			}
			window.draw(_dice.diceAnimSprite);
			if (_manager.displayArrow) window.draw(_manager.arrowSprite);
		}

		window.display();
	}

	return 0;
}
