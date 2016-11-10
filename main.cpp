#include <iostream>
#include <string>
#include <vector>
#include "Search.h"
#include <fstream>

using namespace std;


void print_vector(vector<string> path);

int main()
{
	cout << "Program Starting.............. " << endl;

	Search s;

	return 0;
}


void print_vector(vector<string> path) {

	 vector<string>::iterator i;

	for (i = path.begin(); i != path.end(); i++) {
		cout << *i << endl;
	}

}
