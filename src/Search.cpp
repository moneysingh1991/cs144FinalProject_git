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
#include "PageRank.h"
#include<iterator>

using namespace std;

char file_path[] = "filepath.txt";

char skip_word_file[] = "skip_word.txt";

char table1[] = "created_files/table1.txt";   // this file include table1header content
char table1_header[] = "keyword count filename";

char table1_status_file[] = "created_files/table1_status.txt";   // this file include file status
char table1_status_header[] = "is_searched filename";
char tempfile[] = "tempfile.txt";
char rank_file_path[] = "page_rank.txt";
char temp_user_path[] = "temp_user.txt";


/**
        Created by: Maninderpal Singh
        Every preprocessing will done in constructor
        like check all files exist or some thing update or deleted
**/
Search::Search()
{
    keyword_pre_process(); // this function will count all possible keyword from all file

    std::ofstream ofs ("temp_user.txt", std::ios::out | std::ios::trunc); // clear temp file data
        ofs.close();
}

//---------------------------------------------------------------------------

/**
        Created by: Maninderpal Singh

             produce_result_in_pair_vector()
            function will produce result in pair vector like filename and result
        **/
vector<pair<string,string> > Search::produce_result_in_pair_vector( string search_word)
{
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
        cout << "Setup Process going to start" << endl;

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

            This function will return sorted vector of all file in which keyword exist on the top is good result file
**/

vector<string> Search::produce_result_of_keyword(string word)
{

    vector<string> vec;
    vector<string> vec_temp1;
    vector<string> vec_temp2;
    ifstream file;
    string fileword;
    string count_keyword;
    string filename;
    vector<string> data;
    string temp;
    int count_num;
    vector<pair<string,int> > vec_pair;
    pair<string, int> pair_item;
    PageRank *page_rank;


    if(Search::check_file(table1) == 1)
    {
        file.open(table1);
        while( file >> fileword && file >> count_keyword && file >> filename) // for each fileword word read from the file
        {

            if( helper1::compare_string(word, fileword) == 1)
            {
                vec.push_back(fileword + " " + count_keyword + " " + filename );
            }
        }
        file.close();
    }

    data = vec;

    Search::insert_data_in_tempfile(tempfile, data);

    if(check_file(helper1::convert_string_to_char_array(tempfile)) == 1)
    {
        file.open(tempfile);
        while( file >> fileword && file >> count_keyword && file >> filename)
        {
            temp = fileword + " " + filename;
            istringstream convert(count_keyword);
            convert >> count_num;
            pair_item.first = temp;
            pair_item.second = count_num;
            vec_pair.push_back(pair_item);
        }
        /**
        Here used lambda function and this auto work with c++ 14 only
        **/
        sort(vec_pair.begin(), vec_pair.end(),  [](auto &left, auto &right)
        {
            return left.second > right.second;
        });

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

    // grabbing data from temp_user file

    file.open(temp_user_path);
    if ( file.peek() == std::ifstream::traits_type::eof() ) // Empty File check if file is empty
    {
            //cout << endl << "temp_user.txt is empty" << endl;

            //file empty then nothing to check because it is not search by userid
        } else {
            string file_id;
            string key_wrd;

            file >> file_id && file >> key_wrd;
            vec_temp2 = page_rank->get_result_from_page_rank(key_wrd, helper1::convert_string_to_char_array("created_files/"+file_id+ ".txt")); // getting data from particular user id file

        }

    file.close();

    vec_temp1 =  page_rank->get_result_from_page_rank(word, rank_file_path);


    //removing one vector element  from another vector if match

    if(vec_temp1.size() == 0 && vec_temp2.size() == 0) {
        return vec;
    }

    if(vec_temp1.size() > 0) {

        vec-=vec_temp1; // operator overloading for subtract one vector from another

        // adding vector to another

        vec_temp1+=vec; // operator overloading for add one vector to another

        if(vec_temp2.size() > 0) {

            vec_temp1-=vec_temp2; // operator overloading for subtract one vector from another

        // adding vector to another

            vec_temp2+=vec_temp1; // operator overloading for add one vector to another

            return vec_temp2;
        } else {
            return vec_temp1;
        }
    }

    if(vec_temp2.size() > 0) {

           vec-=vec_temp2; // operator overloading for subtract one vector from another

        // adding vector to another

            vec_temp2+=vec; // operator overloading for add one vector to another

            return vec_temp2;
        }

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
    int number_of_result = 20;

    vec = &vect;

    for ( vector <string>::iterator it=vec->begin(); it!=vec->end(); ++it)
    {
        if(check_file(helper1::convert_string_to_char_array(*it)) == 1)
        {
            file.open(*it);
            while(!file.eof())
            {
                file >> temp;
                if(temp == search_keyword)
                {
                    while(cont < number_of_result)
                    {
                        result = result + temp + " ";

                        file >> temp;
                        cont++;
                    }

                    pair_item.first = *it;
                    pair_item.second = result;
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

/**
        Created by: Maninderpal Singh

             vector<string> produce_result_from_vector()
            function will produce result in big paragraph and will return result in vector
            and will take vector in argument to search result
        **/

vector<string> Search::produce_result_in_paragraph(string filename, string data)
{
    string temp_data;
    ifstream file;

    vector<string> newVec;
    vector<string> paragraph_vec;

    string exit_flag = "";
    string exit_flag_2 = "";
    string exit_flag_3 = "exit";
    int i;
    int number_of_word_shown = 180;

    convert_to_lower(data);


    stringstream ss(data);

    istream_iterator<string> begin(ss);
    istream_iterator<string> end;
    vector<string> vstrings(begin, end);
    int temp_size = 0;

    if(check_file(helper1::convert_string_to_char_array(filename)) == 0)
    {
        cout <<  "Cannot insert. File check failed in produce_result_in_paragraph() " << endl;
    }
    else
    {
        file.open(helper1::convert_string_to_char_array(filename));


        while(exit_flag != "exit")
        {

            if(!file.eof())
            {
                file >> temp_data;

                Search::convert_to_lower(temp_data);
                exit_flag_2 = "";

                while(exit_flag_3 != "exit")
                {
                    for(i = 0; i < number_of_word_shown ; i++)
                    {
                        if(!file.eof())
                        {
                            file >> temp_data;
                            paragraph_vec.push_back(temp_data);
                        }
                    }

                    //exit all loops and return result
                    exit_flag_2 = "exit";
                    exit_flag_3 = "exit";
                    exit_flag = "exit";
                }

                while ( exit_flag_2 != "exit")
                {

                    if(temp_data == vstrings[temp_size])
                    {
                        paragraph_vec.push_back(temp_data);
                        temp_size = temp_size + 1;
                        exit_flag_2 = "exit";

                        if(paragraph_vec.size() == vstrings.size() )
                        {
                            exit_flag_2 = "exit";
                            exit_flag_3 = "";

                        }
                    }
                    else
                    {
                        if (paragraph_vec.size() > 0 )
                        {
                            paragraph_vec.clear(); // clear vector because its not going to use
                        }
                        temp_size = 0;
                        exit_flag_2 = "exit";
                    }
                }
            }
            else
            {
                exit_flag = "exit";
            }
        }
        file.close();
    }

    return paragraph_vec;
}

auto to_lower_case = [](char c)
{
    return tolower(c);
};  // Lambda function for convert to lower case

void Search::convert_to_lower(string &input_string)
{
    transform(input_string.begin(), input_string.end(), input_string.begin(), to_lower_case);
}


        /**
        Created by: Maninderpal Singh

           +=() this is operator overload function used to add two vectors
        **/


template <class T1>

vector<T1> operator+=(vector<T1>& a,   vector<T1>& b)
{
    a.insert(a.end(), b.begin(), b.end());
    return a;
}

template <class T>

vector<T> operator-=(vector<T>& vec,   vector<T>& vec_temp1)
{

    for ( vector<string>::iterator it=vec_temp1.begin(); it!=vec_temp1.end(); ++it)
    {
        vec.erase(remove(vec.begin(), vec.end(), *it), vec.end());

    }
    return vec;
}
