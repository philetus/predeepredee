/*  World.h
 *
 *  interface for adding and removing things from simulator
 *  - manages spatial indexing and collision detection
 *  - initializes physics
 *  - can be rendered with a Window
 *  
 *  copyright 2010 michael philetus weller <philetus@gmail.com>
 *  
 *  you may redistribute or modify this code under the terms of the 
 *  GNU General Public Licence version 3.
 *  for more information see: http://www.gnu.org/licenses/gpl.html
 *  
 */
 
#ifndef PREDEE_PREDEE_WORLD
#define PREDEE_PREDEE_WORLD

#include <list>
#include "Thing.h"

using std::vector;

namespace predeepredee
{
    class World
    {
        list<Thing> things; // list of things in the world
    public:
        World(); // constructor
        ~World(); // destructor
        void welcome(Thing thing);
        void dismiss(Thing thing);
    };
}
 #endif // PREDEE_PREDEE_WORLD
