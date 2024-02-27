#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"

class Player {
public:
	int playerPosIndex;
	int setPos(int);
	bool foundSnakeorLadder;
	sf::Texture playerTexture;
	sf::Sprite playerSprite;
	sf::Vector2f finalPlayerPosition;
	sf::Vector2f startPlayerPosition;
	sf::Vector2f finalPos(Board& _board);
	sf::Vector2f lerp(const sf::Vector2f& start, const sf::Vector2f& end, float percent);
	void InitializePlayer(int);
	void SetPlayerTexture(int);
	void SetPlayerPosition(int);
};

