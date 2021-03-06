/*
 *  device/ak8975.h
 */

/*#####################################################*/
#ifndef AK8975_H_
#define AK8975_H_
/*#####################################################*/
#include <stdbool.h>
#include "api/i2c.h"
#include <include/global.h>
/*#####################################################*/
#define AK8975_ADDR					(0x0C)

/*
 * Read-only registers
 */
#define AK8975_WIA_REG				(0x00)
#define AK8975_INFO_REG				(0x01)
#define AK8975_ST1_REG				(0x02)
#define AK8975_HXL_REG				(0x03)
#define AK8975_HXH_REG				(0x04)
#define AK8975_HYL_REG				(0x05)
#define AK8975_HYH_REG				(0x06)
#define AK8975_HZL_REG				(0x07)
#define AK8975_HZH_REG				(0x08)
#define AK8975_ST2_REG				(0x09)
/*
 * Write/Read registers
 */
#define AK8975_CNTL_REG				(0x0A)
#define AK8975_RSV_REG				(0x0B)
#define AK8975_ASTC_REG				(0x0C)
#define AK8975_TS1_REG				(0x0D)
#define AK8975_TS2_REG				(0x0E)
#define AK8975_I2CDIS_REG			(0x0F)
/*
 * Read-only registers
 */
#define AK8975_ASAX_REG				(0x10)
#define AK8975_ASAY_REG				(0x11)
#define AK8975_ASAZ_REG				(0x12)

/*
 * ST1 reg
 */
#define AK8975_ST1_DREADY_bp		0
#define AK8975_ST1_DREADY_bm		0x01

/*
 * ST2 reg
 */
#define AK8975_ST2_HOLF_bp			3	/* Magnetic sensor overflow */
#define AK8975_ST2_HOLF_bm			(0x01 << AK8975_ST2_HOLF_bp)

#define AK8975_ST2_DERR_bp			3	/* Data error occured */
#define AK8975_ST2_DERR_bm			(0x01 << AK8975_ST2_DERR_bp)

/*
 * CTRL reg
 */
#define AK8975_CTRL_MODE_gp			0	/* Data error occured */
#define AK8975_CTRL_MODE_gm			(0x0F << AK8975_CTRL_MODE_gp)
#define AK8975_CTRL_MODE_PWRDN		(0x00)
#define AK8975_CTRL_MODE_SINGLE		(0x01)
#define AK8975_CTRL_MODE_SELFTEST	(0x08)
#define AK8975_CTRL_MODE_ROM		(0x0F)

/*
 * ASTC reg
 */
#define AK8975_ASTC_SELF_bp			6	/* Data error occured */
#define AK8975_ASTC_SELF_bm			(0x01 << AK8975_ASTC_SELF_bp)

/*
 * I2CDIS reg
 */
#define AK8975_I2CDIS_bp			0	/* Data error occured */
#define AK8975_I2CDIS_bm			(0x01 << AK8975_I2CDIS_bp)

/*#####################################################*/
namespace GI {
namespace Device {
namespace Sensor {
class Ak8975
{
public:
	Ak8975(char *i2cPath, unsigned char icNr);
	~Ak8975();
	SysErr startMeasure();
	SysErr checkReady();
	SysErr getMag(signed short *X_Axis, signed short *Y_Axis, signed short *Z_Axis);
	//SysErr displayResult();

	bool busy;
	GI::Dev::I2c* I2C;
	unsigned char Stage;
private:
	SysErr getData(signed short *X_Axis, signed short *Y_Axis, signed short *Z_Axis);
	unsigned char IcNr;
};
}
}
}
typedef struct AK8975_s{
	//STimer_t Timeout_Timer;
}AK8975_t;

/*#####################################################*/
#ifdef USE_VISUAL_STUDIO
#include "ak8975.cpp"
#endif
/*#####################################################*/
#endif
/*#####################################################*/
