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
    public:
        AtomicThing() atomic(true) {}
        virtual materials::Material get_material() = 0;
        virtual util::Iterator<Vertex> iter_vertices() = 0;
        virtual util::Iterator<Facet> iter_facets() = 0;
    }
}
#endif // PDPD_THINGS_ATOMIC_THING
