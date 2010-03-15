/*  Camera.h
 *
 *  interface for managing window camera view
 *  
 *  copyright 2010 michael philetus weller <philetus@gmail.com>
 *  
 *  you may redistribute or modify this code under the terms of the 
 *  GNU General Public Licence version 3.
 *  for more information see: http://www.gnu.org/licenses/gpl.html
 *  
 */
 
#ifndef PDPD_RENDERER_CAMERA
#define PDPD_RENDERER_CAMERA

#include <GL/gl.h>
#include <GL/glu.h>

#include "../geometry/Vector3.h"

namespace pdpd
{
    namespace renderer
    {
        class Camera
        {
            Camera(const Camera&); // prevent copy-construction
            
        protected:
            static const float pi_over_180 = 0.01745329251994329547; // rad to deg
            static const float epsilon = 0.0000001; // wiggle room
            
            // updated by window
            int width;
            int height;
            
            // tuneable parameters
            float near; // near clipping plane distance
            float far; // far clipping plane distance
            int forward_index;
            geometry::Vector3 forward_axis;
            int up_index;
            geometry::Vector3 up_axis;
                        
        public:
            Camera() 
            :
            width(0),
            height(0), 
            near(1.0),
            far(1000.0),
            forward_index(2), // forward is -z
            forward_axis(0.0, 0.0, -1.0),
            up_index(1), // up is y
            up_axis(0.0, 1.0, 0.0)
            {}
            
            virtual ~Camera() {}

            // called by window on resize event
            virtual void resize(int w, int h)
            {
                width = w;
                height = h;
                
                // update viewport
                glViewport(0, 0, width, height);
            }
            
            // get ray from world to coord on window plane
            virtual geometry::Vector3 get_ray_to(int x, int y) = 0;
            
            // make gl calls to initialize gl perspective matrix
            virtual void set_perspective() = 0;
            
            // adjust angle of camera view
            virtual void tilt(int dx, int dy) = 0; 
            
            // adjust position of camera view
            virtual void pan(int dx, int dy) = 0;
            
            // zoom camera
            virtual void zoom(float dd) = 0;
            
            virtual const geometry::Vector3 get_position() = 0;
        };
    }
}
#endif // PDPD_RENDERER_CAMERA
