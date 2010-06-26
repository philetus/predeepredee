/*  Facet.cpp
 *
 *  triangle in a graphics mesh
 *  - defined by a surface normal and 3 vectors
 *  
 *  copyright 2010 michael philetus weller <philetus@gmail.com>
 *  
 *  you may redistribute or modify this code under the terms of the 
 *  GNU General Public Licence version 3.
 *  for more information see: http://www.gnu.org/licenses/gpl.html
 *  
 */

#include "Facet.h"

using namespace std;

namespace pdpd
{
    namespace geometry
    {
        ostream& operator<<(ostream& os, const Facet& f)
        {
            os << "Facet(" << f.normal << ", " << f.vertex0 << ", " 
                << f.vertex1 << ", " << f.vertex2 << ")";
            return os;
        }
    }
}    

