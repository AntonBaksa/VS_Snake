#pragma once
#include "Vec2.h"

class Food
{
public:
	Vec2 foodPos{ 5, 7 };

	void NewFoodPos(const int width, const int height);
};