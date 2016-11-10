#include <fstream>
#include <iostream>
#include <cstdlib>
#include "Search.h"
#include <fstream>
#include "string.h"
#include <sstream>


using namespace std;

char file_path[] = "filepath.txt";

char skip_word_file[] = "skip_word.txt";

char table1[] = "created_files/table1.txt";   // this file include table1header content
char table1_header[] = "keyword count filename";

char table1_status_file[] = "created_files/table1_status.txt";   // this file include file status
char table1_status_header[] = "is_searched filename";

/**
        Created by: Maninderpal Singh
        Every preprocessing will done in constructor
        like check all files exist or some thing update or deleted
**/
Search::Search()
{
    keyword_pre_process(); // this function will count all possible keyword from all file

}

//--------------------------------------------------------------------------------------
/**
        Created by: Maninderpal Singh
        creating status file for table 1
**/

void Search::create_table1_status_file(char file[], char table1_status_header[])
{
    create_file(file, table1_status_header);
}

//--------------------------------------------------------------------------------------

/**
Created by: Maninderpal Singh
grab_all_Files() function will grab all files path and store in vector and return vector
**/
vector<string> Search::grab_all_Files(char file_path[])
{

    vector<string> filePath;
    ifstream infile;

    //char read_file_name = Search::file_path;

    infile.open(file_path);

    if (infile.fail())
    {
        cout << "open failed" << endl;

    }
    else
    {
        string sLine;
        while (!infile.eof())
        {
            infile >> sLine;

            filePath.push_back(sLine.data());

        }

        infile.close();
    }

    return filePath;
}

//--------------------------------------------------------------------------------------


/**
Created by: Maninderpal Singh

void keyword_pre_process() function will count all possible keyword in all files and store result in new file
**/

void Search::keyword_pre_process()
{
    vector<string> vec;
    vector<string> vec2;

    if(check_file(table1) == 0 ||Search::check_file(table1_status_file) == 0)
    {
        cout << "exit cant run further because no file exist" << endl;

        cout << "You want continue and wait for all processing: Enter yes or no : ";

        string user_input;

        cin >> user_input;

        if(user_input == "yes")
        {
            cout << "Be patient It will take time ........" << endl;
            create_table1_status_file(table1_status_file, table1_status_header);



            create_file(table1, table1_header); // first creating file

            ifstream filename;

            filename.open(table1);

            if(filename.fail() )
            {
                cout << " failed to open " << table1 << endl;
            }
            else
            {
                cout << " file created successfully " << endl;
            }

            insert_data_in_vector(vec, vec2);  // insert data in vector
            insert_data_in_file(table1, vec);  // inserting vector data in file
            insert_data_in_file(table1_status_file, vec2);  // inserting vector data in file
            cout << "Processing ........ Done" << endl;
        }
        else
        {
            cout << "program terminate .............." << endl;
            exit(0);
        }
    }
    else
    {
        insert_data_in_vector(vec,vec2);  // insert data in vector

        insert_data_in_file(table1_status_file, vec2);  // inserting vector data in file
        cout << "Status is good at checking table1 file and table1_status_file" << endl;
    }

}


//--------------------------------------------------------------------------------------
/**
    Created by: Maninderpal Singh

    void create_file(char filename[]) function will create new text file with given name in argument
**/

void Search::create_file(char filename[], char fileHeaderLine[])
{
    try
    {
        ofstream file(filename);

        file << fileHeaderLine << endl;
        file.close();
    }
    catch (exception e)
    {
        cout << "error to create " << filename << endl;
    }
}


//--------------------------------------------------------------------------------------

/**
        Created by: Maninderpal Singh
        inserting data in file
        first argument is file name which char[]
        second aregument is vector which contain data
**/

