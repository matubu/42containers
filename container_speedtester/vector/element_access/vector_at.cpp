
#include "../../tester_utils.hpp"
#include "../../../vector.hpp"

#ifndef NAME //Namespace Type to be tested
# define NAME ft
#endif

#ifndef TYPE //type of variable to be tested
# define TYPE int
#endif

int main ( void ){
    NAME::vector<TYPE> array_42000__(42000, 42);

    array_42000__.at(32000);    array_42000__.at(0);    array_42000__.at(41999);
    array_42000__.at(42);   array_42000__.at(654);  array_42000__.at(9999);
    array_42000__.at(32000);    array_42000__.at(0);    array_42000__.at(41999);
    array_42000__.at(42);   array_42000__.at(654);  array_42000__.at(9999);
    array_42000__.at(32000);    array_42000__.at(0);    array_42000__.at(41999);
    array_42000__.at(42);   array_42000__.at(654);  array_42000__.at(9999);
    array_42000__.at(32000);    array_42000__.at(0);    array_42000__.at(41999);
    array_42000__.at(42);   array_42000__.at(654);  array_42000__.at(9999);
    array_42000__.at(32000);    array_42000__.at(0);    array_42000__.at(41999);
    array_42000__.at(42);   array_42000__.at(654);  array_42000__.at(9999);
    array_42000__.at(32000);    array_42000__.at(0);    array_42000__.at(41999);
    array_42000__.at(42);   array_42000__.at(654);  array_42000__.at(9999);
}