/*  WorldRenderer.cpp
 *
 *  renders things to window with opengl
 *  
 *  copyright 2010 michael philetus weller <philetus@gmail.com>
 *  
 *  you may redistribute or modify this code under the terms of the 
 *  GNU General Public Licence version 3.
 *  for more information see: http://www.gnu.org/licenses/gpl.html
 *  
 */

#include <iostream>

#include "WorldRenderer.h"
 
using namespace std;
using namespace pdpd;
using namespace renderer;

void WorldRenderer::init_gl()
{
	cout << "OpenGL version: " <<  glGetString(GL_VERSION) << "\n";
    cout << "OpenGL vendor: " << glGetString(GL_VENDOR) << "\n";
    cout << "OpenGL renderer: " << glGetString(GL_RENDERER) << "\n";

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    /* cairo surface setup stuff
    glDisable (GL_DEPTH_TEST);
    glEnable (GL_TEXTURE_RECTANGLE_ARB);
        */
}

void WorldRenderer::render()
{
    // set up lights
    enable_lights();

    // update camera perspective
    camera->set_perspective();

    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
  
    // 1st solid rendering pass
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    thing_drawer->visit(world->iter_roots(), thing_drawer->solid_mode, 1);

    // 1st shadow rendering pass
    glDisable(GL_LIGHTING);
    glDepthMask(GL_FALSE);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_STENCIL_TEST);

    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(0.0f, 1.0f);

    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    glStencilFunc(GL_ALWAYS, 1, 0xFFFFFFFFL);
    glFrontFace(GL_CCW);
    glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
    thing_drawer->visit(
        world->iter_roots(), 
        thing_drawer->shadow_mode,
        1,
        shadowcast);    
    
    // 2nd shadow rendering pass
    glFrontFace(GL_CW);
    glStencilOp(GL_KEEP, GL_KEEP, GL_DECR);
    thing_drawer->visit(
        world->iter_roots(), 
        thing_drawer->shadow_mode,
        2,
        shadowcast);

    glDisable(GL_POLYGON_OFFSET_FILL);

    // 2nd solid rendering pass
    glFrontFace(GL_CCW);
    glPolygonMode(GL_FRONT,GL_FILL);
    glPolygonMode(GL_BACK,GL_FILL);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_LIGHTING);
    glDepthMask(GL_TRUE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glStencilFunc(GL_NOTEQUAL, 0, 0xFFFFFFFFL);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    thing_drawer->visit(world->iter_roots(), thing_drawer->solid_mode, 2);

    // put things back?
    glEnable(GL_LIGHTING);
    glDepthFunc(GL_LESS);
    glDisable(GL_STENCIL_TEST);
    glDisable(GL_CULL_FACE);
}
