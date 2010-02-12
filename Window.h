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
 
#ifndef PREDEE_PREDEE_WINDOW
#define PREDEE_PREDEE_WINDOW

#include "World.h"

namespace pdpd
{
    class Window
    {
    
    public:
        Window(World world); // constructor takes a world as an argument
    }
}
#endif PREDEE_PREDEE_WINDOW
