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
	cout << "Enter a filename: ";
	string filename;
	cin >> filename;

	string selection;
	int evalType;
	cout << "Select an evaluation type: ";
	cin >> selection;
	evalType = stoi(selection);
	ReadWrite rwClass;
	AI aiClass;
	char** a = rwClass.readFile(filename);
	int n = rwClass.sizeOf();
	aiClass.get_grid(a, n);
	aiClass.find_path(evalType);

	string r;
	cin >> r;
	
}
