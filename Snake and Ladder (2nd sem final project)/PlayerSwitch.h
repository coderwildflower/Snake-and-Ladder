#pragma once
#include "Player.h"
#include <vector>

class PlayerManager {

public:
	std::vector<Player> players;
	void SetPlayer(int);
	void SetTurnArrow(int);
	void AnimateArrow(float);
	bool displayArrow;
	bool reverse;
	float currentTime;
	int playerTurn;
	sf::Texture arrowTexture;
	sf::Sprite arrowSprite;
};
