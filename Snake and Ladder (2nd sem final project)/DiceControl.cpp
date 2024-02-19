#include "Dice.h"
#include <stdlib.h>
#include <time.h>

int Dice::GetRandomNum()
{
	srand(unsigned(time(0)));

	//pseudo-random num from 1 to 6
	return rand() % 6 + 1;
}

void Dice::RollDice(sf::Clock &_clock)
{
	float targetTime = 2;

	if (_clock.getElapsedTime().asSeconds() > 0.1)
	{
		if (diceRect.left >= 993.35)
		{
			diceRect.left = 0;
		}
		else diceRect.left += 199;
		diceAnimSprite.setTextureRect(diceRect);
		_clock.restart();
	}
	
}

void Dice::InitializeDice()
{
	diceAnimTexture.loadFromFile("assets/textures/Dice_animation.png");
	diceAnimSprite.setTexture(diceAnimTexture);
	diceAnimSprite.setScale(1220/diceAnimSprite.getLocalBounds().width, 80 / diceAnimSprite.getLocalBounds().height);
	diceAnimSprite.setPosition(600, 767);
	diceRect = sf::IntRect(0, 0, 198.67, 88);
	diceAnimSprite.setTextureRect(diceRect);
}
