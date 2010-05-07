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
 
#ifndef PDPD_UTIL_MAP_VALUE_ITERATOR
#define PDPD_UTIL_MAP_VALUE_ITERATOR

#include <iostream>
#include <map>

#include "Iterator.h"

namespace pdpd
{
    namespace util
    {
        template<class Key, class Data>
        class MapValueIterator : public Iterator<Data>
        {
            typename std::map<Key, Data>::const_iterator current; 
            typename std::map<Key, Data>::const_iterator end; // end iterator
                   
        public:
            
            // constructor sets current ptr to beginning of deque and
            // end pointer to end of deque
            MapValueIterator(const std::map<Key, Data>& m) // takes a map by ref
            {
                current = m.begin();
                end = m.end();
            }
                        
            // check if there are more elements to iterate over
            bool has_next() { return (current != end); }
            
            // return next element and increment current ptr
            Data next() { return (*(current++)).second; }
        };
    }
} 
#endif // PDPD_MAP_VALUE_ITERATOR
