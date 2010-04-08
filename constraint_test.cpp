#include <iostream>

#include "Window.h"
#include "World.h"
#include "renderer/TargetCamera.h"
#include "renderer/ThingDrawer.h"
#include "renderer/WorldRenderer.h"
#include "things/Box.h"
#include "things/Flexure.h"
#include "geometry/Vector3.h"
#include "geometry/Rotation3.h"
#include "geometry/Transformation3.h"

using namespace std;
using namespace pdpd;
using namespace things;
using namespace geometry;
using namespace renderer;

int main(int, char**)
{
    // set up world
    cout << "making world" << "\n";
    World world;
    cout << "initializing physics" << "\n";    
    world.init_physics();
                    
    // create some boxes - start box in the air
    Vector3 box_a_position(-28.0, 20.0, 0.0);
    Vector3 box_b_position(-14.0, 20.0, 0.0);
    Vector3 box_c_position(0.0, 20.0, 0.0);
    Vector3 box_d_position(14.0, 20.0, 0.0);
    Vector3 box_e_position(28.0, 20.0, 0.0);
    
    Vector3 box_x_position(0.0, 5.0, 0.0);
    Rotation3 box_orientation(0.0, 0.0, 0.0);
    Transformation3 box_a_world_frame(box_orientation, box_a_position);
    Transformation3 box_b_world_frame(box_orientation, box_b_position);
    Transformation3 box_c_world_frame(box_orientation, box_c_position);
    Transformation3 box_d_world_frame(box_orientation, box_d_position);
    Transformation3 box_e_world_frame(box_orientation, box_e_position);
    
    Transformation3 box_x_world_frame(box_orientation, box_x_position);

    // 10mm x 10mm x 20mm tall oblong box weighing 2 (kilo?)grams
    float box_color[4] = {0.2, 0.2, 0.7, 1.0};
    float shoot_box_color[4] = {0.0, 0.7, 0.7, 1.0};
    Box box_a(Vector3(12.0, 1.0, 8.0), box_a_world_frame, box_color, 0.1);
    Box box_b(Vector3(12.0, 1.0, 8.0), box_b_world_frame, box_color, 0.1);
    Box box_c(Vector3(12.0, 1.0, 8.0), box_c_world_frame, box_color, 0.1);
    Box box_d(Vector3(12.0, 1.0, 8.0), box_d_world_frame, box_color, 0.1);
    Box box_e(Vector3(12.0, 1.0, 8.0), box_e_world_frame, box_color, 0.1);
    
    Box box_x(Vector3(30.0, 10.0, 30.0), box_x_world_frame, shoot_box_color, 0.5);

    world.welcome(&box_a);
    world.welcome(&box_b);
    world.welcome(&box_c);
    world.welcome(&box_d);
    world.welcome(&box_e);
    
    world.welcome(&box_x);

    btRigidBody* body_a = box_a.get_rigid_body();
    btRigidBody* body_b = box_b.get_rigid_body();
    btRigidBody* body_c = box_c.get_rigid_body();
    btRigidBody* body_d = box_d.get_rigid_body();
    btRigidBody* body_e = box_e.get_rigid_body();
        
	btTransform flex_frame_down = btTransform::getIdentity();
	flex_frame_down.setOrigin(btVector3(7.0, 0.0, 0.0));
	btTransform flex_frame_up = btTransform::getIdentity();
	flex_frame_up.setOrigin(btVector3(-7.0, 0.0, 0.0));

	btGeneric6DofConstraint* flex0 = 
	    new btGeneric6DofConstraint(
	        *body_a, *body_b, flex_frame_down, flex_frame_up, true);

	btGeneric6DofConstraint* flex1 = 
	    new btGeneric6DofConstraint(
	        *body_b, *body_c, flex_frame_down, flex_frame_up, true);

	btGeneric6DofConstraint* flex2 = 
	    new btGeneric6DofConstraint(
	        *body_c, *body_d, flex_frame_down, flex_frame_up, true);

	btGeneric6DofConstraint* flex3 = 
	    new btGeneric6DofConstraint(
	        *body_d, *body_e, flex_frame_down, flex_frame_up, true);
	
    world.add_constraint(flex0, false);
    world.add_constraint(flex1, false);
    world.add_constraint(flex2, false);
    world.add_constraint(flex3, false);
	
	btTransform clamp_frame_a = btTransform::getIdentity();
	clamp_frame_a.setOrigin(btVector3(0.0, 0.0, 0.0));
	btTransform clamp_frame_b = btTransform::getIdentity();
	clamp_frame_b.setOrigin(btVector3(0.0, 1.0, 0.0));
	
	btGeneric6DofConstraint* clamp = 
	    new btGeneric6DofConstraint(
	        *body_a, *body_e, clamp_frame_a, clamp_frame_b, true);
	
	clamp->setAngularLowerLimit(btVector3(0, 0, 0));
	clamp->setAngularUpperLimit(btVector3(0, 0, 0));

    world.add_constraint(clamp, true);
    
    // create window onto world and start event loop
    cout << "making window" << "\n";
    TargetCamera camera;
    ThingDrawer drawer;
    WorldRenderer renderer(&world, &camera, &drawer);
    Window window(&world, &camera, &renderer);
    cout << "starting event loop" << "\n";
    window.event_loop();
    return 0;
}

