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
using namespace geometry;
using namespace things;
using namespace renderer;

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
    SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE, 8 ); // shadows need stencil buff
    
    window_surface = get_sdl_surface(width, height);
}

SDL_Surface* Window::get_sdl_surface(int width, int height)
{
    SDL_Surface* surface;

	// get sdl window surface to draw to
	int flags = SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE;
    if(!(surface = SDL_SetVideoMode(width, height, 0, flags)))
    {
        cout << "fail! : can't open sdl window : " << SDL_GetError() << "\n";
        return NULL;
    }
    return surface;
}

void Window::handle_resize(int width, int height)
{
    // get sdl surface in new size
    window_surface = get_sdl_surface(width, height);
    
    // update camera parameters
    camera->resize(width, height);
}

void Window::handle_key_down(SDL_keysym* keysym)
{
    switch( keysym->sym ) 
    {
    case SDLK_ESCAPE:
        handle_quit();
        break;
    case SDLK_SPACE:
        drop_box();
        break;
    case SDLK_x:
        shoot_box();
        break;
    default:
        break;
    }

}

void Window::drop_box()
{
    // start box in the air
    Vector3 box_position(0.0, 100.0, 0.0);
    Rotation3 box_orientation(30.0, 0.0, 30.0);
    Transformation3 box_world_frame(box_orientation, box_position);

    // 10mm x 10mm x 20mm tall oblong box weighing 2 grams
    Box* box = new Box(Vector3(10.0, 20.0, 10.0), box_world_frame, 0.02);
    
    world->welcome(box);
}

void Window::shoot_box()
{
		Transformation3 world_frame;
		btVector3 camera_position = camera->get_position();
		world_frame.setOrigin(camera_position);

		Box* shooter = new Box(Vector3(5.0, 5.0, 5.0), world_frame, 1.0);
		
		world->welcome(shooter);
		
	    btRigidBody* body = shooter->get_rigid_body();
		body->setLinearFactor(btVector3(1,1,1));

		btVector3 linear_velocity = -camera_position;
		linear_velocity.normalize();
		linear_velocity *= 500.0;

		body->getWorldTransform().setOrigin(camera_position);
		body->getWorldTransform().setRotation(btQuaternion(0,0,0,1));
		body->setLinearVelocity(linear_velocity);
		body->setAngularVelocity(btVector3(0,0,0));
		body->setCcdMotionThreshold(1.);
		body->setCcdSweptSphereRadius(0.2f);
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

            case SDL_MOUSEMOTION: 
                handle_pointer_motion(event.motion.x, event.motion.y);
                break;

            case SDL_MOUSEBUTTONDOWN: 
                handle_pointer_down(event.button.x, event.button.y);
                break;

            case SDL_MOUSEBUTTONUP: 
                handle_pointer_up();
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
        
        // clear window
        glClear(
            GL_COLOR_BUFFER_BIT | 
            GL_DEPTH_BUFFER_BIT | 
            GL_STENCIL_BUFFER_BIT);

        // render world
        world_renderer->render();
        
        // TODO: draw overlay
        
        // flush and swap buffers
        glFlush(); // is this necessary?
        SDL_GL_SwapBuffers();
        
        // don't race processor
        SDL_Delay(loop_pause_interval);
    }
}

