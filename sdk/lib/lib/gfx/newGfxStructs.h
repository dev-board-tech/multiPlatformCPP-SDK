/*
 * newGfxHeaders.h
 *
 *  Created on: Jul 21, 2019
 *      Author: Work
 */

#ifndef LIB_LIB_GFX_NEWGFXSTRUCTS_H_
#define LIB_LIB_GFX_NEWGFXSTRUCTS_H_

#include "include/global.h"
#include "controls_definition.h"

/***********************************************************************************/
/*                          System default GFX settings                            */
/***********************************************************************************/
extern const ui systemCornerRound;
extern const ui systemScrollBtnMinSize;
extern const tFont *systemFont;
/***********************************************************************************/
/*                          Buttons default GFX settings                           */
/***********************************************************************************/
typedef struct {
	struct {
		Color::ARGB border;
		Color::ARGB back;
		Color::ARGB ink;
	}disabled;
	struct {
		struct {
			Color::ARGB border;
			Color::ARGB back;
			Color::ARGB ink;
		}push;
		struct {
			Color::ARGB border;
			Color::ARGB back;
			Color::ARGB ink;
		}pull;
	}enabled;
	Color::ARGB parent;
}colorButton;

extern const colorButton systemColorButton;
extern const ui systemButtonWidth;
extern const ui systemButtonHeight;
extern const GI::textAllign systemButtonTextAllign;
extern const bool systemButtonWordWrap;
/***********************************************************************************/
/*                          Progress bars default GFX settings                     */
/***********************************************************************************/
typedef struct {

	Color::ARGB border;
	Color::ARGB back;
	Color::ARGB bar;
	Color::ARGB ink;
	Color::ARGB parent;
}colorProgressBar;

extern const colorProgressBar systemColorProgressBar;
extern const ui systemProgressBarWidth;
extern const ui systemProgressBarHeight;
/***********************************************************************************/
/*                          Check box default GFX settings                         */
/***********************************************************************************/
typedef struct {
	struct {
		Color::ARGB border;
		Color::ARGB back;
		Color::ARGB checkInk;
		Color::ARGB textInk;
	}disabled;
	struct {
		struct {
			Color::ARGB border;
			Color::ARGB back;
			Color::ARGB checkInk;
			Color::ARGB textInk;
		}push;
		struct {
			Color::ARGB border;
			Color::ARGB back;
			Color::ARGB checkInk;
			Color::ARGB textInk;
		}pull;
	}enabled;
	Color::ARGB parent;
}colorCheckBox;

extern const colorCheckBox systemColorCheckBox;
extern const ui systemCheckBoxWidth;
extern const ui systemCheckBoxHeight;
extern const ui systemCheckBoxSize;
/***********************************************************************************/
/*                          Scroll bar default GFX settings                        */
/***********************************************************************************/
typedef struct {
	struct {
		Color::ARGB border;
		Color::ARGB back;
		Color::ARGB ink;
	}disabled;
	struct {
		struct {
			Color::ARGB border;
			Color::ARGB back;
			Color::ARGB ink;
		}push;
		struct {
			Color::ARGB border;
			Color::ARGB back;
			Color::ARGB ink;
		}pull;
	}enabled;
	Color::ARGB back;
	Color::ARGB parent;
}colorScrollBar;

extern const colorScrollBar systemColorScrollBar;
extern const ui systemScrollBarWidth;
extern const ui systemScrollBarHeight;
/***********************************************************************************/
/*                          Label default GFX settings                           */
/***********************************************************************************/
typedef struct {
	struct {
		Color::ARGB back;
		Color::ARGB ink;
	}disabled;
	struct {
		Color::ARGB back;
		Color::ARGB ink;
	}enabled;
	Color::ARGB parent;
}colorLabel;

extern const colorLabel systemColorLabel;
extern const ui systemLabelWidth;
extern const ui systemLabelHeight;
extern const GI::textAllign systemLabelTextAllign;
extern const bool systemLabelWordWrap;


#endif /* LIB_LIB_GFX_NEWGFXSTRUCTS_H_ */
