#ifndef PAGERANK_H
#define PAGERANK_H

#include<string>
#include "Search.h"
#include<vector>



class PageRank : public Search
{
    public:
        PageRank();
        vector<string> operator-( vector<string>& a);
        /**
            Created by: Maninderpal Singh

            function: set_page_rank()

            This function will set rank for particular file according to keyword
        **/
        void set_page_rank(string keyword, string rank_no, string filepath);

        /**
            Created by: Maninderpal Singh

            function:  get_result_from_page_rank()

            This function will get top rank files according to given keyword
        **/

        vector<string>  get_result_from_page_rank(string keyword);

        virtual ~PageRank();

    protected:

    private:

};

#endif // PAGERANK_H
