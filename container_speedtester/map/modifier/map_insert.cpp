
#include "../../tester_utils.hpp"
#include "../../../vector.hpp"
#include "../../../map.hpp"

#ifndef NAME //Namespace Type to be tested
# define NAME ft
#endif

#ifndef TYPE //type of variable to be tested
# define TYPE int
#endif

int main ( void ){
    NAME::map<TYPE, TYPE> array_42000__;
    for (int i = 0; i < 10000; i++){
        array_42000__.insert(NAME::make_pair(i, i));
    }
}
