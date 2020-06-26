/*
 * newCheckBox.h
 *
 *  Created on: Aug 1, 2019
 *      Author: Game
 */

#ifndef LIB_LIB_GFX_NEWCHECKBOX_H_
#define LIB_LIB_GFX_NEWCHECKBOX_H_

#include "include/global.h"
#include <lib/gfx/newGfxStructs.h>
#include "lib/gfx/newString.h"
#include "controls_definition.h"

namespace GI {
namespace Gfx {
class checkBox
{
protected:
	bool isModified;
	bool enabled;
	bool visible;
	bool mouseTrack;
	bool checked;
	si x;
	si y;
	ui width;
	ui height;
	ui cornerRadius;
	ui checkBoxSize;
	colorCheckBox *color;
	GI::Display::Display *pScreen;
	CursorState state;
	GI::Gfx::string text = GI::Gfx::string();
public:
	checkBox(void *parentWindowHandler);
	checkBox();
	checkBox(GI::Display::Display *screenDisplay);
	~checkBox();
	void mouseEventCapture(tControlCommandData* controlComand);
	void idle();

	struct {
		struct
		{
			void* callBackData;
			void* callBackReturnData;
			void*(*callBack)(void*, bool);
			bool move;
			bool getMouseMoveEvent() {
				bool move = this->move;
				this->move = false;
				return move;
			}
		}mouseMove;
		struct
		{
			void* callBackData;
			void* callBackReturnData;
			void*(*callBack)(void*, bool);
			bool release;
			bool getMouseReleaseEvent() {
				bool release = this->release;
				this->release = false;
				return release;
			}
		}mouseRelease;
		struct
		{
			void* callBackData;
			void* callBackReturnData;
			void*(*callBack)(void*, bool);
			bool press;
			bool getMousePressEvent() {
				bool press = this->press;
				this->press = false;
				return press;
			}
		}mousePress;
	}mouseEvents;

	void setChecked(bool checked) {
		if(this->checked != checked) {
			this->isModified = true;
			this->checked = checked;
		}
	}
	s32 getChecked() {
		return this->checked;
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
	void setCornerRadius(ui cornerRadius) {
		if(this->cornerRadius != cornerRadius) {
			this->isModified = true;
			this->cornerRadius = cornerRadius;
		}
	}
	ui getCornerRounded() {
		return cornerRadius;
	}
	void setCheckBoxSize(bool checkBoxSize) {
		if(this->checkBoxSize != checkBoxSize) {
			this->isModified = true;
			this->checkBoxSize = checkBoxSize;
		}
	}
	bool getCheckBoxSize() {
		return checkBoxSize;
	}
	bool isEmpty() {
		return (this->width || this->height) ? false : true;
	}
	bool equals(checkBox *param) {
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
    void setColorDisabledCheckInk(Color::ARGB ink) {
    	if(this->color->disabled.checkInk.ARGB != ink.ARGB) {
    		this->color->disabled.checkInk.ARGB = ink.ARGB;
    		this->isModified = true;
    	}
    }
    void setColorDisabledTextInk(Color::ARGB ink) {
    	if(this->color->disabled.textInk.ARGB != ink.ARGB) {
    		this->color->disabled.textInk.ARGB = ink.ARGB;
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
    void setColorEnabledPushCheckInk(Color::ARGB ink) {
    	if(this->color->enabled.push.checkInk.ARGB != ink.ARGB) {
    		this->color->enabled.push.checkInk.ARGB = ink.ARGB;
    		this->isModified = true;
    	}
    }
    void setColorEnabledPushInk(Color::ARGB ink) {
    	if(this->color->enabled.push.textInk.ARGB != ink.ARGB) {
    		this->color->enabled.push.textInk.ARGB = ink.ARGB;
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
    void setColorEnabledPullCheckInk(Color::ARGB ink) {
    	if(this->color->enabled.pull.checkInk.ARGB != ink.ARGB) {
    		this->color->enabled.pull.checkInk.ARGB = ink.ARGB;
    		this->isModified = true;
    	}
    }
    void setColorEnabledPullInk(Color::ARGB ink) {
    	if(this->color->enabled.pull.textInk.ARGB != ink.ARGB) {
    		this->color->enabled.pull.textInk.ARGB = ink.ARGB;
    		this->isModified = true;
    	}
    }
    void setColorParent(Color::ARGB back) {
    	if(this->color->parent.ARGB != back.ARGB) {
    		this->color->parent.ARGB = back.ARGB;
    		this->isModified = true;
    	}
    }
	void setColor(colorCheckBox *color) {
		if(this->color != color) {
			this->isModified = true;
			this->color = color;
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



#endif /* LIB_LIB_GFX_NEWCHECKBOX_H_ */
