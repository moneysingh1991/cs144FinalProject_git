#include <iostream>
#include <string>
#include <vector>
#include "Search.h"
#include <fstream>
#include "Result.h"
#include "string.h"
#include <algorithm>

#define NUM_OF_RESULT_SHOWN 5

using namespace std;


void print_vector(vector<string> path);


int main()
{
    string input_string = "no";
	Result *r;
	r = new Result();
<<<<<<< HEAD

	delete r;

=======
>>>>>>> ce8738ca0482e5e16c9ac4a5887944fdb95fe23b
	return 0;
}


void print_vector(vector<string> path) {
	for (auto i = path.begin(); i != path.end(); i++) {
		cout << *i << endl;
	}

}
