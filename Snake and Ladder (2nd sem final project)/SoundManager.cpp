#include "Sound.h"

void Sound::loadAllAudio() {
	
	diceRollAudio.loadFromFile("assets/audio/roll.mp3");
	PlayerMoveAudio.loadFromFile("assets/audio/move.mp3");
	LadderAudio.loadFromFile("assets/audio/ladder.mp3");
	SnakeAudio.loadFromFile("assets/audio/snake.mp3");
	victoryAudio.loadFromFile("assets/audio/victory.mp3");

	diceRoll.setBuffer(diceRollAudio);
	playerMove.setBuffer(PlayerMoveAudio);
	ladder.setBuffer(LadderAudio);
	snake.setBuffer(SnakeAudio);
	victory.setBuffer(victoryAudio);
}

void Sound::PlayDiceRoll() {
	diceRoll.play();
}

void Sound::PlayPlyaerMove() {
	playerMove.play();
}

void Sound::PlayLadder() {
	ladder.play();
}

void Sound::PlaySnake() {
	snake.play();
}

void Sound::PlayVictory() {
	victory.play();
}