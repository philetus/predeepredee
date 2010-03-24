/*  Window.h
 *
 *  gui window with 3d rendering of simulation world and 2d menu overlay
 *  - uses sdl for window and mouse events
 *  
 *  copyright 2010 michael philetus weller <philetus@gmail.com>
 *  
 *  you may redistribute or modify this code under the terms of the 
 *  GNU General Public Licence version 3.
 *  for more information see: http://www.gnu.org/licenses/gpl.html
 *  
 */
 
#ifndef PDPD_WINDOW
#define PDPD_WINDOW

#include <string>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "World.h"
#include "renderer/Camera.h"
#include "renderer/WorldRenderer.h"

#include "geometry/Vector3.h"
#include "geometry/Rotation3.h"
#include "geometry/Transformation3.h"
#include "things/Box.h"
#include "things/Flexure.h"

namespace pdpd
{
    class Window
    {
        // global parameters to tune
        static const int loop_pause_interval = 50; // delay time in event loop
                
        // stuff created by window and must be cleaned up
        SDL_Surface* window_surface;
        /*
        cairo_surface_t* cairo_surface;
        unsigned char* surface_data;
        unsigned int texture_id;
        cairo_t* cairo_context;
        */
        
        // stuff passed to window but created somewhere else
        World* world;
        renderer::Camera* camera;
        renderer::WorldRenderer* world_renderer;
        // TODO OverlayDrawer* overlay_drawer;
        
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
           
        // event handlers call appropriate component
        void handle_key_down(SDL_keysym* keysym);
        void handle_key_up(SDL_keysym* keysym);
        SDL_Surface* get_sdl_surface(int width, int height);
        void drop_box();
        void drop_flexure();
        void shoot_box(int x, int y);
        float shoot_box_velocity;
        
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
        
        void handle_resize(int width, int height);
        void handle_quit()
        {
            SDL_Quit();
            exit(0);
        }
        // void handle_expose(); // just redraw?

        // init helpers for constructor
        void init_sdl(int width, int height, std::string title);
        
        Window(); // hide default constructor
        Window(const Window& w); // hide copy-constructor
        
    public:
        Window(
            World* w,
            renderer::Camera* c,
            renderer::WorldRenderer* r,
            int width = 600, 
            int height = 400, 
            std::string title = std::string("predee predee"))
        :
        world(w),
        camera(c),
        world_renderer(r),
        pointer_down(false),
        pointer_mode(tilt_mode),
        pick_constraint(NULL),
        shoot_box_velocity(500.0)
        {
            init_sdl(width, height, title);
            world_renderer->init_gl();
            camera->resize(width, height);
        }

        virtual ~Window()
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

        // main event loop method
        void event_loop();
    };
}
#endif // PDPD_WINDOW
