// Name: Chad Johnson
// Student ID: 1763718
// Email: johns428@mail.chapman.edu
// Course: CPSC 390-01
// Assignment: Assignment #2
// Purpose: ai.cpp implements AI.

#include "ai.h"

int AI::path(int eval_type)
{
	int (*evaluate) (int, int, int, int);

	switch (eval_type)
	{
		case 0:
			evaluate = euclidean_evaluation;
			break;
		case 1:
			evaluate = manhattan_evaluation;
			break;
		case 2:
			evaluate = hueristic_euclidean_evaluation;
			break;
		case 3:
			evaluate = heuristic_manhattan_evaluation;
			break;
		default:
			//print error and return;
			break;
	}

	int currI = 0;
	int currJ = 0;
	int goalI = 0;
	int goalJ = 0;
	int nextI = 0;
	int nextJ = 0;
	int nextCost = 0;

	std::vector<int[2]> fringe = new std::vector();

	//Find initial node.
	for (int i = 0; i < grid.size(); i++){
		for (int j = 0; j < grid[0].size(); i++){
			if (grid[i][j].state == "i")
			{
				currI = i;
				currJ = j;
			}
			else if (grid[i][j].state == "g")
			{
				goalI = i;
				goalJ = j;
			}
		}
	}

	while (gird[currI][currJ].state != "g")
	{
		//Check the four directions.
		//Up
		if ((currI - 1) >= 0 && isPathable(grid[currI - 1][currJ].state) 
			&& !grid[currI - 1][currJ].visited)
		{
			if (!grid[currI - 1][currJ].evaluated){
				grid[currI - 1][currJ].value = evaluate(currI - 1, currJ, goalI, goalJ);
			}
			nextI = currI - 1;
			nextJ = currJ;

			if (!fringeContains(fringe, currI - 1, currJ))
			{
				fringe.push_back({currI - 1, currJ})
			}
		}

		//Down
		if ((currI + 1) <= (dimension - 1) && isPathable(grid[currI + 1][currJ].state) 
			&& !grid[currI + 1][currJ].visited)
		{
			if (!grid[currI + 1][currJ].evaluated){
				grid[currI + 1][currJ].value = evaluate(currI + 1, currJ, goalI, goalJ);
			}
			// if (grid[currI + 1][currJ].value < grid[currI - 1][currJ].value){
			// 	nextI = currI + 1;
			// 	nextJ = currJ;
			// }

			if (!fringeContains(fringe, currI + 1, currJ))
			{
				fringe.push_back({currI + 1, currJ})
			}
		}

		//Left
		if ((currJ - 1) >= 0 && isPathable(grid[currI][currJ - 1].state) 
			&& !grid[currI][currJ - 1].visited)
		{
			if (!grid[currI][currJ - 1].evaluated){
				grid[currI][currJ - 1].value = evaluate(currI, currJ - 1, goalI, goalJ);
			}
			// if (grid[currI][currJ - 1].value < grid[currI + 1][currJ].value){
			// 	nextI = currI;
			// 	nextJ = currJ - 1;
			// }

			if (!fringeContains(fringe, currI, currJ - 1))
			{
				fringe.push_back({currI, currJ - 1})
			}
		}

		//Right
		if ((currJ + 1) <= (dimension - 1) && isPathable(grid[currI][currJ + 1].state) 
			&& !grid[currI][currJ + 1].visited)
		{
			if (!grid[currI][currJ + 1].evaluated){
				grid[currI][currJ + 1].value = evaluate(currI, currJ + 1, goalI, goalJ);
			}
			// if (grid[currI][currJ + 1].value < grid[currI][currJ - 1].value){
			// 	nextI = currI;
			// 	nextJ = currJ + 1;
			// }

			if (!fringeContains(fringe, currI, currJ + 1))
			{
				fringe.push_back({currI, currJ + 1})
			}
		}

		//Choose node with smallest cost in fringe
		for (int i = 0; i < fringe.size(); i++)
		{
			if (i = 0)
			{
				nextCost = grid[fringe[0][0]][fringe[0][1]].value;
				nextI = fringe[0][0];
				nextJ = fringe[0][1];
			}
			else if (grid[fringe[i][0]][fringe[i][1]].value < nextCost)
			{
				nextCost = grid[fringe[i][0]][fringe[i][1]].value;
				nextI = fringe[i][0];
				nextJ = fringe[i][1];
			}
		}

		//Remove next node from fringe
		for (int i = 0; i < fringe.size(); i++)
		{
			if (fringe[i][0] == nextI && fringe[i][1] == nextJ){
				fringe.erase(fringe.begin() + i);
			}
		}

		//Set next node's prevCoords to curr coords
		grid[nextI][nextJ].prevCoords[0] = currI;
		grid[nextI][nextJ].prevCoords[1] = currJ;

		//Set curr node visited to true
		grid[currI][currJ].visited = true;

		//Move to next node
		currI = nextI;
		currJ = nextJ;


	}
}

void AI::get_grid(std::string fileName)
{
	char basic_grid[][] = reader.getGrid();
	dimension = basic_grid[0].size();

	for (int i = 0; i < dimension; i++)
	{
		grid[i] = new Node[dimension];
		for (int j = 0; j < dimension; j++){
			grid[i][j] = new Node();
			grid[i][j].state = basic_grid[i][j];
		}
	}

	return;
}

int AI::euclidean_evaluation(int i0, int j0, int i1, int j1)
{
	return sqrt(pow(i0 - i1, 2) + pow(j0 - j1, 2));
}

int AI::manhattan_evaluation()
{
	return (abs(i0 - i1) + abs(j0 - j1));
}

int AI::hueristic_euclidean_evaluation(int i0, int j0, int i1, int j1)
{
	return currPathCost + euclidean_evaluation(i0, i1, j0, j1);
}

int AI::hueristic_manhattan_evaluation(int i0, int j0, int i1, int j1)
{
	return currPathCost + manahttan_evaluation(i0, i1, j0, j1);
}


bool AI::isPathable(char state)
{
	if (state == '+')
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool AI::fringeContains(std::vector<int[2]> fringe, int i, int j)
{
	for (int i = 0; i < fringe.size(); i++)
	{
		if (fringe[0][0] == i && fringe[0][1] == j)
		{
			return true;
		}
	}
	return false;
}