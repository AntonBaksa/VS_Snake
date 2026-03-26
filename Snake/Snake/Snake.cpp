#include "Snake.h"

bool Snake::CheckSelfCollision()
{
	if (snakeBody.size() > 2)
	{
		for (int i = 1; i < snakeBody.size(); i++)
		{
			if (snakeBody.front().x == snakeBody[i].x && snakeBody.front().y == snakeBody[i].y)
			{
				//Lose
				return true;
			}
		}
	}
	return false;
}

void Snake::Move()
{

	newHead.x = snakeBody.front().x + direction.x;
	newHead.y = snakeBody.front().y + direction.y;

	snakeBody.push_front(newHead);
}

void Snake::Reset()
{
	newHead = { 3,5 };
	snakeBody = { newHead };
	direction = { 1,0 };
}