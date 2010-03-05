/*  CompositeThing.h
 *
 *  superclass for things spanning child nodes
 *  
 *  copyright 2010 michael philetus weller <philetus@gmail.com>
 *  
 *  you may redistribute or modify this code under the terms of the 
 *  GNU General Public Licence version 3.
 *  for more information see: http://www.gnu.org/licenses/gpl.html
 *  
 */
 
#ifndef PDPD_THINGS_COMPOSITE_THING
#define PDPD_THINGS_COMPOSITE_THING

#include "Thing.h"
#include "../util/Iterator.h"

namespace pdpd
{
    namespace things
    {
        class CompositeThing : public Thing
        {
        public:
            virtual util::Iterator<Thing*>* iter_children() = 0;
        };
    }
}
#endif // PDPD_THINGS_COMPOSITE_THING
