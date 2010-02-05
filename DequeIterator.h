/*  DequeIterator.h
 *
 *  iterator over elements of a deque with next() and has_next()
 *  
 *  copyright 2010 michael philetus weller <philetus@gmail.com>
 *  
 *  you may redistribute or modify this code under the terms of the 
 *  GNU General Public Licence version 3.
 *  for more information see: http://www.gnu.org/licenses/gpl.html
 *  
 */
 
#ifndef PREDEE_PREDEE_DEQUE_ITERATOR
#define PREDEE_PREDEE_DEQUE_ITERATOR

#include "Iterator.h"
#include <deque>

using namespace predeepredee
{
    template<class Data>
    class DequeIterator : public Iterator
    {
        std::deque::const_iterator; current; // current iterator
        std::deque::const_iterator; end; // end iterator
               
    public:
        
        // constructor sets current ptr to beginning of deque and
        // end pointer to end of deque
        Iterator(const std::deque& d) // constructor takes a deque by ref
        {
            current = d.begin();
            end = d.end();
        }
        
        // destructor
        ~Iterator() { delete current; delete end; } 
        
        // check if there are more elements to iterate over
        bool has_next() { return current == end; }
        
        // return next element and increment current ptr
        Data next() { return *(current++); }
    }
} 
#endif // PREDEE_PREDEE_DEQUE_ITERATOR
