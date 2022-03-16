
#include "../../tester_utils.hpp"

#ifndef NAME //Namespace Type to be tested
# define NAME ft
#endif

#ifndef TYPE //type of variable to be tested
# define TYPE int
#endif

int main ( void ){
    NAME::set<TYPE> array_42000__;
    NAME::set<TYPE> array_84000__; 
    fill_set(array_42000__, 10000);
    fill_set(array_84000__, 10000);
    for (int i = 0; i < 50000; i++){
        if (i % 2 == 0)
            array_84000__.swap(array_42000__);
        else
            array_42000__.swap(array_84000__);
    }
}
