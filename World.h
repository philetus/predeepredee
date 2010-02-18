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
 
#ifndef PDPD_WORLD
#define PDPD_WORLD

/*
#include <deque>

#include "Thing.h"
#include "Iterator.h"
#include "DequeIterator.h"
 */
 
namespace pdpd
{
    class World
    {
        // std::deque<Thing> things; // list of things in the world
    public:
        /*
        World();
        ~World() { delete things; }
        
        virtual void welcome(Thing& thing);
        virtual void dismiss(Thing& thing);
        
        // iterator over things
        virtual Iterator<Thing> iter_things()
            { return DequeIterator(things) }
         */
    };
}
 #endif // PDPD_WORLD
