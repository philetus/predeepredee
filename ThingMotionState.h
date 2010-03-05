/*  ThingMotionState.h
 *
 *  interface for physics engine to move rigid things
 *  - inherits from the bullet interface
 *  
 *  copyright 2010 michael philetus weller <philetus@gmail.com>
 *  
 *  you may redistribute or modify this code under the terms of the 
 *  GNU General Public Licence version 3.
 *  for more information see: http://www.gnu.org/licenses/gpl.html
 *  
 */
 
#ifndef PDPD_THING_MOTION_STATE
#define PDPD_THING_MOTION_STATE

#include "btBulletDynamicsCommon.h"
#include "geometry/Transformation3.h"
#include "things/AtomicThing.h"

namespace pdpd
{
    // interface between physics engine and things' orientation and position
    class ThingMotionState : public btMotionState
    {
        geometry::Transformation3 init_world_frame; // initial rot and pos
        things::AtomicThing* thing; // thing to be transformed
    public:
        ThingMotionState(
            const geometry::Transformation3 &frame, 
            things::AtomicThing* t)
        :
        init_world_frame(frame),
        thing(t)
        {}
        
        ~ThingMotionState() {}
        
        // provide physics engine with initial position for thing
        virtual void getWorldTransform(btTransform &world_transform) const
        {
            world_transform = init_world_frame;
        }
        
        virtual void setWorldTransform(const btTransform &world_transform)
        {
            if(thing == NULL) return; // silently return if thing unset
            
            geometry::Transformation3 frame(world_transform);
            thing->set_world_frame(frame);
        }
    };
}
#endif // PDPD_THING_MOTION_STATE
