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
void Main_menu();
void Main_prog();
void searching_start();

int main()
{

string input_string = "no";

	Result *r;

	r = new Result();


	return 0;
}


void print_vector(vector<string> path) {

	 vector<string>::iterator i;

	for (i = path.begin(); i != path.end(); i++) {
		cout << *i << endl;
	}

}
