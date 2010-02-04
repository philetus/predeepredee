/*******************************************************************************
**3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
**      10        20        30        40        50        60        70        80
**
** file:
**    cairo-rendering.h
**
** author:
**    Mirco "MacSlow" Mueller <macslow@bangang.de>
**
** copyright (C) Mirco Mueller, July 2006, placed under the terms of the LGPL
**
*******************************************************************************/

#ifndef _CAIRO_RENDERING_H
#define _CAIRO_RENDERING_H

#include <cairo.h>

#include "geometry.h"

cairo_t*
create_cairo_context (int iWidth,
					  int  iHeight,
					  int iChannels,
					  cairo_surface_t** pCairoSurface,
					  unsigned char** pucBuffer);

void render_curve (cairo_t* pCairoContext,
				   int iWidth,
				   int iHeight,
				   Line* pLineOne,
				   Line* pLineTwo,
				   double fLineWidth);

#endif /* _CAIRO_RENDERING_H */
