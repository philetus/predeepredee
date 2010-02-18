#include <iostream>

#include "Window.h"
#include "World.h"
 
using namespace std;
using namespace pdpd;

int main(int argc, char* argv[])
{
    // make world and window
    cout << "making world and window";
    World* world = new World();
    Window* window = new Window(world, 400, 300);
    
    // start event loop
    cout << "starting event loop";
    window->event_loop();
    
    return 0;
}

