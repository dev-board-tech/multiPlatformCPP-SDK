/*
 * newScrollBar.cpp
 *
 *  Created on: Aug 7, 2019
 *      Author: Game
 */

#include "newScrollBar.h"
#include "newGfxUtil.h"
#include "lib/util/converters.h"
#include "api/init.h"


GI::Gfx::scrollBar::scrollBar(void *parentWindowHandler)
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

GI::Gfx::scrollBar::scrollBar() :
		isModified(true), enabled(true), visible(true), mouseTrack(false),
		x(10), y(10), width(systemScrollBarWidth), height(systemScrollBarHeight),cornerRadius(systemCornerRound),
		itemsNumber(500), value(0),
		scrollBtnMinSize(systemScrollBtnMinSize), orientation(horizontal), scrollPosition(0),
		color((colorScrollBar *)&systemColorScrollBar), pScreen(dev.SCREEN[0]),
		scrollBtnHit(false), ULBtnHit(false), RDBtnHit(false),
		scrollBtnSize(5), state(mouseNop)
{
	if(!this) {
		return;
	}
	if(!pScreen) {
		return;
	}
}

GI::Gfx::scrollBar::scrollBar(GI::Display::Display *pScreen) :
		isModified(true), enabled(true), visible(true), mouseTrack(false),
		x(10), y(10), width(systemScrollBarWidth), height(systemScrollBarHeight),cornerRadius(systemCornerRound),
		itemsNumber(500), value(0),
		scrollBtnMinSize(systemScrollBtnMinSize), orientation(horizontal), scrollPosition(0),
		color((colorScrollBar *)&systemColorScrollBar), pScreen(pScreen),
		scrollBtnHit(false), ULBtnHit(false), RDBtnHit(false),
		scrollBtnSize(5), state(mouseNop)
{
	if(!this) {
		return;
	}
	if(!pScreen) {
		return;
	}
}

GI::Gfx::scrollBar::~scrollBar()
{
	if(!this) {
		return;
	}
}

void GI::Gfx::scrollBar::mouseEventCapture(tControlCommandData* controlComand)
{
	u32 value = this->value;
	ui scrollPosition = this->scrollPosition;
	if(this->enabled && this->visible) {
		bool scrollBtnHit = GI::insideBox(scrollBtnMargins.Position.X, scrollBtnMargins.Position.Y, scrollBtnMargins.Size.X, scrollBtnMargins.Size.Y, controlComand->X, controlComand->Y);
		bool ULBtnHit = GI::insideBox(LUBtnMargins.Position.X, LUBtnMargins.Position.Y, LUBtnMargins.Size.X, LUBtnMargins.Size.Y, controlComand->X, controlComand->Y);
		bool RDBtnHit = GI::insideBox(RDBtnMargins.Position.X, RDBtnMargins.Position.Y, RDBtnMargins.Size.X, RDBtnMargins.Size.Y, controlComand->X, controlComand->Y);

		if((scrollBtnHit || ULBtnHit || RDBtnHit) && (CursorState)controlComand->Cursor == mousePress) {
			this->scrollBtnHit = scrollBtnHit;
			this->ULBtnHit = ULBtnHit;
			this->RDBtnHit = RDBtnHit;
			state = mousePress;
			setIsModified(true);
		}
		else if(state == mousePress) {
			state = mouseMove;
		}
		else if(state == mouseMove && ((CursorState)controlComand->Cursor == mouseRelease || (CursorState)controlComand->Cursor == mouseNop)) {
			this->scrollBtnHit = false;
			this->ULBtnHit = false;
			this->RDBtnHit = false;
			state = mouseRelease;
			setIsModified(true);
		}
		else if(state == mouseRelease) {
			state = mouseNop;
		}
		if((CursorState)controlComand->Cursor == mousePress || (CursorState)controlComand->Cursor == mouseMove) {
			/* Convert cursor coordinates to value */
			ui scrollBtnSpace = (orientation == horizontal ? width - (height << 1): height - (width << 1));
			if(this->scrollBtnHit && this->enabled && this->visible) {
				scrollPosition = GUtil::Converters::toPercent((s32)((orientation == horizontal ? x + height : y + width) + (scrollBtnSize >> 1)), (s32)(((orientation == horizontal ? x + height : y + width) + scrollBtnSpace) - (scrollBtnSize >> 1)), (s32)(scrollBtnSpace - scrollBtnSize), (s32)(orientation == horizontal ? controlComand->X : controlComand->Y));
				value = GUtil::Converters::percentTo((s32)0, (s32)itemsNumber,  (s32)(scrollBtnSpace - scrollBtnSize), (s32)scrollPosition);
			}
			else if (this->ULBtnHit && value > 0) {
				value -= 1;
			}
			else if(this->RDBtnHit && value < itemsNumber) {
				value += 1;
			}
			scrollPosition = GUtil::Converters::percentTo((s32)0, (s32)(scrollBtnSpace - this->scrollBtnSize), (s32)itemsNumber, (s32)value);
			if(this->scrollPosition != scrollPosition) {
				this->scrollPosition = scrollPosition;
				isModified = true;
			}
		}
	}
	if(value != this->value) {
		events.valueChanged.valueChanged = true;
		if(events.valueChanged.callBack) {
			events.valueChanged.callBackReturnData = events.valueChanged.callBack(events.valueChanged.callBackData, value);
		}
	}
	this->value = value;
}

