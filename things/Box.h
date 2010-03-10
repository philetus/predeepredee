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

#include "AtomicThing.h"
#include "../util/Iterator.h"
#include "../geometry/Vector3.h"
#include "../geometry/Transformation3.h"
#include "../geometry/Facet.h"

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
        protected:
            // Material* material; // defines what box is made of
            geometry::Vector3 scale; // scale vector representing size of box
            float mass; // mass of box (in grams?)
            
            static const float normal_table[][3]; // table of normals by facet
            static const int vertex_table[][3]; // table of vertices by facet
            
            // *** iterator over facets
            friend class FacetIterator;
            class FacetIterator : public util::Iterator<geometry::Facet>
            {
                static const int facet_count = 12;
                int index;
                Box& box;
            public:
                FacetIterator(Box& b) : index(0), box(b) {}
                virtual bool has_next() { return index < facet_count; }
                virtual geometry::Facet next()
                    { return box.get_facet(index++); }
            }; // FacetIterator
            
        public:
            
            // scale, mass, child
            Box(
                const geometry::Vector3& s,
                const geometry::Transformation3& f,
                float m = 0.0, 
                bool c = false)
            :
            AtomicThing(f),
            scale(s),
            mass(m)
            {
                child = c;
                
                // set collision shape from scale (half size)
                collision_shape = new btBoxShape(
                    btVector3(btScalar(scale.getX() / 2.0),
                              btScalar(scale.getY() / 2.0),
                              btScalar(scale.getZ() / 2.0)));
                
                // if box is dynamic set inertia
                btVector3 inertia(0,0,0);
                if(is_dynamic())
                    collision_shape->calculateLocalInertia(mass, inertia);
                
                // get interface with physics engine
                btMotionState* motion_state = get_motion_state();

                btRigidBody::btRigidBodyConstructionInfo 
                    info(mass, motion_state, collision_shape, inertia);
                rigid_body = new btRigidBody(info);           
            }
            
            // *** thing interface,
            // TODO geometry::Aabb3 get_aabb();
            void get_parent_frame(geometry::Transformation3* t);
            void get_gl_parent_frame(btScalar* m16);
            bool is_dynamic()
            {
                if((mass - epsilon) > 0.0) return true;
                return false;         
            }
            
            // *** atomic thing interface
            // virtual materials::Material* get_material() { return material }
            util::Iterator<geometry::Vector3>* iter_vertices();
            util::Iterator<geometry::Facet>* iter_facets()
                { return new FacetIterator(*this); }
            float get_mass() { return mass; }
            
            // (untransformed) component geometry created on the fly from scale
            geometry::Vector3 get_vertex(int index);
            geometry::Facet get_facet(int index);
            
        };
    }
}
#endif // PDPD_THINGS_ATOMIC_THING
