/*
 * newProgressBar.h.cpp
 *
 *  Created on: Jul 25, 2019
 *      Author: Work
 */

#include "newProgressBar.h"
#include "include/global.h"
#include "lib/util/converters.h"
#include "api/init.h"


GI::Gfx::progressBar::progressBar(void *parentWindowHandler)
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

GI::Gfx::progressBar::progressBar() :
		isModified(true), enabled(true), visible(true), mouseTrack(false),
		x(10), y(10), width(systemProgressBarWidth), height(systemProgressBarHeight),cornerRounded(systemCornerRound ? true : false),
		minimum(-100), maximum(100), value(0),
		orientation(horizontal),
		showPercentage(true), showText(true), barCutMode(true),
		color((colorProgressBar *)&systemColorProgressBar), pScreen(dev.SCREEN[0]), state(mouseNop),
		barLength(0)
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
}

GI::Gfx::progressBar::progressBar(GI::Display::Display *pScreen) :
		isModified(true), enabled(true), visible(true), mouseTrack(false),
		x(10), y(10), width(systemProgressBarWidth), height(systemProgressBarHeight),cornerRounded(systemCornerRound ? true : false),
		minimum(-100), maximum(100), value(0),
		orientation(horizontal),
		showPercentage(true), showText(true), barCutMode(true),
		color((colorProgressBar *)&systemColorProgressBar), pScreen(pScreen), state(mouseNop),
		barLength(0)
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
}

GI::Gfx::progressBar::~progressBar()
{
	if(!this) {
		return;
	}
	text.~string();
}

void GI::Gfx::progressBar::mouseEventCapture(tControlCommandData* controlComand)
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
		s32 value = this->value;
		if(state == mousePress || state == mouseMove) {
			/* Convert cursor coordinates to bar length */
			//ui barLength = GUtil::Converters::toPercent(0, (orientation == horizontal ? width : height), (orientation == horizontal ? width : height), (orientation == horizontal ? controlComand->X - x : ~controlComand->Y - y));
			si barLength = (orientation == horizontal ? controlComand->X - x : ~controlComand->Y - y);
			if(barLength < 0) {
				barLength = 0;
			}
			else if(barLength > (si)(orientation == horizontal ? width : height)) {
				barLength = (orientation == horizontal ? width : height);
			}
			/* Convert barLength to bar value */
			value = GUtil::Converters::percentTo((s32)minimum, (s32)maximum, (s32)(orientation == horizontal ? width : height), (s32)barLength);
		}
		if(value != this->value) {
			events.valueChanged.valueChanged = true;
			if(events.valueChanged.callBack) {
				events.valueChanged.callBackReturnData = events.valueChanged.callBack(events.valueChanged.callBackData, value);
			}
			setValue(value);
		}
		if(mouseTrack) {
			if(insideWindow && state == mousePress) {
				mouseEvents.mousePress.press = true;
				if(mouseEvents.mousePress.callBack) {
					mouseEvents.mousePress.callBackReturnData = mouseEvents.mousePress.callBack(mouseEvents.mousePress.callBackData, value);
				}
			}
			if(insideWindow && state == mouseMove) {
				mouseEvents.mouseMove.move = true;
				if(mouseEvents.mouseMove.callBack) {
					mouseEvents.mouseMove.callBackReturnData = mouseEvents.mouseMove.callBack(mouseEvents.mouseMove.callBackData, value);
				}
			}
			if(insideWindow && state == mouseRelease) {
				mouseEvents.mouseRelease.release = true;
				if(mouseEvents.mouseRelease.callBack) {
					mouseEvents.mouseRelease.callBackReturnData = mouseEvents.mouseRelease.callBack(mouseEvents.mouseRelease.callBackData, value);
				}
			}
		}
	}
}

