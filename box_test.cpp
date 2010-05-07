#include <iostream>

#include "Gooey.h"
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
    cout << "* making gooey" << endl;
    Gooey gooey;
    cout << "* gooey made" << endl;    

        
    // create window onto world and start event loop
    cout << "* making window" << "\n";
    TargetCamera camera;
    ThingDrawer drawer;
    WorldWindow window(&gooey, &camera, &drawer);
    
    cout << "* starting gooey loop" << endl;
    gooey.loop();
    
    cout << "* gooey loop done!" << endl;
    
    return 0;
}

