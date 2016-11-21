#ifndef RESULT_H
#define RESULT_H
#include "Search.h"


class Result : public Search
{
    public:
        Result();
        virtual ~Result();
        vector<pair<string,string> > produce_result_in_pair_vector(string keyword);

    protected:


    private:
        void Main_menu();
        void Main_prog();
        void searching_start();
};

#endif // RESULT_H
