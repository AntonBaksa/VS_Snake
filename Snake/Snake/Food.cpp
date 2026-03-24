#include "Food.h"
#include <cstdlib>

void Food::NewFoodPos(int width, int height)
{
	foodPos.x = rand() % width;
	foodPos.y = rand() % height;
}