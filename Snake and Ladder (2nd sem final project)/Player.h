#pragma once
#include <SFML/Graphics.hpp>

class Player {
	sf::Texture playerTexture;

public:

	int playerPos;
	sf::Sprite playerSprite;
	void MovePlayer(int);
	void InitializePlayer();
	
};