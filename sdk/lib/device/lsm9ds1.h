/*
 * lsm9ds1.h
 *
 *  Created on: Jan 21, 2018
 *      Author: Work
 */

#ifndef LIB_DEVICE_LSM9DS1_H_
#define LIB_DEVICE_LSM9DS1_H_

#include <include/global.h>
#include <api/io_handle.h>
#include "common.h"

#define LSM9DS1_ACCEL_GIR_I2CADDR			0x6A
#define LSM9DS1_MAG_I2CADDR					0x1C



#define LSM9DS1_ACCEL_GIR_ACT_THS			0x04
#define LSM9DS1_ACCEL_GIR_ACT_DUR			0x05
#define LSM9DS1_ACCEL_GIR_INT_GEN_CFG_XL	0x06
#define LSM9DS1_ACCEL_GIR_INT_GEN_THS_X_XL	0x07
#define LSM9DS1_ACCEL_GIR_INT_GEN_THS_Y_XL	0x08
#define LSM9DS1_ACCEL_GIR_INT_GEN_THS_Z_XL	0x09
#define LSM9DS1_ACCEL_GIR_INT_GEN_DUR_XL	0x0A
#define LSM9DS1_ACCEL_GIR_REFERENCE_G		0x0B
#define LSM9DS1_ACCEL_GIR_INT1_CTRL			0x0C
#define LSM9DS1_ACCEL_GIR_INT2_CTRL			0x0D
#define LSM9DS1_ACCEL_GIR_WHO_AM_I			0x0F
#define LSM9DS1_ACCEL_GIR_CTRL_REG1_G		0x10
#define LSM9DS1_ACCEL_GIR_CTRL_REG2_G		0x11
#define LSM9DS1_ACCEL_GIR_CTRL_REG3_G		0x12
#define LSM9DS1_ACCEL_GIR_ORIENT_CFG_G		0x13
#define LSM9DS1_ACCEL_GIR_INT_GEN_SRC_G		0x14
#define LSM9DS1_ACCEL_GIR_OUT_TEMP_L		0x15
#define LSM9DS1_ACCEL_GIR_OUT_TEMP_H		0x16
#define LSM9DS1_ACCEL_GIR_STATUS_REG		0x17
#define LSM9DS1_ACCEL_GIR_OUT_X_L_G			0x18
#define LSM9DS1_ACCEL_GIR_OUT_X_H_G			0x19
#define LSM9DS1_ACCEL_GIR_OUT_Y_L_G			0x1A
#define LSM9DS1_ACCEL_GIR_OUT_Y_H_G			0x1B
#define LSM9DS1_ACCEL_GIR_OUT_Z_L_G			0x1C
#define LSM9DS1_ACCEL_GIR_OUT_Z_H_G			0x1D
#define LSM9DS1_ACCEL_GIR_CTRL_REG4			0x1E
#define LSM9DS1_ACCEL_GIR_CTRL_REG5_XL		0x1F
#define LSM9DS1_ACCEL_GIR_CTRL_REG6_XL		0x20
#define LSM9DS1_ACCEL_GIR_CTRL_REG7_XL		0x21
#define LSM9DS1_ACCEL_GIR_CTRL_REG8			0x22
#define LSM9DS1_ACCEL_GIR_CTRL_REG9			0x23
#define LSM9DS1_ACCEL_GIR_CTRL_REG10		0x24
#define LSM9DS1_ACCEL_GIR_INT_GEN_SRC_XL	0x26
#define LSM9DS1_ACCEL_GIR_STATUS_REG_M		0x27
#define LSM9DS1_ACCEL_GIR_OUT_X_L_XL		0x28
#define LSM9DS1_ACCEL_GIR_OUT_X_H_XL		0x29
#define LSM9DS1_ACCEL_GIR_OUT_Y_L_XL		0x2A
#define LSM9DS1_ACCEL_GIR_OUT_Y_H_XL		0x2B
#define LSM9DS1_ACCEL_GIR_OUT_Z_L_XL		0x2C
#define LSM9DS1_ACCEL_GIR_OUT_Z_H_XL		0x2D
#define LSM9DS1_ACCEL_GIR_FIFO_CTRL			0x2E
#define LSM9DS1_ACCEL_GIR_FIFO_SRC			0x2F
#define LSM9DS1_ACCEL_GIR_INT_GEN_CFG_G		0x30
#define LSM9DS1_ACCEL_GIR_INT_GEN_THS_XH_G	0x31
#define LSM9DS1_ACCEL_GIR_INT_GEN_THS_XL_G	0x32
#define LSM9DS1_ACCEL_GIR_INT_GEN_THS_YH_G	0x33
#define LSM9DS1_ACCEL_GIR_INT_GEN_THS_YL_G	0x34
#define LSM9DS1_ACCEL_GIR_INT_GEN_THS_ZH_G	0x35
#define LSM9DS1_ACCEL_GIR_INT_GEN_THS_ZL_G	0x36
#define LSM9DS1_ACCEL_GIR_INT_GEN_DUR_G		0x37


