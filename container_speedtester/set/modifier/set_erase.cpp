
#include "../../tester_utils.hpp"

#ifndef NAME //Namespace Type to be tested
# define NAME ft
#endif

#ifndef TYPE //type of variable to be tested
# define TYPE int
#endif

int main ( void ){
    /*NAME::vector<TYPE> array_42000__(10000, 42);
    for (int i = 0; i < 10000; i++){
        array_42000__.erase(array_42000__.begin());
    }*/

    NAME::set<TYPE> array_42000_bis;
    fill_set(array_42000_bis, 10000);
    for(int i = 0; i < 9000; i++){
        array_42000_bis.erase(array_42000_bis.begin());
    }
}

