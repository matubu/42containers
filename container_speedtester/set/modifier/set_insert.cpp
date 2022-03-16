
#include "../../tester_utils.hpp"

#ifndef NAME //Namespace Type to be tested
# define NAME ft
#endif

#ifndef TYPE //type of variable to be tested
# define TYPE int
#endif

int main ( void ){
    NAME::set<TYPE> array_42000__;
    for (int i = 0; i < 10000; i++){
        array_42000__.insert(i);
    }
}
