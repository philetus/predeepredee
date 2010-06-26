/*  ConstraintThing.h
 *
 *  superclass for constraints between things
 *  
 *  copyright 2010 michael philetus weller <philetus@gmail.com>
 *  
 *  you may redistribute or modify this code under the terms of the 
 *  GNU General Public Licence version 3.
 *  for more information see: http://www.gnu.org/licenses/gpl.html
 *  
 */
 
#ifndef PDPD_THINGS_CONSTRAINT_THING
#define PDPD_THINGS_CONSTRAINT_THING

#include "Thing.h"
#include "RigidThing.h"
#include "../util/Iterator.h"
#include "../geometry/Vector3.h"
#include "../geometry/Facet.h"

namespace pdpd
{
    namespace things
    {
        class ConstraintThing : public Thing
        {
        protected:
            bool disable_collisions; // disable collisions between constrained
        public:
            ConstraintThing(bool dsbl_cllsns = false)
            :
            Thing(constraint),
            disable_collisions(dsbl_cllsns)
            {}
                        
            virtual btTypedConstraint* get_constraint() = 0;

            virtual util::Iterator<geometry::Vector3>* iter_vertices() = 0;
            virtual util::Iterator<geometry::Facet>* iter_facets() = 0;
            virtual util::Iterator<RigidThing*>* iter_constrained() = 0;
            
            bool get_disable_collisions() { return disable_collisions; }
        };
    }
}
#endif // PDPD_THINGS_CONSTRAINT_THING
