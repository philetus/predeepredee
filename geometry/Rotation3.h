/*  Rotation3.h
 *
 *  3d rotation represented as quaternion vector
 *  - subclasses bullet's btQuaternion
 *  
 *  copyright 2010 michael philetus weller <philetus@gmail.com>
 *  
 *  you may redistribute or modify this code under the terms of the 
 *  GNU General Public Licence version 3.
 *  for more information see: http://www.gnu.org/licenses/gpl.html
 *  
 */

#ifndef PDPD_GEOMETRY_ROTATION3
#define PDPD_GEOMETRY_ROTATION3

#include "btBulletDynamicsCommon.h"

namespace pdpd
{
    namespace geometry
    {
        class Rotation3 : public btQuaternion
        {
            static const float pi_over_180 = 0.01745329251994329547;
            
            // convert float degrees to btscalar radians
            btScalar fd2sr(float d) 
                { return static_cast<btScalar>(d * pi_over_180); }
            
        public:
            
            // constructors take degrees instead of radians
            Rotation3(const btVector3& axis, float angle)
            :
            btQuaternion(axis, fd2sr(angle))
            {}
             
            Rotation3(float yaw, float pitch, float roll)
            :
            btQuaternion(fd2sr(yaw), fd2sr(pitch), fd2sr(roll))
            {}
            
            // set functions also take degrees
            void set_axis_angle(const btVector3& axis, float angle)
                { btQuaternion::setRotation(axis, fd2sr(angle)); }
            
            void set_yaw_pitch_roll(float yaw, float pitch, float roll)
            {
                btQuaternion::setEuler(fd2sr(yaw), fd2sr(pitch), fd2sr(roll));
            }
        };
    }
}
#endif // PDPD_GEOMETRY_ROTATION3

