#ifndef RESULT_H
#define RESULT_H
#include "Search.h"
#include "User.h"

namespace helper2 {
    void Main_menu();

}

class Result : public Search
{
    public:
        Result();
        virtual ~Result();
        vector<pair<string,string>> produce_result_in_pair_vector(string keyword);
        bool userExists(int);
        void Main_prog();

    private:

        void searching_start(User a);
};

#endif // RESULT_H
