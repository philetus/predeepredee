/*  Translation3.h
 *
 *  3d translation vector
 *  - currently an alias to Vector3 from sony vectormath library implementation
 *  
 *  copyright 2010 michael philetus weller <philetus@gmail.com>
 *  
 *  you may redistribute or modify this code under the terms of the 
 *  GNU General Public Licence version 3.
 *  for more information see: http://www.gnu.org/licenses/gpl.html
 *  
 */

#ifndef PDPD_GEOMETRY_TRANSLATION3
#define PDPD_GEOMETRY_TRANSLATION3

#include "../vectormath/vectormath.h"

namespace pdpd
{
    namespace geometry
    {
        // just subclass Vector3
        class Translation3 : public Vectormath::Aos::Vector3 {}
    }
}
#endif // PDPD_GEOMETRY_TRANSLATION3

