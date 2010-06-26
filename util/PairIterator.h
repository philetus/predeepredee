/*  PairIterator.h
 *
 *  iterator over elements of a pair with next() and has_next()
 *  
 *  copyright 2010 michael philetus weller <philetus@gmail.com>
 *  
 *  you may redistribute or modify this code under the terms of the 
 *  GNU General Public Licence version 3.
 *  for more information see: http://www.gnu.org/licenses/gpl.html
 *  
 */
 
#ifndef PDPD_UTIL_PAIR_ITERATOR
#define PDPD_UTIL_PAIR_ITERATOR

#include <iostream>

#include "Iterator.h"

namespace pdpd
{
    namespace util
    {
        template<class Data>
        class PairIterator : public Iterator<Data>
        {
            Data alpha;
            Data beta; 
            int index;
        public:
            
            // constructor sets current ptr to beginning of deque and
            // end pointer to end of deque
            PairIterator(Data lph, Data bt) // takes two args of data type
            :
            alpha(lph),
            beta(bt),
            index(0)
            {}
                        
            // check if there are more elements to iterate over
            bool has_next() { return (index < 2); }
            
            // return next element and increment current ptr
            Data next()
            {
                switch(index++)
                {
                case 0:
                    return alpha;
                case 1:
                    return beta;
                default:
                    std::cout << "overran end of pair iterator!" << std::endl;
                    return NULL;
                }
            }
        };
    }
} 
#endif // PDPD_PAIR_ITERATOR
