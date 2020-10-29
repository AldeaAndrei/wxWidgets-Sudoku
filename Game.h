#pragma once
class Game
{
public:
	const int n = 9;
	int** grid;
	int** solvedGrid;

	bool canSolve = true;

	Game();
	~Game();

public:
	void InitGrid();
	void Solve(int* empty);
	int* FindEmpty();
	bool CanPlace(int val, int x, int y);
	void EraseRandom();
	void SetGame();
};

