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

#include "../geometry/Aabb3.h"
#include "../geometry/Transformation3.h"

namespace pdpd
{
    namespace things
        
        // superclass for things to be simulated
        class Thing
        {
            bool atomic; // is this thing composed of other things?
            bool dynamic; // can this thing move/explode?
            static const double wiggle = 0.000001;
        public:
            Thing() atomic(false) {}
            ~Thing() {}
            bool is_atomic() { return atomic; }
            virtual bool is_dynamic() = 0;
            virtual bool is_child() = 0;
            virtual bool is_root() = 0;
            
            // allow things to be sorted spatially by axis aligned bounding box
            virtual geometry::Aabb3 get_aabb() = 0;
            
            // offset from parent node
            virtual geometry::Transformation3 get_offset() = 0;
        }
    }
}
#endif // PDPD_THINGS_THING
