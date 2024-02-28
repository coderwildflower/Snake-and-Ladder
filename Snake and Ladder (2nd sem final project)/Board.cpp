#include "Board.h";

sf::Vector2f BoardCellPosition[100];

void Board::SetGridCells(sf::RenderWindow& window)
{
	initialX = 170;
	initialY = 680;
	index = 0;
	bool isReverse = false;

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (index % 10 != 0) //dont move x on last cell
			{
				if (!isReverse)
					initialX += 70;
				else initialX -= 70;
			}

			BoardCellPosition[index] = sf::Vector2f(initialX - 50, initialY);
			index++;
		}

		isReverse = !isReverse;
		initialY -= 72;
	}
}

void Board::InitializeBoard(sf::RenderWindow& window)
{
	//Set board's texutre,its height and width and position in window -------------------------------------------------------------------
	bgTexture.loadFromFile("assets/textures/background.png");
	bgSprite.setTexture(bgTexture);
	bgSprite.setScale(900 / bgSprite.getLocalBounds().width, 900 / bgSprite.getLocalBounds().height);
	float boardWidth = 700;
	float boardHeight = 700;

	boardTexture.loadFromFile("assets/textures/board.png");

	//board sprite setup in scene ---------------------
	boardTexture.setSmooth(true);
	boardSprite.setTexture(boardTexture);
	boardSprite.setScale(boardWidth / boardSprite.getLocalBounds().width, boardHeight / boardSprite.getLocalBounds().height);
	boardSprite.setPosition(450 - boardWidth / 2, 20);

	SetGridCells(window);

	//set ladder x and y position
	for (int i = 0; i < 8; i++)
	{
		ladderInitialPosition[i] = BoardCellPosition[ladderInitialIndex[i]];
		ladderFinalPosition[i] = BoardCellPosition[ladderFinalIndex[i]];

		SnakeInitialPosition[i] = BoardCellPosition[snakeInitialIndex[i]];
		SnakeFinalPosition[i] = BoardCellPosition[snakeFinalIndex[i]];
	}

}