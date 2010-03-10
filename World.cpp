/*  World.cpp
 *  
 *  interface for adding and removing things from simulator
 *
 *  copyright 2010 michael philetus weller <philetus@gmail.com>
 *  
 *  you may redistribute or modify this code under the terms of the 
 *  GNU General Public Licence version 3.
 *  for more information see: http://www.gnu.org/licenses/gpl.html
 *  
 */
 
#include <iostream>

#include "World.h"

using namespace std;
using namespace pdpd;
using namespace things;
using namespace util;
using namespace geometry;

World::World()
:
next_address(1), // start thing addresses at 1
gravity(0.0, -1000.0, 0.0) // 10m/s**2 in the -y???
{
    // TODO ???
}

bool World::init_physics()
{
	// use the default collision dispatcher for default setup 
	// for memory, collision handling
	collision_configuration = new btDefaultCollisionConfiguration();
    collision_dispatcher = new btCollisionDispatcher(collision_configuration);
    
    // use aabb tree to identify potential collision pairs
    broadphase_interface = new btDbvtBroadphase();
    
    // keep it simple, use sequential (not parallel) constraint solver
    btSequentialImpulseConstraintSolver* sequential_solver = 
        new btSequentialImpulseConstraintSolver();
    constraint_solver = sequential_solver;
    
    // init physics with above config
    dynamics_world = 
        new btDiscreteDynamicsWorld(
            collision_dispatcher, broadphase_interface, 
            constraint_solver, collision_configuration);
    
    // I fought the law and the law won
    dynamics_world->setGravity(World::gravity);
    
    // make something for gravity to work with
    if (!init_ground()) return false;
    
    return true;
}

bool World::init_ground()
{
    // put top of box on zx plane
    Rotation3 rotation(0.0, 0.0, 0.0);
    Vector3 position(0.0, -10.0, 0.0);
    Transformation3 world_frame(rotation, position);

    // create box for ground plane
    ground = new Box(Vector3(100.0, 10.0, 100.0), world_frame, 0.0);
    
    // introduce it to world
    welcome(ground);
    
    return true;
}

// welcome a new thing into the world at given position and orientation
void World::welcome(Thing* thing)
{       
    // only add root-level things to things list
    roots.push_back(thing);
    thing->set_root(true);
    
    // if atomic just insert thing
    if(thing->is_atomic()) 
        // downcast to atomic thing before insert
        insert(static_cast<AtomicThing*>(thing));

    // if thing is not atomic insert children too and then add constraints
    else 
    {
        // downcast to composite thing
        CompositeThing* daddy = static_cast<CompositeThing*>(thing);
        
        // recursively inserts children
        insert(daddy);
                
        // init constraints between parts
        Iterator<Thing*>* iterator = daddy->iter_children();
        while(iterator->has_next()) 
            init_constraints(iterator->next());
        delete iterator;
    }
}

/*  insert a new thing into the world
 *  - set up graphics object
 *  - set up physics
 */ 
void World::insert(AtomicThing* thing)
{
    // add rigid body to physics world
    btRigidBody* body = thing->get_rigid_body();
    dynamics_world->addRigidBody(body);
    
    // add thing to selection index and store address
    thing->set_address(index(thing));
}

void World::insert(CompositeThing* thing)
{
    // add thing to selection index and store address
    thing->set_address(index(thing));

    // insert children
    Iterator<Thing*>* iterator = thing->iter_children(); 
    while(iterator->has_next())
    {
        Thing* child = iterator->next();
                
        // downcast and insert with appropriate method
        if(child->is_atomic())
            insert(static_cast<AtomicThing*>(child));
        else
            insert(static_cast<CompositeThing*>(child));
    }
    delete iterator;
}

void World::step_physics()
{
    float delta = get_delta_in_seconds();
    if(dynamics_world) dynamics_world->stepSimulation(delta);
}

void World::init_constraints(Thing*) {} // TODO
void World::dismiss(Thing*) {} // TODO
bool World::exit_physics() { return true; } // TODO

