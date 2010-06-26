/*******************************************************************************
**3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
**      10        20        30        40        50        60        70        80
**
** file:
**    geometry.h
**
** author:
**    Mirco "MacSlow" Mueller <macslow@bangang.de>
**
** copyright (C) Mirco Mueller, July 2006, placed under the terms of the GPL
**
*******************************************************************************/

#ifndef _GEOMETRY_H
#define _GEOMETRY_H

typedef struct _Point
{
	double fX;
	double fY;
	int iGrowX;
	int iGrowY;
	double fStepX;
	double fStepY;
	double fLowerLimitX;
	double fUpperLimitX;
	double fLowerLimitY;
	double fUpperLimitY;
} Point;

typedef struct _Line
{
	Point start;
	Point end;
} Line;

void advance (Point* pPoint);

#endif /* _GEOMETRY_H */
