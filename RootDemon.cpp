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

RootDemon* pdpd::start_root_demon()
{
    RootDemon* demon = new RootDemon();
    
    if(SDL_Init(0) < 0)
    {
        cout << "failed to init base sdl!" << endl;
    }

    demon->root_thread = SDL_CreateThread(&root_loop, demon);
    return demon;
}

void pdpd::stop_root_demon(RootDemon* dmn)
{
    int status;
    
    dmn->_stop(); // break out of event loop by setting running flag to false
    SDL_WaitThread(dmn->root_thread, &status); // wait for thread to finish
    SDL_Quit(); // shut down sdl
}

// main event loop method called by start_root_demon
int pdpd::root_loop(void* dmn)
{
    RootDemon* demon = static_cast<RootDemon*>(dmn);
    
    cout << " . " << endl;
    SDL_Delay(1000);
    
    cout << " . initializing sdl" << endl;
    demon->init_sdl();
    cout << " . sdl initialized!" << endl;

    demon->running = true;
            
    cout << " . " << endl;
    SDL_Delay(1000);

    // enter main loop
    while(demon->is_running())
    {
        //demon->handle_things();
        demon->handle_start_windows();
        //demon->handle_events();
        //demon->step_world();
        //demon->render_windows();
        
        // don't race processor
        SDL_Delay(demon->loop_pause_interval);
    }
    
    return 0;
}

void RootDemon::handle_quit()
{
    SDL_Quit();
    exit(0);
}

void RootDemon::init_sdl()
{
    // init SDL video and threaded events
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTTHREAD) < 0) 
    //if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "fail! : can't init sdl : " << SDL_GetError() 
            << std::endl;
        running = false;
        handle_quit();
    }

    // setup opengl context for window
    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
    SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE, 8 ); // shadows need stencil buff
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
            window->handle_key_down(event.key.keysym.sym);
            break;

        case SDL_KEYUP:
            window = get_window(event.key.windowID);
            window->handle_key_up(event.key.keysym.sym);
            break;

        case SDL_MOUSEBUTTONDOWN: 
            window = get_window(event.button.windowID);
            window->handle_pointer_down(event.button.x, event.button.y);
            break;

        case SDL_MOUSEBUTTONUP: 
            window = get_window(event.button.windowID);
            window->handle_pointer_up();
            break;

        case SDL_MOUSEMOTION: 
            window = get_window(event.motion.windowID);
            window->handle_pointer_motion(event.motion.x, event.motion.y);
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
        SDL_Window* sdl_window;
        SDL_GLContext gl_context;
        
        cout << " > creating sdl window" << endl;
        
        // get sdl window
        sdl_window = SDL_CreateWindow(window->get_title().c_str(),
                                      window->get_pos_x(),
                                      window->get_pos_y(),
                                      window->get_width(),
                                      window->get_height(),
                                      SDL_WINDOW_RESIZABLE 
                                        | SDL_WINDOW_OPENGL 
                                        | SDL_WINDOW_SHOWN);
        if(sdl_window == NULL)
        {
            cout << "failed to create sdl window!" << endl;
            break;
        }
        
        cout << " > creating sdl gl context" << endl;

        // create an opengl context
        gl_context = SDL_GL_CreateContext(sdl_window);
        if(gl_context == NULL)
        {
            cout << "failed to create gl context!" << endl;
            break;
        }
        
        cout << " > setting sdl swap interval" << endl;

        SDL_GL_SetSwapInterval(1); // sync buffer swap with vertical refresh
                        
        // add window to root index
        window_index.insert(
            pair<unsigned int, Window*>(window->get_id(), window));
        
        cout << " > calling window start method" << endl;

        // call window's start method to say it is ready
        window->start(sdl_window, gl_context, &world);
        
        cout << "started window" << endl;
    }
}

void RootDemon::step_world()
{
    world.step_physics();
}

void RootDemon::render_windows()
{
    MapValueIterator<unsigned int, Window*> i(window_index);
    while(i.has_next())
    {
        Window* window = i.next();
        
        // make window's opengl context current
        SDL_GL_MakeCurrent(window->get_sdl_window(), window->get_gl_context());
        
        // clear window
        glClear(
            GL_COLOR_BUFFER_BIT | 
            GL_DEPTH_BUFFER_BIT | 
            GL_STENCIL_BUFFER_BIT);

        // call draw method
        window->draw();
        
        // flush and swap window buffers
        glFlush(); // is this necessary?
        SDL_GL_SwapWindow(window->get_sdl_window());
    }
}
 
