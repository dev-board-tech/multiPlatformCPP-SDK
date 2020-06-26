/*
 *  include/global.h
 */

#ifndef LIB_API_GLOBAL_DEF_HPP_
#define LIB_API_GLOBAL_DEF_HPP_

#include <lib/gfx/gfxdef.h>

/*
 * Sys errors definitions.
 */
typedef enum {
	SYS_ERR_OK 						=   0,
	SYS_ERR_UNKNOWN					=  -1,
	SYS_ERR_INVALID_HANDLER			=  -2,
	SYS_ERR_OUT_OF_MEMORY			=  -3,
	SYS_ERR_OUT_OF_RANGE			=  -4,
	SYS_ERR_INVALID_COMMAND			=  -5,
	SYS_ERR_INVALID_PARAM			=  -6,
	SYS_ERR_INIT					=  -7,
	SYS_ERR_NOT_IMPLEMENTED			=  -8,
	SYS_ERR_NOT_INITIALIZED			=  -9,
	SYS_ERR_NO_PATH					= -10,
	SYS_ERR_INVALID_PATH			= -11,
	SYS_ERR_NOT_ACTIVE				= -12,
	SYS_ERR_NAK						= -13,
	SYS_ERR_BUSY					= -14,
	SYS_ERR_WRITE					= -15,
	SYS_ERR_READ					= -16,
	SYS_ERR_NO_REGISTERED_DEVICE	= -17,
	SYS_ERR_BUFF_NOT_ALLOCATED		= -18,
	SYS_ERR_BUS						= -19,
	SYS_ERR_NO_ASSIGNED_DEVICE		= -20,
	SYS_ERR_DEVICE_NOT_MATCH		= -21,
	SYS_ERR_DEVICE_NOT_FOUND		= -22,
	SYS_ERR_TIMEOUT					= -23,
	SYS_ERR_NOTHING_CHANGED			= -24,
    SYS_ERR_NOT_RECEIVED            = -25,
    SYS_ERR_TRANSMISSION            = -26,
    SYS_ERR_RECEPTION               = -27,
    SYS_ERR_TOO_LONG                = -28,
    SYS_ERR_OUT_OF_PAGE				= -29,
    SYS_ERR_INVALID_SIZE			= -30,
	SYS_ERR_INVALID_DEVICE			= -31,
	SYS_ERR_DATA_NOT_READY			= -32,
}SysErr;

typedef enum {
    size1 = 0,
    size2,
    size4,
    size8,
    size16,
    size32,
    size64,
    size128,
    size256,
    size512,
    size1024,
    size2048,
    size4096,
    size8192,
    size16384,
    size32768,
    size65536,
    size131072,
    size262144,
    size524288,
    size1048576,
    size2097152,
    size4194304,
    size8388608,
    size16777216,
}Sizes;

/*
 * Int definitions.
 */

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned long u32;
typedef signed long s32;
typedef unsigned int ui;
typedef signed int si;
typedef unsigned long long u64;
typedef signed long long s64;
typedef float ff;
typedef double dd;

//typedef char* string;

/*
 * Graphic definitions.
 */

namespace GI {
typedef enum {
	center,
	left,
	right
}textAllign;
};

namespace GI {
typedef enum {
	horizontal,
	vertical,
}itemOrientation;
};

#define COLOR_CONVERSION_32_TO_16(COLOR_32) \
(unsigned short)(((((unsigned long)COLOR_32 >> 19) & 0x1F) << 11) | (((COLOR_32 >> 10) & 0x3F) << 5) | ((COLOR_32 >> 3) & 0x1F))

namespace GI {
typedef struct {
    struct {
        si X;
        si Y;
    }Position;
    struct {
        ui X;
        ui Y;
    }Size;
}rectangle;
	static bool insideBox(s32 positionX, s32 positionY, s32 sizeX, s32 sizeY, s32 x, s32 y) {
		if (positionX <= x && positionX + sizeX >= x && positionY <= y && positionY + sizeY >= y)
			return true;
		else
			return false;
	}
};

