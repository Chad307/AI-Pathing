// Name: Chad Johnson
// Student ID: 1763718
// Email: johns428@mail.chapman.edu
// Name: Jerome Martin
// Student ID: 1851031
// Email: marti368@mail.chapman.edu
// Course: CPSC 390-01
// Assignment: Assignment #2
//Purpose: This program takes a maze input from a file as an array, 
//then navigates its way to the end using four potential navigation funtions.
//It then outputs its path to a file.
//The main handles the readwrite class and the ai class.


#include <iostream>
#include <fstream>
#include <string>
#include "ai.h"
#include "readwrite.h"

using namespace std;

//Main askes for file as input, then if it is valid, it will ask for a pathing algorithm.
//The Euclidean evaluation takes the straight line distance to the goal as the value.
//Manhatten evaluation takes the cardinal distance to the goal as the value.
//Heuristic versions of the Euclidean and Manhatten algorithms also factor in tree depth
int main(int argc, char **argv)
{
	string filename;
	filename = argv[1];
	cout << filename;
	ifstream infile(filename);
	if (infile.is_open() == false) {
		cout << "Cannot find file." << endl;
		return 0;
	}
	ReadWrite rwClass;
	char** a = rwClass.readFile(filename);
	int n = rwClass.sizeOf();
	for (int evalType = 1; evalType <5 ; evalType++){
		AI aiClass;
		aiClass.get_grid(a, n);
		aiClass.find_path(evalType);
		rwClass.writeFile(evalType, aiClass.output_states(), n, aiClass.get_path_cost());
	}
	cout << "Done";
	string r;
	cin >> r;

}
//Euclidean Evaluation
//Manhatten Evaluation
//Heuristic Euclidean Evaluation
//Heuristic Manhatten Evaluation
