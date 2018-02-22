// Name: Chad Johnson
// Student ID: 1763718
// Email: johns428@mail.chapman.edu
// Course: CPSC 390-01
// Assignment: Assignment #2
// Purpose: ai.h declares the AI class, which contains code for finding the 
// shortest path using the different evaluation functions.

//every coordinate point is an object/struct with a char value for forbidden/intial/goal, an int value for 
// evaluated cost/value, and a pointer/tuple of indicies pointing to the previous point in the path. This
// is used for backtracking. When the goal state is found, AI backtracks through the path and changes each char
// to o along the way. Try matrix of arrays first. 


#ifndef AI
#define AI

#include <stdio.h>
#include <iostream>
#include <string.h>

using namespace std;

struct node {char state; int value; node* prev;};

class AI
{
	public:
		int path(int eval_type);

	private:
		void get_grid(string fileName);
		int euclidean_evaluation();
		int manhattan_evaluation();
		int hueristic_evaluation();





};
#endif