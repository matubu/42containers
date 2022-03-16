
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
    long long int size = array_42000__.capacity();

    for (int i = 0; i < 10000; i++){
        array_42000__.push_back(i);
        if (size != array_42000__.capacity())
            std::cout << "Size : " << array_42000__.size() << " Capacity : " << array_42000__.capacity() << " at index : " << array_42000__[i] << std::endl;
        size = array_42000__.capacity();
    }
    
}
