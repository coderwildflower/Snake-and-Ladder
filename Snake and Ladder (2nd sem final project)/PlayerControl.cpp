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

	playerPosIndex = 0;
}

int ::Player::setPos(int diceNum)
{
	playerPosIndex += diceNum;
	return playerPosIndex;
}

sf::Vector2f Player::finalPos(Board& _board)
{
	sf::Vector2f pos;
	foundSnakeorLadder = false;
	
	for (int i = 0; i < 8; i++)
	{
		if (playerPosIndex - 1 == _board.ladderInitialIndex[i])
		{
			pos = _board.ladderFinalPosition[i];
			foundSnakeorLadder = true;
			playerPosIndex = _board.ladderFinalIndex[i] + 1;
			break;
		}
	}

	if (!foundSnakeorLadder)
	{
		for (int i = 0; i < 8; i++)
		{
			if (playerPosIndex - 1 == _board.snakeInitialIndex[i])
			{
				pos = _board.SnakeFinalPosition[i];
				playerPosIndex = _board.snakeFinalIndex[i] + 1;
				foundSnakeorLadder = true;
				break;
			}
		}

	}

	return pos;
}

sf::Vector2f Player::lerp(const sf::Vector2f& start, const sf::Vector2f& end, float percent) {
	return start + (end - start) * percent;
}


