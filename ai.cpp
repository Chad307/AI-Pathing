// Name: Chad Johnson
// Student ID: 1763718
// Email: johns428@mail.chapman.edu
// Course: CPSC 390-01
// Assignment: Assignment #2
// Purpose: ai.cpp implements AI.

#include "ai.h"

void AI::path(int eval_type)
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

	int curr_i = 0;
	int curr_j = 0;
	int goal_i = 0;
	int goal_j = 0;
	int next_i = 0;
	int next_j = 0;
	int next_cost = 0;

	std::vector<int[2]> fringe = new std::vector();

	//Find initial node.
	for (int i = 0; i < grid.size(); i++){
		for (int j = 0; j < grid[0].size(); i++){
			if (grid[i][j].state == "i")
			{
				curr_i = i;
				curr_j = j;
			}
			else if (grid[i][j].state == "g")
			{
				goal_i = i;
				goal_j = j;
			}
		}
	}

	while (gird[curr_i][curr_j].state != "g")
	{
		//Check the four directions.
		//Up
		if ((curr_i - 1) >= 0 && is_pathable(grid[curr_i - 1][curr_j].state) 
			&& !grid[curr_i - 1][curr_j].visited)
		{
			if (!grid[curr_i - 1][curr_j].evaluated){
				grid[curr_i - 1][curr_j].value = evaluate(curr_i - 1, curr_j, goal_i, goal_j);
				grid[curr_i - 1][curr_j].depth = path_depth + 1;
				grid[curr_i - 1][curr_j].evaluated = true;
			}

			if (!fringe_contains(fringe, curr_i - 1, curr_j))
			{
				fringe.push_back({curr_i - 1, curr_j})
			}
		}

		//Down
		if ((curr_i + 1) <= (dimension - 1) && is_pathable(grid[curr_i + 1][curr_j].state) 
			&& !grid[curr_i + 1][curr_j].visited)
		{
			if (!grid[curr_i + 1][curr_j].evaluated){
				grid[curr_i + 1][curr_j].value = evaluate(curr_i + 1, curr_j, goal_i, goal_j);
				grid[curr_i + 1][curr_j].depth = path_depth + 1;
				grid[curr_i + 1][curr_j].evaluated = true;
			}

			if (!fringe_contains(fringe, curr_i + 1, curr_j))
			{
				fringe.push_back({curr_i + 1, curr_j})
			}
		}

		//Left
		if ((curr_j - 1) >= 0 && is_pathable(grid[curr_i][curr_j - 1].state) 
			&& !grid[curr_i][curr_j - 1].visited)
		{
			if (!grid[curr_i][curr_j - 1].evaluated){
				grid[curr_i][curr_j - 1].value = evaluate(curr_i, curr_j - 1, goal_i, goal_j);
				grid[curr_i][curr_j - 1].depth = path_depth + 1;
				grid[curr_i][curr_j - 1].evaluated = true;
			}

			if (!fringe_contains(fringe, curr_i, curr_j - 1))
			{
				fringe.push_back({curr_i, curr_j - 1})
			}
		}

		//Right
		if ((curr_j + 1) <= (dimension - 1) && is_pathable(grid[curr_i][curr_j + 1].state) 
			&& !grid[curr_i][curr_j + 1].visited)
		{
			if (!grid[curr_i][curr_j + 1].evaluated){
				grid[curr_i][curr_j + 1].value = evaluate(curr_i, curr_j + 1, goal_i, goal_j);
				grid[curr_i][curr_j + 1].depth = path_depth + 1;
				grid[curr_i][curr_j + 1].evaluated = true;
			}

			if (!fringe_contains(fringe, curr_i, curr_j + 1))
			{
				fringe.push_back({curr_i, curr_j + 1})
			}
		}

		//Choose node with smallest cost in fringe
		for (int i = 0; i < fringe.size(); i++)
		{
			if (i == 0)
			{
				next_cost = grid[fringe[0][0]][fringe[0][1]].value;
				next_i = fringe[0][0];
				next_j = fringe[0][1];
			}
			else if (grid[fringe[i][0]][fringe[i][1]].value < next_cost)
			{
				next_cost = grid[fringe[i][0]][fringe[i][1]].value;
				next_i = fringe[i][0];
				next_j = fringe[i][1];
			}
		}

		//Remove next node from fringe
		for (int i = 0; i < fringe.size(); i++)
		{
			if (fringe[i][0] == next_i && fringe[i][1] == next_j){
				fringe.erase(fringe.begin() + i);
			}
		}

		//Set next node's prevCoords to curr coords
		grid[next_i][next_j].prevCoords[0] = curr_i;
		grid[next_i][next_j].prevCoords[1] = curr_j;

		//Set curr node visited to true
		grid[curr_i][curr_j].visited = true;

		//Move to next node
		curr_i = next_i;
		curr_j = next_j;

		//Set path_depth
		path_depth = grid[curr_i][curr_j].path_depth;
	}

	//Goal found
	//Retrace path
	while (grid[curr_i][curr_j].state != "i")
	{
		if (grid[curr_i][curr_j].state != "g")
		{
			path.push_back({curr_i, curr_j});
		}
		curr_i = grid[curr_i][curr_j].prevCoords[0];
		curr_j = grid[curr_i][curr_j].prevCoords[1];
	}

	//Path stored
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
	return path_depth + euclidean_evaluation(i0, i1, j0, j1);
}

int AI::hueristic_manhattan_evaluation(int i0, int j0, int i1, int j1)
{
	return path_depth + manahttan_evaluation(i0, i1, j0, j1);
}


bool AI::is_pathable(char state)
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

bool AI::fringe_contains(std::vector<int[2]> fringe, int node_i, int node_i)
{
	for (int i = 0; i < fringe.size(); i++)
	{
		if (fringe[i][0] == node_i && fringe[j][1] == node_j)
		{
			return true;
		}
	}
	return false;
}