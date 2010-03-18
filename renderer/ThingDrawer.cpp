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
    int pass,
    const Vector3& cast)
{
    // visit each root level thing
    while(iterator->has_next()) 
    {
        visit(iterator->next(), mode, pass, cast);
    }
    delete iterator;
}

void ThingDrawer::visit(Thing* thing, int mode, int pass, const Vector3& cast)
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
            draw_thing(static_cast<AtomicThing*>(thing), pass);       
        }
        else if(mode == shadow_mode)
        {
            shade_thing(static_cast<AtomicThing*>(thing), cast);
        }
        else if(mode == pick_mode)
        {
            // TODO - need a separate pick method???
            draw_thing(static_cast<AtomicThing*>(thing));
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
            visit(iterator->next(), mode, pass, cast);
        delete iterator;
    }
    
    // pop name on way out
    glPopName();
}

void ThingDrawer::draw_thing(AtomicThing* thing, int pass)
{
    // cout << "drawing " << *thing << endl;

    // preserve gl state
    glPushMatrix();
    
    // TODO: get color from thing's material
    //set_color();

    // set color, adjust for pass
    float color[4];
    float coeff = 1.0;
    if(pass == 2) coeff = 0.3;
    for(int i = 0; i < 4; i++) color[i] = thing->color[i] * coeff;
    glColor4fv(color);
    
    // draw facets directly (soft bodies change without warning)
    draw_facets(thing);
      
    // restore gl state
    glPopMatrix();
}

void ThingDrawer::shade_thing(AtomicThing* thing, const Vector3& cast)
{
    // cout << "shading thing " << *thing << endl;
    
    // preserve gl state
    glPushMatrix();

    // draw shadow volume for each facet
    Iterator<Facet>* iterator = thing->iter_facets();
    while(iterator->has_next())
    {
        Facet facet = iterator->next();

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

void ThingDrawer::pick_thing(AtomicThing*) {}

void ThingDrawer::draw_facets(AtomicThing* thing)
{
    //cout << "drawing facets for " << *thing << endl;
    
    // iterate over facets
    glBegin(GL_TRIANGLES);
    Iterator<Facet>* iterator = thing->iter_facets();

    //cout << "iterating over facets" << endl;    

    while(iterator->has_next())
    {
        Facet facet = iterator->next();
        float m[3]; // float array to hold values to pass to gl
        
        //cout << "  drawing " << facet << endl;
        //cout << "setting facet normal" << endl;   
         
        // set normal
        facet.get_gl_normal(m);
        glNormal3fv(m);
        
        //cout << "setting facet vertices" << endl;   

        // set vertices
        for(int i = 0; i < 3; i++)
        {
            facet.get_gl_vertex(m, i);
            glVertex3fv(m);
        }
    }
    delete iterator;
    
    glEnd();
}

const float ThingDrawer::thing_diffuse[] = {0.6, 0.6, 0.6, 1.0};
const float ThingDrawer::thing_specular[] = {1.0, 1.0, 1.0, 1.0};

void ThingDrawer::dismiss(Thing*) {} // TODO

