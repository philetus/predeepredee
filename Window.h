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

#include <string>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

namespace pdpd
{
    class Window
    {        
    protected:
        // sdl stuff
        SDL_Window* sdl_window;
        SDL_GLContext gl_context;
        mutable bool running; // flag to indicate if root started window yet
        
        // local variables
        int pos_x;
        int pos_y;
        int width;
        int height;
        std::string title;
        
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
        title(ttl),
        running(false)
        {}

        virtual ~Window() {}
        
        // *** public window interface
        int get_pos_x() { return pos_x; }
        int get_pos_y() { return pos_y; }
        int get_height() { return height; }
        int get_width() { return width; }
        std::string get_title() { return title; }
        bool is_running() { return running; }
        
        // *** event handler interface
        virtual void start(SDL_Window* sdl_wndw, 
                           SDL_GLContext gl_cntxt,
                           World*)
        {
            sdl_window = sdl_wndw;
            gl_context = gl_cntxt;
            running = true;
        }
        virtual void set_world(World*) = 0;
        virtual void handle_key_down(SDLKey ky) = 0;
        virtual void handle_key_up(SDLKey ky) = 0;
        virtual void handle_pointer_down(int x, int y) = 0;
        virtual void handle_pointer_motion(int x, int y) = 0;
        virtual void handle_pointer_up() = 0;
        virtual void draw() = 0;
        
        // *** sdl interface
        unsigned int get_id()
        {
            if(sdl_window == NULL) return NULL;
            return SDL_GetWindowID(sdl_window);
        }
        SDL_Window* get_sdl_window() { return sdl_window; }
        SDL_GLContext get_gl_context() { return gl_context; }

    };
}
#endif // PDPD_WINDOW
