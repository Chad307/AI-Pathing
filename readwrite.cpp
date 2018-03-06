#include "readwrite.h"
using namespace std;
char** ReadWrite::readFile(std::string filename) {
	ifstream infile(filename);
	string line;
	n = 0;

	getline(infile, line);
	n = stoi(line);
	cout << n << endl;

	int i = 0;

	char** a = new char*[n];
	for (int i = 0; i < n; ++i) {
		a[i] = new char[n];
	}
	while (getline(infile, line))
	{
		for (int j = 0; j < line.length(); ++j)
		{
			a[i][j] = line[j];
		}
		i++;
	}
	/*for (int i = 0; i < n; i++) {
	cout << "\n";
	for (int j = 0; j < n; j++) {
	cout << a[i][j];
	}
	}*/
	return a;
	delete[] a;
	a = NULL;

}
int ReadWrite::sizeOf() {
	return n;
}