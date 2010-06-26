/*******************************************************************************
**3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
**      10        20        30        40        50        60        70        80
**
** file:
**    opengl-rendering.h
**
** author:
**    Mirco "MacSlow" Mueller <macslow@bangang.de>
**
** copyright (C) Mirco Mueller, July 2006, placed under the terms of the LGPL
**
*******************************************************************************/

#ifndef _OPENGL_RENDERING_H
#define _OPENGL_RENDERING_H

void init_gl ();

void draw_func (int iWidth,
				int iHeight,
				unsigned char* pucSurfaceData,
				unsigned int uiTextureId);

void resize_func (int iWidth,
				  int iHeight,
				  unsigned int* puiTextureId);

#endif /* _OPENGL_RENDERING_H */
