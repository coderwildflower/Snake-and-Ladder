#include "PlayerSwitch.h"

void PlayerManager::SetPlayer(int count)
{	

	for (int i = 0; i < count; i++)
	{
		Player _player;
		//_player.InitializePlayer(i);
		players.push_back(_player); //insert element at last position
	}
}
