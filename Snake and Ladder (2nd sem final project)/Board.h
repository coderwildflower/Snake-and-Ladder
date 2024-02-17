#pragma once
#include <SFML/Graphics.hpp>

extern sf::Vector2f BoardCellPosition[100];

class Board {
	sf::Texture boardTexture;
	
	int ladderInitialPosition[8];
	int ladderFinalPosition[8];

	int SnakeInitialPosition[8];
	int SnakeFinalPosition[8];

	float initialX;
	float initialY;
	int index;

public:
	void SetGridCells(sf::RenderWindow& window);
	void InitializeBoard(sf::RenderWindow& window);
	sf::Sprite boardSprite;
};

