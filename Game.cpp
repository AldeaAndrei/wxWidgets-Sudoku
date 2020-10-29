#include "Game.h"
#include <wx/wx.h>

Game :: Game()
{
	grid = new int* [n];
	solvedGrid = new int* [n];
	for (int i = 0; i < n; i++)
	{
		grid[i] = new int[n];
		solvedGrid[i] = new int[n];
	}
}

void Game::SetGame()
{
	canSolve = true;
	InitGrid();
	Solve(FindEmpty());
	EraseRandom();
}

void Game::InitGrid()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			grid[i][j] = 0;
		}
	}

	int randomizeCount = 5;
	time_t seed = time(NULL);

	for (int i = 0; i < randomizeCount; i++)
	{
		srand((int)seed + pow(i, 5));

		int randX = rand() % n;
		int randY = rand() % n;
		int randVal = rand() % 9 + 1;

		grid[randX][randY] = randVal;
	}
}


void Game::EraseRandom()
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			solvedGrid[i][j] = grid[i][j];

	int remainingVal = 30;
	time_t seed = time(NULL);


	remainingVal = pow(n, 2) - remainingVal;
	while (true)
	{
		srand((int)seed + pow(remainingVal, 3));

		int randX = rand() % n;
		int randY = rand() % n;

		if (grid[randX][randY] != 0)
		{
			grid[randX][randY] = 0;
		}
		remainingVal--;
		if (remainingVal == 0)
		{
			return;
		}
	}
}

void Game::Solve(int* empty)
{
	if (!canSolve)return;

	if (empty == nullptr)
	{
		canSolve = false;
		return;
	}
	else
	{
		int x = empty[0];
		int y = empty[1];

		for (int i = 1; i <= n; i++)
		{
			if (CanPlace(i, x, y))
			{
				grid[x][y] = i;
				Solve(FindEmpty());
				if (canSolve)
				{
					grid[x][y] = 0;
				}
			}
		}
	}
	return;
}

int* Game::FindEmpty()
{

	if (!canSolve)return nullptr;

	int* emptyCoord = (int*)malloc(2 * sizeof(int));

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (grid[i][j] == 0)
			{
				emptyCoord[0] = i;
				emptyCoord[1] = j;
				return emptyCoord;
			}
		}
	}

	return nullptr;
}

bool Game::CanPlace(int val, int x, int y)
{
	
	for (int i = 0; i < n; i++)
	{
		if (i != x)
		{
			if (grid[i][y] == val)
			{
				return false;
			}
		}
	}

	for (int j = 0; j < n; j++)
	{
		if (j != y)
		{
			if (grid[x][j] == val)
			{
				return false;
			}
		}
	}
	 
	int x0 = (int)(x / 3) * 3;
	int y0 = (int)(y / 3) * 3;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (grid[x0 + i][y0 + j] == val && (x0 + i != x && y0 + j != y))
			{
				return false;
			}
		}
	} 
	

	return true;
}
