/*  Rotation3.h
 *
 *  3d rotation represented as quaternion vector
 *  - currently an alias to Quat from sony vectormath library implementation
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

#include "../vectormath/vectormath.h"

namespace pdpd
{
    namespace geometry
    {
        class Rotation3 : public Vectormath::Aos::Quat
        {
            const pi_over_180 = 0.0174532925;
        public:
            
            // construct from angle and axis
            Rotation3(float degrees, Axis3& axis)
            {
                Vectormath::Aos::Quat q = 
                    Vectormath::Aos::Quat::rotation(
                        degrees * pi_over_180, axis);
                this->setX(q.getX);
                this->setY(q.getY);
                this->setZ(q.getZ);
                this->setW(q.getW);
            }
            
            // construct from translation matrix
            Rotation3(Tranformation3& t)
            {
                Vectormath::Aos::Quat q =
                    Vectormath::Aos::Quat(Transformation3.get_upper3x3());
                this->setX(q.getX);
                this->setY(q.getY);
                this->setZ(q.getZ);
                this->setW(q.getW);
            }
            
            // normalize quaternion in place
            void normalize()
            {
                Vectormath::Aos::Quat q = Vectormath::Aos::normalize(this);
                this->setX(q.getX);
                this->setY(q.getY);
                this->setZ(q.getZ);
                this->setW(q.getW);
            }
        }
    }
}
#endif // PDPD_GEOMETRY_ROTATION3

