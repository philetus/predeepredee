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

#include "WorldWindow.h"
 
using namespace std;
using namespace pdpd;
using namespace geometry;
using namespace things;
using namespace renderer;

// *** event handler methods

void Window::handle_key_down(SDLKey ky)
{
    switch(ky) 
    {
    case SDLK_ESCAPE:
        // TODO: quit?
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

void Window::handle_key_up(SDLKey ky)
{
    switch(keysym->sym) 
    {
    default:
        pointer_mode = tilt_mode;
        break;
    }
}

void handle_pointer_down(int x, int y)
{
    pointer_down = true;
    pointer_last_x = x;
    pointer_last_y = y;
    switch(pointer_mode)
    {
    case shoot_mode:
        shoot_box(x, y);
        break;
    case pick_mode:
        pick_thing(x, y);
        break;
    default:
        break;
    }
}

void handle_pointer_up() 
{
    pointer_down = false;
    unpick();
}

void handle_pointer_motion(int x, int y)
{
    if(pointer_down)
    {
        switch(pointer_mode)
        {
        case tilt_mode:
            camera->tilt(x - pointer_last_x, y - pointer_last_y);
            break;
        case pick_mode:
            move_picked(x, y);
            break;
        default:
            break;
        }
        pointer_last_x = x;
        pointer_last_y = y;
    }
}

// *** methods to do stuff in window

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


