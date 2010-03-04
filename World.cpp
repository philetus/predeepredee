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

#include "World.h"

using namespace pdpd;
using namespace things;
using namespace util;
using namespace geometry;

World::World()
:
next_address(1), // start thing addresses at 1
gravity(0.0, -10000.0, 0.0) // 10,000mm/s**2 in the -y???
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
    dynamicsWorld->setGravity(World::gravity);
    
    // make something for gravity to work with
    if (!init_ground()) return false;
    
    return true;
}

bool World::init_ground()
{
    // create box for ground plane
    ground = new Box(Scale3(100.0, 10.0, 100.0), 0.0);
    
    // put top of box on zx plane
    Vector3 ground_position(0.0, -10.0, 0.0);
    Transformation3 ground_transformation(ground_position);
    
    // introduce it to world
    welcome(ground, ground_transformation);
    
    return true;
}

// welcome a new thing into the world at given position and orientation
void World::welcome(
    Thing* thing, 
    const Transformation3* world_frame)
{   
    // only add root-level things to things list
    roots->push_back(thing);
    thing->set_root(true);
    
    // if atomic just insert thing
    if(thing->is_atomic()) atomic_insert(thing, world_frame);

    // if thing is not atomic insert children too and then add constraints
    else 
    {
        // recursively inserts children
        composite_insert(thing, world_frame);
                
        // init constraints between parts
        Iterator<Thing*>* i = thing->iter_children();
        while(i->has_next()) init_constraints(i->next());
    }
}

/*  insert a new thing into the world
 *  - set up graphics object
 *  - set up physics
 */ 
void World::atomic_insert(
    AtomicThing* thing, 
    const Transformation3& world_frame)
{
    // generate rigid body for thing
    btScalar mass(thing->get_mass());
    ThingMotionState* motion_state = new ThingMotionState(world_frame);
    btCollisionShape* collision_shape = thing->get_collision_shape();
    btVector3 inertia(0.0, 0.0, 0.0);
    btRigidBody::btRigidBodyConstructionInfo 
        info(mass, motion_state, collision_shape, inertia);
    btRigidBody* body = new btRigidBody(info);
    
    // is this necessary? motion state already provides interface
    // thing->set_rigid_body(body);
    
    // if thing is dynamic set inertia
    if(thing->is_dynamic()) body->calculateLocalInertia(mass, inertia);
    
    // add rigid body to physics world
    body->setActivationState(ISLAND_SLEEPING); // ???
    dynamics_world->addRigidBody(body);
    body->setActivationState(ISLAND_SLEEPING); // ???  
    
    // add thing to selection index and store address
    thing->set_address(index(thing));
}

void World::composite_insert(Thing* thing, const Transformation3& world_frame)
{
    // add thing to selection index and store address
    thing->set_address(index(thing));

    // insert children
    Iterator<Thing*>* i = thing->iter_children(); 
    while(i->has_next())
    {
        Thing* child = i->next();
        
        // get transformation to child
        // TODO is this correct transform mult order???
        Transformation3 child_world_frame = 
            child->get_parent_frame() * world_frame;
        
        // insert with appropriate method
        if(child->is_atomic()) atomic_insert(child, child_world_frame);
        else composite_insert(child, child_world_frame);
    }    
}

void World::step_physics()
{
    float delta = get_delta_in_seconds();
    if(dynamics_world) dynamics_world->stepSimulation(delta);
}
