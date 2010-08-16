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

#ifndef PDPD_GEOMETRY3_TRANSFORMATION3
#define PDPD_GEOMETRY3_TRANSFORMATION3

#include "btBulletDynamicsCommon.h"

namespace pdpd
{
    namespace geometry3
    {
        class Transformation3 : public btTransform
        {
        public:
            // default constructor produces identity transform
            Transformation3(
                const btMatrix3x3& b = btMatrix3x3::getIdentity(),
                const btVector3& o = btVector3(0.0, 0.0, 0.0))
            :
            btTransform(b, o)
            {}
            
            // rotation, position constuctor
            Transformation3(
                const btQuaternion& r,
                const btVector3& o = btVector3(0.0, 0.0, 0.0))
            :
            btTransform(r, o)
            {}
 
             // copy-constructor from base class
            Transformation3(const btTransform& proto) 
            : 
            btTransform(proto)
            {}
                            
            // copy value from another transform in place
            void crib(const btTransform& proto)
            {
                setOrigin(proto.getOrigin());
                setBasis(proto.getBasis());
            }
        };
    }
}
#endif // PDPD_GEOMETRY3_TRANSFORMATION3

