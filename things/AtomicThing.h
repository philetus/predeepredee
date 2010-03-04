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

#include "Thing.h"
#include "../util/Iterator.h"
#include "../geometry/Vector3.h"
#include "../geometry/Facet.h"
// TODO #include "../materials/Material.h"

namespace pdpd
{
    /*
     *  atomic things' interface requires a material and iterators
     *  over its vertices and facets to facilitate rendering and simulation
     */
    class AtomicThing : public Thing
    {
        Transformation3 world_frame; // position & orientation relative to world
        btCollisionShape* collision_shape;
    public:
        AtomicThing() 
        :
        Thing(), 
        atomic(true), 
        child(false)
        {}
        
        // virtual materials::Material get_material() = 0;
        virtual util::Iterator<Vector3>* iter_vertices() = 0;
        virtual util::Iterator<Facet>* iter_facets() = 0;
        virtual double get_mass() = 0;
        
        virtual void set_world_frame(const geometry::Transformation3& frame)
        {
            world_frame.crib(frame);
            touch(); // set touched flag (and recursively set parents' too)
        }
        
        virtual void get_world_frame(geometry::Transformation3* frame)
            { frame->crib(world_frame); }
        
        virtual void get_gl_world_frame(btScalar* m16)
            { world_frame.getOpenGLMatrix(m16); }
        
        virtual btCollisionShape* get_collision_shape()
            { return collision_shape; }
    }
}
#endif // PDPD_THINGS_ATOMIC_THING
