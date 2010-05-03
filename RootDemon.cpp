/*  RootDemon.cpp
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

#include <iostream>

#include "RootDemon.h"
#include "util/MapValueIterator.h"
 
using namespace std;
using namespace pdpd;
using namespace things;
using namespace util;

RootDemon* start_root_demon()
{
    RootDemon* demon = new RootDemon();
    demon->root_thread = SDL_CreateThread(demon->_start, NULL);
    return demon;
}

void stop_root_demon(RootDemon* dmn)
{
    dmn->_stop(); // break out of event loop by setting running flag to false
    SDL_WaitThread(dmn->root_thread); // wait for thread to finish
    SDL_Quit(); // shut down sdl
}

// *** private methods to handle main loop

void RootDemon::handle_things()
{
    while(!dismiss_queue.is_empty()) world.dismiss(dismiss_queue.pop());    
    while(!welcome_queue.is_empty()) world.welcome(welcome_queue.pop());
}

// poll events and distribute them to appropriate windows
void RootDemon::handle_events()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        Window* window;
        switch(event.type)
        {
        case SDL_KEYDOWN:
            window = get_window(event.key.windowID);
            window->handle_key_down(&event.key.keysym);
            break;

        case SDL_KEYUP:
            window = get_window(event.key.windowID);
            window->handle_key_up(&event.key.keysym);
            break;

        case SDL_MOUSEBUTTONDOWN: 
            window = get_window(event.button.windowID);
            window.handle_pointer_down(event.button.x, event.button.y);
            break;

        case SDL_MOUSEBUTTONUP: 
            window = get_window(event.button.windowID);
            window.handle_pointer_up();
            break;

        case SDL_WINDOWEVENT:
            window = get_window(event.window.windowID);
            if(event.window.type == SDL_WINDOWEVENT_RESIZED)
            {
                window->handle_resize(event.window.data1, event.window.data2);
            }
            else if(event.window.type == SDL_WINDOWEVENT_MOVED)
            {
                window->handle_move(event.window.data1, event.window.data2);
            }
            break;
        
        case SDL_QUIT: // ctrl-c?
            handle_quit();
            break;

        default:
            break;
        }
    }
}

void RootDemon::handle_start_windows()
{
    while(!window_queue.is_empty())
    {
        Window* window = window_queue.pop();

        // get sdl window
        window._sdl_window = SDL_CreateWindow(window->get_title().c_str(),
                                              window->get_x(),
                                              window->get_y(),
                                              window->get_width(),
                                              window->get_height(),
                                              SDL_WINDOW_SHOWN);
        
        // add window to root index
        window_index.insert(
            pair<unsigned int, Window*>(window->get_id(), window));
        window._running = true;
    }
}

void RootDemon::step_world()
{
    world->step_physics();
}

void RootDemon::render_windows()
{
    MapValueIterator i(window_index);
    while(i.has_next())
    {
        Window* window = i.next();
        
    }
}
 
