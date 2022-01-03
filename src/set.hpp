#include "iterators.hpp"
#include "iter_bool.hpp"
#include "RBT.hpp"

template < class T,                        // set::key_type/value_type
           class Compare = std::less<T>,        // set::key_compare/value_compare
           class Alloc = std::allocator<T>      // set::allocator_type
           > class set
{
    public :
        typedef T key_type;
        typedef T value_type;
        typedef Compare key_compare;
        typedef Compare value_compare;
        typedef Alloc allocator_type;
        
        

};