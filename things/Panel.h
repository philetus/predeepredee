/*  Panel.h
 *
 *  a convex 2d polygon extruded to create a panel
 *
 *  - defined by a list of 2d points, a thickness and a world frame
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

#include "RigidThing.h"
#include "../util/Iterator.h"
#include "../geometry/Vector3.h"
#include "../geometry/Transformation3.h"
#include "../geometry/Facet.h"

namespace pdpd
{
    namespace things
    {
        class Panel : public RigidThing
        {
        protected:
            btConvexHullShape* convex_hull; // same as collision shape
            
        public:
            
            // scale, mass, child
            Panel(
                Iterator<Vector3*> vrtcs,
                const geometry::Transformation3& wrld_frm,
                float* clr,
                float mss = 0.0)
            :
            RigidThing(wrld_frm, clr, mss),
            {                
                // set collision shape from scale (half size)
                collision_shape = new btConvexHullShape
                
                // if box is dynamic set inertia
                btVector3 inertia(0,0,0);
                if(is_dynamic())
                    collision_shape->calculateLocalInertia(mass, inertia);
                
                // get interface with physics engine
                btMotionState* motion_state = get_motion_state();
                
                // get rigid body
                btRigidBody::btRigidBodyConstructionInfo 
                    info(mass, motion_state, collision_shape, inertia);
                rigid_body = new btRigidBody(info);           
                
                // add pointer back to parent thing to rigid body
                rigid_body->setUserPointer(static_cast<void*>(this));
            }
            
            // *** thing interface,
            // TODO geometry::Aabb3 get_aabb();
            void get_parent_frame(geometry::Transformation3* t);
            void get_gl_parent_frame(btScalar* m16);
            
            // *** atomic thing interface
            // virtual materials::Material* get_material() { return material }
            util::Iterator<geometry::Vector3>* iter_vertices();
            util::Iterator<geometry::Facet>* iter_facets()
                { return new FacetIterator(*this); }
            
            // (untransformed) component geometry created on the fly from scale
            geometry::Vector3 get_vertex(int index);
            geometry::Facet get_facet(int index);
            
        };
    }
}
#endif // PDPD_THINGS_BOX
