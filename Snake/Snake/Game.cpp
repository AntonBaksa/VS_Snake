#include "Game.h"
#include <iostream>
#include <conio.h>
#include <thread>
#include <chrono>
#include <vector>
#include <deque>

void Game::HandleInput()
{
	if (_kbhit() && canChangeDirection)
	{
		char key = _getch();
		canChangeDirection = false;

		while (_kbhit())
		{
			(void)_getch();
		}

		switch (key)
		{
		case up:
			if (snake.direction.y != 1)
				snake.direction = { 0, -1 };
			break;
		case down:
			if (snake.direction.y != -1)
				snake.direction = { 0, 1 };
			break;
		case left:
			if (snake.direction.x != 1)
				snake.direction = { -1, 0 };
			break;
		case right:
			if (snake.direction.x != -1)
				snake.direction = { 1, 0 };
			break;
		default:
			break;

		}
	}
}

void Game::Update()
{
	ateFood = false;
	bool invalidCell = true;
	snake.Move();

	//colliding with food
	if (snake.newHead.x == food.foodPos.x && snake.newHead.y == food.foodPos.y)
	{
		ateFood = true;
		points++;

		//keep find new position for food untill on empty cell
		while (invalidCell)
		{
			food.NewFoodPos(grid.width, grid.height);
			invalidCell = false;

			for (int i = 0; i < snake.snakeBody.size(); i++)
			{
				if (food.foodPos.x == snake.snakeBody[i].x && food.foodPos.y == snake.snakeBody[i].y)
				{
					invalidCell = true;
					break;
				}
			}
		}
	}

	if (!ateFood)
	{
		snake.snakeBody.pop_back();
	}

	// colliding with walls
	if (snake.newHead.x < 0 || snake.newHead.x > 9)
	{
		//Lose
		state = gameOver;
	}
	if (snake.newHead.y < 0 || snake.newHead.y > 9)
	{
		//Lose
		state = gameOver;
	}

	//check if colliding with itself
	if (snake.CheckSelfCollision())
	{
		state = gameOver;
	}
}

void Game::RenderGrid()
{
	std::cout << "Points:" << points << '\n';
	for (int i = 0; i < grid.width; i++)
	{
		for (int j = 0; j < grid.height; j++)
		{
			bool isSnake = false;
			for (int s = 0; s < snake.snakeBody.size(); s++)
			{
				if (j == snake.snakeBody[s].x && i == snake.snakeBody[s].y)
				{
					isSnake = true;
					break;
				}
			}

			if (isSnake)
			{
				if (j == snake.snakeBody.front().x && i == snake.snakeBody.front().y)
				{
					std::cout << " 0";
				}
				else
				{
					std::cout << " O";
				}
			}
			else if (j == food.foodPos.x && i == food.foodPos.y)
			{
				std::cout << " #";
			}
			else
			{
				std::cout << " .";
			}
		}
		std::cout << '\n';
	}
}

void Game::Reset()
{
	snake.newHead = { 3,5 };
	food = { 5, 7 };
	ateFood = false;
	points = { 0 };
	snake.snakeBody = { snake.newHead };
	snake.direction = { 1,0 };
}

void Game::Run()
{
	canChangeDirection = true;
	HandleInput();
	Update();
	RenderGrid();
	std::this_thread::sleep_for(std::chrono::milliseconds(300));
}

void Game::MainMenu()
{
	std::cout << "=========== Snake ===========\n";
	std::cout << "Press 1,2 or 3 to continue\n";
	std::cout << "1. Play\n";
	std::cout << "2. How To Play\n";
	std::cout << "3. Quit\n";
	std::cout << "=============================\n";

	int input{};
	std::cin >> input;

	if (std::cin.fail())
	{
		std::cout << "Invalid Input!\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	else if (input == 1)
	{
		Reset();

		state = gameRunning;
	}
	else if (input == 2)
	{
		state = howToPlay;
	}
	else if (input == 3)
	{
		state = quit;
	}
	else
	{
		std::cout << "Must enter number 1, 2 or 3!\n";
	}
}

void Game::HowToPlay()
{
	std::cout << "======== How To Play ========\n";
	std::cout << "Press 1 or 2 to continue\n";
	std::cout << "1. Back To Menu\n";
	std::cout << "2. Quit\n\n";
	std::cout << "----------Controls----------\n";
	std::cout << "Use WASD to move around\n";
	std::cout << "W = up\n";
	std::cout << "S = down\n";
	std::cout << "D = right\n";
	std::cout << "A = left\n";
	std::cout << "-------------Goal------------\n";
	std::cout << "Move to # to eat and make \n";
	std::cout << "the snake longer\n";
	std::cout << "Eat as many # without losing\n";
	std::cout << "------------Losing-----------\n";
	std::cout << "You lose if:\n";
	std::cout << " * You go outside the grid\n";
	std::cout << " * Snake collides with itself\n";
	std::cout << "=============================\n";

	int input{};
	std::cin >> input;

	if (std::cin.fail())
	{
		std::cout << "Invalid Input!\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	else if (input == 1)
	{
		state = mainMenu;
	}
	else if (input == 2)
	{
		state = quit;
	}
	else
	{
		std::cout << "Must enter number 1 or 2!\n";
	}
}

void Game::GameOver(int points)
{
	std::cout << "========= Game Over! =========\n\n";
	std::cout << "Points:" << points << "\n\n";
	std::cout << "Press 1 or 2 to continue\n";
	std::cout << "1. Back To Menu\n";
	std::cout << "2. Quit\n";
	std::cout << "=============================\n";

	int input{};
	std::cin >> input;

	if (std::cin.fail())
	{
		std::cout << "Invalid Input!\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	else if (input == 1)
	{
		state = mainMenu;
	}
	else if (input == 2)
	{
		state = quit;
	}
	else
	{
		std::cout << "Must enter number 1 or 2!\n";
	}
}


void Game::Start()
{
	while (state != quit)
	{
		std::cout << "\033[2J\033[1;1H";

		switch (state)
		{
		case mainMenu:
			MainMenu();
			break;

		case howToPlay:
			HowToPlay();
			break;

		case gameRunning:
			Run();
			break;

		case gameOver:
			GameOver(points);
			break;
		}
	}
}