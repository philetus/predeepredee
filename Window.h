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

#include <SDL/SDL.h>
#include <GL/gl.h>

#include "World.h"

namespace pdpd
{
    class Window
    {
        World* world;
        int width;
        int height;
        char title[]; //TODO
        static const int loop_pause_interval = 50; // time to delay in event loop
        SDL_Surface* window_surface;
        /*
        cairo_surface_t* cairo_surface;
        unsigned char* surface_data;
        unsigned int texture_id;
        cairo_t* cairo_context;
        */
        
        // manage initialization in constructor
        bool init_sdl();
        bool init_gl();

        Window(); // prevent argumentless constructor calls
        Window(const Window& w); // prevent copy-construction
    public:
        Window(World* a_world, int a_width = 600, int a_height = 400); 
        // TODO: make this work      const char a_title[] = "predee predee");
        ~Window();

        // main event loop method
        void event_loop(); 
        
        // event handlers to be overridden by base classes
        virtual void handle_key_press(Uint16 unicode);
        virtual void handle_key_release(Uint16 unicode);
        
        virtual void handle_resize();
        virtual void handle_expose();
        virtual void handle_quit();
        
        virtual void handle_draw();
    };
}
#endif // PDPD_WINDOW
