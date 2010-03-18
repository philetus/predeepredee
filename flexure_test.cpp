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
    float r = 4.0;
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
        1.0);
    world.welcome(&flexure);   
    
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

