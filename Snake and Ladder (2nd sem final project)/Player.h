#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"

class Player {
	sf::Texture playerTexture;

public:
	int playerPos;
	sf::Sprite playerSprite;
	sf::Vector2f finalPlayerPosition;
	sf::Vector2f startPlayerPosition;
	sf::Vector2f finalPos(int, Board& _board);
	sf::Vector2f lerp(const sf::Vector2f& start, const sf::Vector2f& end, float percent);
	void InitializePlayer();
	
};