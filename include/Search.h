#ifndef SEARCH_H
#define SEARCH_H
#include<vector>
#include<string>

using namespace std;

 struct letter_only;

template <class T>


vector<T> operator-=(vector<T>& vec,   vector<T>& vec_temp1);

template <class T1>

vector<T1> operator+=(vector<T1>& a,   vector<T1>& b);


namespace helper1 {
    /**
            Created by: Maninderpal Singh

            function: check_word_in_vector()
            return: vector

            This function will return 1 if keyword contain in vector
        **/

        int check_word_in_vector(vector<string> vec, string keyword);

    /**
        Created by: Maninderpal Singh

           convert_string_to_char_array()
            This function will  arrayconvert string to char
**/
    char *convert_string_to_char_array(string word);

/**
        Created by: Maninderpal Singh

            check_extra_character
            This function will check each word of file with invalid character if invalid return 1 otherwise 0
**/

        int check_extra_character(string word);

/**
        Created by: Maninderpal Singh

            print_vector()
            This function will print print vector
**/

template <class T>
        void print_Generic(T path);

      //  void print_vector(vector<string> path);
        void print_vector(vector< pair<string, string> > path);


/**
        Created by: Maninderpal Singh

            compare_string()
            This function will return 1 if string are same otherwise 0
**/
        int compare_string(string word1, string word2);


}


class Search
{
    public:


        /**
        Created by: Maninderpal Singh

           Search() constructor
        **/
        Search();

        /**
        Created by: Maninderpal Singh

            void keyword_pre_process()
            function will count all possible keyword in all files and store result in new file
        **/

        void keyword_pre_process();

        /**
        Created by: Maninderpal Singh

            void convert_to_lower()
            function will convert given string to lowercase
        **/

        void convert_to_lower(string &input_string);

        /**
        Created by: Maninderpal Singh

             vector<string> produce_result_from_vector()
            function will produce result in big paragraph and will return result in vector
            and will take vector in argument to search result
        **/

        vector<string> produce_result_in_paragraph(string filename, string data);

        /**
        Created by: Maninderpal Singh

            insert_data_in_vector
            function will insert string data in vector
        **/
        void insert_data_in_vector(vector<string> &vec,vector<string> &file_status_vector);

        /**
        Created by: Maninderpal Singh

            grab_all_Files()
            function will grab all files path and store in vector and return vector
        **/
        vector<string> grab_all_Files(char file_path[]);




        /**
        Created by: Maninderpal Singh

             void create_file(char filename[], char fileHeaderLine[])
             function will create new text file with first argument
             second argument is first line of file

        **/

        void create_file(char filename[], char fileHeaderLine[]);

        /**
        Created by: Maninderpal Singh
        creating status file for table1
        **/

        void create_table1_status_file(char file[], char table1_status_header[]);

        /**
        Created by: Maninderpal Singh
        inserting data in file
        first argument is file name which char[]
        second aregument is vector which contain data
        **/

        void insert_data_in_file(char filename[], vector<string> data);

        /**
        Created by: Maninderpal Singh
        check if file exist or not
        return 0 if not return 1 if exist

        **/

        int check_file(char filename[]);

        /**
        Created by: Maninderpal Singh
        insert_data_in_tempfile()
        first argument is file name which char[]
        second aregument is vector which contain data
        This function is used for insert data in file in overwrite mode
        **/

        void insert_data_in_tempfile(char filename[], vector<string> data);

        /**
        Created by: Maninderpal Singh

            void produce_result_in_pair_vector()
            function will produce result in pair vector like filename and result
        **/

        vector<pair<string,string> > produce_result_in_pair_vector(string keyword);


    private:
        char keyword_Count_filename[];

        /**
            Created by: Maninderpal Singh

            function: count_word_from_file()
            return: int

            This function will return count of keyword occur in given file
        **/

        int count_word_from_file(char filename[], string keyword);

        /**
            Created by: Maninderpal Singh

            function: produce_result_of_keyword()
            return: vector

            This function will return vector of all keyword result which user searching
        **/

        vector<string> produce_result_of_keyword(string word);

        /**
        Created by: Maninderpal Singh

            void produce_result_of_keyword()
            function will produce result of given keyword and return in vector like <filename, result>
        **/

        vector<pair<string,string> > produce_result_of_keyword(vector<string> vec, string keyword);



};

#endif // SEARCH_H
