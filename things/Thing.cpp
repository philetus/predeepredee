/*  Thing.cpp
 *
 *  superclass for things being simulated
 *  
 *  copyright 2010 michael philetus weller <philetus@gmail.com>
 *  
 *  you may redistribute or modify this code under the terms of the 
 *  GNU General Public Licence version 3.
 *  for more information see: http://www.gnu.org/licenses/gpl.html
 *  
 */

#include "Thing.h"

using namespace std;

namespace pdpd
{
    namespace things
    {
        ostream& operator<<(ostream& os, const Thing& t)
        {
            os << "Thing(" << t.address << ")";
            return os;
        }    
    }
}
