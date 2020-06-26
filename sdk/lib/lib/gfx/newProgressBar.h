/*
 * newProgressBar.h
 *
 *  Created on: Jul 25, 2019
 *      Author: Work
 */

#ifndef LIB_LIB_GFX_NEWPROGRESSBAR_H_
#define LIB_LIB_GFX_NEWPROGRESSBAR_H_


#include "include/global.h"
#include <lib/gfx/newGfxStructs.h>
#include "lib/gfx/newString.h"
#include "controls_definition.h"

namespace GI {
namespace Gfx {
class progressBar
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
	bool cornerRounded;
	s32 minimum;
	s32 maximum;
	s32 value;
	itemOrientation orientation;
	bool showPercentage;
	bool showText;
	bool barCutMode;
	colorProgressBar *color;
	GI::Display::Display *pScreen;
	CursorState state;
	GI::Gfx::string text = GI::Gfx::string();
	ui barLength;
public:
	progressBar(void *parentWindowHandler);
	progressBar();
	progressBar(GI::Display::Display *screenDisplay);
	~progressBar();
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
	struct {
		struct
		{
			void* callBackData;
			void* callBackReturnData;
			void*(*callBack)(void*, s32);
			bool move;
			bool getValueChangedEvent() {
				bool move = this->move;
				this->move = false;
				return move;
			}
		}valueChanged;
		struct
		{
			void* callBackData;
			void* callBackReturnData;
			void*(*callBack)(void*, s32);
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
			void*(*callBack)(void*, s32);
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
			void*(*callBack)(void*, s32);
			bool press;
			bool getMousePressEvent() {
				bool press = this->press;
				this->press = false;
				return press;
			}
		}mousePress;
	}mouseEvents;

	void setMinimum(s32 minimum) {
		if(this->minimum != minimum) {
			this->isModified = true;
			this->minimum = minimum;
		}
	}
	s32 getMinimum() {
		return this->minimum;
	}
	void setMaximum(s32 maximum) {
		if(this->maximum != maximum) {
			this->isModified = true;
			this->maximum = maximum;
		}
	}
	s32 getMaximum() {
		return this->maximum;
	}
	void setValue(s32 value) {
		if(value < minimum) {
			value = minimum;
		}
		if(value > maximum) {
			value = maximum;
		}
		if(this->value != value) {
			this->isModified = true;
			this->value = value;
		}
	}
	s32 getValue() {
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
	void setShowPercentage(bool showPercentage) {
		if(this->showPercentage != showPercentage) {
			this->isModified = true;
			this->showPercentage = showPercentage;
		}
	}
	bool getShowPercentage() {
		return this->showPercentage;
	}
	void setShowText(bool showText) {
		if(this->showText != showText) {
			this->isModified = true;
			this->showText = showText;
		}
	}
	bool getShowText() {
		return this->showText;
	}
	void setBarCut(bool barCutMode) {
		if(this->barCutMode != barCutMode) {
			this->isModified = true;
			this->barCutMode = barCutMode;
		}
	}
	bool getBarCut() {
		return this->barCutMode;
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
	void setCornerRounded(bool cornerRounded) {
		if(this->cornerRounded != cornerRounded) {
			this->isModified = true;
			this->cornerRounded = cornerRounded;
		}
	}
	bool getCornerRounded() {
		return cornerRounded;
	}
	bool isEmpty() {
		return (this->width || this->height) ? false : true;
	}
	bool equals(progressBar *param) {
		return (param->width == this->width && param->height == this->height) ? true : false;
	}
	void setColorBorder(Color::ARGB border) {
		if(this->color->border.ARGB != border.ARGB) {
			this->isModified = true;
			this->color->border.ARGB = border.ARGB;
		}
	}
	void setColorBar(Color::ARGB back) {
		if(this->color->bar.ARGB != back.ARGB) {
			this->isModified = true;
			this->color->bar.ARGB = back.ARGB;
		}
	}
	void setColorInk(Color::ARGB ink) {
		if(this->color->ink.ARGB != ink.ARGB) {
			this->isModified = true;
			this->color->ink.ARGB = ink.ARGB;
		}
	}
	void setColorParent(Color::ARGB back) {
		if(this->color->parent.ARGB != back.ARGB) {
			this->isModified = true;
			this->color->parent.ARGB = back.ARGB;
		}
	}
	void setColor(colorProgressBar *color) {
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




#endif /* LIB_LIB_GFX_NEWPROGRESSBAR_H_ */
