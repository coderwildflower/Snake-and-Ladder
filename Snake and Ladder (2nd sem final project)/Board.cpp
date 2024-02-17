#include "Board.h";

sf::Vector2f BoardCellPosition[100];

void Board::SetGridCells(sf::RenderWindow& window)
{
	initialX = 100;
	initialY = 700;
	index = 0;
	bool isReverse = false;

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			BoardCellPosition[index] = sf::Vector2f(initialX,initialY);

			if (!isReverse)
				initialX += 75;
			else initialX -= 75;

			index++;
		}
		isReverse = !isReverse;
		initialY -= 72;
	}
}

void Board::InitializeBoard(sf::RenderWindow& window)
{
	//Set board's texutre,its height and width and position in window -------------------------------------------------------------------

	float boardWidth = 700;
	float boardHeight = 700;

	boardTexture.loadFromFile("assets/textures/board.png");

	//board sprite setup in scene ---------------------
	boardTexture.setSmooth(true);
	boardSprite.setTexture(boardTexture);
	boardSprite.setScale(boardWidth / boardSprite.getLocalBounds().width, boardHeight / boardSprite.getLocalBounds().height);
	boardSprite.setPosition(450 - boardWidth / 2, 20);

	SetGridCells(window);
}