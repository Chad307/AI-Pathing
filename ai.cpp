#include "ai.h"

void AI::find_path(int eval_type)
{
	int (AI::*evaluate) (int, int, int, int);

	evaluate = &AI::euclidean_evaluation;
	switch (eval_type)
	{
	case 0:
		evaluate = &AI::euclidean_evaluation;
		break;
	case 1:
		evaluate = &AI::manhattan_evaluation;
		break;
	case 2:
		evaluate = &AI::hueristic_euclidean_evaluation;
		break;
	case 3:
		evaluate = &AI::hueristic_manhattan_evaluation;
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
	std::vector<std::vector<int> > fringe;
	std::vector<int> new_coords;
	int num_nodes_visited = 0;
	path_depth = 0;

	//Find initial node.
	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			if (grid[i][j].state == 'i')
			{
				curr_i = i;
				curr_j = j;
			}
			else if (grid[i][j].state == 'g')
			{
				goal_i = i;
				goal_j = j;
			}
		}
	}

	while (grid[curr_i][curr_j].state != 'g')
	{

		/*std::cout << curr_i;
		std::cout << curr_j;
		std::cout << ",";*/
		//Check the four directions.
		//Up
		if ((curr_i - 1) >= 0 && is_pathable(grid[curr_i - 1][curr_j].state)
			&& !grid[curr_i - 1][curr_j].visited)
		{
			if (!grid[curr_i - 1][curr_j].evaluated) {
				grid[curr_i - 1][curr_j].value = (this->*evaluate)(curr_i - 1, curr_j, goal_i, goal_j);
				grid[curr_i - 1][curr_j].depth = grid[curr_i][curr_j].depth + 1;
				grid[curr_i - 1][curr_j].evaluated = true;
			}

			if (!fringe_contains(fringe, curr_i - 1, curr_j))
			{
				grid[curr_i - 1][curr_j].prev_coords[0] = curr_i;
				grid[curr_i - 1][curr_j].prev_coords[1] = curr_j;

				new_coords.push_back(curr_i - 1);
				new_coords.push_back(curr_j);
				fringe.push_back(new_coords);
				new_coords.clear();
			}
		}

		//Down
		if ((curr_i + 1) <= (dimension - 1) && is_pathable(grid[curr_i + 1][curr_j].state)
			&& !grid[curr_i + 1][curr_j].visited)
		{
			if (!grid[curr_i + 1][curr_j].evaluated) {
				grid[curr_i + 1][curr_j].value = (this->*evaluate)(curr_i + 1, curr_j, goal_i, goal_j);
				grid[curr_i + 1][curr_j].depth = grid[curr_i][curr_j].depth + 1;
				grid[curr_i + 1][curr_j].evaluated = true;
			}

			if (!fringe_contains(fringe, curr_i + 1, curr_j))
			{
				grid[curr_i + 1][curr_j].prev_coords[0] = curr_i;
				grid[curr_i + 1][curr_j].prev_coords[1] = curr_j;

				new_coords.push_back(curr_i + 1);
				new_coords.push_back(curr_j);
				fringe.push_back(new_coords);
				new_coords.clear();
			}
		}

		//Left
		if ((curr_j - 1) >= 0 && is_pathable(grid[curr_i][curr_j - 1].state)
			&& !grid[curr_i][curr_j - 1].visited)
		{
			if (!grid[curr_i][curr_j - 1].evaluated) {
				grid[curr_i][curr_j - 1].value = (this->*evaluate)(curr_i, curr_j - 1, goal_i, goal_j);
				grid[curr_i][curr_j - 1].depth = grid[curr_i][curr_j].depth + 1;
				grid[curr_i][curr_j - 1].evaluated = true;
			}

			if (!fringe_contains(fringe, curr_i, curr_j - 1))
			{
				grid[curr_i][curr_j - 1].prev_coords[0] = curr_i;
				grid[curr_i][curr_j - 1].prev_coords[1] = curr_j;

				new_coords.push_back(curr_i);
				new_coords.push_back(curr_j - 1);
				fringe.push_back(new_coords);
				new_coords.clear();
			}
		}

		//Right
		if ((curr_j + 1) <= (dimension - 1) && is_pathable(grid[curr_i][curr_j + 1].state)
			&& !grid[curr_i][curr_j + 1].visited)
		{
			if (!grid[curr_i][curr_j + 1].evaluated) {
				grid[curr_i][curr_j + 1].value = (this->*evaluate)(curr_i, curr_j + 1, goal_i, goal_j);
				grid[curr_i][curr_j + 1].depth = grid[curr_i][curr_j].depth + 1;
				grid[curr_i][curr_j + 1].evaluated = true;
			}

			if (!fringe_contains(fringe, curr_i, curr_j + 1))
			{
				grid[curr_i][curr_j + 1].prev_coords[0] = curr_i;
				grid[curr_i][curr_j + 1].prev_coords[1] = curr_j;

				new_coords.push_back(curr_i);
				new_coords.push_back(curr_j + 1);
				fringe.push_back(new_coords);
				new_coords.clear();
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
			if (fringe[i][0] == next_i && fringe[i][1] == next_j) {
				fringe.erase(fringe.begin() + i);
			}
		}

		//Set curr node visited to true
		grid[curr_i][curr_j].visited = true;

		//Move to next node
		curr_i = next_i;
		curr_j = next_j;

		//Set path_depth
		path_depth = grid[curr_i][curr_j].depth;

		//Increment nodes visited
		num_nodes_visited++;

		printf("Curr: %d, %d\n", curr_i, curr_j);
		printf("Prev: %d, %d\n", grid[curr_i][curr_j].prev_coords[0], grid[curr_i][curr_j].prev_coords[1]);
	}

	//Goal found
	//Retrace path
	int curr_i_temp;
	int curr_j_temp;
	while (grid[curr_i][curr_j].state != 'i')
	{
		//std::cout << curr_i;
		//std::cout << curr_j;
		//std::cout << ",";
	
		if (grid[curr_i][curr_j].state != 'g')
		{
			grid[curr_i][curr_j].state = 'o';

			new_coords.push_back(curr_i);
			new_coords.push_back(curr_j);
			path.push_back(new_coords);
			new_coords.clear();
		}
		curr_i_temp = curr_i;
		curr_j_temp = curr_j;
		curr_i = grid[curr_i_temp][curr_j_temp].prev_coords[0];
		curr_j = grid[curr_i_temp][curr_j_temp].prev_coords[1];
	}

	//Path stored
	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			std::cout << grid[i][j].state;
		}
		printf("\n");
	}

	printf("Number of steps taken: %d\n", path_depth);
	printf("Number of nodes: %d\n", num_nodes_visited);

	return;
}

