// Name: Chad Johnson
// Student ID: 1763718
// Email: johns428@mail.chapman.edu
// Course: CPSC 390-01
// Assignment: Assignment #2
// Purpose: ai.h declares the AI class, which contains code for finding the 
// shortest path using the different evaluation functions.

// every coordinate point is an object/struct with a char value for forbidden/intial/goal, an int value for 
// evaluated cost/value, and a tuple of indicies pointing to the previous point in the path. This
// is used for backtracking. When the goal state is found, AI backtracks through the path and changes each char
// to o along the way. Try matrix of arrays first. 


#ifndef AI_H
#define AI_H

#include <iostream>
#include <math.h>

class AI
{
	public:
		int path(int eval_type);

	private:
		struct Node {char state; int value; bool evaluated = false; int prevCoords[2];};
		void get_grid(std::string fileName);
		int euclidean_evaluation(int i0, int j0, int i1, int j1);
		int manhattan_evaluation(int i0, int j0, int i1, int j1);
		int hueristic_euclidean_evaluation(int i0, int j0, int i1, int j1);
		int hueristic_manhattan_evaluation(int i0, int j0, int i1, int j1);
		bool isPathable(char state);

		//GridReader reader;
		struct Node** grid;
		int dimension;
		int currPathCost;
};

#endif /* AI_H */