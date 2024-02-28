#include "Player.h"
#include "Board.h"

void Player::InitializePlayer(int playerNum)
{
	playerPosIndex = 0;
	SetPlayerTexture(playerNum);
	SetPlayerPosition(playerNum);
}

void Player::SetPlayerPosition(int playerNum)
{
	switch (playerNum)
	{
	case 0:
		startPlayerPosition.x = 20;
		startPlayerPosition.y = 700;
		playerSprite.setPosition(startPlayerPosition);
		break;
	case 1:
		startPlayerPosition.x = 40;
		startPlayerPosition.y = 700;
		playerSprite.setPosition(startPlayerPosition);
		break;
	case 2:
		startPlayerPosition.x = 20;
		startPlayerPosition.y = 740;
		playerSprite.setPosition(startPlayerPosition);
		break;
	case 3:
		startPlayerPosition.x = 40;
		startPlayerPosition.y = 740;
		playerSprite.setPosition(startPlayerPosition);
		break;

	default:
		break;
	}
}


void Player::SetPlayerTexture(int playerNum)
{
	switch (playerNum)
	{
	case 0:
		playerTexture.loadFromFile("assets/textures/token1.png");
		break;
	case 1:
		playerTexture.loadFromFile("assets/textures/token2.png");
		break;
	case 2:
		playerTexture.loadFromFile("assets/textures/token3.png");
		break;
	case 3:
		playerTexture.loadFromFile("assets/textures/token4.png");
		break;

	default:
		break;
	}
	playerTexture.setSmooth(true);
	playerSprite.setTexture(playerTexture);
	playerSprite.setScale(30 / playerSprite.getLocalBounds().width, 45 / playerSprite.getLocalBounds().height);
}

int ::Player::setPos(int diceNum)
{
	playerPosIndex += diceNum;
	return playerPosIndex;
}

void SimpleMove()
{
	
}

sf::Vector2f Player::finalPos(Board& _board)
{
	sf::Vector2f pos;
	foundSnake = false;
	foundLadder = false;
	
	for (int i = 0; i < 8; i++) // check for ladder
	{
		if (playerPosIndex - 1 == _board.ladderInitialIndex[i])
		{
			pos = _board.ladderFinalPosition[i];
			foundLadder = true;
			playerPosIndex = _board.ladderFinalIndex[i] + 1;
			break;
		}
	}

	if (!foundLadder)//if ladder not found check for snake
	{
		for (int i = 0; i < 8; i++)
		{
			if (playerPosIndex - 1 == _board.snakeInitialIndex[i])
			{
				pos = _board.SnakeFinalPosition[i];
				foundSnake = true;
				playerPosIndex = _board.snakeFinalIndex[i] + 1;
				break;
			}
		}

	}

	return pos;
}

sf::Vector2f Player::lerp(const sf::Vector2f& start, const sf::Vector2f& end, float percent) {
	return start + (end - start) * percent;
}