void AI::get_grid(char** arr, int n)
{
	
	dimension = n;

	grid = new Node*[dimension];
	for (int i = 0; i < dimension; i++)
	{
		grid[i] = new Node[dimension];
		for (int j = 0; j < dimension; j++){
	 		grid[i][j] = *new Node();
	 		grid[i][j].state = arr[i][j];
			grid[i][j].evaluated = false;
			grid[i][j].visited = false;
			//std::cout << grid[i][j].state;
		}

	}

	return;
}

int AI::euclidean_evaluation(int i0, int j0, int i1, int j1)
{
	return sqrt(pow(i0 - i1, 2) + pow(j0 - j1, 2));
}

int AI::manhattan_evaluation(int i0, int j0, int i1, int j1)
{
	return (abs(i0 - i1) + abs(j0 - j1));
}

int AI::hueristic_euclidean_evaluation(int i0, int j0, int i1, int j1)
{
	return path_depth + euclidean_evaluation(i0, i1, j0, j1);
}

int AI::hueristic_manhattan_evaluation(int i0, int j0, int i1, int j1)
{
	return path_depth + manhattan_evaluation(i0, i1, j0, j1);
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

bool AI::fringe_contains(std::vector<std::vector<int> > fringe, int node_i, int node_j)
{
	for (int i = 0; i < fringe.size(); i++)
	{
		if (fringe[i][0] == node_i && fringe[i][1] == node_j)
		{
			return true;
		}
	}
	return false;
}