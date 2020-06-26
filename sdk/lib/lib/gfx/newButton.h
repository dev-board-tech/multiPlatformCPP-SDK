/*
 * newButton.h
 *
 *  Created on: Jul 20, 2019
 *      Author: Work
 */

#ifndef LIB_LIB_GFX_NEWBUTTON_H_
#define LIB_LIB_GFX_NEWBUTTON_H_


#include "include/global.h"
#include <lib/gfx/newGfxStructs.h>
#include "lib/gfx/newString.h"
#include "controls_definition.h"

namespace GI {
namespace Gfx {
class button
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
    colorButton *color;
    GI::Display::Display *pScreen;
    CursorState state;
public:
    button(void *parentWindowHandler);
    button();
    button(GI::Display::Display *screenDisplay);
    ~button();
    void mouseEventCapture(tControlCommandData* controlComand);
    void idle();

    struct {
    	struct
		{
    		void* callBackData;
    		void* callBackReturnData;
    		void*(*callBack)(void*);
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
			void*(*callBack)(void*);
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
			void*(*callBack)(void*);
			bool press;
			bool getMousePressEvent() {
				bool press = this->press;
				this->press = false;
				return press;
			}
		}mousePress;
    }mouseEvents;

    void setIsModified(bool isModified) {
    	this->isModified = isModified;
    }
    bool getIsModified() {
    	return this->isModified;
    }
    void setEnable(bool enabled) {
    	if(this->enabled != enabled) {
    		this->enabled = enabled;
    		this->isModified = true;
    	}
    }
    bool getEnable() {
    	return this->enabled;
    }
    void setVisible(bool visible) {
    	if(this->visible != visible) {
    		this->visible = visible;
    		this->isModified = true;
    	}
    }
    bool getVisible() {
    	return this->visible;
    }
    void setX(si x) {
    	if(this->x != x) {
    		this->x = x;
    		this->isModified = true;
    	}
    }
    si getX() {
    	return this->x;
    }
    void setY(si y) {
    	if(this->y != y) {
    		this->y = y;
    		this->isModified = true;
    	}
    }
    si getY() {
    	return this->y;
    }
    void setWidth(ui width) {
    	if(this->width != width) {
    		this->width = width;
    		this->isModified = true;
    	}
    }
    ui getWidth() {
    	return this->width;
    }
    void setHeight(ui height) {
    	if(this->height != height) {
    		this->height = height;
    		this->isModified = true;
    	}
    }
    ui getHeight() {
    	return this->height;
    }
    void setCornerRadius(ui cornerRadius) {
    	if(this->cornerRadius != cornerRadius) {
    		this->cornerRadius = cornerRadius;
    		this->isModified = true;
    	}
    }
    ui getCornerRadius() {
    	return this->cornerRadius;
    }
    bool isEmpty() {
    	return (this->width || this->height) ? false : true;
    }
    bool equals(button *param) {
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
    void setColor(colorButton *color) {
    	if(this->color != color) {
    		this->color = color;
    		this->isModified = true;
    	}
    }
    void setScreen(GI::Display::Display *pScreen) {
    	if(this->pScreen != pScreen) {
    		this->pScreen = pScreen;
    		this->isModified = true;
    	}
    }
    void setMouseTrack(bool track) {
    	this->mouseTrack = track;
    }
    bool getMouseTrack() {
    	return this->mouseTrack;
    }

    GI::Gfx::string text = GI::Gfx::string();
};
}
}




#endif /* LIB_LIB_GFX_NEWBUTTON_H_ */
