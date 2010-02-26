/*  Vector3.h
 *
 *  3d translation vector
 *  - subclasses bullet's btVector3
 *  
 *  copyright 2010 michael philetus weller <philetus@gmail.com>
 *  
 *  you may redistribute or modify this code under the terms of the 
 *  GNU General Public Licence version 3.
 *  for more information see: http://www.gnu.org/licenses/gpl.html
 *  
 */

#ifndef PDPD_GEOMETRY_VECTOR3
#define PDPD_GEOMETRY_VECTOR3

#include "btBulletDynamicsCommon.h"

namespace pdpd
{
    namespace geometry
    {
        // subclass btVector3
        class Vector3 : public btVector3 {}
    }
}
#endif // PDPD_GEOMETRY_VECTOR3

