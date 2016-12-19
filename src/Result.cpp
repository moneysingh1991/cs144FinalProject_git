#include "Result.h"
#include <iostream>
#include <string>
#include <vector>
#include "Search.h"
#include <fstream>
#include "string.h"
#include "User.h"
#include <algorithm>
#include <memory>
#include "PageRank.h"
#include "NumEx.h"
#define NUM_OF_RESULT_SHOWN 5   // For show number of result

 char user_file_name[] = "users.txt";

auto to_lower = [](char c)
{
    return tolower(c);
};  // Lambda function for convert to lower case

Result::Result()
{
    Main_prog();
}

Result::~Result()
{

}

bool Result::userExists(int a)
{
    Search s;
    string check = to_string(a);
    char header[] = "";

    if(s.check_file(user_file_name) == 0)  {
        s.create_file(user_file_name, header);
    }
    ifstream file("users.txt");

//    file.open();
    string str;
    while(getline(file,str))
    {
        if(str == check)
        {
            cout << "User found!" << endl;
             file.close();
            return true;
        }
    }
    cout << "User not found!" << endl;
   file.close();
    return false;
}

/**

Created by: Maninderpal Singh

produce_result_in_pair_vector()
This is function overriding
This function will call produce_result_in_pair_vector() inside Search class which is protected

**/
vector<pair<string,string>> Result::produce_result_in_pair_vector(string keyword)
{
    shared_ptr<Search> s;
    return s->produce_result_in_pair_vector(keyword);
}

namespace helper2
{

/**

Created by: Maninderpal Singh

Main_menu()
This function is just menu to show user what options are available

**/

void Main_menu()
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
    fstream userfile;
   // userfile.open("users.txt",ios::app);
    int user_id = -1;
    helper2::Main_menu();
    while(exit != "exit")
    {
        cout << endl << "Enter selection : ";
        cin >> entry;
        while(!cin)
        {
            cin.clear(); // reset failbit
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input
            cout << "Enter valid selection of 1, 2, or 3: ";
            cin >> entry;
        }
        switch(entry)
        {
        case 1:
            cout << endl << "Welcome to the SJSU Search Engine.";
            cout << endl << "Please enter your user id: ";
            try
            {
                cin >> user_id;
                if(cin.fail()){
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input
                    throw NumEx();
                }
            }
            catch (exception &e)
            {
                cout << e.what();
            }
            if(userExists(user_id))
            {
                User currentUser(user_id);
                searching_start(currentUser);
            }
            else
            {
                cout << "Would you like to create new user with an id of " << user_id << "? yes or no" << endl;
                while(input_string != "yes" && input_string != "no")
                {
                    cin >> input_string;
                    if(input_string == "yes")
                    {
                        userfile.open("users.txt",ios::app);
                        cout << "Create new user with an id of " << user_id << "." << endl;
                        userfile << "\n";
                        userfile << to_string(user_id);
                        userfile.close();
                        User currentUser(user_id);
                        cout << "User search starting." << endl;
                        searching_start(currentUser);
                    }
                    else if(input_string == "no")
                    {
                        cout << "User-less search starting." << endl;
                        user_id = -1;
                        User currentUser(user_id);
                        searching_start(currentUser);
                    }
                    else
                    {
                        cout << "Enter a valid option yes or no: " << endl;
                    }
                }
            }
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
        {
            input_string = "";

            cout << endl << "Welcome to the SJSU Search Engine ";
            User currentUser(0);
            searching_start(currentUser);

            while(input_string != "no")
            {
                cout << endl << "Search again? (yes or no): ";
                cin >> input_string;
                transform(input_string.begin(), input_string.end(), input_string.begin(), to_lower);
                if(input_string == "yes")
                {
                    User currentUser(user_id);
                    searching_start(currentUser);
                }
                else if(input_string == "no")
                {
                    cout  << "Thank you for searching." << endl;
                    exit = "exit";
                }
                else
                {
                    cout << "Invalid entry";
                }
            }
        }
        break;
        case 3:
            cout << "Thank you for searching." << endl;
            exit = "exit";
            break;

        default:
            cout << "Invalid entry";
        }
    }
}

/**

Created by: Maninderpal Singh

searching_start()
This function will show result according to user input and will check all valid inputs

**/

