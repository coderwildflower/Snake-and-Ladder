#pragma once
#include <SFML/Graphics.hpp>

class Dice {

	sf::Texture diceAnimTexture;

public:
	sf::IntRect diceRect;
	sf::Sprite diceAnimSprite;
	int GetRandomNum();
	void RollDice(sf::Clock &clock);
	void InitializeDice();
};
