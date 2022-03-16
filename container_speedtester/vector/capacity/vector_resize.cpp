
#include "../../tester_utils.hpp"
#include "../../../vector.hpp"

#ifndef NAME //Namespace Type to be tested
# define NAME ft
#endif

#ifndef TYPE //type of variable to be tested
# define TYPE int
#endif

int main ( void ){
    NAME::vector<TYPE> array_42000__;
    long long int toto = array_42000__.capacity();

    array_42000__.resize(4, 21);
    for (int i = 0; i < 10000; i++){
        array_42000__.resize(5 + i, 42);
        /*if (array_42000__.capacity() != toto)
            std::cout << "size : " << array_42000__.size() << " capacity : " << array_42000__.capacity() << std::endl;*/
        toto = array_42000__.capacity();        
    }
   array_42000__.resize(653, 32);
    array_42000__.resize(9896, 21);
    array_42000__.resize(1, 0);
    array_42000__.resize(42000, 0);/**/
   // std::cout << "size : " << array_42000__.size() << " capacity : " << array_42000__.capacity() << std::endl;
}