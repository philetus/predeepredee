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
            static const pi_over_180 = 0.0174532925;
        public:
        }
    }
}
#endif // PDPD_GEOMETRY_ROTATION3

