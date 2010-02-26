/*  Transformation3.h
 *
 *  3d transformation matrix
 *  - currently an alias to Vector3 from sony vectormath library implementation
 *  
 *  copyright 2010 michael philetus weller <philetus@gmail.com>
 *  
 *  you may redistribute or modify this code under the terms of the 
 *  GNU General Public Licence version 3.
 *  for more information see: http://www.gnu.org/licenses/gpl.html
 *  
 */

#ifndef PDPD_GEOMETRY_TRANSFORMATION3
#define PDPD_GEOMETRY_TRANSFORMATION3

#include "btBulletDynamicsCommon.h"

namespace pdpd
{
    namespace geometry
    {
        class Transformation3 : public btTransform
        {
        public:
            // create new transformation from prototype
            Transformation3(const btTransform& prototype)
                { this->crib(prototype); }
                
            // copy value from another transform in place
            crib(const btTransform& prototype)
                { this->deSerialize(prototype->serialize); }
        }
    }
}
#endif // PDPD_GEOMETRY_TRANSFORMATION3

