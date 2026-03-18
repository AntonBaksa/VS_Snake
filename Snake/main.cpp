#include <iostream>
#include <conio.h>
#include <thread>
#include <chrono>
#include <vector>
#include <deque>

struct Vec2
{
	int x;
	int y;
};

enum Direction : char
{
	up = 'w',
	down = 's',
	left = 'a',
	right = 'd'
};

class Snake
{
	public:
		Vec2 direction{ 1, 0 };
		Vec2 newHead{ 3, 5 };
		std::deque<Vec2> snakeBody{ newHead };
		
		void CheckSelfCollision()
		{
			if (snakeBody.size() > 2)
			{
				for (int i = 1; i < snakeBody.size(); i++)
				{
					if (snakeBody.front().x == snakeBody[i].x && snakeBody.front().y == snakeBody[i].y)
					{
						//Lose
					}
				}
			}
		}

		void Move()
		{
			newHead.x = snakeBody.front().x + direction.x;
			newHead.y = snakeBody.front().y + direction.y;

			snakeBody.push_front(newHead);
			
			snakeBody.pop_back();
			
		}
};

class Food
{
	public:
		Vec2 foodPos{ 5, 7 };

		void NewFoodPos(int width, int height)
		{

			foodPos.x = rand() % width;
			foodPos.y = rand() % height;

			/*for (int i = 0; i < snake.size(); i++)
			{
				while (foodPos.x == snake[i].x && foodPos.y == snake[i].y)
				{
					foodPos.x = rand() % width;
					foodPos.y = rand() % height;
				}
			}*/
		}
};

enum GameState
{
	mainMenu,
	howToPlay,
	gameRunning,
	gameOver,
	quit
};
enum GameState state{mainMenu};

class Grid
{
	public:
		const int height{ 10 };
		const int width{ 10 };	
};

class Game
{
private:
	Snake snake;
	Food food;
	Grid grid;
	bool ateFood = false;

public:
	int points{ 0 };

	void HandleInput(Vec2& direction)
	{
		if (_kbhit())
		{
			char key = _getch();

			switch (key)
			{
			case up:
				if (direction.y != 1)
					direction = { 0, -1 };
				break;
			case down:
				if (direction.y != -1)
					direction = { 0, 1 };
				break;
			case left:
				if (direction.x != 1)
					direction = { -1, 0 };
				break;
			case right:
				if (direction.x != -1)
					direction = { 1, 0 };
				break;
			default:
				break;

			}
		}
	}

	void Update()
	{
		snake.Move();

		//colliding with food
		if (snake.newHead.x == food.foodPos.x && snake.newHead.y == food.foodPos.y)
		{
			ateFood = true;
			points++;
		}

		// colliding with walls
		if (snake.newHead.x < 0 || snake.newHead.x > 9)
		{
			//Lose
		}
		if (snake.newHead.y < 0 || snake.newHead.y > 9)
		{
			//Lose
		}
		snake.CheckSelfCollision();
	}

	void RenderGrid()
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

	void Reset()
	{
		snake.newHead = { 3,5 };
		food = { 5, 7 };
		ateFood = false;
		points = { 0 };
		snake.snakeBody = { snake.newHead };
		snake.direction = { 1,0 };
	}

	void Run()
	{
		HandleInput(snake.direction);
		Update();
		RenderGrid();
		std::this_thread::sleep_for(std::chrono::milliseconds(400));
	}
};
Game game;

void MainMenu()
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
		game.Reset();
		
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

void HowToPlay()
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
	std::cout << " * Collide with with yourself\n";
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

void GameOver(int points)
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
	else if(input == 1)
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

int main() 
{
	srand(time(NULL));

	while (state != quit)
	{
		switch (state)
		{
			case mainMenu:
				std::cout << "\033[2J\033[1;1H";
				MainMenu();
				break;

			case howToPlay:
				std::cout << "\033[2J\033[1;1H";
				HowToPlay();
				break;

			case gameRunning:
				std::cout << "\033[2J\033[1;1H";
				game.Run();
				break;

			case gameOver:
				std::cout << "\033[2J\033[1;1H";
				GameOver(game.points);
				break;
				
			default:
				break;
		}
	}
}