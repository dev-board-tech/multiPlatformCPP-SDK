/*
 * cursor_ctrl.cpp
 *
 *  Created on: Apr 19, 2017
 *      Author: Cutare
 */

#include "cursor_ctl_def.h"
#include <api/timer.h>

bool GI::Display::Cursor::dataReady()
{
	if(!irqHeandle->in())
	{
		return false;
	}
	else
	{
		return true;
	}
}




