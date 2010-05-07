/*  WorldWindow.h
 *
 *  subclass of window to render a world with a camera
 *  
 *  copyright 2010 michael philetus weller <philetus@gmail.com>
 *  
 *  you may redistribute or modify this code under the terms of the 
 *  GNU General Public Licence version 3.
 *  for more information see: http://www.gnu.org/licenses/gpl.html
 *  
 */
 
#ifndef PDPD_WORLD_WINDOW
#define PDPD_WORLD_WINDOW

#include <string>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Window.h"
#include "World.h"
#include "renderer/Camera.h"
#include "renderer/ThingDrawer.h"
#include "renderer/WorldRenderer.h"

#include "geometry/Vector3.h"
#include "geometry/Rotation3.h"
#include "geometry/Transformation3.h"
#include "things/Box.h"
#include "things/Flexure.h"

namespace pdpd
{
    class WorldWindow : public Window
    {
    protected:
        // stuff passed to window but created somewhere else
        renderer::Camera* camera;
        renderer::ThingDrawer* thing_drawer;
        World* world;
        renderer::WorldRenderer* world_renderer;
        
        bool pointer_down;
        int pointer_last_x;
        int pointer_last_y;
        enum {
            tilt_mode,
            pick_mode,
            shoot_mode
        } pointer_mode;
        things::RigidThing* picked_thing;
        btPoint2PointConstraint* pick_constraint;
        static const float pick_clamping = 30.0;
        geometry::Vector3 old_pick_position;
        geometry::Vector3 old_hit_position;
        float old_pick_distance;

        void pick_thing(int x, int y);
        void unpick();
        void move_picked(int x, int y);
 
        void drop_box();
        void drop_flexure();
        void shoot_box(int x, int y);
        float shoot_box_velocity;
                
        WorldWindow(); // hide default constructor
        WorldWindow(const Window& w); // hide copy-constructor
        
    public:
        WorldWindow(
            renderer::Camera* cmr,
            renderer::ThingDrawer* drwr,
            int wdth = 600, 
            int hght = 400, 
            std::string ttl = std::string("predee predee"))
        :
        Window(wdth, hght, ttl),
        camera(cmr),
        thing_drawer(drwr),
        pointer_down(false),
        pointer_mode(tilt_mode),
        pick_constraint(NULL),
        shoot_box_velocity(500.0)
        {}
        
        // called when root demon inits window
        void start(SDL_Window* sdl_wndw,
                   SDL_GLContext gl_cntxt,
                   World* wrld)
        {
            sdl_window = sdl_wndw;
            gl_context = gl_cntxt;
            world = wrld;
            world_renderer = 
                new renderer::WorldRenderer(world, camera, thing_drawer);
            world_renderer->init_gl();
            camera->resize(width, height);
            running = true;
        }

        // *** event handler interface
        void handle_key_down(SDLKey ky);
        void handle_key_up(SDLKey ky);
        void handle_pointer_down(int x, int y);
        void handle_pointer_motion(int x, int y);
        void handle_pointer_up();
        void handle_move(int x, int y);
        void handle_resize(int wdth, int hght);
        void draw()
        {
            // render world
            world_renderer->render();
        }
        
    };
}
#endif // PDPD_WORLD_WINDOW