class Color {
public:
	enum {
#if (__SIZEOF_INT__ == 4)
		AliceBlue            = 0x00F0F8FF,
		AntiqueWhite         = 0x00FAEBD7,
		Aqua                 = 0x0000FFFF,
		Aquamarine           = 0x007FFFD4,
		Azure                = 0x00F0FFFF,
		Beige                = 0x00F5F5DC,
		Bisque               = 0x00FFE4C4,
		Black                = 0x00000000,
		BlanchedAlmond       = 0x00FFEBCD,
		Blue                 = 0x000000FF,
		BlueViolet           = 0x008A2BE2,
		Brown                = 0x00A52A2A,
		BurlyWood            = 0x00DEB887,
		CadetBlue            = 0x005F9EA0,
		Chartreuse           = 0x007FFF00,
		Chocolate            = 0x00D2691E,
		Coral                = 0x00FF7F50,
		CornflowerBlue       = 0x006495ED,
		Cornsilk             = 0x00FFF8DC,
		Crimson              = 0x00DC143C,
		Cyan                 = 0x0000FFFF,
		DarkBlue             = 0x0000008B,
		DarkCyan             = 0x00008B8B,
		DarkGoldenrod        = 0x00B8860B,
		DarkGray             = 0x00A9A9A9,
		DarkGreen            = 0x00006400,
		DarkKhaki            = 0x00BDB76B,
		DarkMagenta          = 0x008B008B,
		DarkOliveGreen       = 0x00556B2F,
		DarkOrange           = 0x00FF8C00,
		DarkOrchid           = 0x009932CC,
		DarkRed              = 0x008B0000,
		DarkSalmon           = 0x00E9967A,
		DarkSeaGreen         = 0x008FBC8F,
		DarkSlateBlue        = 0x00483D8B,
		DarkSlateGray        = 0x002F4F4F,
		DarkTurquoise        = 0x0000CED1,
		DarkViolet           = 0x009400D3,
		DeepPink             = 0x00FF1493,
		DeepSkyBlue          = 0x0000BFFF,
		DimGray              = 0x00696969,
		DodgerBlue           = 0x001E90FF,
		FireBrick            = 0x00B22222,
		FloralWhite          = 0x00FFFAF0,
		ForestGreen          = 0x00228B22,
		Fuchsia              = 0x00FF00FF,
		Gainsboro            = 0x00DCDCDC,
		GhostWhite           = 0x00F8F8FF,
		Gold                 = 0x00FFD700,
		Goldenrod            = 0x00DAA520,
		Gray                 = 0x00808080,
		Green                = 0x00008000,
		GreenYellow          = 0x00ADFF2F,
		Honeydew             = 0x00F0FFF0,
		HotPink              = 0x00FF69B4,
		IndianRed            = 0x00CD5C5C,
		Indigo               = 0x004B0082,
		Ivory                = 0x00FFFFF0,
		Khaki                = 0x00F0E68C,
		Lavender             = 0x00E6E6FA,
		LavenderBlush        = 0x00FFF0F5,
		LawnGreen            = 0x007CFC00,
		LemonChiffon         = 0x00FFFACD,
		LightBlue            = 0x00ADD8E6,
		LightCoral           = 0x00F08080,
		LightCyan            = 0x00E0FFFF,
		LightGoldenrodYellow = 0x00FAFAD2,
		LightGreen           = 0x0090EE90,
		LightGrey            = 0x00D3D3D3,
		LightPink            = 0x00FFB6C1,
		LightSalmon          = 0x00FFA07A,
		LightSeaGreen        = 0x0020B2AA,
		LightSkyBlue         = 0x0087CEFA,
		LightSlateGray       = 0x00778899,
		LightSteelBlue       = 0x00B0C4DE,
		LightYellow          = 0x00FFFFE0,
		Lime                 = 0x0000FF00,
		LimeGreen            = 0x0032CD32,
		Linen                = 0x00FAF0E6,
		Magenta              = 0x00FF00FF,
		Maroon               = 0x00800000,
		MediumAquamarine     = 0x0066CDAA,
		MediumBlue           = 0x000000CD,
		MediumOrchid         = 0x00BA55D3,
		MediumPurple         = 0x009370DB,
		MediumSeaGreen       = 0x003CB371,
		MediumSlateBlue      = 0x007B68EE,
		MediumSpringGreen    = 0x0000FA9A,
		MediumTurquoise      = 0x0048D1CC,
		MediumVioletRed      = 0x00C71585,
		MidnightBlue         = 0x00191970,
		MintCream            = 0x00F5FFFA,
		MistyRose            = 0x00FFE4E1,
		Moccasin             = 0x00FFE4B5,
		NavajoWhite          = 0x00FFDEAD,
		Navy                 = 0x00000080,
		OldLace              = 0x00FDF5E6,
		Olive                = 0x00808000,
		OliveDrab            = 0x006B8E23,
		Orange               = 0x00FFA500,
		OrangeRed            = 0x00FF4500,
		Orchid               = 0x00DA70D6,
		PaleGoldenrod        = 0x00EEE8AA,
		PaleGreen            = 0x0098FB98,
		PaleTurquoise        = 0x00AFEEEE,
		PaleVioletRed        = 0x00DB7093,
		PapayaWhip           = 0x00FFEFD5,
		PeachPuff            = 0x00FFDAB9,
		Peru                 = 0x00CD853F,
		Pink                 = 0x00FFC0CB,
		Plum                 = 0x00DDA0DD,
		PowderBlue           = 0x00B0E0E6,
		Purple               = 0x00800080,
		Red                  = 0x00FF0000,
		RosyBrown            = 0x00BC8F8F,
		RoyalBlue            = 0x004169E1,
		SaddleBrown          = 0x008B4513,
		Salmon               = 0x00FA8072,
		SandyBrown           = 0x00F4A460,
		SeaGreen             = 0x002E8B57,
		Seashell             = 0x00FFF5EE,
		Sienna               = 0x00A0522D,
		Silver               = 0x00C0C0C0,
		SkyBlue              = 0x0087CEEB,
		SlateBlue            = 0x006A5ACD,
		SlateGray            = 0x00708090,
		Snow                 = 0x00FFFAFA,
		SpringGreen          = 0x0000FF7F,
		SteelBlue            = 0x004682B4,
		Tan                  = 0x00D2B48C,
		Teal                 = 0x00008080,
		Thistle              = 0x00D8BFD8,
		Tomato               = 0x00FF6347,
		Turquoise            = 0x0040E0D0,
		Violet               = 0x00EE82EE,
		Wheat                = 0x00F5DEB3,
		White                = 0x00FFFFFF,
		WhiteSmoke           = 0x00F5F5F5,
		Yellow               = 0x00FFFF00,
		YellowGreen          = 0x009ACD32,
#else
		AliceBlue            = COLOR_CONVERSION_32_TO_16(0x00F0F8FF),
		AntiqueWhite         = COLOR_CONVERSION_32_TO_16(0x00FAEBD7),
		Aqua                 = COLOR_CONVERSION_32_TO_16(0x0000FFFF),
		Aquamarine           = COLOR_CONVERSION_32_TO_16(0x007FFFD4),
		Azure                = COLOR_CONVERSION_32_TO_16(0x00F0FFFF),
		Beige                = COLOR_CONVERSION_32_TO_16(0x00F5F5DC),
		Bisque               = COLOR_CONVERSION_32_TO_16(0x00FFE4C4),
		Black                = COLOR_CONVERSION_32_TO_16(0x00000000),
		BlanchedAlmond       = COLOR_CONVERSION_32_TO_16(0x00FFEBCD),
		Blue                 = COLOR_CONVERSION_32_TO_16(0x000000FF),
		BlueViolet           = COLOR_CONVERSION_32_TO_16(0x008A2BE2),
		Brown                = COLOR_CONVERSION_32_TO_16(0x00A52A2A),
		BurlyWood            = COLOR_CONVERSION_32_TO_16(0x00DEB887),
		CadetBlue            = COLOR_CONVERSION_32_TO_16(0x005F9EA0),
		Chartreuse           = COLOR_CONVERSION_32_TO_16(0x007FFF00),
		Chocolate            = COLOR_CONVERSION_32_TO_16(0x00D2691E),
		Coral                = COLOR_CONVERSION_32_TO_16(0x00FF7F50),
		CornflowerBlue       = COLOR_CONVERSION_32_TO_16(0x006495ED),
		Cornsilk             = COLOR_CONVERSION_32_TO_16(0x00FFF8DC),
		Crimson              = COLOR_CONVERSION_32_TO_16(0x00DC143C),
		Cyan                 = COLOR_CONVERSION_32_TO_16(0x0000FFFF),
		DarkBlue             = COLOR_CONVERSION_32_TO_16(0x0000008B),
		DarkCyan             = COLOR_CONVERSION_32_TO_16(0x00008B8B),
		DarkGoldenrod        = COLOR_CONVERSION_32_TO_16(0x00B8860B),
		DarkGray             = COLOR_CONVERSION_32_TO_16(0x00A9A9A9),
		DarkGreen            = COLOR_CONVERSION_32_TO_16(0x00006400),
		DarkKhaki            = COLOR_CONVERSION_32_TO_16(0x00BDB76B),
		DarkMagenta          = COLOR_CONVERSION_32_TO_16(0x008B008B),
		DarkOliveGreen       = COLOR_CONVERSION_32_TO_16(0x00556B2F),
		DarkOrange           = COLOR_CONVERSION_32_TO_16(0x00FF8C00),
		DarkOrchid           = COLOR_CONVERSION_32_TO_16(0x009932CC),
		DarkRed              = COLOR_CONVERSION_32_TO_16(0x008B0000),
		DarkSalmon           = COLOR_CONVERSION_32_TO_16(0x00E9967A),
		DarkSeaGreen         = COLOR_CONVERSION_32_TO_16(0x008FBC8F),
		DarkSlateBlue        = COLOR_CONVERSION_32_TO_16(0x00483D8B),
		DarkSlateGray        = COLOR_CONVERSION_32_TO_16(0x002F4F4F),
		DarkTurquoise        = COLOR_CONVERSION_32_TO_16(0x0000CED1),
		DarkViolet           = COLOR_CONVERSION_32_TO_16(0x009400D3),
		DeepPink             = COLOR_CONVERSION_32_TO_16(0x00FF1493),
		DeepSkyBlue          = COLOR_CONVERSION_32_TO_16(0x0000BFFF),
		DimGray              = COLOR_CONVERSION_32_TO_16(0x00696969),
		DodgerBlue           = COLOR_CONVERSION_32_TO_16(0x001E90FF),
		FireBrick            = COLOR_CONVERSION_32_TO_16(0x00B22222),
		FloralWhite          = COLOR_CONVERSION_32_TO_16(0x00FFFAF0),
		ForestGreen          = COLOR_CONVERSION_32_TO_16(0x00228B22),
		Fuchsia              = COLOR_CONVERSION_32_TO_16(0x00FF00FF),
		Gainsboro            = COLOR_CONVERSION_32_TO_16(0x00DCDCDC),
		GhostWhite           = COLOR_CONVERSION_32_TO_16(0x00F8F8FF),
		Gold                 = COLOR_CONVERSION_32_TO_16(0x00FFD700),
		Goldenrod            = COLOR_CONVERSION_32_TO_16(0x00DAA520),
		Gray                 = COLOR_CONVERSION_32_TO_16(0x00808080),
		Green                = COLOR_CONVERSION_32_TO_16(0x00008000),
		GreenYellow          = COLOR_CONVERSION_32_TO_16(0x00ADFF2F),
		Honeydew             = COLOR_CONVERSION_32_TO_16(0x00F0FFF0),
		HotPink              = COLOR_CONVERSION_32_TO_16(0x00FF69B4),
		IndianRed            = COLOR_CONVERSION_32_TO_16(0x00CD5C5C),
		Indigo               = COLOR_CONVERSION_32_TO_16(0x004B0082),
		Ivory                = COLOR_CONVERSION_32_TO_16(0x00FFFFF0),
		Khaki                = COLOR_CONVERSION_32_TO_16(0x00F0E68C),
		Lavender             = COLOR_CONVERSION_32_TO_16(0x00E6E6FA),
		LavenderBlush        = COLOR_CONVERSION_32_TO_16(0x00FFF0F5),
		LawnGreen            = COLOR_CONVERSION_32_TO_16(0x007CFC00),
		LemonChiffon         = COLOR_CONVERSION_32_TO_16(0x00FFFACD),
		LightBlue            = COLOR_CONVERSION_32_TO_16(0x00ADD8E6),
		LightCoral           = COLOR_CONVERSION_32_TO_16(0x00F08080),
		LightCyan            = COLOR_CONVERSION_32_TO_16(0x00E0FFFF),
		LightGoldenrodYellow = COLOR_CONVERSION_32_TO_16(0x00FAFAD2),
		LightGreen           = COLOR_CONVERSION_32_TO_16(0x0090EE90),
		LightGrey            = COLOR_CONVERSION_32_TO_16(0x00D3D3D3),
		LightPink            = COLOR_CONVERSION_32_TO_16(0x00FFB6C1),
		LightSalmon          = COLOR_CONVERSION_32_TO_16(0x00FFA07A),
		LightSeaGreen        = COLOR_CONVERSION_32_TO_16(0x0020B2AA),
		LightSkyBlue         = COLOR_CONVERSION_32_TO_16(0x0087CEFA),
		LightSlateGray       = COLOR_CONVERSION_32_TO_16(0x00778899),
		LightSteelBlue       = COLOR_CONVERSION_32_TO_16(0x00B0C4DE),
		LightYellow          = COLOR_CONVERSION_32_TO_16(0x00FFFFE0),
		Lime                 = COLOR_CONVERSION_32_TO_16(0x0000FF00),
		LimeGreen            = COLOR_CONVERSION_32_TO_16(0x0032CD32),
		Linen                = COLOR_CONVERSION_32_TO_16(0x00FAF0E6),
		Magenta              = COLOR_CONVERSION_32_TO_16(0x00FF00FF),
		Maroon               = COLOR_CONVERSION_32_TO_16(0x00800000),
		MediumAquamarine     = COLOR_CONVERSION_32_TO_16(0x0066CDAA),
		MediumBlue           = COLOR_CONVERSION_32_TO_16(0x000000CD),
		MediumOrchid         = COLOR_CONVERSION_32_TO_16(0x00BA55D3),
		MediumPurple         = COLOR_CONVERSION_32_TO_16(0x009370DB),
		MediumSeaGreen       = COLOR_CONVERSION_32_TO_16(0x003CB371),
		MediumSlateBlue      = COLOR_CONVERSION_32_TO_16(0x007B68EE),
		MediumSpringGreen    = COLOR_CONVERSION_32_TO_16(0x0000FA9A),
		MediumTurquoise      = COLOR_CONVERSION_32_TO_16(0x0048D1CC),
		MediumVioletRed      = COLOR_CONVERSION_32_TO_16(0x00C71585),
		MidnightBlue         = COLOR_CONVERSION_32_TO_16(0x00191970),
		MintCream            = COLOR_CONVERSION_32_TO_16(0x00F5FFFA),
		MistyRose            = COLOR_CONVERSION_32_TO_16(0x00FFE4E1),
		Moccasin             = COLOR_CONVERSION_32_TO_16(0x00FFE4B5),
		NavajoWhite          = COLOR_CONVERSION_32_TO_16(0x00FFDEAD),
		Navy                 = COLOR_CONVERSION_32_TO_16(0x00000080),
		OldLace              = COLOR_CONVERSION_32_TO_16(0x00FDF5E6),
		Olive                = COLOR_CONVERSION_32_TO_16(0x00808000),
		OliveDrab            = COLOR_CONVERSION_32_TO_16(0x006B8E23),
		Orange               = COLOR_CONVERSION_32_TO_16(0x00FFA500),
		OrangeRed            = COLOR_CONVERSION_32_TO_16(0x00FF4500),
		Orchid               = COLOR_CONVERSION_32_TO_16(0x00DA70D6),
		PaleGoldenrod        = COLOR_CONVERSION_32_TO_16(0x00EEE8AA),
		PaleGreen            = COLOR_CONVERSION_32_TO_16(0x0098FB98),
		PaleTurquoise        = COLOR_CONVERSION_32_TO_16(0x00AFEEEE),
		PaleVioletRed        = COLOR_CONVERSION_32_TO_16(0x00DB7093),
		PapayaWhip           = COLOR_CONVERSION_32_TO_16(0x00FFEFD5),
		PeachPuff            = COLOR_CONVERSION_32_TO_16(0x00FFDAB9),
		Peru                 = COLOR_CONVERSION_32_TO_16(0x00CD853F),
		Pink                 = COLOR_CONVERSION_32_TO_16(0x00FFC0CB),
		Plum                 = COLOR_CONVERSION_32_TO_16(0x00DDA0DD),
		PowderBlue           = COLOR_CONVERSION_32_TO_16(0x00B0E0E6),
		Purple               = COLOR_CONVERSION_32_TO_16(0x00800080),
		Red                  = COLOR_CONVERSION_32_TO_16(0x00FF0000),
		RosyBrown            = COLOR_CONVERSION_32_TO_16(0x00BC8F8F),
		RoyalBlue            = COLOR_CONVERSION_32_TO_16(0x004169E1),
		SaddleBrown          = COLOR_CONVERSION_32_TO_16(0x008B4513),
		Salmon               = COLOR_CONVERSION_32_TO_16(0x00FA8072),
		SandyBrown           = COLOR_CONVERSION_32_TO_16(0x00F4A460),
		SeaGreen             = COLOR_CONVERSION_32_TO_16(0x002E8B57),
		Seashell             = COLOR_CONVERSION_32_TO_16(0x00FFF5EE),
		Sienna               = COLOR_CONVERSION_32_TO_16(0x00A0522D),
		Silver               = COLOR_CONVERSION_32_TO_16(0x00C0C0C0),
		SkyBlue              = COLOR_CONVERSION_32_TO_16(0x0087CEEB),
		SlateBlue            = COLOR_CONVERSION_32_TO_16(0x006A5ACD),
		SlateGray            = COLOR_CONVERSION_32_TO_16(0x00708090),
		Snow                 = COLOR_CONVERSION_32_TO_16(0x00FFFAFA),
		SpringGreen          = COLOR_CONVERSION_32_TO_16(0x0000FF7F),
		SteelBlue            = COLOR_CONVERSION_32_TO_16(0x004682B4),
		Tan                  = COLOR_CONVERSION_32_TO_16(0x00D2B48C),
		Teal                 = COLOR_CONVERSION_32_TO_16(0x00008080),
		Thistle              = COLOR_CONVERSION_32_TO_16(0x00D8BFD8),
		Tomato               = COLOR_CONVERSION_32_TO_16(0x00FF6347),
		Turquoise            = COLOR_CONVERSION_32_TO_16(0x0040E0D0),
		Violet               = COLOR_CONVERSION_32_TO_16(0x00EE82EE),
		Wheat                = COLOR_CONVERSION_32_TO_16(0x00F5DEB3),
		White                = COLOR_CONVERSION_32_TO_16(0x00FFFFFF),
		WhiteSmoke           = COLOR_CONVERSION_32_TO_16(0x00F5F5F5),
		Yellow               = COLOR_CONVERSION_32_TO_16(0x00FFFF00),
		YellowGreen          = COLOR_CONVERSION_32_TO_16(0x009ACD32),
#endif
	};
	typedef union {
		struct {
			u8 R;
			u8 G;
			u8 B;
			u8 A;
		};
		u32 ARGB;
		u32 RGB;
	}ARGB;
	static Color::ARGB fromArgb(u8 red, u8 green, u8 blue, u8 alpha){
		Color::ARGB color;
		color.R = red;
		color.G = green;
		color.B = blue;
		color.A = alpha;
		return color;
	}
	static Color::ARGB fromRgb(u8 red, u8 green, u8 blue){
		Color::ARGB color;
		color.R = red;
		color.G = green;
		color.B = blue;
		color.A = 0xFF;
		return color;
	}
	static Color::ARGB fromArgb(u32 color){
		Color::ARGB _color;
		_color.R = color;
		_color.G = color >> 8;
		_color.B = color >> 16;
		_color.A = color >> 24;
		return _color;
	}
	static Color::ARGB fromRgb(u32 color){
		Color::ARGB _color;
		_color.R = color;
		_color.G = color >> 8;
		_color.B = color >> 16;
		_color.A = 0xFF;
		return _color;
	}
	static u16 to16(Color::ARGB color){
		return ((unsigned)(((color.R)>>3)&0b11111) | (((color.G)<<3)&0b11111100000) | (((color.B)<<8)&0b1111100000000000));
	}
	static u16 to16(unsigned long color){
		unsigned char R = color >> 16,G = color >> 8,B = color;
		return ((u16)(((R)>>3)&0b11111) | (((G)<<3)&0b11111100000) | (((B)<<8)&0b1111100000000000));
	}
	static u32 to32(Color::ARGB color){
		return (((u32)color.A << 24) | ((u32)color.R << 16) | ((u32)color.G << 8) | (u32)color.B);
	}
};

typedef struct charDev_s
{

} charDev;

#define UNUSED(x) (void(x))

/*#####################################################*/
#ifdef USE_VISUAL_STUDIO
#include "global_color.cpp"
#endif
/*#####################################################*/


#endif /* LIB_API_GLOBAL_DEF_HPP_ */
