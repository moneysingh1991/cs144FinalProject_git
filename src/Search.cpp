#include <fstream>
#include <iostream>
#include <cstdlib>
#include "Search.h"
#include <fstream>
#include "string.h"
#include <sstream>
#include <algorithm>
#include <map>
#include <typeinfo>

using namespace std;

char file_path[] = "filepath.txt";

char skip_word_file[] = "skip_word.txt";

char table1[] = "created_files/table1.txt";   // this file include table1header content
char table1_header[] = "keyword count filename";

char table1_status_file[] = "created_files/table1_status.txt";   // this file include file status
char table1_status_header[] = "is_searched filename";
char tempfile[] = "tempfile.txt";
//string search_word = "str";

/**
        Created by: Maninderpal Singh
        Every preprocessing will done in constructor
        like check all files exist or some thing update or deleted
**/
Search::Search()
{

    keyword_pre_process(); // this function will count all possible keyword from all file

    //Search::produce_result_of_keyword("hello");

   // helper1::print_vector(Search::produce_result_of_keyword( Search::produce_result_of_keyword(search_word), search_word));


    //produce_result_from_file("and");



    // cout << strcasecmp(helper1::convert_string_to_char_array("hellooooo"), helper1::convert_string_to_char_array("Hello"));


}

//---------------------------------------------------------------------------

/**
        Created by: Maninderpal Singh

            void produce_result_in_pair_vector()
            function will produce result in pair vector like filename and result
        **/
         vector<pair<string,string> > Search::produce_result_in_pair_vector( string search_word) {
             vector<pair<string,string> > vec;

            return Search::produce_result_of_keyword( Search::produce_result_of_keyword(search_word), search_word);

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
        cout << "Failed to open." << endl;

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
        cout << "Exit can't run further because no file exists" << endl;

        cout << "Do you wish to continue? Enter yes or no: ";

        string user_input;

        cin >> user_input;

        if(user_input == "yes")
        {
            cout << "Please be patient. This will take some time ........" << endl;
            create_table1_status_file(table1_status_file, table1_status_header);
            create_file(table1, table1_header); // first creating file

            ifstream filename;

            filename.open(table1);

            if(filename.fail())
            {
                cout << "Failed to open" << table1 << endl;
            }
            else
            {
                cout << "File created successfully" << endl;
            }

            insert_data_in_vector(vec, vec2);  // insert data in vector
            insert_data_in_file(table1, vec);  // inserting vector data in file
            insert_data_in_file(table1_status_file, vec2);  // inserting vector data in file
            cout << "Processing finished" << endl;
        }
        else
        {
            cout << "Terminating..." << endl;
            exit(0);
        }
    }
    else
    {
        // insert_data_in_vector(vec,vec2);  // insert data in vector

        //insert_data_in_file(table1_status_file, vec2);  // inserting vector data in file
        //cout << "Status is good at checking table1 file and table1_status_file" << endl;
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
        cout << "Error on creation" << filename << endl;
    }
}


//--------------------------------------------------------------------------------------

/**
        Created by: Maninderpal Singh
        inserting data in file
        first argument is file name which char[]
        second argument is vector which contain data
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
    ifstream file;
    string result;
    vector<string> check_word;
    for (i = file_vector.begin(); i != file_vector.end(); i++)
    {

        cout << endl <<*i << " started ............."<< endl;
        vector_str = *i;

        //  stncpy(tab2, vector_str.c_str());

        tab2 = helper1::convert_string_to_char_array(vector_str);

        if(Search::check_file(tab2) == 1)
        {
            file.open(tab2);

            while(file >> keyword)
            {

                if(helper1::check_extra_character(keyword) == 0 && keyword.size() > 2 && helper1::check_word_in_vector(check_word, keyword) == 1)
                {
                    // storing result of count in file with converting int to string
                    result = static_cast<ostringstream*>( &(ostringstream() << Search::count_word_from_file(tab2, keyword)) )->str();
                    vec_store_string =  keyword + " " + result + " " +*i ;
                    vec.push_back(vec_store_string);
                    check_word.push_back(keyword);
                }

            }

            file.close();

            // helper1::print_vector(check_word);

            check_word.clear();

            cout << endl << *i << " finished ............."<< endl;

        }
        else
        {
            cout << endl << tab2 << " file not found ............."<< endl;
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
        while(check_char_file >> char_check_string)
        {
            word_check_array = helper1::convert_string_to_char_array(char_check_string);
        }
        check_char_file.close();
    }
    else
    {
        cout << "Failed to open file: " << skip_word_file << endl;
    }
    while(word_check_array[i] != '\0')   // read array till end
    {
        if(strchr(word.c_str(), word_check_array[i]))
        {
            return 1;
        }
        i++;
    }
    return 0;
}
//----------------------------------------------------------------//

/**
            Created by: Maninderpal Singh

            function: produce_result_of_keyword()
            return: vector

            This function will return vector of all keyword result which user searching
**/

