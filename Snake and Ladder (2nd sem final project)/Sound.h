#pragma once
#include <SFML/Audio.hpp>

class Sound {
	sf::SoundBuffer diceRollAudio;
	sf::SoundBuffer PlayerMoveAudio;
	sf::SoundBuffer LadderAudio;
	sf::SoundBuffer SnakeAudio;
	sf::SoundBuffer victoryAudio;

	sf::Sound diceRoll;
	sf::Sound playerMove;
	sf::Sound ladder;
	sf::Sound snake;
	sf::Sound victory;

public:
	void loadAllAudio();
	void PlayDiceRoll();
	void PlayPlyaerMove();
	void PlayLadder();
	void PlaySnake();
	void PlayVictory();

};