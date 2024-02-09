#include "Dice.h"
#include <stdlib.h>
#include <time.h>

int Dice::GetRandomNum()
{
	srand(time(0));

	//pseudo-random num from 1 to 6
	int randomNum = (rand() % 6) + 1;
	return randomNum;
}
