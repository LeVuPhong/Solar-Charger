/*
 * ina2xx.h
 *
 *  Created on: Feb 27, 2021
 *      Author: le vu phong
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef INC_INA2XX_H_
#define INC_INA2XX_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Exported define -----------------------------------------------------------*/
#define INA220
/** @defgroup INA2xx_Reg	INA2xx base register
  * @{
  */
#ifdef INA233

#else

#define INA2xx_REG_CONFIG			0x00 	/* All-register reset, settings for bus voltage range, PGA gain, ADC resolution/averaging */
#define INA2xx_REG_VSHUNT			0x01 	/* Shunt voltage measurement data */
#define INA2xx_REG_VBUS				0x02 	/* Bus voltage measurement data */
#define INA2xx_REG_POWER			0x03	/* Power measurement data */
#define INA2xx_REG_CURRENT			0x04	/* Contains the value of the current flowing through the shunt resistor */
#define INA2xx_REG_CALIBRATION		0x05	/* Sets full-scale range and LSB of current and power measurements. Overall system calibration */

#endif

/**
  * @}
  */

/** @defgroup INA2xx_CONFIG		INA2xx config register value
  * @{
  */
#ifdef INA233


#else //INA220
#define INA2xx_CONFIG_DEFAULT			0x399F

#define INA2xx_CONFIG_RESET_0			0x4000
#define INA2xx_CONFIG_RESET_1			0xC000

/* BRNG[13]: Bus Voltage Range */
#define INA2xx_CONFIG_BRNG_Pos			13
#define INA2xx_CONFIG_BRNG_Msk			(0x1 << INA2xx_CONFIG_BRNG_Pos)
#define INA2xx_CONFIG_BRNG_16V			0x0
#define INA2xx_CONFIG_BRNG_32V			0x1 /* default value */

/* PG[12:11]: PGA (Shunt Voltage Only) - Sets PGA gain and range. Note that the PGA defaults to ÷8 (320-mV range)*/
#define INA2xx_CONFIG_PGA_Pos			11
#define INA2xx_CONFIG_PGA_Msk			(0x3 << INA2xx_CONFIG_PGA_Pos)
#define INA2xx_CONFIG_PGA_1				0x0	/* +- 40mV */
#define INA2xx_CONFIG_PGA_2				0x1	/* +- 70mV */
#define INA2xx_CONFIG_PGA_4				0x2	/* +- 160mV */
#define INA2xx_CONFIG_PGA_8				0x3	/* +- 320mV (default value)*/

/* BADC[10:7]: BADC Bus ADC Resolution/Averaging - These bits adjust the Bus ADC resolution (9-, 10-, 11-, or 12-bit) or set the number of samples used when averaging results for the Bus Voltage Register (02h) */
#define INA2xx_CONFIG_BADC_Pos			7
#define INA2xx_CONFIG_BADC_Msk			(0xF << INA2xx_CONFIG_BADC_Pos)
#define INA2xx_CONFIG_BADC_9bit			0x0 	/* Bus ADC resolution 9 bit, convertion time 84us */
#define INA2xx_CONFIG_BADC_10_bit		0x1 	/* Bus ADC resolution 10 bit, convertion time 184us */
#define INA2xx_CONFIG_BADC_11_bit		0x2 	/* Bus ADC resolution 11 bit, convertion time 276us */
#define INA2xx_CONFIG_BADC_12_bit		0x3 	/* Bus ADC resolution 12 bit, convertion time 532us */
#define INA2xx_CONFIG_BADC_2_sample		0x9		/* Bus ADC number of samples (averaging results) 2, convertion time 1.06ms */
#define INA2xx_CONFIG_BADC_4_sample		0xA		/* Bus ADC number of samples (averaging results) 4, convertion time 2.13ms */
#define INA2xx_CONFIG_BADC_8_sample		0xB		/* Bus ADC number of samples (averaging results) 8, convertion time 4.26ms */
#define INA2xx_CONFIG_BADC_16_sample	0xC		/* Bus ADC number of samples (averaging results) 16, convertion time 8.516ms */
#define INA2xx_CONFIG_BADC_32_sample	0xD		/* Bus ADC number of samples (averaging results) 32, convertion time 17.02ms */
#define INA2xx_CONFIG_BADC_64_sample	0xE		/* Bus ADC number of samples (averaging results) 64, convertion time 34.05ms */
#define INA2xx_CONFIG_BADC_128_sample	0xF		/* Bus ADC number of samples (averaging results) 128, convertion time 68.10ms */

