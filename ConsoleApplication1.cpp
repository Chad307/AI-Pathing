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
	bool outerLoop = true;
	string filename;
	while (outerLoop == true) {
		bool loop = true;
		while (loop == true) {
			cout << "Enter a filename: ";
			filename;
			cin >> filename;
			ifstream infile(filename);
			if (infile.is_open()) {
				loop = false;
			}
			else {
				loop = true;
				cout << "Cannot find file." << endl;
			}
		}
		loop = true;
		bool validInput = true;
		while (loop == true) {
			string selection;
			int evalType;
			cout << "1) Euclidean Evaluation" << endl;
			cout << "2) Manhatten Evaluation" << endl;
			cout << "3) Heuristic Euclidean Evaluation" << endl;
			cout << "4) Heuristic Manhatten Evaluation" << endl;
			cout << "5) Exit" << endl;
			cout << "Select an evaluation type (1-4):";
			cin >> selection;
			evalType = stoi(selection);
			switch (evalType)
			{
			case 1:
				validInput = true;
				break;
			case 2:
				validInput = true;
				break;
			case 3:
				validInput = true;
				break;
			case 4:
				validInput = true;
				break;
			case 5:
				return 0;
			default:
				cout << "Please enter an appropriate input";
				validInput = false;
				break;
			}
			if (validInput == true) {
				loop = false;
				ReadWrite rwClass;
				AI aiClass;
				char** a = rwClass.readFile(filename);
				int n = rwClass.sizeOf();
				aiClass.get_grid(a, n);
				aiClass.find_path(evalType);
				rwClass.writeFile(aiClass.output_states(), n, aiClass.get_path_cost());
			}

		}

	}
}