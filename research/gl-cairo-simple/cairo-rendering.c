/*******************************************************************************
**3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
**      10        20        30        40        50        60        70        80
**
** file:
**    cairo-rendering.c
**
** author:
**    Mirco "MacSlow" Mueller <macslow@bangang.de>
**
** copyright (C) Mirco Mueller, July 2006, placed under the terms of the LGPL
**
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "geometry.h"
#include "cairo-rendering.h"

cairo_t*
create_cairo_context (int  iWidth,
					  int iHeight,
					  int iChannels,
					  cairo_surface_t** pSurface,
					  unsigned char** pucBuffer)
{
	cairo_t* pCairoContext = NULL;

	/* create cairo-surface/context to act as OpenGL-texture source */
	*pucBuffer = calloc (iChannels * iWidth * iHeight, sizeof (unsigned char));
	if (!*pucBuffer)
	{
        printf ("create_cairo_context() - Couldn't allocate surface-buffer\n");
        return NULL;
	}

	*pSurface = cairo_image_surface_create_for_data (*pucBuffer,
													 CAIRO_FORMAT_ARGB32,
													 iWidth,
													 iHeight,
													 iChannels * iWidth);
	if (cairo_surface_status (*pSurface) != CAIRO_STATUS_SUCCESS)
	{
		free (*pucBuffer);
        printf ("create_cairo_context() - Couldn't create surface\n");
        return NULL;
	}

	pCairoContext = cairo_create (*pSurface);
	if (cairo_status (pCairoContext) != CAIRO_STATUS_SUCCESS)
	{
		free (*pucBuffer);
        printf ("create_cairo_context() - Couldn't create context\n");
        return NULL;
	}

	return pCairoContext;
}

void
render_curve (cairo_t* pCairoContext,
			  int iWidth,
			  int iHeight,
			  Line* pLineOne,
			  Line* pLineTwo,
			  double fLineWidth)
{
	if (pLineOne == NULL || pLineTwo == NULL)
		return;

	cairo_save (pCairoContext);
	cairo_set_operator (pCairoContext, CAIRO_OPERATOR_OVER);
	cairo_scale (pCairoContext, (double) iWidth / 1.0f, (double) iHeight / 1.0f);
	cairo_set_source_rgba (pCairoContext, 0.0f, 1.0f, 0.0f, 1.0f);
	cairo_paint (pCairoContext);

	cairo_set_source_rgba (pCairoContext, 0.0f, 0.0f, 0.0f, 1.0f);
	cairo_set_line_cap (pCairoContext, CAIRO_LINE_CAP_ROUND);
	cairo_set_line_width (pCairoContext, fLineWidth);
	cairo_move_to (pCairoContext, pLineOne->start.fX, pLineOne->start.fY);
	cairo_curve_to (pCairoContext,
					pLineOne->end.fX,
					pLineOne->end.fY,
					pLineTwo->start.fX,
					pLineTwo->start.fY,
					pLineTwo->end.fX,
					pLineTwo->end.fY);
	cairo_stroke (pCairoContext);
	cairo_restore (pCairoContext);
}
