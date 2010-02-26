/*  Window.cpp
 *
 *  gui window with 3d rendering of simulation world and 2d menu overlay
 *  
 *  copyright 2010 michael philetus weller <philetus@gmail.com>
 *  
 *  you may redistribute or modify this code under the terms of the 
 *  GNU General Public Licence version 3.
 *  for more information see: http://www.gnu.org/licenses/gpl.html
 *  
 */

#include <iostream>

#include "Window.h"
 
using namespace std;
using namespace pdpd;

/*
 *  constructor
 */
Window::Window( World* a_world, int a_width /*= 600*/, int a_height /*= 400*/ ) 
        // const char a_title[] /*="predee predee"*/)
:
world(a_world),
width(a_width),
height(a_height)
{
    init_sdl();
    init_gl();
}

/*
 *  destructor
 */
Window::~Window()
{
    /*
    delete title;
    delete window_surface;
    delete cairo_surface;
    delete surface_data;
    delete texture_id;
    delete cairo_context;
    */
}

bool Window::init_sdl()
{

    // init SDL video
    if(SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        cout << "fail! : can't init video : " << SDL_GetError() << "\n";
        return false;
    }

	// set window title
	SDL_WM_SetCaption("predee predee", NULL); //TODO fix title

    // setup opengl context for window
    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	// get sdl window surface to draw to
	int flags = SDL_OPENGL | SDL_RESIZABLE;
    if(!(window_surface = SDL_SetVideoMode(width, height, 0, flags)))
    {
        cout << "fail! : can't open sdl window : " << SDL_GetError() << "\n";
        return false;
    }
}

bool Window::init_gl()
{
	cout << "OpenGL version: " <<  glGetString(GL_VERSION) << "\n";
	cout << "OpenGL vendor: " << glGetString(GL_VENDOR) << "\n";
	cout << "OpenGL renderer: " << glGetString(GL_RENDERER) << "\n";

	glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
	
	/* cairo surface setup stuff
	glDisable (GL_DEPTH_TEST);
    glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable (GL_TEXTURE_RECTANGLE_ARB);
	 */

    /* Our shading model--Gouraud (smooth). */
    glShadeModel( GL_SMOOTH );

    /* Culling. */
    glCullFace( GL_BACK );
    glFrontFace( GL_CCW );
    glEnable( GL_CULL_FACE );

    // call resize handler to finish init
    handle_resize();
}

void Window::handle_keypress(SDL_keysym* keysym)
{
    switch( keysym->sym ) 
    {
    case SDLK_ESCAPE:
        handle_quit();
        break;
    default:
        break;
    }

}
void Window::handle_keyrelease(SDL_keysym* keysym) {} // TODO
void Window::handle_expose() {} // TODO: write expose handler

void Window::handle_quit() {
    SDL_Quit();
    exit(0);
}

void Window::handle_resize()
{
    /* Setup our viewport. */
    glViewport( 0, 0, width, height );

    /*
     * Change to the projection matrix and set
     * our viewing volume.
     */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // TODO: make this adjustable
    float aspect = (float) width / (float) height;
    GLdouble top = 1.732050808;
    GLdouble bottom = -top;
    GLdouble near = 1.0;
    GLdouble far = 1024.0;     
    GLdouble left = aspect * bottom;
    GLdouble right = aspect * top;
    glFrustum(left, right, bottom, top, near, far);
}

void Window::event_loop()
{
    /* Our SDL event placeholder. */
    SDL_Event event;
    
    while(true) // main event loop
    {
        // process all events in queue
        while(SDL_PollEvent(&event)) {
            switch(event.type)
            {
            case SDL_KEYDOWN:
                handle_keypress(&event.key.keysym);
                break;

            case SDL_VIDEORESIZE: // on resize first update width and height
                width = event.resize.w;
                height = event.resize.h;
                handle_resize();
                break;
            
            /*
            case SDL_VIDEOEXPOSE: // redraw screen after expose event
                handle_expose();
                break;
             */

            case SDL_QUIT: // ctrl-c
                handle_quit();
                break;

            default:
                break;
            }
        }
        
        // step physics, redraw window to buffer then swap buffers
        world->step_physics();
        handle_draw();
        glFlush(); // is this necessary?
        SDL_GL_SwapBuffers();
        
        // don't race processor
        SDL_Delay(loop_pause_interval);
    }
}