void Search::insert_data_in_file(char filename[], vector<string> data)
{
    if(check_file(filename) == 0)
    {
        cout <<  "cannot insert file check fail" << endl;
    }
    else
    {
        ofstream writefile;

        writefile.open(filename, ios_base::app | ios_base::out);  // insert data in file as append mode


        vector<string>::iterator i;

        for (i = data.begin(); i != data.end(); i++)
        {
            writefile  << *i << '\n';
        }


        writefile.close();

    }

}

//--------------------------------------------------------------------------------------

/**
        Created by: Maninderpal Singh
        check if file exist or not
**/

int Search::check_file(char filename[])
{
    ifstream file;

    file.open(filename);

    if(file.fail())
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

//--------------------------------------------------------------------------------------

/**
        Created by: Maninderpal Singh
        insert_data_in_vector() This function will insert data in vector as string 2 vectors are being
        use for insert data in 2 diffirent files
**/
void Search::insert_data_in_vector(vector<string> &vec, vector<string> &file_status_vector)
{

    vector<string> file_vector = grab_all_Files(file_path);
    char* tab2 = new char [1024]; // char[] for copy string value

    vector<string>::iterator i;

    string vector_str;
    string vec_store_string;
    string keyword;
    ostringstream convert;

    string result;

    for (i = file_vector.begin(); i != file_vector.end(); i++)
    {
        cout << *i << endl;
        vector_str = *i;

        //  stncpy(tab2, vector_str.c_str());

        tab2 = helper1::convert_string_to_char_array(vector_str);

        ifstream file;

        if(Search::check_file(tab2) == 1)
        {
            file.open(tab2);

            while(file >> keyword)
            {
                if(helper1::check_extra_character(keyword) == 0 && keyword.size() > 2) {
                    result = static_cast<ostringstream*>( &(ostringstream() << Search::count_word_from_file(tab2, keyword)) )->str();
                    vec_store_string =  keyword + " " + result + " " +*i ;
                    vec.push_back(vec_store_string);
                }

            }

        }
        else
        {
            vec_store_string = "false " + *i;
        }
        vec_store_string = "true " + *i;
        file_status_vector.push_back(vec_store_string);
    }
    // vec.push_back("file1name1 computer 300");
}
//----------------------------------------------------------------//

/**
        Created by: Maninderpal Singh
        count_word_from_file() this function will return count of argument keyword and argument file name
**/

int Search::count_word_from_file(char filename[], string keyword)
{

    ifstream file;
    int countwords = 0 ;
    string fileword;



    if(Search::check_file(filename) == 1)
    {

        file.open(filename);


        while( file >> fileword ) // for each fileword word read from the file
        {

            if( keyword == fileword )
            {
                ++countwords ;
            }

        }

        file.close(); // close file

        return countwords;
    }

    else
    {
        cerr << "Error! File not found!\n" ;
        return 1 ;
    }

}

 /**
        Created by: Maninderpal Singh

            check_extra_character
            This function will check each word of file with invalid character if invalid return 1 otherwise 0
        **/


int helper1::check_extra_character(string word)
{

    string char_check_string;
    int i = 0;

    char* word_check_array = new char[1024];  // for store all extra character from file for check
   // char* word_check_array = new char[1024];

    ifstream check_char_file;

    check_char_file.open(skip_word_file);

    if(!check_char_file.fail())
    {
        while(check_char_file >> char_check_string) {

            word_check_array = helper1::convert_string_to_char_array(char_check_string);
        }
        check_char_file.close();
    } else {
        cout << "file open failed : " << skip_word_file << endl;
    }



    while(word_check_array[i] != '\0') { // read array till end

         if(strchr(word.c_str(), word_check_array[i]))
        {
            return 1;
        }
        i++;
    }

    return 0;

}

//--------------------------------------------------------------//

namespace helper1
{

char *convert_string_to_char_array(string word)
{

    char* word_array = new char[1024];

    strcpy(word_array, word.c_str());

    return word_array;
}

}
//--------------------------------------------------------------
