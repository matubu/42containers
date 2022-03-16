
#include "../tester_utils.hpp"

#ifndef NAME //Namespace Type to be tested
# define NAME ft
#endif

#ifndef TYPE //type of variable to be tested
# define TYPE int
#endif

int main ( void ){
    NAME::stack<TYPE> array_42000__;
    for(int j = 0; j < 100; j++){
        for (int i = 0; i < 1000000; i++){
            array_42000__.push(i);
            array_42000__.top();
        }
    }
}