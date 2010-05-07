/*  Gooey.h
 *
 *  manages event loop and physics world
 *  
 *  copyright 2010 michael philetus weller <philetus@gmail.com>
 *  
 *  you may redistribute or modify this code under the terms of the 
 *  GNU General Public Licence version 3.
 *  for more information see: http://www.gnu.org/licenses/gpl.html
 *  
 */
 
#ifndef PDPD_GOOEY
#define PDPD_GOOEY

#include <map>
#include <string>
#include <SDL/SDL.h>

#include "World.h"
#include "Window.h"
#include "things/Thing.h"

namespace pdpd
{ 
    void kill_gooey();

    class Gooey
    {
        // global parameters to tune
        static const int loop_pause_interval = 50; // delay time in event loop
        
        bool looping;
        World world; // physics simulation
        std::map<unsigned int, Window*> window_index;
                
        // helper methods for main loop
        void handle_events();
        void render_windows();

        // private helper methods
        void handle_quit()
        {
            looping = false;
            kill_gooey();
        }
        void init_sdl();
                
        // get window from index by id
        Window* get_window(unsigned int wndw_id)
        {
            std::map<unsigned int, Window*>::iterator i 
                = window_index.find(wndw_id);
            if(i == window_index.end()) return NULL;
            return i->second;
        }
        
        Gooey(const Gooey& gy); // hide copy-constructor
        
    public:
    
        Gooey()
        :
        looping(false)
        {
            init_sdl();
            world.init_physics();
        }
        
        // get pointer to physics world
        World* get_world() { return &world; }
        
        // add and remove windows
        void welcome(Window* wndw);
        void dismiss(Window* wndw);
        
        // just push thing onto welcome queue
        void welcome(things::Thing* thng)
        {
            world.welcome(thng);
        }

        // just push thing onto remove queue
        void dismiss(things::Thing* thng)
        {
            world.dismiss(thng);
        }
        
        void loop(); // start event loop
        
        ~Gooey()
        {
            world.exit_physics();
        }
        
    };
}
#endif // PDPD_GOOEY
