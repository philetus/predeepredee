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
    cout << "* making root demon" << endl;
    RootDemon* rut = start_root_demon();
    cout << "* root demon started" << endl;    

    SDL_Delay(500);
        
    // create window onto world and start event loop
    cout << "* making window" << "\n";
    TargetCamera camera;
    ThingDrawer drawer;
    WorldWindow window(&camera, &drawer);
    
    SDL_Delay(500);

    cout << "* starting window" << endl;
    rut->start_window(&window);
    
    //while(rut->is_running()) { SDL_Delay(1000); }
    
    SDL_Delay(10000);
    //int status;
    //SDL_WaitThread(rut->root_thread, &status);
    
    cout << "* done waiting for root demon thread" << endl;
    
    SDL_Quit();
    
    return 0;
}

