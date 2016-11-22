#include "Result.h"
#include <iostream>
#include <string>
#include <vector>
#include "Search.h"
#include <fstream>
#include "string.h"
#include <algorithm>
#include <memory>

#define NUM_OF_RESULT_SHOWN 5   // For show number of result

auto to_lower = [](char c)
{
    return tolower(c);
};  // Lambda function for convert to lower case

Result::Result()
{
    Result::Main_prog();
}

Result::~Result()
{

}

/**

Created by: Maninderpal Singh

produce_result_in_pair_vector()
This is function overriding
This function will call produce_result_in_pair_vector() inside Search class which is protected

**/
vector<pair<string,string> > Result::produce_result_in_pair_vector(string keyword)
{
    shared_ptr<Search> s;
    return s->produce_result_in_pair_vector(keyword);
}


/**

Created by: Maninderpal Singh

Main_menu()
This function is just menu to show user what options are available

**/

void Result::Main_menu()
{
    cout << endl;
    cout << endl << "***************************************************";
    cout << endl << "*            SJSU SEARCH ENGINE                   *";
    cout << endl << "*                                                 *";
    cout << endl << "* Enter 1 for User Login                          *";
    cout << endl << "* Enter 2 for Search                              *";
    cout << endl << "* Enter 3 for Exit                                *";
    cout << endl << "***************************************************";
    cout << endl;
}


/**

Created by: Maninderpal Singh

Main_prog()
This function will show main menu and will accept user input according to that

**/

void Result::Main_prog()
{
    string input_string = "";
    string exit = "";
    int entry = 0;
    int user_id;
    while(exit != "exit")
    {
        Main_menu();

        cout << endl << "Enter selection : ";
        cin >> entry;

        while(!cin)
        {
            cin.clear(); // reset failbit
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input
            cout << endl << "Enter valid selection of 1, 2, or 3: ";
            cin >> entry;
        }

        switch(entry)
        {
        case 1:
            cout << endl << "Welcome to the SJSU Search Engine ";

            cout << endl << "Please enter your user id:";
            cin >> user_id;

            while(!cin)
            {
                cin.clear(); // reset failbit
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input
                cout << endl << "Please enter a valid user id: ";
                cin >> entry;
            }
            exit = "exit";
            break;
        case 2:

            input_string = "";

            cout << endl << "Welcome to the SJSU Search Engine ";

            searching_start();

            while(input_string != "no")
            {
                cout << endl << "Search again? (yes or no): ";
                cin >> input_string;
                transform(input_string.begin(), input_string.end(), input_string.begin(), to_lower);
                if(input_string == "yes")
                {
                    searching_start();

                }
                else if(input_string == "no")
                {
                    cout << endl << "Thank you for searching" << endl;
                    exit = "exit";

                }
                else
                {
                    cout << endl << "Invalid entry";
                }

            }

            break;

        case 3:
            cout << endl << "Thank you for searching" << endl;
            exit = "exit";
            break;

        default:
            cout << endl << "Invalid entry";
        }
    }
}

/**

Created by: Maninderpal Singh

searching_start()
This function will show result according to user input and will check all valid inputs

**/

void Result::searching_start()
{

    string search_keyword;
    int number_of_result_shown;
    vector<pair<string, string> > vec_pair_result;
    Search s;
    Result *result_obj;
    int entry = 9999999;
    int i = 0;
    int index = 0;
    string input_string = "";
    string result_file_name = "";
    int flag = 0;


    cout << endl << endl << "Enter search keyword:";
    cin >> search_keyword;

    transform(search_keyword.begin(), search_keyword.end(), search_keyword.begin(),  to_lower);

    if(produce_result_in_pair_vector(search_keyword).size() > 0)
    {
        vec_pair_result = produce_result_in_pair_vector(search_keyword);
        cout << endl << "Total " << vec_pair_result.size() << " found";
        while(input_string != "exit")
        {
            flag = 0;
            cout << endl << "----------------------Result---------------------" << endl;
            for( i = index; i < index + NUM_OF_RESULT_SHOWN; i++)
            {
                if(i < vec_pair_result.size() )
                {
                    cout << endl << "[" << i <<"]"<<vec_pair_result[i].second;
                }
            }
            cout << endl << "----------------------Result---------------------" << endl;
            index = i;
            cout << endl << "Did you like the result? (yes, no, or exit) : ";
            cin >> input_string;
            transform(input_string.begin(), input_string.end(), input_string.begin(), to_lower);

            if(input_string == "exit")
            {
                //??????????????????????????????????????
            }
            else
            {

                while(flag != 1)
                {

                    if(input_string == "no" || input_string == "yes" || input_string == "exit")
                    {
                        flag = 1;   // exit flag
                    }
                    else
                    {
                        cout << endl << "Invalid Entry Please enter yes, no or exit:";
                        cin >> input_string;
                        transform(input_string.begin(), input_string.end(), input_string.begin(), to_lower);
                    }
                }
                if(input_string == "yes")
                {

                    cout << endl << "Which result do you want to open:";
                    cin >> entry;

                    while(entry < 0 || entry >= index)
                    {
                        cout << endl << "Provide a valid entry to be opened:";
                        cin >> entry;

                    }
                    input_string = "exit";
                    //  break;
                }
            }
        }
        if(entry > -1 && entry < index)
        {
            result_file_name = vec_pair_result[entry].first;
            cout << endl << "Opening file name : " << result_file_name;
            entry = 9999999;
        }
    }
    else
    {
        cout << endl << "No result found" << endl;
    }
}
