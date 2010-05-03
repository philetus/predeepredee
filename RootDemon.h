/*  RootDemon.h
 *
 *  manages world simulation and window events
 *  
 *  copyright 2010 michael philetus weller <philetus@gmail.com>
 *  
 *  you may redistribute or modify this code under the terms of the 
 *  GNU General Public Licence version 3.
 *  for more information see: http://www.gnu.org/licenses/gpl.html
 *  
 */
 
#ifndef PDPD_ROOT_DEMON
#define PDPD_ROOT_DEMON

#include <map>
#include <string>
#include <SDL/SDL.h>

#include "World.h"
#include "Window.h"
#include "util/GuardedQueue.h"
#include "things/Thing.h"

namespace pdpd
{
    class RootDemon
    {
        // global parameters to tune
        static const int loop_pause_interval = 50; // delay time in event loop
                        
        World world; // physics simulation
        std::map<unsigned int, Window*> window_index;
        util::GuardedQueue<Window*> window_queue;
        util::GuardedQueue<things::Thing*> dismiss_queue;
        util::GuardedQueue<things::Thing*> welcome_queue;
        mutable bool running;
        
        // private helper functions to run in main loop
        void handle_things();
        void handle_events();
        void handle_start_windows();
        void step_world();
        void render_windows();
                
        // get window from index by id
        Window* get_window(unsigned int wndw_id)
        {
            std::map<unsigned int, Window*>::iterator i 
                = window_index.find(wndw_id);
            if(i == window_index.end()) return NULL;
            return i->second;
        }
        
        RootDemon(const RootDemon& dmn); // hide copy-constructor
        
    public:
        SDL_Thread* root_thread; // holds thread demon is running in
        
        RootDemon()
        :
        running(true)
        {
            // init SDL video and threaded events
            if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTTHREAD) < 0) 
            {
                std::cout << "fail! : can't init sdl : " << SDL_GetError() 
                    << std::endl;
                running = false;
                SDL_Quit();
            }
        }
        
        // just push window onto window queue
        void start_window(Window* wndw)
        {
            window_queue.push(wndw);
        }
        
        // just push thing onto welcome queue
        void welcome(things::Thing* thng)
        {
            welcome_queue.push(thng);
        }

        // just push thing onto remove queue
        void dismiss(things::Thing* thng)
        {
            dismiss_queue.push(thng);
        }

        // main event loop method called by start_root_demon
        void _start(void*)
        {
            // start physics
            world.init_physics();
            
            // enter main loop
            while(running)
            {
                handle_things();
                handle_start_windows();
                handle_events();
                step_world();
                render_windows();
                
                // don't race processor
                SDL_Delay(loop_pause_interval);
            }
        }
        
        void _stop() // called from outside root thread by stop_root_demon
        {
            running = false;
            world.exit_physics();
        }
    };
    
    // only make one root demon, use this factory function
    RootDemon* start_root_demon();
    void stop_root_demon(RootDemon* dmn);
}
#endif // PDPD_ROOT_DEMON
