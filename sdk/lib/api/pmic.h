#ifndef TOUCHSCREEN_DEF_H_
#define TOUCHSCREEN_DEF_H_
/*#####################################################*/

#include <include/global.h>
#include <api/io_handle.h>
#include "common.h"

namespace GI {
namespace Sys {
class Pmic {
public:
    SysErr readRegs(unsigned char WriteAddr, unsigned char *pBuffer, unsigned char NumByteToWrite);
    SysErr writeRegs(unsigned char ReadAddr, unsigned char *pBuffer, unsigned char NumByteToRead);
    SysErr wled_enable();
    SysErr wled_level( unsigned char level);
   GI::IO *hwIo;

private:

};
}
}

/*#####################################################*/
#endif /* TOUCHSCREEN_DEF_H_ */
