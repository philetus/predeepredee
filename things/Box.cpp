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

Box::Box(geometry::Scale3 a_scale, double a_mass /*= 0.0*/)
:
scale(a_scale),
mass(a_mass)
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

bool Box::is_dynamic()
{
    if((mass - wiggle) > 0.0) return true;
    return false;
}

// index is binary for 3 axes - 0 is (0 0 0) which is -x, -y, -z
// index should be in range [0..7]
Vertex Box::get_vertex(int index)
{
    // create vertex at half-extent of scale centered on axis
    double x = scale.getX() / 2.0;
    double y = scale.getY() / 2.0;
    double z = scale.getZ() / 2.0;
    if(!(index & 1)) x = -x;
    if(!(index & 2)) y = -y;
    if(!(index & 4)) z = -z;
    Vertex vertex(x, y, z);
    
    // transform vertex by current world transformation
    vertex.transform(transformation);
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
    
// iterate over facets
Facet Box::FacetIterator::next()
{
    return box.get_facet(index++);
}
