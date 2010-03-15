/*  Vector3.cpp
 *
 *  3d translation vector
 *  
 *  copyright 2010 michael philetus weller <philetus@gmail.com>
 *  
 *  you may redistribute or modify this code under the terms of the 
 *  GNU General Public Licence version 3.
 *  for more information see: http://www.gnu.org/licenses/gpl.html
 *  
 */
 
#include "Vector3.h"

using namespace std;

namespace pdpd
{
    namespace geometry
    {
        ostream& operator<<(ostream& os, const Vector3& v)
        {
            os << "Vector3(" << v[0] << ", " << v[1] << ", " << v[2] << ")";
            return os;
        }
    }
}
