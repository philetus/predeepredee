/*  ThingDrawer.cpp
 *  
 *  draws things in world with opengl
 *  - generates display lists for each atomic thing
 *
 *  copyright 2010 michael philetus weller <philetus@gmail.com>
 *  
 *  you may redistribute or modify this code under the terms of the 
 *  GNU General Public Licence version 3.
 *  for more information see: http://www.gnu.org/licenses/gpl.html
 *  
 */

#include "ThingDrawer.h"

using namespace pdpd;
using namespace util;
using namespace things;
using namespace geometry;

// iterates over root-level things and descends tree to atomic things
void ThingDrawer::visit(Iterator<Thing*>* iterator)
{
    // visit each root level thing
    while(iterator->has_next()) 
        visit(iterator->next());
    delete iterator;
}

void ThingDrawer::visit(Thing* thing)
{
    // push address onto gl name stack for selection
    glPushName(thing->get_address());
    
    // if thing is atomic draw it
    if(thing->is_atomic())
    {
        // downcast to atomic thing before calling draw method
        draw_atomic_thing(static_cast<AtomicThing*>(thing));
    }
    else
    {
        // downcast to composite thing
        CompositeThing* daddy = static_cast<CompositeThing*>(thing);
        
        // otherwise recurse over children
        Iterator<Thing*>* iterator = daddy->iter_children();
        while(iterator->has_next())
            visit(iterator->next());
        delete iterator;
    }
    
    // pop name on way out
    glPopName();
}

void ThingDrawer::draw_atomic_thing(AtomicThing* thing)
{
    // if display list is not cached build it now
    GLuint display_list;
    if(!get_cached(thing, &display_list))
        display_list = build_display_list(thing);
    
    // preserve gl state
    glPushMatrix();
    
    // set color 
    // TODO: get color from thing's material
    glMaterialfv(GL_FRONT, GL_DIFFUSE, thing_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, thing_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, thing_shininess);
     
    // translate to current position
    btScalar m[16];
    thing->get_gl_world_frame(m);
    glMultMatrixf(m);
    
    // call display list to render thing
    glCallList(display_list);
    
    // restore gl state
    glPopMatrix();
}

GLuint ThingDrawer::build_display_list(AtomicThing* thing)
{
    // get new display list name
    GLuint display_list = glGenLists(1);
    
    // compile new display list
    glNewList(display_list, GL_COMPILE);
    
    // iterate over facets
    glBegin(GL_TRIANGLES);
    Iterator<Facet>* iterator = thing->iter_facets();
    while(iterator->has_next())
    {
        Facet facet = iterator->next();
        float m[3]; // float array to hold values to pass to gl
        
        // set normal
        facet.get_gl_normal(m);
        glNormal3fv(m);
        
        // set vertices
        for(int i = 0; i < 3; i++)
        {
            facet.get_gl_vertex(m, i);
            glVertex3fv(m);
        }
    }
    
    glEnd();
    glEndList();
    
    return display_list;
}

const float ThingDrawer::thing_diffuse[] = {0.6, 0.6, 0.6, 1.0};
const float ThingDrawer::thing_specular[] = {1.0, 1.0, 1.0, 1.0};

void ThingDrawer::dismiss(Thing*) {} // TODO

