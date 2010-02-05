/*  Iterator.h
 *
 *  sane iterator with next() and has_next()
 *  
 *  copyright 2010 michael philetus weller <philetus@gmail.com>
 *  
 *  you may redistribute or modify this code under the terms of the 
 *  GNU General Public Licence version 3.
 *  for more information see: http://www.gnu.org/licenses/gpl.html
 *  
 */
 
#ifndef PREDEE_PREDEE_ITERATOR
#define PREDEE_PREDEE_ITERATOR

#include <vector>
#include <deque>
#include <list>

using namespace predeepredee
{
    template<class Data>
    class Iterator
    {
        enum container_type = {vector_type, deque_type, list_type};
        container_type container;
        void* current; // current iterator
        void* end; // end iterator
        
        typedef vector_iter std::vector::const_iterator;
        typedef deque_iter std::deque::const_iterator;
        typedef list_iter std::list::const_iterator;
        
    public:
        // separate constructors for each container type
        Iterator(const std::vector& v);
        Iterator(const std::deque& d);
        Iterator(const std::list& l);

        ~Iterator(); // destructor
        bool has_next(); // check if there are more elements to iterate over
        Data next(); // return next element
    }
} 
#endif // PREDEE_PREDEE_ITERATOR
