/*******************************************************************************
**3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
**      10        20        30        40        50        60        70        80
**
** file:
**    geometry.c
**
** author:
**    Mirco "MacSlow" Mueller <macslow@bangang.de>
**
** copyright (C) Mirco Mueller, July 2006, placed under the terms of the GPL
**
*******************************************************************************/

#include <stdio.h>

#include "geometry.h"

void
advance (Point* pPoint)
{
	if (pPoint == NULL)
		return;

	if (pPoint->iGrowX != 0)
	{
		if (pPoint->fX + pPoint->fStepX < pPoint->fUpperLimitX)
			pPoint->fX += pPoint->fStepX;
		else
		{
			pPoint->iGrowX = 0;
			pPoint->fX -= pPoint->fStepX;
		}
	}
	else
	{
		if (pPoint->fX - pPoint->fStepX > pPoint->fLowerLimitX)
			pPoint->fX -= pPoint->fStepX;
		else
		{
			pPoint->iGrowX = 1;
			pPoint->fX += pPoint->fStepX;
		}
	}

	if (pPoint->iGrowY != 0)
	{
		if (pPoint->fY + pPoint->fStepY < pPoint->fUpperLimitY)
			pPoint->fY += pPoint->fStepY;
		else
		{
			pPoint->iGrowY = 0;
			pPoint->fY -= pPoint->fStepY;
		}
	}
	else
	{
		if (pPoint->fY - pPoint->fStepY > pPoint->fLowerLimitY)
			pPoint->fY -= pPoint->fStepY;
		else
		{
			pPoint->iGrowY = 1;
			pPoint->fY += pPoint->fStepY;
		}
	}
}
