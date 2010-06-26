/*  RigidThing.h
 *
 *  superclass for rigid bodies
 *  
 *  copyright 2010 michael philetus weller <philetus@gmail.com>
 *  
 *  you may redistribute or modify this code under the terms of the 
 *  GNU General Public Licence version 3.
 *  for more information see: http://www.gnu.org/licenses/gpl.html
 *  
 */
 
#ifndef PDPD_THINGS_RIGID_THING
#define PDPD_THINGS_RIGID_THING

#include <iostream>

#include "AtomicThing.h"
#include "../geometry/Transformation3.h"

namespace pdpd
{
    namespace things
    {
        class RigidThing : public AtomicThing
        {
            RigidThing(); // hide
            RigidThing(const RigidThing&); // hide
        protected:
            geometry::Transformation3 world_frame;
            btCollisionShape* collision_shape;
            btRigidBody* rigid_body;
        public:
            RigidThing(
                const geometry::Transformation3& wrld_frm,
                float* clr,
                float mss = 0.0)
            :
            AtomicThing(false, clr, mss), // soft, color, mass, child
            world_frame(wrld_frm)
            {}
            
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
            
            // virtual void set_rigid_body(btRigidBody* b) { rigid_body = b; }
            virtual btRigidBody* get_rigid_body() { return rigid_body; }
                        
            /*  motion state
             *  - interface to physics engine
             *  - implements btMotionState interface
             *    > getWorldTransform - provides initial position to engine
             *    > setWorldTransform - allows physics engine to move thing
             */
            friend class MotionState;
            class MotionState : public btMotionState
            {
                RigidThing* thing; // thing to be transformed
            public:
                MotionState(RigidThing* thng)
                :
                thing(thng)
                {}
                
                // provide physics engine with initial position for thing
                virtual void getWorldTransform(
                    btTransform &wrld_trnsfrm) const
                    { wrld_trnsfrm = thing->world_frame; }
                
                virtual void setWorldTransform(
                    const btTransform &wrld_trnsfrm)
                {
                    geometry::Transformation3 frame(wrld_trnsfrm);
                    thing->set_world_frame(frame);
                }
            };
            
            btMotionState* get_motion_state() { return new MotionState(this); }
        };
    }
}
#endif // PDPD_THINGS_RIGID_THING
