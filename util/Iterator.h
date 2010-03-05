/*  Iterator.h
 *
 *  abstract interface for sane iterators with next() and has_next()
 *
 *  inheriting from this interface allows iteration to be decoupled
 *  from the details of the container (whose implementation may thus be hidden)
 *  
 *  copyright 2010 michael philetus weller <philetus@gmail.com>
 *  
 *  you may redistribute or modify this code under the terms of the 
 *  GNU General Public Licence version 3.
 *  for more information see: http://www.gnu.org/licenses/gpl.html
 *  
 */
 
#ifndef PDPD_UTIL_ITERATOR
#define PDPD_UTIL_ITERATOR

namespace pdpd
{
    namespace util
    {
        template<class Data>
        class Iterator
        {        
        public:
            virtual ~Iterator();
            virtual bool has_next() = 0; // check if there are more elements
            virtual Data next() = 0; // return next element
        };
    }
} 
#endif // PDPD_UTIL_ITERATOR
