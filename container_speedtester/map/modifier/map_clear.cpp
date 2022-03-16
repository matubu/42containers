
#include "../../tester_utils.hpp"
#include "../../../map.hpp"

#ifndef NAME //Namespace Type to be tested
# define NAME ft
#endif

#ifndef TYPE //type of variable to be tested
# define TYPE int
#endif

int main ( void ){
    NAME::map<TYPE, TYPE> array_42000__;
    
    for (int i = 0; i < 1000; i++){
        fill_map(array_42000__, 10000);
        array_42000__.clear();
    }
}
