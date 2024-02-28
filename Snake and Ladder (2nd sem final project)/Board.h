#pragma once
#include <SFML/Graphics.hpp>

extern sf::Vector2f BoardCellPosition[100];

class Board {
	sf::Texture boardTexture;

	float initialX;
	float initialY;
	int index;

public:
	int ladderInitialIndex[8] = { 0,3,8,20,27,50,70,79 };
	int ladderFinalIndex[8] = { 37,13,30,41,83,66,90,99 };
	int snakeInitialIndex[8] = { 16, 53,61,63,86,92,94,97 };
	int snakeFinalIndex[8] = { 6,33,18,59,23,72,74,78 };

	sf::Vector2f ladderInitialPosition[8];
	sf::Vector2f ladderFinalPosition[8];
	sf::Vector2f SnakeInitialPosition[8];
	sf::Vector2f SnakeFinalPosition[8];

	void SetGridCells(sf::RenderWindow& window);
	void InitializeBoard(sf::RenderWindow& window);
	sf::Sprite boardSprite;
	sf::Texture bgTexture;
	sf::Sprite bgSprite;
};

