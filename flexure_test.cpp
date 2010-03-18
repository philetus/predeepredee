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
    float r = 8.0;
    float x = 0.0;
    float y = 20.0;
    float z = 0.0;
    float color[4] = {0.8, 0.0, 0.0, 0.0};
    Flexure flexure(
        Vector3(x - r, y, z - r),
        Vector3(x + r, y, z - r),
        Vector3(x - r, y, z + r),
        Vector3(x + r, y, z + r),
        color,
        1.0, // mass
        5, // x resolution
        5, // y resolution
        0); // fixed corners - 1 | 2 | 4 | 8
    world.welcome(&flexure);
    
    // create a box
    // start box in the air
    Vector3 box_a_position(-20.0, 20.0, 0.0);
    Vector3 box_b_position(20.0, 20.0, 0.0);
    Vector3 box_c_position(0.0, 5.0, 0.0);
    Rotation3 box_orientation(0.0, 0.0, 0.0);
    Transformation3 box_a_world_frame(box_orientation, box_a_position);
    Transformation3 box_b_world_frame(box_orientation, box_b_position);
    Transformation3 box_c_world_frame(box_orientation, box_c_position);

    // 10mm x 10mm x 20mm tall oblong box weighing 2 grams
    float box_color[4] = {0.2, 0.2, 0.7, 1.0};
    float shoot_box_color[4] = {0.0, 0.7, 0.7, 1.0};
    Box box_a(Vector3(24.0, 2.0, 16.0), box_a_world_frame, box_color, 0.5);
    Box box_b(Vector3(24.0, 2.0, 16.0), box_b_world_frame, box_color, 0.5);
    Box box_c(Vector3(30.0, 10.0, 30.0), box_c_world_frame, shoot_box_color, 0.5);

    world.welcome(&box_a);
    world.welcome(&box_b);
    world.welcome(&box_c);

    flexure.get_soft_body()->appendAnchor(0, box_a.get_rigid_body());
	flexure.get_soft_body()->appendAnchor(4, box_a.get_rigid_body());

    flexure.get_soft_body()->appendAnchor(8, box_b.get_rigid_body());
	flexure.get_soft_body()->appendAnchor(12, box_b.get_rigid_body());

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

