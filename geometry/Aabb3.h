/*  Aabb3.h
 *
 *  3D axis aligned bounding box
 *  
 *  copyright 2010 michael philetus weller <philetus@gmail.com>
 *  
 *  you may redistribute or modify this code under the terms of the 
 *  GNU General Public Licence version 3.
 *  for more information see: http://www.gnu.org/licenses/gpl.html
 *  
 */

#ifndef PDPD_GEOMETRY_AABB3
#define PDPD_GEOMETRY_AABB3

#include "btBulletDynamicsCommon.h"
#include "../vectormath/vectormath.h"

namespace pdpd
{
    namespace geometry
    {
        class Aabb3
        {
            static const margin = 0.0001;
            Point3 min;
            Point3 max;
        public:
        
            // construct from min, max vectors
            Aabb3(const btVector3 a_min, const btVector3 a_max)
            :
            min(a_min), max(a_max)
            {}

            // construct from unaligned box
            Aabb3(const Transformation3 transformation, const Scale3 scale)
            {
                btVector3 half_extents(
                    btScalar(scale.getX()/2.0),
                    btScalar(scale.getY()/2.0),
                    btScalar(scale.getZ()/2.0));
                btTransformAabb(
                    half_extents, margin, transformation, min, max);
            }
            
        }
    }
}
#endif // PDPD_GEOMETRY_AABB3
