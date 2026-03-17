#include <iostream>
#include <conio.h>
#include <thread>
#include <chrono>
#include <vector>
#include <deque>

const int height{ 10 };
const int width{ 10 };

struct Vec2
{
	int x;
	int y;
};

Vec2 direction{ 1, 0 };

Vec2 newHead{ 3,5 };
Vec2 food{ 5, 7 };
bool ateFood = false;
int points{ 0 };
std::deque<Vec2> snake{ newHead };

class Snake 
{
public:
};

enum GameStates
{
	mainMenu,
	howToPlay,
	gameRunning,
	gameOver,
	quit
};
enum GameStates state{mainMenu};

void Reset()
{
	newHead = { 3,5 };
	food = { 5, 7 };
	ateFood = false;
	points = { 0 };
	snake = { newHead };
	direction = { 1, 0 };
}

void HandleInput(Vec2& direction)
{
	if (_kbhit())
	{
		char key = _getch();

		switch (key)
		{
			case 'w':
				if(direction.y != 1)
					direction = { 0, -1 };
				break;
			case 's':
				if (direction.y != -1)
					direction = { 0, 1 };
				break;
			case 'a':
				if (direction.x != 1)
					direction = { -1, 0 };
				break;
			case 'd':
				if (direction.x != -1)
					direction = { 1, 0 };
				break;
			default:
				break;

		}
	}	
}

void Randomization()
{

	food.x = rand() % width;
	food.y = rand() % height;

	for (int i = 0; i < snake.size(); i++)
	{
		while (food.x == snake[i].x && food.y == snake[i].y)
		{
			food.x = rand() % width;
			food.y = rand() % height;
		}
	}

	ateFood = false;
}

void Collision()
{
	//colliding with snake
	if (snake.size() > 2)
	{
		for (int i = 1; i < snake.size(); i++)
		{
			if (snake.front().x == snake[i].x && snake.front().y == snake[i].y)
			{
				state = gameOver;
			}
		}
	}
	
	//colliding with food
	if (newHead.x == food.x && newHead.y == food.y)
	{
		ateFood = true;
		points++;
	}

	// colliding with walls
	if (newHead.x < 0 || newHead.x > 9)
	{
		state = gameOver;
	}
	if (newHead.y < 0 || newHead.y > 9)
	{
		state = gameOver;
	}
}

void Update()
{

	newHead.x = snake.front().x + direction.x;
	newHead.y = snake.front().y + direction.y;

	snake.push_front(newHead);

	Collision();

	if (!ateFood)
	{
		snake.pop_back();
	}

	if (ateFood)
	{
		Randomization();
	}
}

void RenderGrid()
{
	std::cout << "Points:" << points << '\n';
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			bool isSnake = false;
			for (int s = 0; s < snake.size(); s++)
			{
				if (j == snake[s].x && i == snake[s].y)
				{
					isSnake = true;
					break;
				}
			}

			if (isSnake)
			{
				if (j == snake.front().x && i == snake.front().y)
				{
					std::cout << " 0";
				}
				else
				{
					std::cout << " O";
				}
			}
			else if (j == food.x && i == food.y)
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

void HowToPlay()
{
	std::cout << "======== How To Play ========\n";
	std::cout << "Press 1 or 2 to continue\n";
	std::cout << "1. Back To Menu\n";
	std::cout << "2. Quit\n\n";
	std::cout << "----------Controles----------\n";
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

void GameOver()
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
				HandleInput(direction);
				Update();
				RenderGrid();
				std::this_thread::sleep_for(std::chrono::milliseconds(800));
				break;

			case gameOver:
				std::cout << "\033[2J\033[1;1H";
				GameOver();
				break;

			default:
				break;
		}
	}
}