// draw some stuff for test
void Window::handle_draw()
{
    static bool should_rotate = true;
    
    /* Our angle of rotation. */
    static float angle = 55.0f;

    static GLfloat v0[] = { -1.0f, -1.0f,  1.0f };
    static GLfloat v1[] = {  1.0f, -1.0f,  1.0f };
    static GLfloat v2[] = {  1.0f,  1.0f,  1.0f };
    static GLfloat v3[] = { -1.0f,  1.0f,  1.0f };
    static GLfloat v4[] = { -1.0f, -1.0f, -1.0f };
    static GLfloat v5[] = {  1.0f, -1.0f, -1.0f };
    static GLfloat v6[] = {  1.0f,  1.0f, -1.0f };
    static GLfloat v7[] = { -1.0f,  1.0f, -1.0f };
    static GLubyte red[]    = { 255,   0,   0, 255 };
    static GLubyte green[]  = {   0, 255,   0, 255 };
    static GLubyte blue[]   = {   0,   0, 255, 255 };
    static GLubyte white[]  = { 255, 255, 255, 255 };
    static GLubyte yellow[] = {   0, 255, 255, 255 };
    static GLubyte black[]  = {   0,   0,   0, 255 };
    static GLubyte orange[] = { 255, 255,   0, 255 };
    static GLubyte purple[] = { 255,   0, 255,   0 };

    /* Clear the color and depth buffers. */
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    /* We don't want to modify the projection matrix. */
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );

    /* Move down the z-axis. */
    glTranslatef( 0.0, 0.0, -5.0 );

    /* Rotate. */
    glRotatef( angle, 0.0, 1.0, 0.0 );

    if ( should_rotate ) {
        if ( ++angle > 360.0f ) {
            angle = 0.0f;
        }
    }

    /* Send our triangle data to the pipeline. */
    glBegin( GL_TRIANGLES );

    glColor4ubv( red );
    glVertex3fv( v0 );
    glColor4ubv( green );
    glVertex3fv( v1 );
    glColor4ubv( blue );
    glVertex3fv( v2 );

    glColor4ubv( red );
    glVertex3fv( v0 );
    glColor4ubv( blue );
    glVertex3fv( v2 );
    glColor4ubv( white );
    glVertex3fv( v3 );

    glColor4ubv( green );
    glVertex3fv( v1 );
    glColor4ubv( black );
    glVertex3fv( v5 );
    glColor4ubv( orange );
    glVertex3fv( v6 );

    glColor4ubv( green );
    glVertex3fv( v1 );
    glColor4ubv( orange );
    glVertex3fv( v6 );
    glColor4ubv( blue );
    glVertex3fv( v2 );

    glColor4ubv( black );
    glVertex3fv( v5 );
    glColor4ubv( yellow );
    glVertex3fv( v4 );
    glColor4ubv( purple );
    glVertex3fv( v7 );

    glColor4ubv( black );
    glVertex3fv( v5 );
    glColor4ubv( purple );
    glVertex3fv( v7 );
    glColor4ubv( orange );
    glVertex3fv( v6 );

    glColor4ubv( yellow );
    glVertex3fv( v4 );
    glColor4ubv( red );
    glVertex3fv( v0 );
    glColor4ubv( white );
    glVertex3fv( v3 );

    glColor4ubv( yellow );
    glVertex3fv( v4 );
    glColor4ubv( white );
    glVertex3fv( v3 );
    glColor4ubv( purple );
    glVertex3fv( v7 );

    glColor4ubv( white );
    glVertex3fv( v3 );
    glColor4ubv( blue );
    glVertex3fv( v2 );
    glColor4ubv( orange );
    glVertex3fv( v6 );

    glColor4ubv( white );
    glVertex3fv( v3 );
    glColor4ubv( orange );
    glVertex3fv( v6 );
    glColor4ubv( purple );
    glVertex3fv( v7 );

    glColor4ubv( green );
    glVertex3fv( v1 );
    glColor4ubv( red );
    glVertex3fv( v0 );
    glColor4ubv( yellow );
    glVertex3fv( v4 );

    glColor4ubv( green );
    glVertex3fv( v1 );
    glColor4ubv( yellow );
    glVertex3fv( v4 );
    glColor4ubv( black );
    glVertex3fv( v5 );

    glEnd( );    
}
