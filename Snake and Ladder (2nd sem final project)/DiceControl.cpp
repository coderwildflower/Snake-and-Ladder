#include "Dice.h"
#include <stdlib.h>
#include <time.h>

int Dice::GetRandomNum()
{
	srand(unsigned(time(0)));

	//pseudo-random num from 1 to 6
	return rand() % 6 + 1;
}

void Dice::InitializeDice()
{
	diceAnimTexture.loadFromFile("assets/textures/Dice_static.png");
	diceAnimSprite.setTexture(diceAnimTexture);
	//diceAnimSprite.setScale(120 / diceAnimSprite.getLocalBounds().width, 80 / diceAnimSprite.getLocalBounds().height);
	diceAnimSprite.setPosition(600, 767);
	diceRect = sf::IntRect(0, 0, 70, 70);
	diceAnimSprite.setTextureRect(diceRect);
}

void Dice::RollDice(sf::Clock &_clock)
{
	float targetTime = 2;

	if (_clock.getElapsedTime().asSeconds() > 0.5)
	{
		if (diceRect.left >= 350){
			diceRect.left = 0;
			
		} 
		else {

			diceRect.left += 70;	
		}
		diceAnimSprite.setTextureRect(diceRect);
		_clock.restart();
	}
}

