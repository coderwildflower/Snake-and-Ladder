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
	diceAnimSprite.setPosition(415, 767);
	diceRect = sf::IntRect(0, 0, 70, 70);
	diceAnimSprite.setTextureRect(diceRect);
	SetDiceFace();
}

void Dice::RollDice(float elaspedTime)
{
	float currentTime = 0;
	float targetTime = 1;

	//elaspedTime = 0;
	currentTime += elaspedTime;

	if (currentTime <= targetTime)
	{
		if (diceRect.left >= 350) {
			diceRect.left = 0;
		}
		else diceRect.left += 70;

		diceAnimSprite.setTextureRect(diceRect);
	}

	currentTime = 0;
}

void Dice::SetDiceFace()
{
	diceFace[0] = sf::IntRect(350, 0, 70, 70);
	diceFace[1] = sf::IntRect(0, 0, 70, 70);
	diceFace[2] = sf::IntRect(210, 0, 70, 70);
	diceFace[3] = sf::IntRect(140, 0, 70, 70);
	diceFace[4] = sf::IntRect(280, 0, 70, 70);
	diceFace[5] = sf::IntRect(70, 0, 70, 70);
}

