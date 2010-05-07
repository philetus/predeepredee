/*  Gooey.cpp
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

#include <iostream>

#include "Gooey.h"
#include "util/MapValueIterator.h"
 
using namespace std;
using namespace pdpd;
using namespace things;
using namespace util;

// main event loop method
void Gooey::loop()
{
    looping = true;
    
    // enter main loop
    while(looping)
    {
        handle_events();
        world.step_physics();
        render_windows();
        
        // don't race processor
        SDL_Delay(loop_pause_interval);
    }
}

void Gooey::init_sdl()
{
    // init SDL video and threaded events
    if(SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        cout << "fail! : can't init sdl : " << SDL_GetError() << endl;
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

// poll events and distribute them to appropriate windows
void Gooey::handle_events()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        Window* window;
        switch(event.type)
        {
        case SDL_KEYDOWN:
            // quit when escape key is pressed!
            if(event.key.keysym.sym == SDLK_ESCAPE) handle_quit();
            
            if((window = get_window(event.key.windowID)) == NULL) break;
            window->handle_key_down(event.key.keysym.sym);
            break;

        case SDL_KEYUP:
            if((window = get_window(event.key.windowID)) == NULL) break;
            window->handle_key_up(event.key.keysym.sym);
            break;

        case SDL_MOUSEBUTTONDOWN: 
            if((window = get_window(event.button.windowID)) == NULL) break;
            window->handle_pointer_down(event.button.x, event.button.y);
            break;

        case SDL_MOUSEBUTTONUP: 
            if((window = get_window(event.button.windowID)) == NULL) break;
            window->handle_pointer_up();
            break;

        case SDL_MOUSEMOTION: 
            if((window = get_window(event.motion.windowID)) == NULL) break;
            window->handle_pointer_motion(event.motion.x, event.motion.y);
            break;

        case SDL_WINDOWEVENT:            
            if((window = get_window(event.window.windowID)) == NULL) break;
            set_gl_focus(window); // set gl focus to allow gl viewport resize
            if(event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                window->handle_resize(event.window.data1, event.window.data2);
            }
            else if(event.window.event == SDL_WINDOWEVENT_MOVED)
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

void Gooey::welcome(Window* wndw)
{
    // bless window
    wndw->bless(&world);
    
    // add window to root index
    window_index.insert(pair<unsigned int, Window*>(wndw->get_id(), wndw));
}

void Gooey::dismiss(Window*)
{
    // TODO
}


void Gooey::render_windows()
{
    MapValueIterator<unsigned int, Window*> i(window_index);
    while(i.has_next())
    {
        Window* window = i.next();
        
        // make window's opengl context current
        set_gl_focus(window);
        
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
 
void pdpd::kill_gooey()
{
    SDL_Quit();
    exit(0);
}