void GI::Gfx::scrollBar::idle()
{
	if(visible) {
		if(isModified) {
			this->scrollBtnMargins = {(si)(x + (orientation == horizontal ? height : 0)), (si)(y + (orientation == horizontal ? 0 : width)), (si)(orientation == horizontal ? width - (height << 1) : width), (si)(orientation == horizontal ? height : height - (width << 1)) };
			this->LUBtnMargins = {(si)x, (si)y, (si)(orientation == horizontal ? height : width), (si)(orientation == horizontal ? height : width) };
			this->RDBtnMargins = {(si)(x + (orientation == horizontal ? width - height : 0)), (si)(y + (orientation == horizontal ? 0 : height - width)), (si)(orientation == horizontal ? height : width), (si)(orientation == horizontal ? height : width) };
			tRectangle scrLimits = pScreen->sClipRegion;
			pScreen->sClipRegion.sXMin = x;
			pScreen->sClipRegion.sXMax = x + width;
			pScreen->sClipRegion.sYMin = y;
			pScreen->sClipRegion.sYMax = y + height;

			ui scrollBtnSpace = (orientation == horizontal ? width - (height << 1) : height - (width << 1));
			/* Calculate scroll btn position */
			ui scrollPosition = GUtil::Converters::percentTo((s32)0, (s32)(scrollBtnSpace - this->scrollBtnSize), (s32)itemsNumber, (s32)value);
			/* Calculate scroll btn size */
			scrollBtnSize = ((scrollBtnSpace << 16) / (itemsNumber) * scrollBtnSpace) >> 16;
			if(scrollBtnSize > scrollBtnSpace) {
				scrollBtnSize = scrollBtnSpace;
			}
			if(scrollBtnSize < scrollBtnMinSize) {
				scrollBtnSize = scrollBtnMinSize;
			}
			pScreen->drawRectangle(x, y, width, height, true, color->back.ARGB, cornerRadius);
			pScreen->drawRectangle(x, y, width, height, false, color->back.ARGB, cornerRadius);
			if(enabled) {
				pScreen->drawRectangle(x + (orientation == horizontal ? scrollPosition + height : 0), y + (orientation == horizontal ? 0 : scrollPosition + width), (orientation == horizontal ? scrollBtnSize : width), (orientation == horizontal ? height : scrollBtnSize), true, ((state == mousePress || state == mouseMove) && scrollBtnHit) ? color->enabled.push.back.ARGB : color->enabled.pull.back.ARGB, cornerRadius);
				pScreen->drawRectangle(x + (orientation == horizontal ? scrollPosition + height : 0), y + (orientation == horizontal ? 0 : scrollPosition + width), (orientation == horizontal ? scrollBtnSize : width), (orientation == horizontal ? height : scrollBtnSize), false, ((state == mousePress || state == mouseMove) && scrollBtnHit) ? color->enabled.push.border.ARGB : color->enabled.pull.border.ARGB, cornerRadius);
				pScreen->drawRectangle(LUBtnMargins.Position.X, LUBtnMargins.Position.Y, LUBtnMargins.Size.X, LUBtnMargins.Size.Y, true, ((state == mousePress || state == mouseMove) && ULBtnHit) ? color->enabled.push.back.ARGB : color->enabled.pull.back.ARGB, cornerRadius);
				pScreen->drawRectangle(LUBtnMargins.Position.X, LUBtnMargins.Position.Y, LUBtnMargins.Size.X, LUBtnMargins.Size.Y, false, ((state == mousePress || state == mouseMove) && ULBtnHit) ? color->enabled.push.border.ARGB : color->enabled.pull.border.ARGB, cornerRadius);
				pScreen->drawRectangle(RDBtnMargins.Position.X, RDBtnMargins.Position.Y, RDBtnMargins.Size.X, RDBtnMargins.Size.Y, true, ((state == mousePress || state == mouseMove) && RDBtnHit) ? color->enabled.push.back.ARGB : color->enabled.pull.back.ARGB, cornerRadius);
				pScreen->drawRectangle(RDBtnMargins.Position.X, RDBtnMargins.Position.Y, RDBtnMargins.Size.X, RDBtnMargins.Size.Y, false, ((state == mousePress || state == mouseMove) && RDBtnHit) ? color->enabled.push.border.ARGB : color->enabled.pull.border.ARGB, cornerRadius);
				if(orientation == horizontal) {
					pScreen->drawTriangle(x + (height >> 2), y + (height >> 1), x + (height >> 2) + (height >> 1), y + (height >> 2), x + (height >> 2) + (height >> 1), y + (height >> 2) + (height >> 1), false, ((state == mousePress || state == mouseMove) && RDBtnHit) ? color->enabled.push.ink.ARGB : color->enabled.pull.ink.ARGB);
					pScreen->drawTriangle((x + width) - (height >> 2), y +  (height >> 1), (x + width) - ((height >> 2) + (height >> 1)), y + (height >> 2), (x + width) - ((height >> 2) + (height >> 1)), y + (height >> 2) + (height >> 1), false, ((state == mousePress || state == mouseMove) && RDBtnHit) ? color->enabled.push.ink.ARGB : color->enabled.pull.ink.ARGB);
				} else {
					pScreen->drawTriangle(x + (width >> 1), y + (width >> 2), x + (width >> 2), y + (width >> 2) + (width >> 1), x + (width >> 2) + (width >> 1), y + (width >> 2) + (width >> 1), false, ((state == mousePress || state == mouseMove) && RDBtnHit) ? color->enabled.push.ink.ARGB : color->enabled.pull.ink.ARGB);
					pScreen->drawTriangle(x + (width >> 1), (y + height) - (width >> 2), x + (width >> 2), (y + height) - ((width >> 2) + (width >> 1)), x + (width >> 2) + (width >> 1), (y + height) - ((width >> 2) + (width >> 1)), false, ((state == mousePress || state == mouseMove) && RDBtnHit) ? color->enabled.push.ink.ARGB : color->enabled.pull.ink.ARGB);
				}
			}
			else {
				pScreen->drawRectangle(x + (orientation == horizontal ? scrollPosition + height : 0), y + (orientation == horizontal ? 0 : scrollPosition + width), (orientation == horizontal ? scrollBtnSize : width), (orientation == horizontal ? height : scrollBtnSize), true, color->disabled.back.ARGB, cornerRadius);
				pScreen->drawRectangle(x + (orientation == horizontal ? scrollPosition + height : 0), y + (orientation == horizontal ? 0 : scrollPosition + width), (orientation == horizontal ? scrollBtnSize : width), (orientation == horizontal ? height : scrollBtnSize), false, color->disabled.border.ARGB, cornerRadius);
				pScreen->drawRectangle(LUBtnMargins.Position.X, LUBtnMargins.Position.Y, LUBtnMargins.Size.X, LUBtnMargins.Size.Y, true, color->disabled.back.ARGB, cornerRadius);
				pScreen->drawRectangle(LUBtnMargins.Position.X, LUBtnMargins.Position.Y, LUBtnMargins.Size.X, LUBtnMargins.Size.Y, false, color->disabled.border.ARGB, cornerRadius);
				pScreen->drawRectangle(RDBtnMargins.Position.X, RDBtnMargins.Position.Y, RDBtnMargins.Size.X, RDBtnMargins.Size.Y, true, color->disabled.back.ARGB, cornerRadius);
				pScreen->drawRectangle(RDBtnMargins.Position.X, RDBtnMargins.Position.Y, RDBtnMargins.Size.X, RDBtnMargins.Size.Y, false, color->disabled.border.ARGB, cornerRadius);
				if(orientation == horizontal) {
					pScreen->drawTriangle(x + (height >> 2), y + (height >> 1), x + (height >> 2) + (height >> 1), y + (height >> 2), x + (height >> 2) + (height >> 1), y + (height >> 2) + (height >> 1), false, ((state == mousePress || state == mouseMove) && RDBtnHit) ? color->disabled.ink.ARGB : color->disabled.ink.ARGB);
					pScreen->drawTriangle((x + width) - (height >> 2), y +  (height >> 1), (x + width) - ((height >> 2) + (height >> 1)), y + (height >> 2), (x + width) - ((height >> 2) + (height >> 1)), y + (height >> 2) + (height >> 1), false, ((state == mousePress || state == mouseMove) && RDBtnHit) ? color->disabled.ink.ARGB : color->disabled.ink.ARGB);
				} else {
					pScreen->drawTriangle(x + (width >> 1), y + (width >> 2), x + (width >> 2), y + (width >> 2) + (width >> 1), x + (width >> 2) + (width >> 1), y + (width >> 2) + (width >> 1), false, ((state == mousePress || state == mouseMove) && RDBtnHit) ? color->enabled.push.ink.ARGB : color->disabled.ink.ARGB);
					pScreen->drawTriangle(x + (width >> 1), (y + height) - (width >> 2), x + (width >> 2), (y + height) - ((width >> 2) + (width >> 1)), x + (width >> 2) + (width >> 1), (y + height) - ((width >> 2) + (width >> 1)), false, ((state == mousePress || state == mouseMove) && RDBtnHit) ? color->disabled.ink.ARGB : color->disabled.ink.ARGB);
				}
			}

			this->scrollBtnSize = scrollBtnSize;
			setIsModified(false);
			pScreen->sClipRegion = scrLimits;
		}
	}
}
