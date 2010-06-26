#include <iostream>

#include "../Window.h"
#include "../World.h"
 
using namespace std;
using namespace pdpd;

int main(int argc, char* argv[])
{
    // make world and window
    cout << "making world and window" << "\n";
    World* world = new World();
    Window* window = new Window(world);
    
    // start event loop
    cout << "starting event loop" << "\n";
    window->event_loop();
    
    return 0;
}

