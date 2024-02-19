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

	playerPos = 0;
}


void Player::MovePlayer(int diceNum)
{
	playerPos += diceNum;
	sf::Vector2f finalPos = BoardCellPosition[playerPos - 1];
	finalPos.x -= 40; //centre the token wrt to board's square
	playerSprite.setPosition(finalPos);
	//playerSprite.move(2,0);
}
