/*  Light.h
 *
 *  an opengl light
 *  
 *  copyright 2010 michael philetus weller <philetus@gmail.com>
 *  
 *  you may redistribute or modify this code under the terms of the 
 *  GNU General Public Licence version 3.
 *  for more information see: http://www.gnu.org/licenses/gpl.html
 *  
 */
 
#ifndef PDPD_RENDERER_LIGHT
#define PDPD_RENDERER_LIGHT

#include <GL/gl.h>
#include <GL/glu.h>

namespace pdpd
{
    namespace renderer
    {
        class Light
        {        
            unsigned int name;
            float position[4];
            float ambient[4];
            float diffuse[4];
            float specular[4];
            
            Light(); // hide default constructor
            Light(const Light&); // hide copy-constructor
        public:
            Light(
                const float *p,
                const float *a,
                const float *d,
                const float *s)
            :
            name(0)
            {
                for(int i = 0; i < 4; i++)
                {
                    position[i] = p[i];
                    ambient[i] = a[i];
                    diffuse[i] = d[i];
                    specular[i] = s[i];
                }
            }
            
            // execute gl calls to init light
            void enable()
            {
                glLightfv(name, GL_POSITION, position);
                glLightfv(name, GL_AMBIENT, ambient);
                glLightfv(name, GL_DIFFUSE, diffuse);
                glLightfv(name, GL_SPECULAR, specular);
                glEnable(name);
            }
            
            void set_name(unsigned int n) { name = n; }
        };
    }
}
#endif // PDPD_RENDERER_LIGHT
