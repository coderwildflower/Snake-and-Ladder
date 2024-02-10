#include "Dice.h"
#include <stdlib.h>
#include <time.h>

int Dice::GetRandomNum()
{
	srand(unsigned(time(0)));

	//pseudo-random num from 1 to 6
	return rand() % 6 + 1;
}
