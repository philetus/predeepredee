/*  ThingDrawer.h
 *
 *  visitor to render things to window with opengl
 *  
 *  copyright 2010 michael philetus weller <philetus@gmail.com>
 *  
 *  you may redistribute or modify this code under the terms of the 
 *  GNU General Public Licence version 3.
 *  for more information see: http://www.gnu.org/licenses/gpl.html
 *  
 */
 
#ifndef PDPD_RENDERER_THING_DRAWER
#define PDPD_RENDERER_THING_DRAWER

#include <iostream>
#include <iterator>
#include <map>
#include <GL/gl.h>
#include <GL/glu.h>

#include "../util/Iterator.h"
#include "../geometry3/Vector3.h"
#include "../geometry3/Facet.h"
#include "../things/Thing.h"
#include "../things/AtomicThing.h"
#include "../things/CompositeThing.h"

namespace pdpd
{
    namespace renderer
    {
        class ThingDrawer
        {
            std::map<things::Thing*, GLuint> list_cache; // display list id cache
        protected:
            
            // hack to color things
            static const float thing_diffuse[];
            static const float thing_specular[];
            static const float thing_shininess = 100.0;
            
            // check if key is in cache and if it is copy value
            bool get_cached(things::Thing* key, GLuint* value)
            {
                // get pointer to key's value with find
                std::map<things::Thing*, GLuint>::iterator i = 
                    list_cache.find(key);
                
                // if pointer is at end of cache, key not in cache
                if(i == list_cache.end()) return false;
                
                // otherwise copy value and return true
                *value = i->second;
                return true;
            }
            
            // add thing*, gluint pair to cache
            void cache(things::Thing* key, GLuint value)
            {
                list_cache.insert(std::make_pair(key, value));
            }
            
            // compile display list for thing & add to cache & return index
            GLuint build_display_list(things::AtomicThing* thing);

            // visit an individual thing
            virtual void visit(
                things::Thing* thing,
                int mode,
                int pass,
                const geometry3::Vector3& cast);

            // just this method can be overridden to change appearance
            virtual void draw_thing(things::AtomicThing* thing, int pass = 0);
            virtual void draw_facets(things::AtomicThing* thing);
            virtual void pick_thing(things::AtomicThing* thing);
            virtual void shade_thing(
                things::AtomicThing* thing,
                const geometry3::Vector3& cast);
            virtual void shade_facet(
                geometry3::Facet& near, 
                const geometry3::Vector3& cast);
            
        public:
            virtual ~ThingDrawer() {}
            
            // visit modes
            static const int solid_mode = 0;
            static const int shadow_mode = 1;
            static const int pick_mode = 2;
            
            // visit takes iterator over root-level things in world
            // TODO (root-level things that overlap viewing frustum)
            virtual void visit(
                util::Iterator<things::Thing*>* iterator,
                int mode,
                int pass = 0,
                const geometry3::Vector3& cast = 
                    geometry3::Vector3(0.0, -1000.0, 0.0));
            
            // clear display lists for dismissed things
            virtual void dismiss(things::Thing* thing);
            
            void set_color()
            {
                glMaterialfv(GL_FRONT, GL_DIFFUSE, thing_diffuse);
                glMaterialfv(GL_FRONT, GL_SPECULAR, thing_specular);
                glMaterialf(GL_FRONT, GL_SHININESS, thing_shininess);
            }
        };
    }
}

#endif // PDPD_RENDERER_THING_DRAWER
