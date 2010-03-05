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
 
#ifndef PDPD_UTIL_DEQUE_ITERATOR
#define PDPD_UTIL_DEQUE_ITERATOR

#include "Iterator.h"
#include <deque>

namespace pdpd
{
    namespace util
    {
        template<class Data>
        class DequeIterator : public Iterator<Data>
        {
            typename std::deque<Data>::const_iterator current; // current iterator
            typename std::deque<Data>::const_iterator end; // end iterator
                   
        public:
            
            // constructor sets current ptr to beginning of deque and
            // end pointer to end of deque
            DequeIterator(const std::deque<Data>& d) // takes a deque by ref
            {
                current = d.begin();
                end = d.end();
            }
                        
            // check if there are more elements to iterate over
            bool has_next() { return current == end; }
            
            // return next element and increment current ptr
            Data next() { return *(current++); }
        };
    }
} 
#endif // PDPD_DEQUE_ITERATOR
