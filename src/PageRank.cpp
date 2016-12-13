#include "PageRank.h"
#include "Search.h"
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>

using namespace std;

char rank_file_path[] = "page_rank.txt";

PageRank::PageRank()
{
    //ctor
}

PageRank::~PageRank()
{
    //dtor
}

  /**
            Created by: Maninderpal Singh

            function: set_page_rank()

            This function will set rank for particular file according to keyword
        **/
void PageRank::set_page_rank(string keyword, string rank_no, string filepath) {

    vector<string> data;

    data.push_back(keyword + " " + rank_no + " " + filepath);


    if(Search::check_file(rank_file_path) == 0) {
        cout << endl << "file not exist please create page_rank.txt file";
    } else {
        Search::insert_data_in_file(rank_file_path,data);
    }

}

vector<string>  PageRank::get_result_from_page_rank(string keyword) {
    vector<pair<string,int> > vec_pair;
    pair<string, int> pair_item;
    ifstream file;
    string fileword, count_keyword, filename;
    map<string, int> map_item;
    int count_map = 0;
    vector<string> result_vec;

    if(Search::check_file(rank_file_path) == 0) {
        cout << endl << "something wrong getting result from page_rank.txt file";
    } else {
        file.open(rank_file_path);
        while( file >> fileword && file >> count_keyword && file >> filename) // for each fileword word read from the file
        {


            if( keyword == fileword )
            {
                if(map_item.find(filename) == map_item.end()) {
                    map_item[filename] = 1;
                  //  cout << endl << "insert -> " << filename << " = 1" << endl;
                } else {
                    map_item[filename] = map_item[filename]+ 1;
                  //  cout << endl << "increasing " << filename << " value" << endl;
                }
            }
        }
        file.close(); // close file
    }


    /**
        adding  map value into vector
    **/

    for(map<string, int >::iterator it = map_item.begin(); it != map_item.end(); ++it)
    {

        pair_item.first = it->first;
        pair_item.second = it->second;
        vec_pair.push_back(pair_item);
    }

    //sorting vector here most high rank file at top

     sort(vec_pair.begin(), vec_pair.end(),  [](auto &left, auto &right)
        {
            return left.second > right.second;
        });

        // inserting all filenames in string vector
        for ( vector<pair<string,int> >::iterator it=vec_pair.begin(); it!=vec_pair.end(); ++it)
        {
            result_vec.push_back(it->first);
        }

    return result_vec;
}

vector<string> operator-( vector<string>& vec) {
    vector<string> vec2;

    vec.erase(std::remove(vec.begin(), vec.end(), ""), vec.end());

    return vec2;
}
