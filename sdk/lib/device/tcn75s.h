/*
 * tcn75s.h
 *
 *  Created on: Jan 22, 2018
 *      Author: Work
 */

#ifndef LIB_DEVICE_TCN75S_H_
#define LIB_DEVICE_TCN75S_H_

#include <include/global.h>
#include <api/io_handle.h>
#include "common.h"

#define TCN75S_I2CADDR			0x48
/*#####################################################*/
namespace GI {
namespace Device {
namespace Sensor {
class Tcn75s
{
public:
	Tcn75s(char *hwPath, unsigned char subAddr);
	~Tcn75s();
	SysErr probe();

    enum shut_down_e {
    	TCN75S_SHUT_DOWN_MASK = 0x01,
    	TCN75S_SHUT_DOWN_POSITION = 0x00,
    	TCN75S_SHUT_DOWN_DISABLE = 0x00,
    	TCN75S_SHUT_DOWN_ENABLE = 0x01,
    };

    enum comp_int_e {
    	TCN75S_COMP_INT_MASK = 0x02,
    	TCN75S_COMP_INT_POSITION = 0x01,
    	TCN75S_COMP_INT_COMPARATOR = 0x00,
    	TCN75S_COMP_INT_INTERRUPT = 0x01,
    };

    enum alert_polarity_e {
    	TCN75S_ALERT_POLARITY_MASK = 0x04,
    	TCN75S_ALERT_POLARITY_POSITION = 0x02,
    	TCN75S_ALERT_POLARITY_LOW = 0x00,
    	TCN75S_ALERT_POLARITY_HIGH = 0x01,
    };

    enum fault_queue_e {
    	TCN75S_FAULT_QUEUE_MASK = 0x18,
    	TCN75S_FAULT_QUEUE_POSITION = 0x03,
    	TCN75S_FAULT_QUEUE_1 = 0x00,
    	TCN75S_FAULT_QUEUE_2 = 0x01,
    	TCN75S_FAULT_QUEUE_4 = 0x02,
    	TCN75S_FAULT_QUEUE_6 = 0x03,
    };

    enum adc_resolution_e {
    	TCN75S_ADC_RESOLUTION_MASK = 0x60,
    	TCN75S_ADC_RESOLUTION_POSITION = 0x05,
    	TCN75S_ADC_RESOLUTION_0_5GR = 0x00,
    	TCN75S_ADC_RESOLUTION_0_25GR = 0x01,
    	TCN75S_ADC_RESOLUTION_0_125GR = 0x02,
    	TCN75S_ADC_RESOLUTION_0_0625GR = 0x03,
    };

    enum one_shot_e {
    	TCN75S_ONE_SHOT_MASK = 0x80,
    	TCN75S_ONE_SHOT_POSITION = 0x07,
    	TCN75S_ONE_SHOT_DISABLE = 0x00,
    	TCN75S_ONE_SHOT_ENABLE = 0x01,
    };

	SysErr setShutDown(GI::Device::Sensor::Tcn75s::shut_down_e shut_down);
	SysErr getShutDown(GI::Device::Sensor::Tcn75s::shut_down_e *shut_down);
	SysErr setCompInt(GI::Device::Sensor::Tcn75s::comp_int_e comp_int);
	SysErr getCompInt(GI::Device::Sensor::Tcn75s::comp_int_e *comp_int);
	SysErr setAlertPolarity(GI::Device::Sensor::Tcn75s::alert_polarity_e alert_polarity);
	SysErr getAlertPolarity(GI::Device::Sensor::Tcn75s::alert_polarity_e *alert_polarity);
	SysErr setFaultQueue(GI::Device::Sensor::Tcn75s::fault_queue_e fault_queue);
	SysErr getFaultQueue(GI::Device::Sensor::Tcn75s::fault_queue_e *fault_queue);
	SysErr setAdcResolution(GI::Device::Sensor::Tcn75s::adc_resolution_e adc_resolution);
	SysErr getAdcResolution(GI::Device::Sensor::Tcn75s::adc_resolution_e *adc_resolution);
	SysErr setOneShot(GI::Device::Sensor::Tcn75s::one_shot_e one_shot);
	SysErr getOneShot(GI::Device::Sensor::Tcn75s::one_shot_e *one_shot);
	SysErr startOneShot();
	SysErr readTemp(float *temperature);
    unsigned char subAddr;
	bool busy;
	GI::IO *hwIo;
};
}
}
}
/*#####################################################*/
#ifdef USE_VISUAL_STUDIO
#include "lsm9ds1.cpp"
#endif
/*#####################################################*/
#endif /* LIB_DEVICE_TCN75S_H_ */
