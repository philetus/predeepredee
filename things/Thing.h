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

#include <iostream>

//#include "../geometry3/Aabb3.h"
#include "../geometry3/Transformation3.h"

namespace pdpd
{
    namespace things
    {
        // superclass for things to be simulated
        class Thing
        {
            friend std::ostream& operator<<(
                std::ostream& os, 
                const Thing& t);
        protected:
            static const double epsilon = 0.000001;
            Species species; // composite | atomic | constraint
            bool child; // true if has parent
            bool root; // true if thing is stored in world thing list
            bool touched; // true if physics has moved this node or child node
            unsigned int address; // uint uniquely identifying this thing
            Thing* parent; // parent thing
        public:
            enum Species
            {
                composite,
                atomic,
                constraint
            };
            
            Thing(Species spcs) 
            :
            species(spcs),
            child(false),
            root(false),
            touched(false), 
            address(0)
            {}
            
            virtual ~Thing() {}
            
            void set_address(unsigned int a) { address = a; }
            unsigned int get_address() { return address; }
            
            Species get_species() { return species; }
            bool is_child() { return child; }
            bool is_root() { return root; }
            
            void set_root() {
                root = true;
                parent = NULL;
                child = false;
            }
            
            void set_parent(Thing* thng) 
            {
                parent = thng;
                if(thng == NULL)
                {
                    child = false;
                    return;
                }
                child = true;
            }
            
            // allow things to be sorted spatially by axis aligned bounding box
            // TODO virtual geometry3::Aabb3 get_aabb() = 0;
            
            // offset from parent node
            virtual void get_parent_frame(geometry3::Transformation3* t) = 0;
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
