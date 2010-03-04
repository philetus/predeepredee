#include <iostream>

#include "Window.h"
#include "World.h"
#include "TargetCamera.h"
#include "things/Box.h"
 
using namespace std;
using namespace pdpd;
using namespace things;

int main(int argc, char* argv[])
{
    // set up world
    cout << "making world" << "\n";
    World* world = new World();
    cout << "initializing physics" << "\n";    
    world->init_physics();
    
    // 10mm x 10mm x 20mm tall oblong box weighing 2 grams
    Box* box = new Box(Scale3(10.0, 20.0, 10.0), 2.0);
    
    // start box in the air
    Translation3 box_position(0.0, 50.0, 0.0);
    Rotation3 box_orientation(5.0, 0.0, 5.0);
    Transformation3 box_transformation(box_position, box_orientation);
    world->welcome(box, box_transformation);
    
    // create window onto world and start event loop
    cout << "making window" << "\n";
    TargetCamera* camera = new TargetCamera(600, 400);
    Window* window = new Window(*world, *camera);
    cout << "starting event loop" << "\n";
    window->event_loop();
    return 0;
}

