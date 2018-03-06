// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
#include <string>
#include "ai.h"
#include "readwrite.h"

using namespace std;
int main(int argc, char **argv)
{
	bool outerLoop = true;
	string filename;
	while(outerLoop == true){
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
				cout << "Cannot find file."<<endl;
			}
		}
		loop = true;
		bool validInput = true;
		while (loop = true) {
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
				validInput = true;
			case 4:
				break;
			case 5:
				return 0;
				break;
			default:
				cout << "Please enter an appropriate input";
				validInput = false;
				break;
			}
			if (validInput == true) {
				ReadWrite rwClass;
				AI aiClass;
				char** a = rwClass.readFile(filename);
				int n = rwClass.sizeOf();
				aiClass.get_grid(a, n);
				aiClass.find_path(evalType);
				rwClass.writeFile(aiClass.output_states(), n);
			}

		}

	}
}
