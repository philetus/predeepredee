/*  WorldRenderer.h
 *
 *  renders things in world with opengl
 *  
 *  copyright 2010 michael philetus weller <philetus@gmail.com>
 *  
 *  you may redistribute or modify this code under the terms of the 
 *  GNU General Public Licence version 3.
 *  for more information see: http://www.gnu.org/licenses/gpl.html
 *  
 */
 
#ifndef PDPD_RENDERER_WORLD_RENDERER
#define PDPD_RENDERER_WORLD_RENDERER

#include <GL/gl.h>
#include <GL/glu.h>
#include <deque>

#include "../World.h"
#include "../geometry/Vector3.h"
#include "../util/DequeIterator.h"
#include "Light.h"
#include "Camera.h"
#include "ThingDrawer.h"

namespace pdpd
{
    namespace renderer
    {
        class WorldRenderer
        {
            WorldRenderer(); // hide
            WorldRenderer(const WorldRenderer&); // hide
            
            World* world; // world to render
            Camera* camera; // camera to track view parameters
            ThingDrawer* thing_drawer; // class to handle rendering things
            
            unsigned int next_light;            
            std::deque<Light*> lights; // and then there was light
            geometry::Vector3 shadowcast;
        public:
            
            WorldRenderer(World* w, Camera* c, ThingDrawer* d)
            :
            world(w),
            camera(c),
            thing_drawer(d),
            next_light(GL_LIGHT0),
            shadowcast(1000.0, -2000.0, 1000.0)
            {
                init_lights();
            }
            
            virtual ~WorldRenderer() {};
            
            virtual void render(); // do the damn thing
            
            virtual void init_gl(); // opengl setup stuff?
            
            // set up some lights
            virtual void init_lights()
            {
                float p0[] = {600.0, 400.0, 500.0, 0.0};
                float p1[] = {-600.0, -400.0, 500.0, 0.0};
                float p2[] = {600.0, 400.0, -500.0, 0.0};
                //float p3[] = {-600.0, -400.0, -500.0, 0.0};
                
                float a[] = {0.2, 0.2, 0.2, 1.0};
                float d[] = {1.0, 1.0, 1.0, 1.0};
                float s[] = {1.0, 1.0, 1.0, 1.0};
                
                add_light(new Light(p0, a, d, s));
                add_light(new Light(p1, a, d, s));
                add_light(new Light(p2, a, d, s));
                //add_light(new Light(p3, a, d, s));     
            }
            
            virtual void clear_lights()
            {
                // TODO
            }
            
            void add_light(Light* light)
            {
                light->set_name(next_light++);
                lights.push_back(light);
            }
            
            void enable_lights()
            {
                util::DequeIterator<Light*> iterator = 
                    util::DequeIterator<Light*>(lights);
                while(iterator.has_next()) iterator.next()->enable();
                glEnable(GL_LIGHTING);
            }
            
        };
    }
}
#endif // PDPD_RENDERER_WORLD_RENDERER
