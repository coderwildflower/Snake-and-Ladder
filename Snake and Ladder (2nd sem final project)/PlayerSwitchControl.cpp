#include "PlayerSwitch.h"

void PlayerManager::SetPlayer(int count)
{
	for (int i = 0; i < count; i++)
	{
		Player _player;
		players.push_back(_player); //insert element at last position
	}

	arrowTexture.loadFromFile("assets/textures/arrow.png");
	arrowSprite.setTexture(arrowTexture);
}

void PlayerManager::SetTurnArrow(int turn)
{
	arrowTexture.setSmooth(true);
	arrowSprite.setPosition(players[turn].playerSprite.getPosition().x, players[turn].playerSprite.getPosition().y - 40);
	arrowSprite.setScale(30 / arrowSprite.getLocalBounds().width, 40 / arrowSprite.getLocalBounds().height);
}

void PlayerManager::AnimateArrow(float elapsedTime)
{
	currentTime += elapsedTime;
	if (currentTime > 0.3f)
	{
		currentTime = 0;
		reverse = !reverse;
	}

	if(!reverse)
		arrowSprite.move(0, -1);
	else 
		arrowSprite.move(0, 1);
}
