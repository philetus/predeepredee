/*  Vector3.h
 *
 *  3 x 3 matrix for operating on vectors and quaternions
 *  - subclassed from bullet's implementation
 *  
 *  copyright 2010 michael philetus weller <philetus@gmail.com>
 *  
 *  you may redistribute or modify this code under the terms of the 
 *  GNU General Public Licence version 3.
 *  for more information see: http://www.gnu.org/licenses/gpl.html
 *  
 */

#ifndef PDPD_GEOMETRY_MATRIX3X3
#define PDPD_GEOMETRY_MATRIX3X3

#include "btBulletDynamicsCommon.h"

namespace pdpd
{
    namespace geometry
    {
        class Matrix3x3 : public btMatrix3x3
        {
        }
        
    }
}
#endif // PDPD_GEOMETRY_MATRIX3X3

