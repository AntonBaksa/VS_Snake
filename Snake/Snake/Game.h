#pragma once

#include <iostream>
#include <conio.h>
#include <thread>
#include <chrono>
#include <vector>
#include <deque>
#include "Vec2.h"
#include "Snake.h"
#include "Food.h"
#include "Grid.h"

enum Direction : char
{
	up = 'w',
	down = 's',
	left = 'a',
	right = 'd'
};

class Game
{

	Snake snake;
	Food food;
	Grid grid;
	bool ateFood = false;
	bool canChangeDirection = true;
	int points = 0;

	enum GameState
	{
		mainMenu,
		howToPlay,
		gameRunning,
		gameOver,
		quit
	};
	enum GameState state { mainMenu };

	void HandleInput();

	void Update();

	void RenderGrid();

	void Reset();

	void Run();

	void MainMenu();

	void HowToPlay();

	void GameOver(int points);
	
public:

	void Start();
	
};