#define LSM9DS1_MAG_OFFSET_X_REG_L_M		0x05
#define LSM9DS1_MAG_OFFSET_X_REG_H_M		0x06
#define LSM9DS1_MAG_OFFSET_Y_REG_L_M		0x07
#define LSM9DS1_MAG_OFFSET_Y_REG_H_M		0x08
#define LSM9DS1_MAG_OFFSET_Z_REG_L_M		0x09
#define LSM9DS1_MAG_OFFSET_Z_REG_H_M		0x0A
#define LSM9DS1_MAG_WHO_AM_I_M				0x0F
#define LSM9DS1_MAG_CTRL_REG1_M				0x20
#define LSM9DS1_MAG_CTRL_REG2_M				0x21
#define LSM9DS1_MAG_CTRL_REG3_M				0x22
#define LSM9DS1_MAG_CTRL_REG4_M				0x23
#define LSM9DS1_MAG_CTRL_REG5_M				0x24
#define LSM9DS1_MAG_STATUS_REG_M			0x27
#define LSM9DS1_MAG_OUT_X_L_M				0x28
#define LSM9DS1_MAG_OUT_X_H_M				0x29
#define LSM9DS1_MAG_OUT_Y_L_M				0x2A
#define LSM9DS1_MAG_OUT_Y_H_M				0x2B
#define LSM9DS1_MAG_OUT_Z_L_M				0x2C
#define LSM9DS1_MAG_OUT_Z_H_M				0x2D
#define LSM9DS1_MAG_INT_CFG_M				0x30
#define LSM9DS1_MAG_INT_SRC_M				0x31
#define LSM9DS1_MAG_INT_THS_L_M				0x32
#define LSM9DS1_MAG_INT_THS_H_M				0x33
/*#####################################################*/
namespace GI {
namespace Device {
namespace Sensor {
class Lsm9ds1
{
public:
	Lsm9ds1(char *hwPath, unsigned char sa0, unsigned char sa1);
	~Lsm9ds1();
	SysErr probe();

	enum scale_e {
    	LSM9DS1_SCALE_MASK = 0x0C,
		LSM9DS1_SCALE_245 = 0x00,   // 245bps
		LSM9DS1_SCALE_500 = 0x01,   // 500bps
		LSM9DS1_SCALE_2000 = 0x03   // 2000bps
    };

    enum bandwidth_e {
    	LSM9DS1_BW_MASK  = 0x03,
    	LSM9DS1_BW_0  = 0x00,
		LSM9DS1_BW_1  = 0x01,
		LSM9DS1_BW_2 = 0x02,
		LSM9DS1_BW_3 = 0x03,
    };

