#include "readwrite.h"
using namespace std;
char** ReadWrite::readFile(std::string filename) {
	ifstream infile(filename);
	string line;
	n = 0;

	getline(infile, line);
	n = stoi(line);
	//cout << n << endl;

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
void ReadWrite::writeFile(char** arr, int n, int p) {

	ofstream outputFile("outputFile.txt");
	char** output_grid = new char*[n];
	for (int i = 0; i < n; i++)
	{
		output_grid[i] = new char[n];
		for (int j = 0; j < n; j++) {
			output_grid[i][j] = arr[i][j];
			outputFile << arr[i][j];
			cout << arr[i][j];
		}
		outputFile << endl;
		printf("\n");

	}
	outputFile << "PathCost:"<<p<<endl;
	printf("Path cost: %d\n\n", p);
	outputFile.close();

	return;
}