
#include "../../tester_utils.hpp"
#include "../../../vector.hpp"

#ifndef NAME //Namespace Type to be tested
# define NAME ft
#endif

#ifndef TYPE //type of variable to be tested
# define TYPE int
#endif

int main ( void ){
    NAME::vector<TYPE> array_42000__(10000, 42);
    NAME::vector<TYPE> array_84000__(10000, 84); 
    for (int i = 0; i < 10000; i++){
        if (i % 2 == 0)
            array_84000__.swap(array_42000__);
        else
            array_42000__.swap(array_84000__);
    }
}
