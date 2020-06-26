/*
 * newButton.cpp
 *
 *  Created on: Jul 20, 2019
 *      Author: Work
 */

#include "newButton.h"
#include "include/global.h"
#include "api/init.h"

GI::Gfx::button::button(void *parentWindowHandler)
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

GI::Gfx::button::button() :
		isModified(true), enabled(true), visible(true), mouseTrack(false),
		x(10), y(10), width(systemButtonWidth), height(systemButtonHeight),cornerRadius(systemCornerRound),
		color((colorButton *)&systemColorButton), pScreen(dev.SCREEN[0]), state(mouseNop)
{
	if(!this) {
		return;
	}
	if(!pScreen) {
		return;
	}
	text.textAlign = systemButtonTextAllign;
	text.wordWrap = systemButtonWordWrap;
	text.pFont = (tFont *)systemFont;
	text.opaque = false;
	text.setText((char *)"Button");
}

GI::Gfx::button::button(GI::Display::Display *pScreen) :
		isModified(true), enabled(true), visible(true), mouseTrack(false),
		x(10), y(10), width(systemButtonWidth), height(systemButtonHeight),cornerRadius(systemCornerRound),
		color((colorButton *)&systemColorButton), pScreen(pScreen), state(mouseNop)
{
	if(!this) {
		return;
	}
	if(!pScreen) {
		return;
	}
	text.textAlign = systemButtonTextAllign;
	text.wordWrap = systemButtonWordWrap;
	text.pFont = (tFont *)systemFont;
	text.opaque = false;
	text.setText((char *)"Button");
}

GI::Gfx::button::~button()
{
	if(!this) {
		return;
	}
	text.~string();
}

void GI::Gfx::button::mouseEventCapture(tControlCommandData* controlComand)
{
	if(this->enabled && this->visible) {
		bool insideWindow = GI::insideBox(x, y, width, height, controlComand->X, controlComand->Y);
		if(insideWindow && (CursorState)controlComand->Cursor == mousePress) {
			state = mousePress;
			setIsModified(true);
		}
		else if(state == mousePress) {
			state = mouseMove;
		}
		else if(state == mouseMove && ((CursorState)controlComand->Cursor == mouseRelease || (CursorState)controlComand->Cursor == mouseNop)) {
			state = mouseRelease;
			setIsModified(true);
		}
		else if(state == mouseRelease) {
			state = mouseNop;
		}
		if(mouseTrack) {
			if(insideWindow && state == mousePress) {
				mouseEvents.mousePress.press = true;
				if(mouseEvents.mousePress.callBack) {
					mouseEvents.mousePress.callBackReturnData = mouseEvents.mousePress.callBack(mouseEvents.mousePress.callBackData);
				}
			}
			if(insideWindow && state == mouseMove) {
				mouseEvents.mouseMove.move = true;
				if(mouseEvents.mouseMove.callBack) {
					mouseEvents.mouseMove.callBackReturnData = mouseEvents.mouseMove.callBack(mouseEvents.mouseMove.callBackData);
				}
			}
			if(insideWindow && state == mouseRelease) {
				mouseEvents.mouseRelease.release = true;
				if(mouseEvents.mouseRelease.callBack) {
					mouseEvents.mouseRelease.callBackReturnData = mouseEvents.mouseRelease.callBack(mouseEvents.mouseRelease.callBackData);
				}
			}
		}
	}
}

void GI::Gfx::button::idle()
{
	if(visible) {
		if(isModified || text.isModifyed) {
			tRectangle scrLimits = pScreen->sClipRegion;
			pScreen->sClipRegion.sXMin = x;
			pScreen->sClipRegion.sXMax = x + width;
			pScreen->sClipRegion.sYMin = y;
			pScreen->sClipRegion.sYMax = y + height;
			if(enabled) {
				pScreen->drawRectangle(x, y, width, height, true, (state == mousePress || state == mouseMove) ? color->enabled.push.back.ARGB : color->enabled.pull.back.ARGB, cornerRadius);
				pScreen->drawRectangle(x, y, width, height, false, (state == mousePress || state == mouseMove) ? color->enabled.push.border.ARGB : color->enabled.pull.border.ARGB, cornerRadius);
			}
			else {
				pScreen->drawRectangle(x, y, width, height, true, color->disabled.back.ARGB, cornerRadius);
				pScreen->drawRectangle(x, y, width, height, false, color->disabled.border.ARGB, cornerRadius);
			}
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
				if(state == mousePress || state == mouseMove) {
					text.foreColor = color->enabled.push.ink;
					text.backColor = color->enabled.push.back;
				}
				else {
					text.foreColor = color->enabled.pull.ink;
					text.backColor = color->enabled.pull.back;
				}
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

