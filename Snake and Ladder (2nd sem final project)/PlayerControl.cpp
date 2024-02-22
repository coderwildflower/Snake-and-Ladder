#include "Player.h"
#include "Board.h"

void  Player::InitializePlayer()
{
	playerTexture.loadFromFile("assets/textures/token.png");

	//player sprite setup in scene ---------------------
	playerTexture.setSmooth(true);
	playerSprite.setTexture(playerTexture);
	playerSprite.setScale(30 / playerSprite.getLocalBounds().width, 45 / playerSprite.getLocalBounds().height);
	playerSprite.setPosition(20, 700);

	playerPos = 0;
}

sf::Vector2f Player::finalPos(int diceNum,Board& _board)
{
	sf::Vector2f pos;
	bool foundSnakeorLadder = false;
	playerPos += diceNum;

	for (int i = 0; i < 8; i++)
	{
		if (playerPos - 1 == _board.ladderInitialIndex[i])
		{
			pos = _board.ladderFinalPosition[i];
			foundSnakeorLadder = true;
			playerPos = _board.ladderFinalIndex[i] + 1;
			break;
		}
	}

	if (!foundSnakeorLadder)
	{
		for (int i = 0; i < 8; i++)
		{
			if (playerPos - 1 == _board.snakeInitialIndex[i])
			{
				pos = _board.SnakeFinalPosition[i];
				playerPos = _board.snakeFinalIndex[i] + 1;
				foundSnakeorLadder = true;
				break;
			}
		}

	}

	if (!foundSnakeorLadder) pos = BoardCellPosition[playerPos - 1];


	return pos;
}

sf::Vector2f Player::lerp(const sf::Vector2f& start, const sf::Vector2f& end, float percent) {
	return start + (end - start) * percent;
}


