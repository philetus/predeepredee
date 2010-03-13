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
#include <map>

#include "btBulletDynamicsCommon.h"
#include "BulletSoftBody/btSoftBody.h"
#include "BulletSoftBody/btSoftRigidDynamicsWorld.h"
#include "BulletSoftBody/btSoftBodyRigidBodyCollisionConfiguration.h"
#include "BulletSoftBody/btSoftBodyHelpers.h"

#include "things/Thing.h"
#include "things/AtomicThing.h"
#include "things/CompositeThing.h"
#include "things/Box.h"
#include "util/Iterator.h"
#include "util/DequeIterator.h"
#include "geometry/Vector3.h"
#include "geometry/Rotation3.h"
#include "geometry/Transformation3.h"

namespace pdpd
{
    class World
    {
        // private data
        std::deque<things::Thing*> roots; // list of root things in the world
        std::map<unsigned int, things::Thing*> thing_index; // things by address
        unsigned int next_address;
        static const unsigned int max_address = 0xffff;
        static const int max_proxies = 32766;
        static const int max_overlap = 65535;
        static const float world_radius = 1000.0;
	    btDynamicsWorld* dynamics_world; // this is the most important class
	    btClock step_timer; // track time between rendering passes
	    btTypedConstraint* pick_constraint; // constraint for mouse picking
        btBroadphaseInterface* broadphase_interface;
        btCollisionDispatcher* collision_dispatcher;
        btConstraintSolver* constraint_solver;
        btDefaultCollisionConfiguration* collision_configuration;
        geometry::Vector3 gravity;
        things::Box* ground;
	    btSoftBodyWorldInfo	softbody_world_info;
        // TODO do we need these?
        //btAlignedObjectArray<btSoftSoftCollisionAlgorithm*> 
        //    soft_soft_collision_algorithms;
        //btAlignedObjectArray<btSoftRididCollisionAlgorithm*> 
        //    soft_rigid_collision_algorithms;
        
        // things must be downcast to atomic or composite before insertion
        void insert(things::AtomicThing* thing);
        void insert(things::CompositeThing* thing);
            
        void init_constraints(things::Thing* thing);
        
        // TODO: for really tho
        unsigned int get_next_address() { return next_address++; }
        
        // adds a thing to index and returns address
        unsigned int index(things::Thing* thing)
        {
            unsigned int address = get_next_address();
            thing_index.insert(std::make_pair(address, thing));
            return address;
        }
        
    public:
        World();
        virtual ~World() {}
        
        virtual void welcome(things::Thing* thing);
        virtual void dismiss(things::Thing* thing);
        
        // iterator over root things
        virtual util::Iterator<things::Thing*>* iter_roots()
            { return new util::DequeIterator<things::Thing*>(roots); }
        
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
