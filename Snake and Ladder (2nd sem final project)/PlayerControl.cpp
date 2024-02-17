#include "Player.h"
#include "Board.h"

void  Player::InitializePlayer()
{
	playerTexture.loadFromFile("assets/textures/token.png");

	//player sprite setup in scene ---------------------
	playerTexture.setSmooth(true);
	playerSprite.setTexture(playerTexture);
	playerSprite.setScale(20 / playerSprite.getLocalBounds().width,25 / playerSprite.getLocalBounds().height);
	playerSprite.setPosition(20, 700);
}


void Player::MovePlayer(int diceNum)
{
	playerPos += diceNum;
	sf::Vector2f finalPos = BoardCellPosition[playerPos - 1];
	sf::Vector2f playerScale = playerSprite.getScale();
	finalPos.x -= playerScale.x / 2;
	playerSprite.setPosition(finalPos);
}
