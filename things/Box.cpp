/*  World.cpp
 *  
 *  interface for adding and removing things from simulator
 *
 *  copyright 2010 michael philetus weller <philetus@gmail.com>
 *  
 *  you may redistribute or modify this code under the terms of the 
 *  GNU General Public Licence version 3.
 *  for more information see: http://www.gnu.org/licenses/gpl.html
 *  
 */

#include "Box.h"

using namespace pdpd;
using namespace things;
using namespace geometry;

Box::Box(Vector3 s, double m /*= 0.0*/, bool child /*= false*/)
:
scale(s), mass(m), child(c)
{
    // set collision shape from scale (half size)
    collision_shape = new btCollisionShape(
        btVector3(btScalar(scale.getX() / 2.0),
                  btScalar(scale.getY() / 2.0),
                  btScalar(scale.getZ() / 2.0)));
    
    // if box is dynamic set inertia
    if(is_dynamic())
    {
        btVector3 inertia(0,0,0);
        collision_shape->calculateLocalInertia(mass, inertia);
    }
}

/*  return vector with position of transformed vertex at index
 *
 *  - index is binary for 3 axes - 0 is (0 0 0) which is -x, -y, -z
 *  - index should be in range [0..7]
 */ 
Vector3 Box::get_vertex(int index)
{
    // create vertex at half-extent of scale centered on axis
    double x = scale.getX() / 2.0;
    double y = scale.getY() / 2.0;
    double z = scale.getZ() / 2.0;
    if(!(index & 1)) x = -x;
    if(!(index & 2)) y = -y;
    if(!(index & 4)) z = -z;
    Vector3 vertex(x, y, z);
    
    // transform vertex by current world transformation and return
    return transformation * vertex;
}

// index should be in range [0..11]
Facet Box::get_facet(int index)
{
    return Facet(
        Normal3(
            normal_table[index][0],
            normal_table[index][1],
            normal_table[index][2]),
        get_vertex(vertex_table[index][0]),
        get_vertex(vertex_table[index][1]),
        get_vertex(vertex_table[index][2]));
}
    