    enum data_rate_e {
    	LSM9DS1_ODR_PWR_MASK  = 0xE0,
    	LSM9DS1_ODR_PWR_DN  = 0x00,
    	LSM9DS1_ODR_14_9HZ  = 0x01,
		LSM9DS1_ODR_59_5HZ = 0x02,
		LSM9DS1_ODR_119HZ = 0x03,
		LSM9DS1_ODR_238HZ = 0x04,
		LSM9DS1_ODR_476HZ  = 0x05,
		LSM9DS1_ODR_952HZ = 0x06,
    };

    enum mag_performance_e {
    	LSM9DS1_MAG_PERFORMANCE_MASK  = 0x60,
    	LSM9DS1_MAG_PERFORMANCE_LOW  = 0x00,
    	LSM9DS1_MAG_PERFORMANCE_MED  = 0x01,
    	LSM9DS1_MAG_PERFORMANCE_HIGH  = 0x02,
    	LSM9DS1_MAG_PERFORMANCE_UHIGH  = 0x03,
    };

    enum mag_data_rate_e {
    	LSM9DS1_MAG_ODR_PWR_MASK  = 0x1C,
    	LSM9DS1_MAG_ODR_0_625HZ  = 0x00,
		LSM9DS1_MAG_ODR_1_25HZ = 0x01,
		LSM9DS1_MAG_ODR_2_5HZ = 0x02,
		LSM9DS1_MAG_ODR_5HZ = 0x03,
		LSM9DS1_MAG_ODR_10HZ  = 0x04,
		LSM9DS1_MAG_ODR_20HZ = 0x05,
		LSM9DS1_MAG_ODR_40HZ = 0x06,
		LSM9DS1_MAG_ODR_80HZ = 0x07,
    };

    enum mag_temp_compensation_e {
    	LSM9DS1_MAG_TMP_COMP_MASK = 0x80,
    	LSM9DS1_MAG_TMP_COMP_OFF = 0x00,
    	LSM9DS1_MAG_TMP_COMP_ON = 0x01,
    };

    enum mag_scale_e {
    	LSM9DS1_MAG_SCALE_MASK = 0x60,
    	LSM9DS1_MAG_SCALE_4G = 0x00,
    	LSM9DS1_MAG_SCALE_8G = 0x01,
    	LSM9DS1_MAG_SCALE_12G = 0x02,
    	LSM9DS1_MAG_SCALE_16G = 0x03,
    };

    enum mag_op_mode_e {
    	LSM9DS1_MAG_OP_MODE_MASK = 0x03,
    	LSM9DS1_MAG_OP_MODE_CONTINUOUS = 0x00,
    	LSM9DS1_MAG_OP_MODE_SINGLE = 0x01,
    	LSM9DS1_MAG_OP_MODE_PWR_DOWN = 0x03,
    };

	SysErr setScale(GI::Device::Sensor::Lsm9ds1::scale_e scale);
	SysErr setBandwidth(GI::Device::Sensor::Lsm9ds1::bandwidth_e bandwidth);
	SysErr setDataRate(GI::Device::Sensor::Lsm9ds1::data_rate_e data_rate);
	SysErr readTemp(float *temperature);
	SysErr readAccel(signed short *X, signed short *Y, signed short *Z);
	SysErr readGyro(signed short *X, signed short *Y, signed short *Z);
	SysErr setMagPerformance(GI::Device::Sensor::Lsm9ds1::mag_performance_e performance);
	SysErr setMagDataRate(GI::Device::Sensor::Lsm9ds1::mag_data_rate_e data_rate);
	SysErr setMagTempCompensation(GI::Device::Sensor::Lsm9ds1::mag_temp_compensation_e temp_compensation);
	SysErr setMagScale(GI::Device::Sensor::Lsm9ds1::mag_scale_e scale);
	SysErr setMagOpMode(GI::Device::Sensor::Lsm9ds1::mag_op_mode_e op_mode);
	SysErr setMagOffset(signed short X, signed short Y, signed short Z);
	SysErr readMag(signed short *X, signed short *Y, signed short *Z);
	unsigned char sa0;
	unsigned char sa1;
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
#endif /* LIB_DEVICE_LSM9DS1_H_ */
