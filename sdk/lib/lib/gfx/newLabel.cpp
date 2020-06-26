/*
 * newLabel.cpp
 *
 *  Created on: Aug 11, 2019
 *      Author: Work
 */

#ifndef LIB_LIB_GFX_NEWLABEL_CPP_
#define LIB_LIB_GFX_NEWLABEL_CPP_

#include "newLabel.h"

#include "newButton.h"
#include "newGfxUtil.h"
#include "include/global.h"
#include "api/init.h"

GI::Gfx::label::label(void *parentWindowHandler)
{
	if(!this) {
		return;
	}
	if(!parentWindowHandler) {
		return;
	}
	memset(this, 0, sizeof(*this));
	isModified = true;
}

GI::Gfx::label::label() :
		isModified(true), enabled(true), visible(true),
		x(10), y(10), width(systemButtonWidth), height(systemButtonHeight),
		color((colorLabel *)&systemColorLabel), pScreen(dev.SCREEN[0])
{
	if(!this) {
		return;
	}
	if(!pScreen) {
		return;
	}
	text.textAlign = systemLabelTextAllign;
	text.wordWrap = systemLabelWordWrap;
	text.pFont = (tFont *)systemFont;
	text.opaque = false;
	text.setText((char *)"Label");
}

GI::Gfx::label::label(GI::Display::Display *pScreen) :
		isModified(true), enabled(true), visible(true),
		x(10), y(10), width(systemButtonWidth), height(systemButtonHeight),
		color((colorLabel *)&systemColorLabel), pScreen(pScreen)
{
	if(!this) {
		return;
	}
	if(!pScreen) {
		return;
	}
	text.textAlign = systemLabelTextAllign;
	text.wordWrap = systemLabelWordWrap;
	text.pFont = (tFont *)systemFont;
	text.opaque = false;
	text.setText((char *)"Label");
}

GI::Gfx::label::~label()
{
	if(!this) {
		return;
	}
	text.~string();
}

void GI::Gfx::label::idle()
{
	if(visible) {
		if(isModified || text.isModifyed) {
			tRectangle scrLimits = pScreen->sClipRegion;
			pScreen->sClipRegion.sXMin = x;
			pScreen->sClipRegion.sXMax = x + width;
			pScreen->sClipRegion.sYMin = y;
			pScreen->sClipRegion.sYMax = y + height;
			pScreen->drawRectangle(x, y, width, height, true, color->parent.ARGB);
			text.window.sXMin = x + 3;
			text.window.sXMax = x + width - 1;
			text.window.sYMin = y + 1;
			text.window.sYMax = y + height - 3;
			s32 x_str_location = text.window.sXMin;
			s32 y_str_location = text.window.sYMin;
			if(text.textAlign == GI::textAllign::center) {
				StringProperties_t str_properties = text.getStrProp();
				x_str_location = text.window.sXMin + (width >> 1) - (str_properties.StringRowsMaxLength_Pixels >> 1);
				y_str_location = text.window.sYMin + (height >> 1) - (str_properties.StringColsHeight_Pixels >> 1);
			}
			else if(text.textAlign == GI::textAllign::right) {
				StringProperties_t str_properties = text.getStrProp();
				x_str_location = text.window.sXMax - str_properties.StringRowsMaxLength_Pixels - 2;
				y_str_location = text.window.sYMin + (height >> 1) - (str_properties.StringColsHeight_Pixels >> 1);
			}
			text.visible = visible;
			text.x = x_str_location;
			text.y = y_str_location;
			text.selStart = 0;
			text.selLen = 0;
			if(enabled == true) {
				text.foreColor = color->enabled.ink;
				text.backColor = color->enabled.back;
			} else {
				text.foreColor = color->disabled.ink;
				text.backColor = color->disabled.back;
			}
			pScreen->refresh();
			setIsModified(false);
			text.isModifyed = true;
			pScreen->sClipRegion = scrLimits;
		}
		text.idle();
	}
}


#endif /* LIB_LIB_GFX_NEWLABEL_CPP_ */
