/*
 * newScrollBar.h
 *
 *  Created on: Aug 7, 2019
 *      Author: Game
 */

#ifndef LIB_LIB_GFX_NEWSCROLLBAR_H_
#define LIB_LIB_GFX_NEWSCROLLBAR_H_



#include "include/global.h"
#include <lib/gfx/newGfxStructs.h>
#include "lib/gfx/newString.h"
#include "controls_definition.h"

namespace GI {
namespace Gfx {
class scrollBar
{
protected:
	bool isModified;
	bool enabled;
	bool visible;
	bool mouseTrack;
	si x;
	si y;
	ui width;
	ui height;
	ui cornerRadius;
	u32 itemsNumber;
	u32 value;
	ui scrollBtnMinSize;
	itemOrientation orientation;
	ui scrollPosition;
	colorScrollBar *color;
	GI::Display::Display *pScreen;
	GI::rectangle scrollBtnMargins;
	GI::rectangle LUBtnMargins;
	GI::rectangle RDBtnMargins;
	bool scrollBtnHit;
	bool ULBtnHit;
	bool RDBtnHit;

	ui scrollBtnSize;
	CursorState state;
public:
	scrollBar(void *parentWindowHandler);
	scrollBar();
	scrollBar(GI::Display::Display *screenDisplay);
	~scrollBar();
	void mouseEventCapture(tControlCommandData* controlComand);
	void idle();

	struct {
		struct
		{
			void* callBackData;
			void* callBackReturnData;
			void*(*callBack)(void*, s32);
			bool valueChanged;
			bool getValueChangedEvent() {
				bool valueChanged = this->valueChanged;
				this->valueChanged = false;
				return valueChanged;
			}
		}valueChanged;
	}events;
	void setItemsNumber(u32 itemsNumber) {
		if(this->itemsNumber != itemsNumber) {
			this->isModified = true;
			this->itemsNumber = itemsNumber;
		}
	}
	u32 getItemsNumber() {
		return this->itemsNumber;
	}
	void setValue(u32 value) {
		if(this->value != value) {
			this->isModified = true;
			this->value = value;
		}
	}
	u32 getValue() {
		return this->value;
	}

	void setScrollBtnMinSize(u32 scrollBtnMinSize) {
		if(this->scrollBtnMinSize != scrollBtnMinSize) {
			this->isModified = true;
			this->scrollBtnMinSize = scrollBtnMinSize;
		}
	}
	u32 getScrollBtnMinSize() {
		return this->value;
	}

	void setOrientation(itemOrientation orientation) {
		if(this->orientation != orientation) {
			this->isModified = true;
			this->orientation = orientation;
		}
	}
	itemOrientation getOrientation() {
		return this->orientation;
	}

	void setIsModified(bool isModified) {
		this->isModified = isModified;
	}
	bool getIsModified() {
		return this->isModified;
	}
	void setEnable(bool enabled) {
		if(this->enabled != enabled) {
			this->isModified = true;
			this->enabled = enabled;
		}
	}
	bool getEnable() {
		return this->enabled;
	}
	void setVisible(bool visible) {
		if(this->visible != visible) {
			this->isModified = true;
			this->visible = visible;
		}
	}
	bool getVisible() {
		return this->visible;
	}
	void setX(si x) {
		if(this->x != x) {
			this->isModified = true;
			this->x = x;
		}
	}
	si getX() {
		return this->x;
	}
	void setY(si y) {
		if(this->y != y) {
			this->isModified = true;
			this->y = y;
		}
	}
	si getY() {
		return this->y;
	}
	void setWidth(ui width) {
		if(this->width != width) {
			this->isModified = true;
			this->width = width;
		}
	}
	ui getWidth() {
		return this->width;
	}
	void setHeight(ui height) {
		if(this->height != height) {
			this->isModified = true;
			this->height = height;
		}
	}
	ui getHeight() {
		return this->height;
	}
	void setCornerRounded(ui cornerRadius) {
		if(this->cornerRadius != cornerRadius) {
			this->isModified = true;
			this->cornerRadius = cornerRadius;
		}
	}
	ui getCornerRounded() {
		return cornerRadius;
	}
	bool isEmpty() {
		return (this->width || this->height) ? false : true;
	}
	bool equals(scrollBar *param) {
		return (param->width == this->width && param->height == this->height) ? true : false;
	}
    void setColorDisabledBorder(Color::ARGB border) {
    	if(this->color->disabled.border.ARGB != border.ARGB) {
    		this->color->disabled.border.ARGB = border.ARGB;
    		this->isModified = true;
    	}
    }
    void setColorDisabledBack(Color::ARGB back) {
    	if(this->color->disabled.back.ARGB != back.ARGB) {
    		this->color->disabled.back.ARGB = back.ARGB;
    		this->isModified = true;
    	}
    }
    void setColorDisabledInk(Color::ARGB ink) {
    	if(this->color->disabled.ink.ARGB != ink.ARGB) {
    		this->color->disabled.ink.ARGB = ink.ARGB;
    		this->isModified = true;
    	}
    }
    void setColorEnabledPushBorder(Color::ARGB border) {
    	if(this->color->enabled.push.border.ARGB != border.ARGB) {
    		this->color->enabled.push.border.ARGB = border.ARGB;
    		this->isModified = true;
    	}
    }
    void setColorEnabledPushBack(Color::ARGB back) {
    	if(this->color->enabled.push.back.ARGB != back.ARGB) {
    		this->color->enabled.push.back.ARGB = back.ARGB;
    		this->isModified = true;
    	}
    }
    void setColorEnabledPushInk(Color::ARGB ink) {
    	if(this->color->enabled.push.ink.ARGB != ink.ARGB) {
    		this->color->enabled.push.ink.ARGB = ink.ARGB;
    		this->isModified = true;
    	}
    }
    void setColorEnabledPullBorder(Color::ARGB border) {
    	if(this->color->enabled.pull.border.ARGB != border.ARGB) {
    		this->color->enabled.pull.border.ARGB = border.ARGB;
    		this->isModified = true;
    	}
    }
    void setColorEnabledPullBack(Color::ARGB back) {
    	if(this->color->enabled.pull.back.ARGB != back.ARGB) {
    		this->color->enabled.pull.back.ARGB = back.ARGB;
    		this->isModified = true;
    	}
    }
    void setColorEnabledPullInk(Color::ARGB ink) {
    	if(this->color->enabled.pull.ink.ARGB != ink.ARGB) {
    		this->color->enabled.pull.ink.ARGB = ink.ARGB;
    		this->isModified = true;
    	}
    }
    void setColorParent(Color::ARGB back) {
    	if(this->color->parent.ARGB != back.ARGB) {
    		this->color->parent.ARGB = back.ARGB;
    		this->isModified = true;
    	}
    }
    void setColor(colorScrollBar *color) {
    	if(this->color != color) {
    		this->color = color;
    		this->isModified = true;
    	}
    }
	void setScreen(GI::Display::Display *pScreen) {
		if(this->pScreen != pScreen) {
			this->isModified = true;
			this->pScreen = pScreen;
		}
	}
	void setMouseTrack(bool track) {
		this->mouseTrack = track;
	}
	bool getMouseTrack() {
		return this->mouseTrack;
	}
};
}
}




#endif /* LIB_LIB_GFX_NEWSCROLLBAR_H_ */
