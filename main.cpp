#include <iostream>
#include <string>
#include "Result.h"
#include<vector>

#define NUM_OF_RESULT_SHOWN 5

using namespace std;


int main()
{

    Result *r;

    if(Search *s = dynamic_cast<Result*>(new Result))
    {
		delete s;
	}
	else {
		cout << endl << "dynamic cast fail" << endl;
	}


    return 0;
}



