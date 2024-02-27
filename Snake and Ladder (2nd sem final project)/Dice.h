#pragma once
#include <SFML/Graphics.hpp>

class Dice {

	sf::Texture diceAnimTexture;

public:
	sf::IntRect diceRect;
	sf::IntRect diceFace[6]; //store each dice face image to dispaly after dice roll ends
	sf::Sprite diceAnimSprite;
	int GetRandomNum();
	void InitializeDice();
	void RollDice(float);
	void SetDiceFace();
};
