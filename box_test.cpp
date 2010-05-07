#include <iostream>

#include "RootDemon.h"
#include "WorldWindow.h"
#include "World.h"
#include "renderer/TargetCamera.h"
#include "renderer/ThingDrawer.h"
#include "renderer/WorldRenderer.h"
#include "things/Box.h"
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
    cout << "making root demon" << endl;
    RootDemon* rut = start_root_demon();
    cout << "root demon started" << endl;    
    
    /*
    // 10mm x 10mm x 20mm tall oblong box weighing 2 grams
    Box box(Vector3(10.0, 20.0, 10.0), 2.0);
    
    // start box in the air
    Vector3 box_position(0.0, 50.0, 0.0);
    Rotation3 box_orientation(5.0, 0.0, 5.0);
    Transformation3 box_world_frame(box_orientation, box_position);
    world.welcome(&box, box_world_frame);
     */
    
    // create window onto world and start event loop
    cout << "making window" << "\n";
    TargetCamera camera;
    ThingDrawer drawer;
    WorldWindow window(&camera, &drawer);
    
    cout << "starting window" << "\n";
    rut->start_window(&window);
    
    return 0;
}

