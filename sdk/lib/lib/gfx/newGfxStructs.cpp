/*
 * newGfxStructs.cpp
 *
 *  Created on: Jul 21, 2019
 *      Author: Work
 */

#include "newGfxStructs.h"
#include "include/global.h"
#include "lib/gfx/resource/fonts.h"



/***********************************************************************************/
/*                          System default GFX settings                            */
/***********************************************************************************/
const ui systemCornerRound = 8;
const ui systemScrollBtnMinSize = 20;
const Color::ARGB systemParentColor = Color::fromArgb(Color::White);
const tFont *systemFont = &g_sFontCmss14b;

/***********************************************************************************/
/*                          Buttons default GFX settings                           */
/***********************************************************************************/
const colorButton systemColorButton = {
		Color::fromArgb(Color::Gray),
		Color::fromArgb(0x989CB6),
		Color::fromArgb(0x7F7F7F),
		Color::fromArgb(Color::Gray),
		Color::fromArgb(0xa0a0a0),
		Color::fromArgb(Color::Black),
		Color::fromArgb(Color::Gray),
		Color::fromArgb(0xf0f0f0),
		Color::fromArgb(0x393939),
		Color::fromArgb(systemParentColor.ARGB)
};
const ui systemButtonWidth = 100;
const ui systemButtonHeight = 27;
const GI::textAllign systemButtonTextAllign = GI::textAllign::center;
const bool systemButtonWordWrap = false;
/***********************************************************************************/
/*                          Progress bars default GFX settings                     */
/***********************************************************************************/
const colorProgressBar systemColorProgressBar = {
		Color::fromArgb(Color::Gray),
		Color::fromArgb(Color::LightGrey),
		Color::fromArgb(Color::SeaGreen),
		Color::fromArgb(0x393939),
		Color::fromArgb(systemParentColor.ARGB)
};
const ui systemProgressBarWidth = 100;
const ui systemProgressBarHeight = 27;
/***********************************************************************************/
/*                          Check box default GFX settings                     */
/***********************************************************************************/
const colorCheckBox systemColorCheckBox = {
		Color::fromArgb(Color::Gray),
		Color::fromArgb(0x989CB6),
		Color::fromArgb(Color::DarkGray),
		Color::fromArgb(0x7F7F7F),
		Color::fromArgb(Color::Gray),
		Color::fromArgb(0xa0a0a0),
		Color::fromArgb(Color::Green),
		Color::fromArgb(0x7F7F7F),
		Color::fromArgb(Color::Gray),
		Color::fromArgb(0xf0f0f0),
		Color::fromArgb(Color::SeaGreen),
		Color::fromArgb(Color::Black),
		Color::fromArgb(systemParentColor.ARGB)
};
const ui systemCheckBoxWidth = 100;
const ui systemCheckBoxHeight = 27;
const ui systemCheckBoxSize = 15;
/***********************************************************************************/
/*                          Scroll bar default GFX settings                        */
/***********************************************************************************/
const colorScrollBar systemColorScrollBar = {
		Color::fromArgb(Color::Gray),
		Color::fromArgb(0x989CB6),
		Color::fromArgb(0x7F7F7F),
		Color::fromArgb(Color::Gray),
		Color::fromArgb(0xa0a0a0),
		Color::fromArgb(Color::Black),
		Color::fromArgb(Color::Gray),
		Color::fromArgb(0xf0f0f0),
		Color::fromArgb(0x393939),
		Color::fromArgb(0xf0f0f0),
		Color::fromArgb(systemParentColor.ARGB)
};
const ui systemScrollBarWidth = 100;
const ui systemScrollBarHeight = 27;
/***********************************************************************************/
/*                          Label default GFX settings                           */
/***********************************************************************************/
const colorLabel systemColorLabel = {
		Color::fromArgb(0x989CB6),
		Color::fromArgb(0x7F7F7F),
		Color::fromArgb(0xa0a0a0),
		Color::fromArgb(Color::Black),
		Color::fromArgb(systemParentColor.ARGB)
};
const ui systemLabelWidth = 100;
const ui systemLabelHeight = 27;
const GI::textAllign systemLabelTextAllign = GI::textAllign::left;
const bool systemLabelWordWrap = false;













