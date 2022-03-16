
#include "../tester_utils.hpp"
 
#ifndef NAME //Namespace Type to be tested
# define NAME ft
#endif

#ifndef TYPE //type of variable to be tested
# define TYPE int
#endif

int main ( void ){
    NAME::stack<TYPE> array_42000__;
    
    for(int i=0; i < 1000; i++){
        for (int i = 0; i < 100000; i++){
            array_42000__.push(i);
        }
        for (int i = 0; i < 100000; i++){
            array_42000__.pop();
        }   
    }
}