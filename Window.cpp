/*  Window.cpp
 *
 *  gui window with 3d rendering of simulation world and 2d menu overlay
 *  
 *  copyright 2010 michael philetus weller <philetus@gmail.com>
 *  
 *  you may redistribute or modify this code under the terms of the 
 *  GNU General Public Licence version 3.
 *  for more information see: http://www.gnu.org/licenses/gpl.html
 *  
 */

#include <iostream>

#include "Window.h"
 
using namespace std;
using namespace pdpd;

/*
 *  constructor
 */
Window::Window(
    World* w, 
    Camera* c, 
    ThingDrawer* td,
    int width, 
    int height, 
    string title) 
:
world(w),
camera(c),
thing_drawer(td)
{
    init_sdl(width, height, title);
    init_gl(width, height);
}

/*
 *  destructor
 */
Window::~Window()
{
    /*
    delete title;
    delete window_surface;
    delete cairo_surface;
    delete surface_data;
    delete texture_id;
    delete cairo_context;
    */
}

void Window::init_gl(int width, int height)
{
	cout << "OpenGL version: " <<  glGetString(GL_VERSION) << "\n";
    cout << "OpenGL vendor: " << glGetString(GL_VENDOR) << "\n";
    cout << "OpenGL renderer: " << glGetString(GL_RENDERER) << "\n";

    glClearColor (0.0f, 0.0f, 0.0f, 0.0f);

    /* cairo surface setup stuff
    glDisable (GL_DEPTH_TEST);
    glEnable (GL_TEXTURE_RECTANGLE_ARB);
        */

    camera->enable_lights();
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /* Our shading model--Gouraud (smooth). */
    glShadeModel( GL_SMOOTH );

    /* Culling. */
    glCullFace( GL_BACK );
    glFrontFace( GL_CCW );
    glEnable( GL_CULL_FACE );

    // call camera resize handler to finish init
    camera->resize(width, height);
}

void Window::init_sdl(int width, int height, string title)
{
    // init SDL video
    if(SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        cout << "fail! : can't init video : " << SDL_GetError() << "\n";
        handle_quit();
    }

	// set window title
	SDL_WM_SetCaption(title.c_str(), NULL);

    // setup opengl context for window
    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	// get sdl window surface to draw to
	int flags = SDL_OPENGL | SDL_RESIZABLE;
    if(!(window_surface = SDL_SetVideoMode(width, height, 0, flags)))
    {
        cout << "fail! : can't open sdl window : " << SDL_GetError() << "\n";
        handle_quit();
    }
}

void Window::handle_key_down(SDL_keysym* keysym)
{
    switch( keysym->sym ) 
    {
    case SDLK_ESCAPE:
        handle_quit();
        break;
    default:
        break;
    }

}
// void Window::handle_key_up(SDL_keysym* keysym) {} // TODO
// void Window::handle_expose() {} // TODO: write expose handler


void Window::event_loop()
{
    /* Our SDL event placeholder. */
    SDL_Event event;
    
    while(true) // main event loop
    {
        // process all events in queue
        while(SDL_PollEvent(&event)) {
            switch(event.type)
            {
            case SDL_KEYDOWN:
                handle_key_down(&event.key.keysym);
                break;

            case SDL_VIDEORESIZE: 
                handle_resize(event.resize.w, event.resize.h);
                break;
            
            /*
            case SDL_VIDEOEXPOSE: // redraw screen after expose event
                handle_expose();
                break;
             */

            case SDL_QUIT: // ctrl-c
                handle_quit();
                break;

            default:
                break;
            }
        }
        
        // step physics
        world->step_physics();
        
        // draw things
        camera->set_perspective();
        thing_drawer->visit(world->iter_roots());
        
        // TODO: draw overlay
        
        // flush and swap buffers
        glFlush(); // is this necessary?
        SDL_GL_SwapBuffers();
        
        // don't race processor
        SDL_Delay(loop_pause_interval);
    }
}

