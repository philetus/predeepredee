/*  SoftThing.h
 *
 *  superclass for soft bodies
 *  
 *  copyright 2010 michael philetus weller <philetus@gmail.com>
 *  
 *  you may redistribute or modify this code under the terms of the 
 *  GNU General Public Licence version 3.
 *  for more information see: http://www.gnu.org/licenses/gpl.html
 *  
 */
 
#ifndef PDPD_THINGS_SOFT_THING
#define PDPD_THINGS_SOFT_THING

#include <iostream>
#include "BulletSoftBody/btSoftBody.h"

#include "AtomicThing.h"

namespace pdpd
{
    namespace things
    {
        class SoftThing : public AtomicThing
        {
            SoftThing(); // hide
            SoftThing(const SoftThing&); // hide
        protected:
            btSoftBody* soft_body;
        public:
            SoftThing(
                float* clr,
                float mss = 0.0,
                bool chld = false)
            :
            AtomicThing(true, clr, mss, chld) // soft, color, mass, child
            {}
            
            virtual btSoftBody* init_soft_body(btSoftBodyWorldInfo&)
                { return NULL; }
            virtual btSoftBody* get_soft_body() { return soft_body; }            
        };
    }
}
#endif // PDPD_THINGS_SOFT_THING