/* SADC[6:3]: SADC Shunt ADC Resolution/Averaging - These bits adjust the Shunt ADC resolution (9-, 10-, 11-, or 12-bit) or set the number of samples used when averaging results for the Shunt Voltage Register (01h) */
#define INA2xx_CONFIG_SADC_Pos			3
#define INA2xx_CONFIG_SADC_Msk			(0xF << INA2xx_CONFIG_SADC_Pos)
#define INA2xx_CONFIG_SADC_9bit			0x0 	/* Shunt ADC resolution 9 bit, convertion time 84us */
#define INA2xx_CONFIG_SADC_10_bit		0x1 	/* Shunt ADC resolution 10 bit, convertion time 184us */
#define INA2xx_CONFIG_SADC_11_bit		0x2 	/* Shunt ADC resolution 11 bit, convertion time 276us */
#define INA2xx_CONFIG_SADC_12_bit		0x3 	/* Shunt ADC resolution 12 bit, convertion time 532us */
#define INA2xx_CONFIG_SADC_2_sample		0x9		/* Shunt ADC number of samples (averaging results) 2, convertion time 1.06ms */
#define INA2xx_CONFIG_SADC_4_sample		0xA		/* Shunt ADC number of samples (averaging results) 4, convertion time 2.13ms */
#define INA2xx_CONFIG_SADC_8_sample		0xB		/* Shunt ADC number of samples (averaging results) 8, convertion time 4.26ms */
#define INA2xx_CONFIG_SADC_16_sample	0xC		/* Shunt ADC number of samples (averaging results) 16, convertion time 8.516ms */
#define INA2xx_CONFIG_SADC_32_sample	0xD		/* Shunt ADC number of samples (averaging results) 32, convertion time 17.02ms */
#define INA2xx_CONFIG_SADC_64_sample	0xE		/* Shunt ADC number of samples (averaging results) 64, convertion time 34.05ms */
#define INA2xx_CONFIG_SADC_128_sample	0xF		/* Shunt ADC number of samples (averaging results) 128, convertion time 68.10ms */

/* MODE[2:0]: Operating Mode - Selects continuous, triggered, or power-down mode of operation. These bits default to continuous shunt and bus measurement mode */
#define INA2xx_CONFIG_MODE_Pos					0
#define INA2xx_CONFIG_MODE_Msk					(0x7 << INA2xx_CONFIG_MODE_Pos)
#define INA2xx_CONFIG_MODE_Power_Down			0x0		/* Power-down */
#define INA2xx_CONFIG_MODE_Vsh_Trig				0x1		/* Shunt voltage, triggered */
#define INA2xx_CONFIG_MODE_Vbus_Trig			0x2		/* Bus voltage, triggered */
#define INA2xx_CONFIG_MODE_Vsh_Vbus_Trig		0x3		/* Shunt and bus, triggered */
#define INA2xx_CONFIG_MODE_ADC_off				0x4		/* ADC off (disabled) */
#define INA2xx_CONFIG_MODE_Vsh_Continuous		0x5		/* Shunt voltage, continuous */
#define INA2xx_CONFIG_MODE_Vbus_Continuous		0x6		/* Bus voltage, continuous */
#define INA2xx_CONFIG_MODE_Vsh_Vbus_Continuous	0x7		/* Shunt and bus, continuous */

#define INA2xx_VSHUNT_LSB		10
#define INA2xx_VBUS_LSB			4
#define INA2xx_POWER_LSB		20

#endif
/**
  * @}
  */

