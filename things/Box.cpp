/*  Box.cpp
 *  
 *  a rigid box defined by a scale vector and a world frame
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
using namespace util;
using namespace geometry;

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

    // return untransformed vertex
    return Vector3(x, y, z);
    
    // transform vertex by current world transformation and return
    // return transformation * vertex;
}

// index should be in range [0..11]
Facet Box::get_facet(int index)
{
    Facet facet(
        Vector3(
            normal_table[index][0],
            normal_table[index][1],
            normal_table[index][2]),
        get_vertex(vertex_table[index][0]),
        get_vertex(vertex_table[index][1]),
        get_vertex(vertex_table[index][2]));
    
    // transform to world coordinates
    facet.transform(world_frame);
    
    return facet;
}

const float Box::normal_table[][3] = 
    {{-1.0, 0.0, 0.0},
     {-1.0, 0.0, 0.0},
     {0.0, -1.0, 0.0},
     {0.0, -1.0, 0.0},
     {0.0, 0.0, -1.0},
     {0.0, 0.0, -1.0},
     {1.0, 0.0, 0.0},
     {1.0, 0.0, 0.0},
     {0.0, 1.0, 0.0},
     {0.0, 1.0, 0.0},
     {0.0, 0.0, 1.0},
     {0.0, 0.0, 1.0}};

// faces should wind ccw!
// wtf is going on here?
const int Box::vertex_table[][3] = 
    {{0, 6, 2},  // -x
     {0, 4, 6},  // -x
     {5, 4, 0},  // -y
     {1, 5, 0},  // -y
     {3, 1, 0},  // -z
     {2, 3, 0},  // -z
     {7, 5, 1},  // +x
     {7, 1, 3},  // +x
     {2, 6, 7},  // +y
     {3, 2, 7},  // +y
     {7, 6, 4},  // +z
     {7, 4, 5}}; // +z

Iterator<Vector3>* Box::iter_vertices() { return NULL; } // TODO
void Box::get_parent_frame(geometry::Transformation3*) {} // TODO
void Box::get_gl_parent_frame(btScalar*) {} // TODO

