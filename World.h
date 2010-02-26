/*  World.h
 *
 *  interface for adding and removing things from simulator
 *  - manages spatial indexing and collision detection
 *  - initializes physics
 *  - can be rendered with a Window
 *  
 *  copyright 2010 michael philetus weller <philetus@gmail.com>
 *  
 *  you may redistribute or modify this code under the terms of the 
 *  GNU General Public Licence version 3.
 *  for more information see: http://www.gnu.org/licenses/gpl.html
 *  
 */
 
#ifndef PDPD_WORLD
#define PDPD_WORLD


#include <deque>
#include "btBulletDynamicsCommon.h"

#include "Thing.h"
#include "Iterator.h"
#include "DequeIterator.h"

namespace pdpd
{
    class World
    {
        // private data
        std::deque<Thing>* things; // list of things in the world
	    btDynamicsWorld* dynamics_world; // this is the most important class
	    btClock step_timer; // track time between rendering passes
	    btTypedConstraint* pick_constraint; // constraint for mouse picking
        btBroadphaseInterface* broadphase_interface;
        btCollisionDispatcher* collision_dispatcher;
        btConstraintSolver* constraint_solver;
        btDefaultCollisionConfiguration* collision_configuration;
        btVector3 gravity;
        things::Box* ground;
        
        // private methods
        void insert(Thing* thing);
        void init_constraints(Thing* thing);
        
    public:
        World();
        ~World() { delete things; }
        
        virtual void welcome(Thing* thing);
        virtual void dismiss(Thing* thing);
        
        // iterator over things
        virtual Iterator<Thing> iter_things()
            { return DequeIterator(things) }
        
        // manage physics
        virtual bool init_physics();
        virtual bool exit_physics();
        
        // set up object to serve as ground plane
        virtual bool init_ground();
        
        // get time since last physics update
        btScalar get_delta_in_seconds()
        {
            btScalar us_delta = step_timer.getTimeMicroseconds();
            step_timer.reset(); // getTime returns time since last reset
            return us_delta / btScalar(1000000.0);
        }
        
        // update physics simulation
        void step_physics();
    };
}
 #endif // PDPD_WORLD
