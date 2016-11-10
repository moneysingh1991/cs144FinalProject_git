#ifndef SEARCH_H
#define SEARCH_H
#include<vector>
#include<string>

using namespace std;

 struct letter_only;


namespace helper1 {
    char *convert_string_to_char_array(string word);

/**
        Created by: Maninderpal Singh

            check_extra_character
            This function will check each word of file with invalid character if invalid return 1 otherwise 0
        **/

        int check_extra_character(string word);
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


    protected:

    private:
        char keyword_Count_filename[];

        int count_word_from_file(char filename[], string keyword);
};

#endif // SEARCH_H
