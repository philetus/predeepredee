/*******************************************************************************
**3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
**      10        20        30        40        50        60        70        80
**
** program:
**    gl-cairo-simple
**
** author:
**    Mirco "MacSlow" Mueller <macslow@bangang.de>
**
** copyright (C) Mirco Mueller, July 2006
**
** notes:
**    Simple example demonstrating how one could use cairo for generating
**    dynamic texture-mapping with OpenGL. I put this program under the terms of
**    the "GNU Lesser General Public License". If you don't know what that means
**    take a look a here...
**
**        http://www.gnu.org/licenses/licenses.html#TOCLGPL
**
*******************************************************************************/

#include <stdlib.h>

#include "SDL.h"
#include "SDL_opengl.h"
#include "geometry.h"
#include "opengl-rendering.h"
#include "cairo-rendering.h"

#define WIN_WIDTH	256
#define WIN_HEIGHT	256

void
update_animation_vars (Line* pLineOne,
					   Line* pLineTwo)
{
	advance (&pLineOne->start);
	advance (&pLineOne->end);
	advance (&pLineTwo->start);
	advance (&pLineTwo->end);
}

int main (int argc, char** argv)
{
	int iWidth = WIN_WIDTH;
	int iHeight = WIN_HEIGHT;
	Line lineOne;
	Line lineTwo;
	unsigned int uiTextureId;
    SDL_Surface* pSurfaceWindow = NULL;
    SDL_Event event;
	int iKeepRunning = 1;
	cairo_surface_t* pCairoSurface = NULL;
	cairo_t* pCairoContext;
	unsigned char* pucSurfaceData;
	double fLineWidth = 0.05f;

	/* initialize the four control-points of the two lines to draw
	** the bezier-curve between */
	lineOne.start.fX = 0.1f;
	lineOne.start.fY = 0.2f;
	lineOne.start.iGrowX = 1;
	lineOne.start.iGrowY = 1;
	lineOne.start.fStepX = 0.025f;
	lineOne.start.fStepY = 0.02f;
	lineOne.start.fLowerLimitX = 0.1f;
	lineOne.start.fUpperLimitX = 0.9f;
	lineOne.start.fLowerLimitY = 0.1f;
	lineOne.start.fUpperLimitY = 0.9f;

	lineOne.end.fX = 0.5f;
	lineOne.end.fY = 0.7f;
	lineOne.end.iGrowX = 1;
	lineOne.end.iGrowY = 0;
	lineOne.end.fStepX = 0.025f;
	lineOne.end.fStepY = 0.01f;
	lineOne.end.fLowerLimitX = 0.1f;
	lineOne.end.fUpperLimitX = 0.9f;
	lineOne.end.fLowerLimitY = 0.1f;
	lineOne.end.fUpperLimitY = 0.9f;

	lineTwo.start.fX = 0.75f;
	lineTwo.start.fY = 0.1f;
	lineTwo.start.iGrowX = 0;
	lineTwo.start.iGrowY = 1;
	lineTwo.start.fStepX = 0.01f;
	lineTwo.start.fStepY = 0.025f;
	lineTwo.start.fLowerLimitX = 0.1f;
	lineTwo.start.fUpperLimitX = 0.9f;
	lineTwo.start.fLowerLimitY = 0.1f;
	lineTwo.start.fUpperLimitY = 0.9f;

	lineTwo.end.fX = 0.8f;
	lineTwo.end.fY = 0.8f;
	lineTwo.end.iGrowX = 0;
	lineTwo.end.iGrowY = 0;
	lineTwo.end.fStepX = 0.01f;
	lineTwo.end.fStepY = 0.01f;
	lineTwo.end.fLowerLimitX = 0.1f;
	lineTwo.end.fUpperLimitX = 0.9f;
	lineTwo.end.fLowerLimitY = 0.1f;
	lineTwo.end.fUpperLimitY = 0.9f;

	/* init SDL */
	if ((SDL_Init (SDL_INIT_VIDEO | SDL_INIT_TIMER) == -1))
	{
		printf ("Could not initialize SDL: %s.\n", SDL_GetError ());
		exit (-1);
	}

	/* set window title */
	SDL_WM_SetCaption ("gl-cairo-simple", NULL);

	/* create "GL-context" */
	SDL_GL_SetAttribute (SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute (SDL_GL_GREEN_SIZE, 6);
	SDL_GL_SetAttribute (SDL_GL_BLUE_SIZE, 5);
	SDL_GL_SetAttribute (SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute (SDL_GL_DOUBLEBUFFER, 1);
    pSurfaceWindow = SDL_SetVideoMode (iWidth,
									   iHeight,
									   0,
									   SDL_OPENGL |
									   SDL_RESIZABLE);

	/* did we get what we want? */
    if (!pSurfaceWindow)
    {
        printf ("Couldn't open SDL-window: %s\n", SDL_GetError ());
        exit (-2);
    }

	/* create cairo-surface/context to act as OpenGL-texture source */
	pCairoContext = create_cairo_context (iWidth,
										  iHeight,
										  4,
										  &pCairoSurface,
										  &pucSurfaceData);

	/* setup "GL-context" */
	init_gl ();
    resize_func (iWidth, iHeight, &uiTextureId);

	/* enter event-loop */
	while (iKeepRunning)
	{
		/* get event from queue */
		SDL_PollEvent (&event);
		switch (event.type)
		{
			/* check for user hitting close-window widget */
			case SDL_QUIT :
				iKeepRunning = 0;
			break;

			/* check for mouse-buttons */
			case SDL_MOUSEBUTTONDOWN :

				if (event.button.button == SDL_BUTTON_WHEELUP)
					if (fLineWidth < 0.2f)
						fLineWidth += 0.005f;

				if (event.button.button == SDL_BUTTON_WHEELDOWN)
					if (fLineWidth > 0.01f)
						fLineWidth -= 0.005f;

			break;

			/* check for the keys being pressed */
			case SDL_KEYDOWN :

				/* ESC-key, exit program */
				if (event.key.keysym.sym == SDLK_ESCAPE)
					iKeepRunning = 0;

				/* q-key, exit program */
				if (event.key.keysym.sym == SDLK_q)
					iKeepRunning = 0;

				/* d-key, dump last cairo-rendered frame in a PNG-file */
				if (event.key.keysym.sym == SDLK_d)
					cairo_surface_write_to_png (pCairoSurface, "frame.png");

			break;

			/* user resized window */
			case SDL_VIDEORESIZE :
				iWidth = event.resize.w;
				iHeight = event.resize.h;
				pSurfaceWindow = SDL_SetVideoMode (iWidth,
									   			   iHeight,
												   0,
												   SDL_OPENGL |
												   SDL_RESIZABLE);
			    resize_func (iWidth, iHeight, &uiTextureId);
				free (pucSurfaceData);
				cairo_destroy (pCairoContext);
				pCairoContext = create_cairo_context (iWidth,
													  iHeight,
													  4,
													  &pCairoSurface,
													  &pucSurfaceData);
			break;
		}

		update_animation_vars (&lineOne, &lineTwo);
		render_curve (pCairoContext,
					  iWidth,
					  iHeight,
					  &lineOne,
					  &lineTwo,
					  fLineWidth);
		draw_func (iWidth, iHeight, pucSurfaceData, uiTextureId);

		/* try to get a redraw-rate of 20 Hz */
		SDL_Delay (50);
	}

	/* clear resources before exit */
	glDeleteTextures (1, &uiTextureId);
	free (pucSurfaceData);
	cairo_destroy (pCairoContext);
	SDL_Quit ();

	return 0;
}
