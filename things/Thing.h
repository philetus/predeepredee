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
 
#ifndef PDPD_THINGS_THING
#define PDPD_THINGS_THING

#include "../geometry/Aabb.h"

namespace pdpd
{
    namespace things
        
        // superclass for things to be simulated
        class Thing
        {
            bool atomic; // is this thing composed of other things?
        public:
            Thing() atomic(false) {}
            ~Thing() { delete atomic; }
            bool is_atomic() { return atomic; }
            
            // allow things to be sorted spatially by axis aligned bounding box
            virtual geometry::Aabb get_aabb() = 0;
        }
    }
}
#endif PDPD_THINGS_THING
