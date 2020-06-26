/*
 * lps25hb.h
 *
 *  Created on: Jan 21, 2018
 *      Author: Work
 */

#ifndef LIB_DEVICE_LPS25HB_H_
#define LIB_DEVICE_LPS25HB_H_

#include <include/global.h>
#include <api/io_handle.h>
#include "common.h"

#define LPS25HB_I2CADDR			0x5C
/*#####################################################*/
#define LPS25HB_REF_P_XL		0x08
#define LPS25HB_REF_P_L			0x09
#define LPS25HB_REF_P_H			0x0A
#define LPS25HB_WHO_AM_I		0x0F
#define LPS25HB_RES_CONF		0x10
#define LPS25HB_CTRL_REG1		0x20
#define LPS25HB_CTRL_REG2		0x21
#define LPS25HB_CTRL_REG3		0x22
#define LPS25HB_CTRL_REG4		0x23
#define LPS25HB_INTERRUPT_CFG	0x24
#define LPS25HB_INT_SOURCE		0x25
#define LPS25HB_STATUS_REG		0x27
#define LPS25HB_PRESS_OUT_XL	0x28
#define LPS25HB_PRESS_OUT_L		0x29
#define LPS25HB_PRESS_OUT_H		0x2A
#define LPS25HB_TEMP_OUT_L		0x2B
#define LPS25HB_TEMP_OUT_H		0x2C
#define LPS25HB_FIFO_CTRL		0x2E
#define LPS25HB_FIFO_STATUS		0x2F
#define LPS25HB_THS_P_L			0x30
#define LPS25HB_THS_P_H			0x31
#define LPS25HB_RPDS_L			0x39
#define LPS25HB_RPDS_H			0x3A
/*#####################################################*/
namespace GI {
namespace Device {
namespace Sensor {
class Lps25hb
{
public:
	Lps25hb(char *hwPath, unsigned char sa);
	~Lps25hb();
	SysErr probe();

	enum temp_avarage_e {
		LPS25HB_TEMP_AVARAGE_MASK = 0x0C,
		LPS25HB_TEMP_AVARAGE_8 = 0x00,
		LPS25HB_TEMP_AVARAGE_16 = 0x01,
		LPS25HB_TEMP_AVARAGE_32 = 0x02,
		LPS25HB_TEMP_AVARAGE_64 = 0x03,
	};

	enum press_avarage_e {
		LPS25HB_PRESS_AVARAGE_MASK = 0x03,
		PWR_DOWN = 0x00,
		LPS25HB_PRESS_AVARAGE_16 = 0x01,
		LPS25HB_PRESS_AVARAGE_32 = 0x02,
		LPS25HB_PRESS_AVARAGE_64 = 0x03,
	};

	enum power_down_e {
		LPS25HB_PWR_DOWN_MASK = 0x80,
		LPS25HB_PWR_DOWN_TRUE = 0x00,
		LPS25HB_PWR_DOWN_FALSE = 0x01,
	};

	enum data_rate_e {
		LPS25HB_ODR_MASK = 0x70,
		LPS25HB_ODR_ONE_SHOT = 0x00,
		LPS25HB_ODR_1HZ = 0x01,
		LPS25HB_ODR_7HZ = 0x02,
		LPS25HB_ODR_12_5HZ = 0x03,
		LPS25HB_ODR_25HZ = 0x04,
	};

	enum update_mode_e {
		LPS25HB_UPDATE_MODE_MASK = 0x04,
		LPS25HB_UPDATE_MODE_CONTINUOUS = 0x00,
		LPS25HB_UPDATE_MODE_AFTER_READ = 0x01,
	};



	SysErr getRefPress(signed long *ref_press);
	SysErr setRefPress(signed long ref_press);
	SysErr setTempAvarage(GI::Device::Sensor::Lps25hb::temp_avarage_e temp_avarage);
	SysErr setPressAvarage(GI::Device::Sensor::Lps25hb::press_avarage_e press_avarage);
	SysErr setPowerDown(GI::Device::Sensor::Lps25hb::power_down_e power_down);
	SysErr setDataRate(GI::Device::Sensor::Lps25hb::data_rate_e data_rate);
	SysErr setUpdateMode(GI::Device::Sensor::Lps25hb::update_mode_e update_mode);
	SysErr startOneShot();
	SysErr getTempDataReady(bool *status);
	SysErr getPressDataReady(bool *status);
	SysErr readTemp(float *temperature);
	SysErr readPress(float *pressure);
	unsigned char sa;
	bool busy;
	GI::IO *hwIo;
	SysErr err;
};
}
}
}

/*#####################################################*/
#ifdef USE_VISUAL_STUDIO
#include "lsm9ds1.cpp"
#endif
/*#####################################################*/
#endif /* LIB_DEVICE_LPS25HB_H_ */
