#pragma once
#include "Player.h"
#include <vector>

class PlayerManager {

public:
	std::vector<Player> players;
	void SetPlayer(int);
	int playerTurn;
};
