#pragma once
#include <SFML/Graphics.hpp>

class Dice {

	sf::Texture diceAnimTexture;
	

public:
	sf::Sprite diceAnimSprite;
	sf::IntRect diceRect;
	int GetRandomNum();
	void RollDice(sf::Clock &clock);
	void InitializeDice();
};
