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

#include "../util/Iterator.h"
#include "../materials/Material.h"
#include "Thing.h"
#include "Vertex.h"
#include "Facet.h"

namespace pdpd
{
    /*
     *  atomic things' interface requires a material and iterators
     *  over its vertices and facets to facilitate rendering and simulation
     */
    class AtomicThing : public Thing
    {
        btCollisionShape* collision_shape;
    public:
        AtomicThing() atomic(true), child(false) {}
        // virtual materials::Material get_material() = 0;
        virtual util::Iterator<Vertex>* iter_vertices() = 0;
        virtual util::Iterator<Facet>* iter_facets() = 0;
        virtual double get_mass() = 0;
        virtual void set_transformation(
            const geometry::Transformation3 a_transformation) = 0;
        virtual btCollisionShape* get_collision_shape()
        {
            return collision_shape;
        }
    }
}
#endif // PDPD_THINGS_ATOMIC_THING
