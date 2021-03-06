/*  Window.h
 *
 *  interface for a window initialized by root demon
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

#include <iostream>
#include <string>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "World.h"

namespace pdpd
{
    class Window
    {        
    protected:
    
        int pos_x;
        int pos_y;
        int width;
        int height;
        std::string title;
        
        SDL_Window* sdl_window;
        SDL_GLContext gl_context;
        
        void init_sdl_window()
        {
            std::cout << " > creating sdl window" << std::endl;
        
            // get sdl window
            sdl_window = SDL_CreateWindow(
                title.c_str(), pos_x, pos_y, width, height,
                SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
            if(sdl_window == NULL)
            {
                std::cout << "failed to create sdl window!" << std::endl;
                return;
            }
            
            std::cout << " > creating sdl gl context" << std::endl;

            // create an opengl context
            gl_context = SDL_GL_CreateContext(sdl_window);
            if(gl_context == NULL)
            {
                std::cout << "failed to create gl context!" << std::endl;
                return;
            }
            
            std::cout << " > setting sdl swap interval" << std::endl;

            SDL_GL_SetSwapInterval(1); // sync buffer swap with vert refresh
        }

        Window(); // hide default constructor
        Window(const Window& w); // hide copy-constructor
        
    public:
        Window(
            int wdth = 600, 
            int hght = 400, 
            std::string ttl = std::string("predee predee"),
            int ps_x = SDL_WINDOWPOS_UNDEFINED,
            int ps_y = SDL_WINDOWPOS_UNDEFINED)
        :
        pos_x(ps_x),
        pos_y(ps_y),
        width(wdth),
        height(hght),
        title(ttl)
        {}
        
        virtual ~Window() {}
        
        // called by gooey when welcomed
        virtual void wake(World*) { init_sdl_window(); }

        // *** public window interface
        int get_pos_x() { return pos_x; }
        int get_pos_y() { return pos_y; }
        int get_height() { return height; }
        int get_width() { return width; }
        std::string get_title() { return title; }
        
        // *** event handler interface
        virtual void handle_key_down(SDLKey ky) = 0;
        virtual void handle_key_up(SDLKey ky) = 0;
        virtual void handle_pointer_down(int x, int y) = 0;
        virtual void handle_pointer_motion(int x, int y) = 0;
        virtual void handle_pointer_up() = 0;
        virtual void handle_move(int x, int y) = 0;
        virtual void handle_resize(int wdth, int hght) = 0;
        virtual void draw() = 0;
        
        // *** sdl interface
        unsigned int get_id()
        {
            if(sdl_window == NULL) return 0;
            return SDL_GetWindowID(sdl_window);
        }
        SDL_Window* get_sdl_window() { return sdl_window; }
        SDL_GLContext get_gl_context() { return gl_context; }

    };
}
#endif // PDPD_WINDOW