void Result::searching_start(User currentUser)
{

    string search_keyword;
    vector<pair<string, string>> vec_pair_result;
    Search s;
    int entry = 9999999;
    int i = 0;
    int index = 0;
    string input_string = "";
    string result_file_name = "";
    int flag = 0;
    string results[NUM_OF_RESULT_SHOWN];
    PageRank p_rank;
    char header[] = "";

    cout << endl << "Enter search keyword: ";
    cin >> search_keyword;
    int count = 0;

    transform(search_keyword.begin(), search_keyword.end(), search_keyword.begin(),  to_lower);

    if(currentUser.id > 0) { // enter info in temp_user file to help produce result
        vector<string> vec1;
        vec1.push_back(to_string(currentUser.id) + " " + search_keyword);

        if(s.check_file(helper1::convert_string_to_char_array("temp_user.txt")) == 0) {
            s.create_file(helper1::convert_string_to_char_array("temp_user.txt"), header);
        }

        std::ofstream ofs ("temp_user.txt", std::ios::out | std::ios::trunc); // clear temp file data
        ofs.close();
        s.insert_data_in_file(helper1::convert_string_to_char_array("temp_user.txt"), vec1);
    }

    if(produce_result_in_pair_vector(search_keyword).size() > 0)
    {
        vec_pair_result = produce_result_in_pair_vector(search_keyword);
        cout << endl << "Total " << vec_pair_result.size() << " found";

        if(typeid(input_string).name() != typeid(string).name())
            cout << "Invalid Input Detected. Unexpected output may be generated." << endl;

        while(input_string != "exit")
        {
            flag = 0;
            cout << endl << "----------------------Result---------------------" << endl;
            for(i = index; i < index + NUM_OF_RESULT_SHOWN; i++)
            {
                if(i < vec_pair_result.size())
                {
                    cout << "[" << i <<"]"<< vec_pair_result[i].second  << endl;
                    results[count++] =  vec_pair_result[i].first;
                }
            }
            cout << endl << "----------------------Result---------------------" << endl;
            index = i;
            count = 0;
            cout << endl << "Did you like the result? (yes, no, or exit): ";
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
                        cout << endl << "Invalid Entry. Please enter yes, no or exit: ";
                        cin >> input_string;
                        transform(input_string.begin(), input_string.end(), input_string.begin(), to_lower);
                    }
                }
                if(input_string == "yes")
                {
                    cout << "Which result do you want to open: ";
                    cin >> entry;

                    if(currentUser.id > 0)
                    {

                        string temp_string = "created_files/"+  to_string(currentUser.id) + ".txt";

                        if(s.check_file(helper1::convert_string_to_char_array(temp_string)) == 0) {
                            s.create_file(helper1::convert_string_to_char_array(temp_string), header);
                        }

                        cout << "Saving results for keyword \"" << search_keyword << "\" to file." << endl;
                        string outFileName = to_string(currentUser.id);
                        ofstream outfile;
                      //  outfile.open("created_files\\"+outFileName+".txt",ios::app);

                        vector<string> temp_vec;


                        temp_vec.push_back(search_keyword+ " 1 " + vec_pair_result[entry].first);
                      //  for(int x = 0; x < sizeof(results)/sizeof(*results); x++)
                           // outfile << results[x] + "\n";
                           s.insert_data_in_file(helper1::convert_string_to_char_array(temp_string), temp_vec);
                      //  outfile.close();
                    }


                    while(entry < 0 || entry >= index)
                    {
                        cout << endl << "Provide a valid entry to be opened: ";
                        cin >> entry;
                    }
                    input_string = "exit";
                }
            }
        }
        if(entry > -1 && entry < index)
        {
            vector<string> display_vec;

            p_rank.set_page_rank(search_keyword,"1", vec_pair_result[entry].first);

            result_file_name = vec_pair_result[entry].first;

            display_vec = s.produce_result_in_paragraph(result_file_name, vec_pair_result[entry].second);

            cout << endl << "*************************** Result *********************************" << endl;

            for ( vector<string>::iterator it=display_vec.begin(); it!=display_vec.end(); ++it)
            {
                cout << *it << " ";

            }

            cout << endl << "**************************** Result ********************************" << endl;
            cout << endl << "********************* To Read full document open -> "<< result_file_name << endl;

            entry = 9999999;
        }
    }
    else
    {
        cout << "No results were found." << endl;
    }
}
