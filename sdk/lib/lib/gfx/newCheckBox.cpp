/*
 * newCheckBox.cpp
 *
 *  Created on: Aug 1, 2019
 *      Author: Game
 */

#include "newCheckBox.h"
#include "include/global.h"
#include "api/init.h"

GI::Gfx::checkBox::checkBox(void *parentWindowHandler)
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

GI::Gfx::checkBox::checkBox() :
		isModified(true), enabled(true), visible(true), mouseTrack(false), checked(false),
		x(10), y(10), width(systemProgressBarWidth), height(systemProgressBarHeight),cornerRadius(systemCornerRound), checkBoxSize(systemCheckBoxSize),
		color((colorCheckBox *)&systemColorCheckBox), pScreen(dev.SCREEN[0]), state(mouseNop)
{
	if(!this) {
		return;
	}
	if(!pScreen) {
		return;
	}
	text.textAlign = GI::textAllign::center;
	text.wordWrap = false;
	text.pFont = controls_color.DefaultFont;
	text.pFont = (tFont *)systemFont;
	text.opaque = false;
	text.setText((const char *)"checkBox");
}

GI::Gfx::checkBox::checkBox(GI::Display::Display *pScreen) :
		isModified(true), enabled(true), visible(true), mouseTrack(false), checked(false),
		x(10), y(10), width(systemProgressBarWidth), height(systemProgressBarHeight),cornerRadius(systemCornerRound), checkBoxSize(systemCheckBoxSize),
		color((colorCheckBox *)&systemColorCheckBox), pScreen(pScreen), state(mouseNop)
{
	if(!this) {
		return;
	}
	if(!pScreen) {
		return;
	}
	text.textAlign = GI::textAllign::center;
	text.wordWrap = false;
	text.pFont = controls_color.DefaultFont;
	text.pFont = (tFont *)systemFont;
	text.opaque = false;
	text.setText((const char *)"checkBox");
}

GI::Gfx::checkBox::~checkBox()
{
	if(!this) {
		return;
	}
	text.~string();
}

void GI::Gfx::checkBox::mouseEventCapture(tControlCommandData* controlComand)
{
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
	if(insideWindow && state == mouseRelease) {
		setChecked(checked ? false : true);
	}
	if(mouseTrack) {
		if(insideWindow && state == mousePress) {
			mouseEvents.mousePress.press = true;
			if(mouseEvents.mousePress.callBack) {
				mouseEvents.mousePress.callBackReturnData = mouseEvents.mousePress.callBack(mouseEvents.mousePress.callBackData, checked);
			}
		}
		if(insideWindow && state == mouseMove) {
			mouseEvents.mouseMove.move = true;
			if(mouseEvents.mouseMove.callBack) {
				mouseEvents.mouseMove.callBackReturnData = mouseEvents.mouseMove.callBack(mouseEvents.mouseMove.callBackData, checked);
			}
		}
		if(insideWindow && state == mouseRelease) {
			mouseEvents.mouseRelease.release = true;
			if(mouseEvents.mouseRelease.callBack) {
				mouseEvents.mouseRelease.callBackReturnData = mouseEvents.mouseRelease.callBack(mouseEvents.mouseRelease.callBackData, checked);
			}
		}
	}
}

void GI::Gfx::checkBox::idle()
{
	if(visible) {
		if(isModified || text.isModifyed) {
			tRectangle scrLimits = pScreen->sClipRegion;
			pScreen->sClipRegion.sXMin = x;
			pScreen->sClipRegion.sXMax = x + width;
			pScreen->sClipRegion.sYMin = y;
			pScreen->sClipRegion.sYMax = y + height;
			ui checkYPosition = y + (height >> 1) - (checkBoxSize >> 1);
			if(enabled) {
				pScreen->drawRectangle(x + 2, checkYPosition, checkBoxSize, checkBoxSize, true, (state == mousePress || state == mouseMove) ? color->enabled.push.back.ARGB : color->enabled.pull.back.ARGB, cornerRadius);
				pScreen->drawRectangle(x + 2, checkYPosition, checkBoxSize, checkBoxSize, false, (state == mousePress || state == mouseMove) ? color->enabled.push.border.ARGB : color->enabled.pull.border.ARGB, cornerRadius);
				if(checked) {
					//pScreen->drawLine(x + 5, checkYPosition + 3, x + checkBoxSize - 2, checkYPosition + checkBoxSize - 4, 6, (state == mousePress || state == mouseMove) ? color->enabled.push.checkInk.ARGB : color->enabled.pull.checkInk.ARGB);
					//pScreen->drawLine(x + 5, checkYPosition + checkBoxSize - 4, x  + checkBoxSize - 2, checkYPosition + 3, 6, (state == mousePress || state == mouseMove) ? color->enabled.push.checkInk.ARGB : color->enabled.pull.checkInk.ARGB);
					pScreen->drawRectangle(x + 4, checkYPosition + 2, checkBoxSize - 3, checkBoxSize - 4, true, (state == mousePress || state == mouseMove) ? color->enabled.push.checkInk.ARGB : color->enabled.pull.checkInk.ARGB, cornerRadius);
				}
			}
			else {
				pScreen->drawRectangle(x + 2, checkYPosition, checkBoxSize, checkBoxSize, true, color->disabled.back.ARGB, cornerRadius);
				pScreen->drawRectangle(x + 2, checkYPosition, checkBoxSize, checkBoxSize, false, color->disabled.border.ARGB, cornerRadius);
				if(checked) {
					//pScreen->drawLine(x + 5, checkYPosition + 3, x + checkBoxSize - 2, checkYPosition + checkBoxSize - 4, 6, color->disabled.checkInk.ARGB);
					//pScreen->drawLine(x + 5, checkYPosition + checkBoxSize - 4, x  + checkBoxSize - 2, checkYPosition + 3, 6, color->disabled.checkInk.ARGB);
					pScreen->drawRectangle(x + 4, checkYPosition + 2, checkBoxSize - 3, checkBoxSize - 4, true, color->disabled.checkInk.ARGB, cornerRadius);
				}
			}
			text.window.sXMin = x + checkBoxSize + 5;
			text.window.sXMax = x + width - checkBoxSize - 5;
			text.window.sYMin = y + 1;
			text.window.sYMax = y + height - 3;
			pScreen->sClipRegion.sXMin = text.window.sXMin;
			s32 x_str_location = text.window.sXMin;
			StringProperties_t str_properties = text.getStrProp();
			s32 y_str_location = text.window.sYMin + (height >> 1) - (str_properties.StringColsHeight_Pixels >> 1);
			text.visible = visible;
			text.x = x_str_location;
			text.y = y_str_location;
			text.selStart = 0;
			text.selLen = 0;
			if(enabled == true) {
				if(state == mousePress || state == mouseMove) {
					text.foreColor = color->enabled.push.textInk;
					text.backColor = color->parent;
				}
				else {
					text.foreColor = color->enabled.pull.textInk;
					text.backColor = color->parent;
				}
			} else {
				text.foreColor = color->disabled.textInk;
				text.backColor = color->parent;
			}
			pScreen->refresh();
			setIsModified(false);
			text.isModifyed = true;
			pScreen->sClipRegion = scrLimits;
		}
		text.idle();
	}
}

