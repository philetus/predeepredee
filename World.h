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
#include "things/RigidThing.h"
#include "things/SoftThing.h"
#include "things/Box.h"
#include "util/Iterator.h"
#include "util/DequeIterator.h"
#include "geometry3/Vector3.h"
#include "geometry3/Rotation3.h"
#include "geometry3/Transformation3.h"

namespace pdpd
{
    class World
    {
        // private data
        std::deque<things::Thing*> roots; // list of root things in the world
        std::map<unsigned int, things::Thing*> thing_index; // things by address
        unsigned int next_address;
        unsigned int max_address;
        int max_proxies;
        int max_overlap;
        float world_radius;
        geometry3::Vector3 gravity;

	    btSoftRigidDynamicsWorld* dynamics_world; // the most important class
	    btClock step_timer; // track time between rendering passes
	    btTypedConstraint* pick_constraint; // constraint for mouse picking
        btBroadphaseInterface* broadphase_interface;
        btCollisionDispatcher* collision_dispatcher;
        btConstraintSolver* constraint_solver;
        btDefaultCollisionConfiguration* collision_configuration;
        things::Box* ground;
	    btSoftBodyWorldInfo	soft_world_info;
        // TODO do we need these?
        //btAlignedObjectArray<btSoftSoftCollisionAlgorithm*> 
        //    soft_soft_collision_algorithms;
        //btAlignedObjectArray<btSoftRididCollisionAlgorithm*> 
        //    soft_rigid_collision_algorithms;
        
        // things must be downcast before insertion
        void insert(things::RigidThing* thing);
        void insert(things::SoftThing* thing);
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
        World()
        :
        next_address(1), // start thing addresses at 1
        max_address(0xffff),
        max_proxies(32766),
        max_overlap(65535),
        world_radius(1000.0),
        gravity(0.0, -100.0, 0.0) // 10m/s**2 in the -y???
        {}
        
        ~World() {}
        
        void welcome(things::Thing* thing);
        void dismiss(things::Thing* thing);
        
        bool is_go()
        {
            if(dynamics_world != NULL) return true;
            return false;
        }
        
        // iterator over root things
        util::Iterator<things::Thing*>* iter_roots()
            { return new util::DequeIterator<things::Thing*>(roots); }
        
        // manage physics
        bool init_physics();
        bool exit_physics();
        
        // set up object to serve as ground plane
        bool init_ground();
        
        // get time since last physics update
        btScalar get_delta_in_seconds()
        {
            btScalar us_delta = step_timer.getTimeMicroseconds();
            step_timer.reset(); // getTime returns time since last reset
            return us_delta / btScalar(1000000.0);
        }
        
        // update physics simulation
        void step_physics();
        
        void ray_pick(
            const geometry3::Vector3& ry_frm, 
            const geometry3::Vector3& ry_t,
            btCollisionWorld::ClosestRayResultCallback& ry_cllbck)
        {
            if(dynamics_world)
                dynamics_world->rayTest(ry_frm, ry_t, ry_cllbck);
        }
        
        void add_constraint(
            btTypedConstraint* cnstrnt, 
            bool dsbl_lnkd_cllsns = false) // disable linked body collisions
            { dynamics_world->addConstraint(cnstrnt, dsbl_lnkd_cllsns); }
        
        void remove_constraint(btTypedConstraint* cnstrnt)
            { dynamics_world->removeConstraint(cnstrnt); }
    };
}
 #endif // PDPD_WORLD
