/*
 * app/sys/util.h
 */

#ifndef LIB_APP_SYS_UTIL_H_
#define LIB_APP_SYS_UTIL_H_

#include <include/global.h>
#include <lib/string.h>

namespace Sys{
class Util {
public:
	static SysErr strToCmd(GI::string *inStr, GI::stringArray **result);
};
}

/*#####################################################*/
#ifdef USE_VISUAL_STUDIO
#include "util.cpp"
#endif
/*#####################################################*/

#endif /* LIB_APP_SYS_UTIL_H_ */
