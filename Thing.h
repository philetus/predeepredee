/*  Thing.h
 *
 *  superclass for things being simulated
 *  
 *  copyright 2010 michael philetus weller <philetus@gmail.com>
 *  
 *  you may redistribute or modify this code under the terms of the 
 *  GNU General Public Licence version 3.
 *  for more information see: http://www.gnu.org/licenses/gpl.html
 *  
 */
 
#ifndef PREDEE_PREDEE_THING
#define PREDEE_PREDEE_THING

#include <deque>
#include "Iterator.h"

namespace predeepredee
{
    class Thing
    {
        std::deque<Facet> facets; // stores facets for gl rendering
    public:
        Thing(); // default constructor
        ~Thing(); // destructor
        Iterator<Facet> iter_facets(); // iterator over facets
    }
}
#endif PREDEE_PREDEE_THING
