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
#include "Camera.h"
#include "ThingDrawer.h"

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
        Camera* camera;
        ThingDrawer* thing_drawer;
        // TODO OverlayDrawer* overlay_drawer;

        // event handlers call appropriate component
        void handle_key_down(SDL_keysym* keysym);
        void handle_key_up(SDL_keysym* keysym);
        
        void handle_pointer_down();
        void handle_pointer_up();
        void handle_pointer_move();
        
        void handle_resize(int w, int h) { camera->resize(w, h); }
        void handle_quit()
        {
            SDL_Quit();
            exit(0);
        }
        // void handle_expose(); // just redraw?

        // init helpers for constructor
        void init_sdl(int width, int height, std::string title);
        void init_gl(int width, int height);

        Window(); // hide default constructor
        Window(const Window& w); // hide copy-constructor
        
    public:
        Window(
            World* w,
            Camera* c,
            ThingDrawer* td,
            int width = 600, 
            int height = 400, 
            std::string title = std::string("predee predee")); 
        virtual ~Window();

        // main event loop method
        void event_loop();
    };
}
#endif // PDPD_WINDOW
