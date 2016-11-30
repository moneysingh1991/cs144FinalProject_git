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
<<<<<<< HEAD
        void Main_prog();

    private:

=======
    private:
        void Main_menu();
        void Main_prog();
>>>>>>> ce8738ca0482e5e16c9ac4a5887944fdb95fe23b
        void searching_start(User a);
};

#endif // RESULT_H
