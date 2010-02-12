/*  Box.h
 *
 *  simple atomic thing
 *
 *  defined by a size (width, depth, height) and a position transform
 *
 *  default color is gray
 *  
 *  copyright 2010 michael philetus weller <philetus@gmail.com>
 *  
 *  you may redistribute or modify this code under the terms of the 
 *  GNU General Public Licence version 3.
 *  for more information see: http://www.gnu.org/licenses/gpl.html
 *  
 */
 
#ifndef PDPD_THINGS_BOX
#define PDPD_THINGS_BOX

#include <deque>
#include "../geometry/Transform3.h"
#include "../geometry/Vector3.h"
#include "../util/DequeIterator.h"
#include "../materials/Material.h"
#include "AtomicThing.h"
#include "Vertex.h"
#include "Facet.h"

namespace pdpd
{
    namespace things
    {
        /*
         *  atomic things' interface requires a material and iterators
         *  over its vertices and facets to facilitate rendering and simulation
         */
        class Box : public AtomicThing
        {
            Material* material; // defines what box is made of
            Transform3 transformation; // position & orientation of box
            Vector3 half_size; // vector to pos corner of box centered on origin
        public:
            Box();
            ~Box() { delete material; delete position; delete half_size; }
            
            // *** thing interface
            geometry::Aabb get_aabb();
            
            // *** atomic thing interface
            materials::Material* get_material() { return material }
            util::Iterator<Vertex> iter_vertices();
            util::Iterator<Facet> iter_facets();
        }
    }
}
#endif // PDPD_THINGS_ATOMIC_THING
