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
    switch(keysym->sym) 
    {
    case SDLK_ESCAPE:
        handle_quit();
        break;
    case SDLK_SPACE: // pick mode
        pointer_mode = pick_mode;
        break;
    case SDLK_x: // shoot mode
        pointer_mode = shoot_mode;
        break;
    case SDLK_b:
        drop_box();
        break;
    case SDLK_f:
        drop_flexure();
        break;
    default:
        break;
    }
}

void Window::handle_key_up(SDL_keysym* keysym)
{
    switch(keysym->sym) 
    {
    default:
        pointer_mode = tilt_mode;
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
    float color[4] = {0.0, 0.7, 0.7, 1.0};
    Box* box = new Box(Vector3(10.0, 20.0, 10.0), box_world_frame, color, 0.02);
    
    world->welcome(box);
}

void Window::shoot_box(int x, int y)
{
        // shoot box in direction of pointer
        Vector3 linear_velocity = camera->get_ray_to(x, y);
        linear_velocity -= camera->get_position();
		linear_velocity.normalize();
		linear_velocity *= shoot_box_velocity;
        
		Transformation3 world_frame;
		btVector3 camera_position = camera->get_position();
		world_frame.setOrigin(camera_position);
        float color[4] = {0.9, 0.9, 0.0, 1.0};
		Box* shooter = new Box(Vector3(5.0, 5.0, 5.0), world_frame, color, 1.0);
		
		world->welcome(shooter);
		
	    btRigidBody* body = shooter->get_rigid_body();
		body->setLinearFactor(btVector3(1,1,1));

		body->getWorldTransform().setOrigin(camera_position);
		body->getWorldTransform().setRotation(btQuaternion(0,0,0,1));
		body->setLinearVelocity(linear_velocity);
		body->setAngularVelocity(btVector3(0,0,0));
		body->setCcdMotionThreshold(1.);
		body->setCcdSweptSphereRadius(0.2f);
}

void Window::drop_flexure()
{
    // create a flexure
    float r = 8.0;
    float x = 0.0;
    float y = 60.0;
    float z = 0.0;
    float color[4] = {0.8, 0.0, 0.0, 0.0};
    Flexure* flexure = new Flexure(
        Vector3(x - r, y, z - r),
        Vector3(x + r, y, z - r),
        Vector3(x - r, y, z + r),
        Vector3(x + r, y, z + r),
        color,
        0.01, // mass
        5, // x resolution
        5, // y resolution
        0); // fixed corners - 1 | 2 | 4 | 8
    world->welcome(flexure);   

}

// void Window::handle_expose() {} // TODO: write expose handler

void Window::move_picked(int x, int y)
{
    if(pick_constraint != NULL)
    {
        //keep it at the same picking distance
        Vector3 new_ray_to = camera->get_ray_to(x, y);
        Vector3 new_ray_from = camera->get_position();
        Vector3 direction = new_ray_to - new_ray_from;
        direction.normalize();
        direction *= old_pick_distance;
        Vector3 new_pivot_basis = new_ray_from + direction;

        pick_constraint->setPivotB(new_pivot_basis);
    }
}

void Window::unpick()
{
    if ((pick_constraint != NULL) && world->is_go())
    {
        //cout << "removing pick constraint: '" << pick_constraint << "'" << endl;
        
        world->remove_constraint(pick_constraint);
        delete pick_constraint;
        pick_constraint = NULL;
        
        //cout << "removed pick constraint: '" << pick_constraint << "'" << endl;

        if(picked_thing != NULL)
        {
            //cout << "deactivating picked thing: '" << picked_thing << "'" << endl;

            picked_thing->get_rigid_body()->forceActivationState(ACTIVE_TAG);
            picked_thing->get_rigid_body()->setDeactivationTime( 0.f );
            picked_thing = NULL;
        }
    }
}

void Window::pick_thing(int x, int y)
{
    if(world->is_go())
    {
        // get from and to rays in world coords
        Vector3 ray_to = camera->get_ray_to(x, y);
        Vector3 ray_from = camera->get_position();
        
        // pass callback to ray pick method
        btCollisionWorld::ClosestRayResultCallback 
            ray_callback(ray_from, ray_to);
        world->ray_pick(ray_from, ray_to, ray_callback);
		
		if(ray_callback.hasHit())
		{
		    btRigidBody* body = 
		        btRigidBody::upcast(ray_callback.m_collisionObject);
		    if(body != NULL)
		    {
		        if(!(body->isStaticObject() || body->isKinematicObject()))
		        {
		            body->setActivationState(DISABLE_DEACTIVATION);
		            picked_thing = 
		                static_cast<RigidThing*>(body->getUserPointer());
		            Vector3 pick_position(ray_callback.m_hitPointWorld);
		            
		            cout << "pick position: " << pick_position << endl;
		            
		            btVector3 local_pivot = 
		                body->getCenterOfMassTransform().inverse() 
		                * pick_position;
		            pick_constraint = 
		                new btPoint2PointConstraint(*body, local_pivot);
                    pick_constraint->m_setting.m_impulseClamp = pick_clamping;

                    world->add_constraint(pick_constraint);
 
                    // very weak constraint for picking
                    pick_constraint->m_setting.m_tau = 0.1f;
                    
                    //save mouse position for dragging
                    old_pick_position = ray_to;
                    old_hit_position = pick_position;
                    old_pick_distance  = (pick_position - ray_from).length();
		        }
		    }
		}
    }
}

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

            case SDL_KEYUP:
                handle_key_up(&event.key.keysym);
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