#ifdef INA226
	#define INA226_CONFIG_RESET_0		0x4000
	#define INA226_CONFIG_RESET_1		0xC000

	#define INA226_CONFIG_AVG_Pos		9
	#define INA226_CONFIG_AVG_Msk		(0x7 << INA226_CONFIG_AVG_Pos)
	#define INA226_CONFIG_AVG_1			0x0
	#define INA226_CONFIG_AVG_4			(0x1 << INA226_CONFIG_AVG_Pos)
	#define INA226_CONFIG_AVG_16		(0x2 << INA226_CONFIG_AVG_Pos)
	#define INA226_CONFIG_AVG_64		(0x3 << INA226_CONFIG_AVG_Pos)
	#define INA226_CONFIG_AVG_128		(0x4 << INA226_CONFIG_AVG_Pos)
	#define INA226_CONFIG_AVG_256		(0x5 << INA226_CONFIG_AVG_Pos)
	#define INA226_CONFIG_AVG_512		(0x6 << INA226_CONFIG_AVG_Pos)
	#define INA226_CONFIG_AVG_1024		(0x7 << INA226_CONFIG_AVG_Pos)

	#define INA226_CONFIG_VBUSCT_pos	6
	#define INA226_CONFIG_VBUSCT_Msk	(0x7 << INA226_CONFIG_VBUSCT_pos)
	#define INA226_CONFIG_VBUSCT_0		0x0
	#define INA226_CONFIG_VBUSCT_1		(0x1 << INA226_CONFIG_VBUSCT_pos)
	#define INA226_CONFIG_VBUSCT_2		(0x2 << INA226_CONFIG_VBUSCT_pos)
	#define INA226_CONFIG_VBUSCT_3		(0x3 << INA226_CONFIG_VBUSCT_pos)
	#define INA226_CONFIG_VBUSCT_4		(0x4 << INA226_CONFIG_VBUSCT_pos)
	#define INA226_CONFIG_VBUSCT_5		(0x5 << INA226_CONFIG_VBUSCT_pos)
	#define INA226_CONFIG_VBUSCT_6		(0x6 << INA226_CONFIG_VBUSCT_pos)
	#define INA226_CONFIG_VBUSCT_7		(0x7 << INA226_CONFIG_VBUSCT_pos)

	#define INA226_CONFIG_VSHCT_pos		3
	#define INA226_CONFIG_VSHCT_Msk		(0x7 << INA226_CONFIG_VSHCT_pos)
	#define INA226_CONFIG_VSHCT_0		0x0
	#define INA226_CONFIG_VSHCT_1		(0x1 << INA226_CONFIG_VSHCT_pos)
	#define INA226_CONFIG_VSHCT_2		(0x2 << INA226_CONFIG_VSHCT_pos)
	#define INA226_CONFIG_VSHCT_3		(0x3 << INA226_CONFIG_VSHCT_pos)
	#define INA226_CONFIG_VSHCT_4		(0x4 << INA226_CONFIG_VSHCT_pos)
	#define INA226_CONFIG_VSHCT_5		(0x5 << INA226_CONFIG_VSHCT_pos)
	#define INA226_CONFIG_VSHCT_6		(0x6 << INA226_CONFIG_VSHCT_pos)
	#define INA226_CONFIG_VSHCT_7		(0x7 << INA226_CONFIG_VSHCT_pos)

	#define INA226_CONFIG_MODE_pos		0
	#define INA226_CONFIG_MODE_Msk		0x7
	#define INA226_CONFIG_MODE_0		0x0
	#define INA226_CONFIG_MODE_1		0x1
	#define INA226_CONFIG_MODE_2		0x2
	#define INA226_CONFIG_MODE_3		0x3
	#define INA226_CONFIG_MODE_4		0x4
	#define INA226_CONFIG_MODE_5		0x5
	#define INA226_CONFIG_MODE_6		0x6
	#define INA226_CONFIG_MODE_7		0x7

	#define INA226_REG_CONFIG			0x00
	#define INA226_REG_VSHUNT			0x01
	#define INA226_REG_VBUS				0x02
	#define INA226_REG_POWER			0x03
	#define INA226_REG_CURRENT			0x04
	#define INA226_REG_CALIBRATION		0x05
	#define INA226_REG_ALERT_EN			0x06
	#define INA226_REG_ALERT_LIMIT		0x07
	#define INA226_REG_MANUF_ID			0xFE
	#define INA226_REG_DIE_ID			0xFF

	#define INA226_MANUF_ID_DEFAULT		0x5449
	#define INA226_DIE_ID_DEFAULT		0x2260

	#define INA226_VSHUNT_LSB			2.5
	#define INA226_VBUS_LSB				1.25
	#define INA226_POWER_LSB			25

	#define INA226_ALERT_SOL			0x8000
	#define INA226_ALERT_SUL			0x4000
	#define INA226_ALERT_BOL			0x2000
	#define INA226_ALERT_BUL			0x1000
	#define INA226_ALERT_POL			0x0800
#endif
/* Exported types ------------------------------------------------------------*/

/* Exported variables --------------------------------------------------------*/

/* Exported macros -----------------------------------------------------------*/

/* External funtion and variable ---------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
//uint16_t ina2xx_getManufID(void);
HAL_StatusTypeDef ina2xx_Init(uint8_t slave_addr,uint16_t calbration,uint16_t config);
HAL_StatusTypeDef ina2xx_setCalibration(uint8_t slave_addr, uint16_t value);
HAL_StatusTypeDef ina2xx_set_VshuntOver_Alert(uint16_t limit_value);
HAL_StatusTypeDef ina2xx_getBusVoltage_mV(uint8_t slave_addr, uint16_t * vbus);
HAL_StatusTypeDef ina2xx_getBusVoltage_V(uint8_t slave_addr, float * vbus);
HAL_StatusTypeDef ina2xx_getShuntVoltage_uV(uint8_t slave_addr, int16_t * vshunt);
HAL_StatusTypeDef ina2xx_getCurrent_mA(uint8_t slave_addr, int16_t * current);
HAL_StatusTypeDef ina2xx_getCurrent_A(uint8_t slave_addr, float * current);
HAL_StatusTypeDef ina2xx_getPower_W(uint8_t slave_addr, float * power);

#endif /* INC_INA2XX_H_ */
