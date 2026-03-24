#pragma once
#include "Vec2.h"
#include <deque>

class Snake
{
public:
	Vec2 direction{ 1, 0 };
	Vec2 newHead{ 3, 5 };
	std::deque<Vec2> snakeBody{ newHead };

	bool CheckSelfCollision();
	
	void Move();
	
};