void GI::Gfx::progressBar::idle()
{
	if(visible) {
		if(isModified) {
			tRectangle scrLimits = pScreen->sClipRegion;
			pScreen->sClipRegion.sXMin = x;
			pScreen->sClipRegion.sXMax = x + width;
			pScreen->sClipRegion.sYMin = y;
			pScreen->sClipRegion.sYMax = y + height;
			/* Convert value to bar length */
			ui barLength = GUtil::Converters::toPercent(minimum, maximum, (orientation == horizontal ? width : height) - (barCutMode ? 0 : 2), value) + (barCutMode ? 0 : 1);
			if(barLength > (orientation == horizontal ? width : height) - (barCutMode ? 0 : 2)) {
				barLength = (orientation == horizontal ? width : height) - (barCutMode ? 0 : 2);
			}
			/* Clear old bar */
			pScreen->drawRectangle(x, y, width, height, true, color->back.ARGB, cornerRounded ? -1 : 0);
			ui oldBarWidth = orientation == horizontal ? height : width;
			si oldBarLocationY = y + (orientation == horizontal ? 1 : 2);
			si oldBarLocationX = x + (orientation == horizontal ? 2 : 1);
			ui newBarWidth = orientation == horizontal ? height : width;
			si newBarLocationY = y + (orientation == horizontal ? 1 : 2);
			si newBarLocationX = x + (orientation == horizontal ? 2 : 1);

			if(oldBarWidth >= (this->barLength << 1)) {
				oldBarWidth = (this->barLength << 1) - 1;
				(orientation == horizontal ? oldBarLocationY : oldBarLocationX) += ((orientation == horizontal ? height : width) >> 1) - (oldBarWidth >> 1);
			}
			if(newBarWidth >= (barLength << 1)) {
				newBarWidth = (barLength << 1) - 1;
				(orientation == horizontal ? newBarLocationY : newBarLocationX) += ((orientation == horizontal ? height : width) >> 1) - (newBarWidth >> 1);
			}
			/*if(this->barLength) {
				pScreen->drawRectangle(oldBarLocationX, orientation == horizontal ? oldBarLocationY : oldBarLocationY + height - this->barLength - 1, orientation == horizontal ? this->barLength - 1 : oldBarWidth - 2, orientation == horizontal ? oldBarWidth - 2 : this->barLength - 1, true, color->parent.ARGB, cornerRounded ? -1 : 0);
			}*/

			/* Draw new bar */
			if(barLength) {
				if(barCutMode) {
					tRectangle barLimits = pScreen->sClipRegion;
					pScreen->sClipRegion.sXMax = x + width;
					pScreen->sClipRegion.sYMin = y;
					if(orientation == horizontal) {
						pScreen->sClipRegion.sXMax = x + barLength + 1;
					} else {
						pScreen->sClipRegion.sYMin = newBarLocationY + height - barLength - 1;
					}
					pScreen->drawRectangle(x, y, width, height, true, color->bar.ARGB, cornerRounded ? -1 : 0);
					pScreen->sClipRegion = barLimits;
				} else {
					pScreen->drawRectangle(newBarLocationX, orientation == horizontal ? newBarLocationY : newBarLocationY + height - barLength - 1, orientation == horizontal ? barLength - 1 : newBarWidth - 2, orientation == horizontal ? newBarWidth - 2 : barLength - 1, true, color->bar.ARGB, cornerRounded ? -1 : 0);
				}
			}
			pScreen->drawRectangle(x, y, width, height, false, color->border.ARGB, cornerRounded ? -1 : 0);
			this->barLength = barLength;
			if(showText == true &&  width >= ((ui)text.pFont->ucMaxWidth << 2)) {
				text.window.sXMin = x + 3;
				text.window.sXMax = x + width - 1;
				text.window.sYMin = y + 1;
				text.window.sYMax = y + height - 3;
				text.setText((const char *)(showPercentage == true ? "%d%%" : "%d"), showPercentage == true ? GUtil::Converters::toPercent(minimum, maximum, 100, value) : value);
				StringProperties_t str_properties = text.getStrProp();
				s32 x_str_location = text.window.sXMin + (width >> 1) - (str_properties.StringRowsMaxLength_Pixels >> 1);
				s32 y_str_location = text.window.sYMin + (height >> 1) - (str_properties.StringColsHeight_Pixels >> 1);
				text.visible = visible;
				text.x = x_str_location;
				text.y = y_str_location;
				text.selStart = 0;
				text.selLen = 0;
				text.foreColor = color->ink;
				text.backColor = color->parent;
				pScreen->refresh();
				text.isModifyed = true;
			}
			setIsModified(false);
			pScreen->sClipRegion = scrLimits;
		}
		/* Mandatory, bar length need to be minimum 4 characters length to display the text */
		if(visible && showText == true && width >= ((ui)text.pFont->ucMaxWidth << 2)) {
			text.idle();
		}
	}
}

