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
    {
        // superclass for things to be simulated
        class Thing
        {
        protected:
            static const double epsilon = 0.000001;

            bool atomic; // is this thing composed of other things?
            bool dynamic; // can this thing move/explode?
            bool child; // true if has parent
            bool touched; // true if physics has moved this node or child node
            bool root; // true if thing is stored in world thing list
            unsigned int address; // uint uniquely identifying this thing
            Thing* parent; // parent thing
        public:
            Thing() 
            :
            atomic(false),  
            dynamic(false),
            child(false), 
            touched(false), 
            root(false),
            address(0)
            {}
            
            virtual ~Thing() {}
            
            void set_address(unsigned int a) { address = a; }
            unsigned int get_address() { return address; }
            
            bool is_atomic() { return atomic; }
            bool is_root() { return root; }
            void set_root(bool r) { root = r; }
            virtual bool is_dynamic() = 0;
            virtual bool is_child() { return child; }
            
            // allow things to be sorted spatially by axis aligned bounding box
            // TODO virtual geometry::Aabb3 get_aabb() = 0;
            
            // offset from parent node
            virtual void get_parent_frame(geometry::Transformation3* t) = 0;
            virtual void get_gl_parent_frame(btScalar* m16) = 0;
            
            // recursively set touched flags to indicate physics engine has
            // moved stuff
            virtual void touch()
            {
                touched = true;
                if(is_child()) parent->touch();
            }
        };
    }
}
#endif // PDPD_THINGS_THING
