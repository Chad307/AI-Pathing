#ifndef ReadWrite_H
#define ReadWrite_H


#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h> 

class ReadWrite
{
public:
	char** readFile(std::string filename);
	int sizeOf();
	void writeFile(char** arr, int n);
private:
	int n;
};

#endif