vector<string> Search::produce_result_of_keyword(string word)
{

    vector<string> vec;
    ifstream file;
    string fileword;
    string count_keyword;
    string filename;
    vector<string> data;
    string temp;
    int count_num;
    vector<pair<string,int> > vec_pair;
    pair<string, int> pair_item;


    if(Search::check_file(table1) == 1)
    {
        file.open(table1);
        while( file >> fileword && file >> count_keyword && file >> filename) // for each fileword word read from the file
        {
            // cout << endl << fileword << " " << count_keyword << " " << filename;

            if( helper1::compare_string(word, fileword) == 1)
            {
                vec.push_back(fileword + " " + count_keyword + " " + filename );
            }
        }
        file.close();
        // return vec;
    }


    // data = produce_result_of_keyword(keyword);

    data = vec;


    // helper1::print_vector(data);

    Search::insert_data_in_tempfile(tempfile, data);

    if(check_file(helper1::convert_string_to_char_array(tempfile)) == 1)
    {
        //  cout << endl << "This is working for temp file ........";
        file.open(tempfile);
        while( file >> fileword && file >> count_keyword && file >> filename)
        {
            //  cout << endl << fileword << " "<< count_keyword << " " << filename;
            temp = fileword + " " + filename;
            istringstream convert(count_keyword);
            convert >> count_num;
            //  cout << endl << count_num;
            //  map_data[temp] = count_num;
            pair_item.first = temp;
            pair_item.second = count_num;
            vec_pair.push_back(pair_item);
        }

        /**
        Here used lemda function and this auto work with c++ 14 only
        **/
        sort(vec_pair.begin(), vec_pair.end(),  [](auto &left, auto &right)
        {
            return left.second > right.second;
        });

        // cout << endl << "This is map " << endl;

        //for ( vector<pair<string,int> >::iterator it=vec_pair.begin(); it!=vec_pair.end(); ++it)
        //  cout << it->first << " => " << it->second << '\n';

        file.close();

        // writing sorting data with descending order data in temp file
        ofstream writefile;
        writefile.open(tempfile);

        for ( vector<pair<string,int> >::iterator it=vec_pair.begin(); it!=vec_pair.end(); ++it)
        {
            writefile  << it->first << '\n';

        }

        writefile.close();

    }

    // grab data from temp file

    vec.clear();

    file.open(tempfile);

    while( file >> fileword && file >> filename) // for each fileword word read from the file
    {
        vec.push_back(filename);
    }

    file.close();

    return vec;

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

void print_vector(vector<pair<string, string> > path)
{
    int k = 0;

    if(path.size() > 0)
    {
        for ( vector<pair<string,string> >::iterator it=path.begin(); it!=path.end(); ++it)
        {
            //cout << endl << it->first;
            cout << endl << "[" << k <<"] = " << it->second;
            k++;
        }

    }

    else
    {
        cout << endl << "No Result found";
    }
}

template <class T>
void print_Generic(T path)
{

    int k = 0;

    if(path.size() > 0)
    {

            for (auto i = path.begin(); i != path.end(); i++)
            {
                cout << endl << "[" << k <<"] = " << *i;
                k++;

            }


    }
    else
    {
        cout << endl << "vector is empty " << endl ;
    }
}


/**
        Created by: Maninderpal Singh

            compare_string()
            This function will return 1 if string are same otherwise 0
**/
int compare_string(string word1, string word2)
{

    string data = word1;
    string data2 = word2;

    transform(data.begin(), data.end(), data.begin(), ::tolower);
    transform(data2.begin(), data2.end(), data2.begin(), ::tolower);

    // cout << endl << "a = " << data << ", b =  " << data2 << endl;

    if(data.compare(data2) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
    Created by: Maninderpal Singh

    function: check_word_in_vector()
    return: vector

    This function will return 1 if keyword contain in vector
**/

int check_word_in_vector(vector<string> path, string keyword)
{
    if(path.size() == 0)
    {

        return 1;
    }

    vector<string>::iterator i;

    for (i = path.begin(); i != path.end(); i++)
    {
        if(compare_string(*i, keyword) == 1)
        {
            return 0;
        }

    }

    return 1;
}

}
//--------------------------------------------------------------

/**
        Created by: Maninderpal Singh

            void produce_result_from_file()
            function will produce result of given keyword
        **/

vector<pair<string,string> > Search::produce_result_of_keyword(vector<string> vect, string search_keyword)
{
    vector<string> *vec = nullptr;
    vector<string> result_vector;
    ifstream file;
    string result = " ";
    string temp;
    vector<pair<string,string> > vec_pair;
    pair<string, string> pair_item;

    int cont = 1;

    vec = &vect;

    for ( vector <string>::iterator it=vec->begin(); it!=vec->end(); ++it)
    {
        // cout << endl << "------------------------------------------------------------";
        if(check_file(helper1::convert_string_to_char_array(*it)) == 1)
        {
            file.open(*it);
            while(!file.eof())
            {
                file >> temp;
                if(temp == search_keyword)
                {
                    while(cont < 20)
                    {
                        result = result + temp + " ";

                        file >> temp;
                        cont++;
                    }

                    pair_item.first = *it;
                    pair_item.second = result;
                    // result_vector.push_back(result);
                    vec_pair.push_back(pair_item);
                    result = " ";
                    cont = 1;
                }
            }
            file.close();
        }
        else
        {
            cout << endl << "File does not exist";
        }
        //cout << endl << "------------------------------------------------------------";
    }
    return vec_pair;
}
//------------------------------------------------------------------

/**
        Created by: Maninderpal Singh
        insert_data_in_tempfile()
        first argument is file name which char[]
        second aregument is vector which contain data
        This function is used for insert data in file in overwrite mode
        **/

void Search::insert_data_in_tempfile(char filename[], vector<string> data)
{
    if(check_file(filename) == 0)
    {
        cout <<  "Cannot insert. File check failed" << endl;
    }
    else
    {
        ofstream writefile;
        writefile.open(filename);  // insert data in file as append mode
        vector<string>::iterator i;
        for (i = data.begin(); i != data.end(); i++)
        {
            writefile  << *i << '\n';
        }
        writefile.close();
    }
}
