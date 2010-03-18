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
	// use the softbody collision configuration and the default collision
	// dispatcher for default setup for memory and collision handling
	collision_configuration = new btSoftBodyRigidBodyCollisionConfiguration();
    collision_dispatcher = new btCollisionDispatcher(collision_configuration);
    soft_world_info.m_dispatcher = collision_dispatcher;
    
    cout << "got dispatcher" << "\n";

    // use 3 axis sweep to identify potential collision pairs
	btVector3 world_min(-world_radius, -world_radius, -world_radius);
	btVector3 world_max(world_radius, world_radius, world_radius);
    broadphase_interface = new btAxisSweep3(world_min, world_max, max_proxies);
    soft_world_info.m_broadphase = broadphase_interface;
    
    cout << "got broadphase" << "\n";

    // keep it simple, use sequential (not parallel) constraint solver
    constraint_solver = new btSequentialImpulseConstraintSolver();
    
    // init physics with above config
    dynamics_world = 
        new btSoftRigidDynamicsWorld(
            collision_dispatcher, broadphase_interface, 
            constraint_solver, collision_configuration);

    cout << "got dynamics world" << "\n";
    
    // callback to handle dragging soft bodies 
    // TODO - do we need this?
    // dynamics_world->setInternalTickCallback(pretick_callback, this, true);
    
    // TODO is this really necessary?
    dynamics_world->getDispatchInfo().m_enableSPU = true;
    
    // I fought the law and the law won
    dynamics_world->setGravity(World::gravity);
    soft_world_info.m_gravity.setValue(
        World::gravity[0], World::gravity[1], World::gravity[2]);
    
    // wtf? unexplained magic in bullet softbody demo
    soft_world_info.m_sparsesdf.Initialize();
    
    cout << "initialized sparsesdf" << "\n";

    // make something for gravity to work with
    if (!init_ground()) return false;

    cout << "initialized ground" << "\n";
    
    return true;
}

bool World::init_ground()
{
    cout << "initializing ground" << "\n";

    // put top of box on zx plane
    Rotation3 rotation(0.0, 0.0, 0.0);
    Vector3 position(0.0, -10.0, 0.0);
    Transformation3 world_frame(rotation, position);

    // create box for ground plane
    float color[4] = {0.0, 0.7, 0.0, 1.0};
    ground = new Box(Vector3(100.0, 10.0, 100.0), world_frame, color, 0.0);
    
    // introduce it to world
    welcome(ground);
    
    return true;
}

// welcome a new thing into the world at given position and orientation
void World::welcome(Thing* thing)
{       
    cout << "welcoming thing: " << *thing << endl;

    // only add root-level things to things list
    roots.push_back(thing);
    thing->set_root(true);
    
    // if atomic just insert thing
    if(thing->is_atomic()) 
    {
        // downcast and insert
        if(static_cast<AtomicThing*>(thing)->is_soft())
            insert(static_cast<SoftThing*>(thing));        
        else
            insert(static_cast<RigidThing*>(thing));
    }
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
void World::insert(RigidThing* thing)
{
    // add rigid body to physics world
    btRigidBody* body = thing->get_rigid_body();
    dynamics_world->addRigidBody(body);

    // add thing to selection index and store address
    thing->set_address(index(thing));

    cout << "inserted rigid thing: " << *thing << endl;
}

void World::insert(SoftThing* thing)
{
    // add soft body to physics world
    btSoftBody* body = thing->init_soft_body(soft_world_info);        
    dynamics_world->addSoftBody(body);
    
    // add thing to selection index and store address
    thing->set_address(index(thing));

    cout << "inserted soft thing: " << *thing << endl;
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
        {
            // downcast and insert
            if(static_cast<AtomicThing*>(child)->is_soft())
                insert(static_cast<SoftThing*>(child));        
            else
                insert(static_cast<RigidThing*>(child));
        }
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

