/*  AtomicThing.h
 *
 *  superclass for things made of one hunk of stuff
 *  
 *  copyright 2010 michael philetus weller <philetus@gmail.com>
 *  
 *  you may redistribute or modify this code under the terms of the 
 *  GNU General Public Licence version 3.
 *  for more information see: http://www.gnu.org/licenses/gpl.html
 *  
 */
 
#ifndef PDPD_THINGS_ATOMIC_THING
#define PDPD_THINGS_ATOMIC_THING

#include <iostream>

#include "Thing.h"
#include "../util/Iterator.h"
#include "../geometry/Vector3.h"
#include "../geometry/Facet.h"
// TODO #include "../materials/Material.h"

namespace pdpd
{
    namespace things
    {
        /*
         *  atomic things' interface requires a material and iterators
         *  over its vertices and facets to facilitate rendering and simulation
         */
        class AtomicThing : public Thing
        {
            AtomicThing(); // hide
            AtomicThing(const AtomicThing&); // hide
        protected:
            bool soft;
            float mass; // mass of thing (in kg?)
        public:
            float color[4]; // color (TODO implement material class)

            AtomicThing(
                bool sft,
                float* clr,
                float mss = 0.0)
            :
            Thing(atomic),
            soft(sft),
            mass(mss)
            {
                for(int i = 0; i < 4; i++) color[i] = clr[i];
            }
            
            // virtual materials::Material get_material() = 0;
            virtual util::Iterator<geometry::Vector3>* iter_vertices() = 0;
            virtual util::Iterator<geometry::Facet>* iter_facets() = 0;
            virtual bool is_dynamic()
            {
                if((mass - epsilon) > 0.0) return true;
                return false;         
            }
            virtual float get_mass() { return mass; }
            
            bool is_soft() { return soft; }            
        };
    }
}
#endif // PDPD_THINGS_ATOMIC_THING
