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

#include <iostream>

#include "ThingDrawer.h"

using namespace std;
using namespace pdpd;
using namespace renderer;
using namespace util;
using namespace things;
using namespace geometry;

// iterates over root-level things and descends tree to atomic things
void ThingDrawer::visit(
    Iterator<Thing*>* iterator, 
    int mode, 
    const Vector3& cast)
{
    // visit each root level thing
    while(iterator->has_next()) 
    {
        visit(iterator->next(), mode, cast);
    }
    delete iterator;
}

void ThingDrawer::visit(Thing* thing, int mode, const Vector3& cast)
{
    // push address onto gl name stack for selection
    glPushName(thing->get_address());
    
    // if thing is atomic draw it
    if(thing->is_atomic())
    {
        // choose action based on mode
        // downcast to atomic thing before passing
        if(mode == solid_mode)
        {
            draw_atomic_thing(static_cast<AtomicThing*>(thing));       
        }
        else if(mode == shadow_mode)
        {
            shade_atomic_thing(static_cast<AtomicThing*>(thing), cast);
        }
        else if(mode == pick_mode)
        {
            // TODO - need a separate pick method???
            draw_atomic_thing(static_cast<AtomicThing*>(thing));
        }
        else
        {
            cout << "wtf??? unrecognized visit mode: " << mode << "!" << endl;
        }
    }
    else
    {
        // downcast to composite thing
        CompositeThing* daddy = static_cast<CompositeThing*>(thing);
        
        // otherwise recurse over children
        Iterator<Thing*>* iterator = daddy->iter_children();
        while(iterator->has_next())
            visit(iterator->next(), mode, cast);
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
    {
        display_list = build_display_list(thing);
        cache(thing, display_list);
    }
    
    // preserve gl state
    glPushMatrix();
    
    // set color 
    // TODO: get color from thing's material
    //set_color();
     
    // translate to current position
    btScalar m[16];
    thing->get_gl_world_frame(m);
    glMultMatrixf(m);
    
    // call display list to render thing
    glCallList(display_list);
    
    // restore gl state
    glPopMatrix();
}

void ThingDrawer::shade_atomic_thing(AtomicThing* thing, const Vector3& cast)
{
    // cout << "shading thing " << *thing << endl;
    
    Transformation3 world_frame;
    thing->get_world_frame(&world_frame);

    // preserve gl state
    glPushMatrix();

    // draw shadow volume for each facet
    Iterator<Facet>* iterator = thing->iter_facets();
    while(iterator->has_next())
    {
        Facet facet = iterator->next();
        facet.transform(world_frame);

        // only draw if facet is facing the light
        if(facet.get_normal().angle_to(cast) > 90.0)
        {
            shade_facet(facet, cast);
        }
    }
    delete iterator;

    // restore gl state
    glPopMatrix();
}

// draw shadow volume for facet
void ThingDrawer::shade_facet(Facet& near, const Vector3& cast)
{
    // cout << "shading facet " << near << endl;
    
    // far facet is near facet translated by shadowcast vector
    Facet far(near);
    far += cast;
    
    float m[3]; // float array to hold values to pass to gl

    // draw end caps of shadow volume
    glBegin(GL_TRIANGLES);
    for(int i = 0; i < 3; i++) // near
    {
        near.get_gl_vertex(m, i);
        glVertex3fv(m);
    }
    for(int i = 2; i >= 0; i--) // far
    {
        far.get_gl_vertex(m, i);
        glVertex3fv(m);
    }
    glEnd();
    
    // draw sides
    glBegin(GL_QUAD_STRIP);
    for(int i = 0; i <= 3; i++)
    {
        near.get_gl_vertex(m, i % 3);
        glVertex3fv(m);
        far.get_gl_vertex(m, i % 3);
        glVertex3fv(m);
    }
    glEnd();
    
}

void ThingDrawer::pick_atomic_thing(AtomicThing*){}

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
    delete iterator;
    
    glEnd();
    glEndList();
    
    return display_list;
}

const float ThingDrawer::thing_diffuse[] = {0.6, 0.6, 0.6, 1.0};
const float ThingDrawer::thing_specular[] = {1.0, 1.0, 1.0, 1.0};

void ThingDrawer::dismiss(Thing*) {} // TODO

