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
    
    // create a flexure
    float ur = 1.0;
    float vr = 4.0;
    float x0 = -21.0;
    float x1 = -7.0;
    float x2 = 7.0;
    float x3 = 21.0;
    float y = 20.0;
    float z = 0.0;
    float color[4] = {0.8, 0.0, 0.0, 0.0};
    float mass = 0.5; // mass
    int u_res = 3; // u resolution
    int v_res = 9; // v resolution
    int fxd_c = 0; // fixed corners - 1 | 2 | 4 | 8 
    Flexure flexure0(
        Vector3(x0 - ur, y, z - vr),
        Vector3(x0 + ur, y, z - vr),
        Vector3(x0 - ur, y, z + vr),
        Vector3(x0 + ur, y, z + vr),
        color, mass, u_res, v_res, fxd_c); 
    Flexure flexure1(
        Vector3(x1 - ur, y, z - vr),
        Vector3(x1 + ur, y, z - vr),
        Vector3(x1 - ur, y, z + vr),
        Vector3(x1 + ur, y, z + vr),
        color, mass, u_res, v_res, fxd_c);
    Flexure flexure2(
        Vector3(x2 - ur, y, z - vr),
        Vector3(x2 + ur, y, z - vr),
        Vector3(x2 - ur, y, z + vr),
        Vector3(x2 + ur, y, z + vr),
        color, mass, u_res, v_res, fxd_c);
    Flexure flexure3(
        Vector3(x3 - ur, y, z - vr),
        Vector3(x3 + ur, y, z - vr),
        Vector3(x3 - ur, y, z + vr),
        Vector3(x3 + ur, y, z + vr),
        color, mass, u_res, v_res, fxd_c);
        
    world.welcome(&flexure0);
    world.welcome(&flexure1);
    world.welcome(&flexure2);
    world.welcome(&flexure3);
        
    // create a box
    // start box in the air
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
        
    btSoftBody* body0 = flexure0.get_soft_body();
    btSoftBody* body1 = flexure1.get_soft_body();
    btSoftBody* body2 = flexure2.get_soft_body();
    btSoftBody* body3 = flexure3.get_soft_body();

    cout << "flexure body 0 has " << body0->m_nodes.size() << " nodes" << endl;

    body0->appendAnchor(24, body_a);
    body0->appendAnchor(0, body_a);
	body0->appendAnchor(2, body_b);
	body0->appendAnchor(26, body_b);

    body1->appendAnchor(24, body_b);
    body1->appendAnchor(0, body_b);
	body1->appendAnchor(2, body_c);
	body1->appendAnchor(26, body_c);

    body2->appendAnchor(24, body_c);
    body2->appendAnchor(0, body_c);
	body2->appendAnchor(2, body_d);
	body2->appendAnchor(26, body_d);

    body3->appendAnchor(24, body_d);
    body3->appendAnchor(0, body_d);
	body3->appendAnchor(2, body_e);
	body3->appendAnchor(26, body_e);
	
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

