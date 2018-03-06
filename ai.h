// Name: Chad Johnson
// Student ID: 1763718
// Email: johns428@mail.chapman.edu
// Course: CPSC 390-01
// Assignment: Assignment #2
// Purpose: ai.h declares the AI class, which contains code for finding the 
// shortest path using the different evaluation functions.

#ifndef AI_H
#define AI_H

#include <iostream>
#include <math.h>
#include <vector>
#include <stdlib.h> 

//Finds shortest path in grid using specified algorithm.
class AI
{
public:
	//summary: Mark path nodes in grid using specified evaluation function.
	//parameter: "eval_type": enum for which eval function to use.
	void find_path(int eval_type);

	//summary: Set grid and dimension fields.
	//parameter: "arr": char matrix.
	//parameter: "n": dimension of matrix.
	void get_grid(char** arr, int n);

	//summary: Output char matrix with updated path positions.
	//return: char matrix with updated chars.
	char** output_states();

	//summary: Return path_depth.
	//return: path_depth int.
	int get_path_cost();

private:
	//summary: Struct representing a position in the grid.
	//parameter: "state": state of position (goal, initial, forbidden, etc.)
	//parameter: "value": evaluated cost of position.
	//parameter: "depth": depth value as part of its path.
	//parameter: "evaluated": state of whether this position has been evaluated.
	//parameter: "visited": state of whether this position has been visited.
	//parameter: "prev_coords": coordinates of previous node in path.
	struct Node { char state; int value; int depth; bool evaluated; bool visited; int prev_coords[2]; };

	//summary: Returns euclidean evaluation value based on two positions.
	//parameter: "i0": i coord of first position.
	//parameter: "j0": j coord of first position.
	//parameter: "i1": i coord of second position.
	//parameter: "j1": j coord of second position.
	//return: evaluated cost of position.
	int euclidean_evaluation(int i0, int j0, int i1, int j1);

	//summary: Returns manhattan evaluation value based on two positions.
	//parameter: "i0": i coord of first position.
	//parameter: "j0": j coord of first position.
	//parameter: "i1": i coord of second position.
	//parameter: "j1": j coord of second position.
	//return: evaluated cost of position.
	int manhattan_evaluation(int i0, int j0, int i1, int j1);

	//summary: Returns heuristic euclidean evaluation value based on two positions.
	//parameter: "i0": i coord of first position.
	//parameter: "j0": j coord of first position.
	//parameter: "i1": i coord of second position.
	//parameter: "j1": j coord of second position.
	//return: evaluated cost of position.
	int hueristic_euclidean_evaluation(int i0, int j0, int i1, int j1);

	//summary: Returns heuristic manhattan evaluation value based on two positions.
	//parameter: "i0": i coord of first position.
	//parameter: "j0": j coord of first position.
	//parameter: "i1": i coord of second position.
	//parameter: "j1": j coord of second position.
	//return: evaluated cost of position.
	int hueristic_manhattan_evaluation(int i0, int j0, int i1, int j1);

	//summary: Checks if specified position can be moved to.
	//parameter: "state": state of position.
	//return: true if position can be moved to, false otherwise.
	bool is_pathable(char state);

	//summary: Checks if fringe contains specified grid position.
	//parameter: "fringe": fringe vector.
	//parameter: "node_i": i coord of position.
	//parameter: "node_j": j coord of position.
	//return: true if fringe contains positions, false otherwise.
	bool fringe_contains(std::vector<std::vector<int> > fringe, int node_i, int node_j);

	//Matrix of Node structs.
	struct Node** grid;

	//Dimension of grid.
	int dimension;

	//Depth of current path.
	int path_depth;
};

#endif /* AI_H */