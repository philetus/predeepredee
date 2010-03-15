/*  TargetCamera.h
 *
 *  superclass for things being simulated
 *  
 *  copyright 2010 michael philetus weller <philetus@gmail.com>
 *  
 *  you may redistribute or modify this code under the terms of the 
 *  GNU General Public Licence version 3.
 *  for more information see: http://www.gnu.org/licenses/gpl.html
 *  
 */
 
#ifndef PDPD_RENDERER_TARGET_CAMERA
#define PDPD_RENDERER_TARGET_CAMERA

#include "Camera.h"
#include "../geometry/Vector3.h"
#include "../geometry/Rotation3.h"
#include "../geometry/Matrix3x3.h"

namespace pdpd
{
    namespace renderer
    {
        class TargetCamera : public Camera
        {
            // camera view parameters
            float azimuth; // angle heading in degrees
            float elevation; // angle to look up or down
            float distance; // distance from camera to target 
            geometry::Vector3 position; // position of camera
            geometry::Vector3 target; // point to look at
            
            TargetCamera(const TargetCamera&); // hide copy-constructor 
        public:
            TargetCamera()
            :
            Camera(), // call superclass constructor first
            azimuth(-30.0),
            elevation(30.0),
            distance(100.0),
            target(0.0, 0.0, 0.0)
            {}
            
            // implements camera interface for rendering and pointer handlers
            void set_perspective();
            geometry::Vector3 get_ray_to(int x, int y);
            void tilt(int dx, int dy); // tilt adjusts azimuth and elevation
            void pan(int dx, int dy); // pan moves target
            void zoom(float dd); // zoom adjusts camera distance
            
            // target camera extended direct interface
            void set_target(const geometry::Vector3& t) { target.crib(t); }
            void set_distance(float d) { distance = d; }
            void set_azimuth(float a) { azimuth = a; }
            void set_elevation(float e) { elevation = e; }
            
            const geometry::Vector3 get_position() { return position; }
        };
    }
}
#endif // PDPD_RENDERER_TARGET_CAMERA
