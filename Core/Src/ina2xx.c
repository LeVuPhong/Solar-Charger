/*
 * ina2xx.c
 *
 *  Created on: Feb 27, 2021
 *      Author: le vu phong
 */

/* Includes ------------------------------------------------------------------*/
#include <ina2xx.h>
#include "i2c.h"
//#include "header_system.h"
/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define INA226_I2C	hi2c1
#define Slave_Addr1	0x40
#define INA226_Addr	Slave_Addr1 << 1
/* Private macro -------------------------------------------------------------*/

/* Extern variables ----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
uint8_t i2c_buffer[8];

uint16_t calbration_value = 2750;//2560;//calibration = 0.00512/(Current_LSB * Rshunt): Current_LSB = 0.001, Rshunt = 0.002
uint16_t Vshunt_Over_Value = 60;//Rshunt = 2mOhm ~ Over current = 30A
/* Private function prototypes -----------------------------------------------*/

/* Extern function prototypes ------------------------------------------------*/
static HAL_StatusTypeDef ina2xx_WriteRegister(uint8_t slave_addr, uint8_t reg, uint16_t value)
{
	i2c_buffer[0] = reg;
	i2c_buffer[1] = value >> 8;
	i2c_buffer[2] = value & 0xFF;
	return HAL_I2C_Master_Transmit(&INA226_I2C, slave_addr, i2c_buffer, 3, 100);
}

static HAL_StatusTypeDef ina2xx_ReadRegister(uint8_t slave_addr, uint8_t reg, uint16_t * value)
{
	HAL_StatusTypeDef res;
	i2c_buffer[0] = 0;
	i2c_buffer[1] = 0;
//	res = HAL_I2C_Master_Receive(&INA226_I2C, INA226_Addr, i2c_buffer, 2, 100);
	res = HAL_I2C_Mem_Read(&INA226_I2C, slave_addr, reg, I2C_MEMADD_SIZE_8BIT, i2c_buffer, 2, 10);
	if (res == HAL_OK)
	{
		*value = ((uint16_t)i2c_buffer[0] << 8) | i2c_buffer[1];
		return res;
	}
//	debug_write("INA226_Addr = %.2X\n",INA226_Addr);
	return res;
}
//
//uint16_t ina2xx_getManufID(void)
//{
//	uint16_t value;
//	ina2xx_ReadRegister(INA226_REG_MANUF_ID, &value);
//	return value;
//}
//
HAL_StatusTypeDef ina2xx_Init(uint8_t slave_addr,uint16_t calbration,uint16_t config)
{
	uint16_t manuf_ID;
	uint16_t cfg;
	/*check manufactuner ID*/

//	ina2xx_ReadRegister(INA226_REG_MANUF_ID, &manuf_ID);
//	if(manuf_ID != INA226_MANUF_ID_DEFAULT)
//	{
//		//return HAL_ERROR;
//	}

	/* Set config */
	/* Read config register value */
	ina2xx_ReadRegister(slave_addr, INA2xx_REG_CONFIG, &cfg);
	if(config != cfg)
	{
		/* Write config register value */
		if(ina2xx_WriteRegister(slave_addr, INA2xx_REG_CONFIG, config) != HAL_OK)
		{
			if(ina2xx_WriteRegister(slave_addr, INA2xx_REG_CONFIG, config) != HAL_OK)
			{
				return HAL_ERROR;
			}
		}
	}

	/* Set calibration value */
	if(ina2xx_WriteRegister(slave_addr, INA2xx_REG_CALIBRATION, calbration) != HAL_OK)
	{
		if(ina2xx_WriteRegister(slave_addr, INA2xx_REG_CALIBRATION, calbration) != HAL_OK)
		{
			return HAL_ERROR;
		}
	}
//	if(ina2xx_set_VshuntOver_Alert(Vshunt_Over_Value) != HAL_OK)
//	{
//		if(ina2xx_set_VshuntOver_Alert(Vshunt_Over_Value) != HAL_OK)
//		{
//			return HAL_ERROR;
//		}
//	}
	return HAL_OK;
}

HAL_StatusTypeDef ina2xx_setCalibration(uint8_t slave_addr, uint16_t value)
{
	return ina2xx_WriteRegister(slave_addr, INA2xx_REG_CALIBRATION, value);
}

//HAL_StatusTypeDef ina2xx_set_VshuntOver_Alert(uint16_t limit_value)
//{
//	HAL_StatusTypeDef res;
//	uint16_t value = (float)limit_value/2.5;
//	res = ina2xx_WriteRegister(INA226_REG_ALERT_EN, INA226_ALERT_SOL);
//	if(res != HAL_OK) return res;
//
//	res = ina2xx_WriteRegister(INA226_REG_ALERT_LIMIT, value);
//	return res;
//}
//
HAL_StatusTypeDef ina2xx_getBusVoltage_raw(uint8_t slave_addr, uint16_t * vbus)
{
	uint16_t value;
	if(ina2xx_ReadRegister(slave_addr, INA2xx_REG_VBUS, &value) != HAL_OK)
	{
		*vbus = 0;
		return HAL_ERROR;
	}
#ifdef INA220
	*vbus = (value >> 3) & 0x1F;
#else
	*vbus = value & 0x7F;
#endif

	return HAL_OK;
}

HAL_StatusTypeDef ina2xx_getBusVoltage_mV(uint8_t slave_addr, uint16_t * vbus)
{
	uint16_t value;
	if(ina2xx_getBusVoltage_raw(slave_addr, &value) != HAL_OK)
	{
		return HAL_ERROR;
	}

	*vbus = value * INA2xx_VBUS_LSB;
}
HAL_StatusTypeDef ina2xx_getBusVoltage_V(uint8_t slave_addr,float * vbus)
{
	uint16_t value;
	if(ina2xx_getBusVoltage_raw(slave_addr, &value) != HAL_OK)
	{
		return HAL_ERROR;
	}

	*vbus = (float)(value * INA2xx_VBUS_LSB) / 1000;
}

HAL_StatusTypeDef ina2xx_getShuntVoltage_raw(uint8_t slave_addr, int16_t * vshunt)
{
	uint16_t value;
	if(ina2xx_ReadRegister(slave_addr, INA2xx_REG_VSHUNT, &value) != HAL_OK)
	{
		*vshunt = 0;
		return HAL_ERROR;
	}

	*vshunt = (int16_t)value;

	return HAL_OK;
}

HAL_StatusTypeDef ina2xx_getShuntVoltage_uV(uint8_t slave_addr, int16_t * vshunt)
{
	uint16_t value;
	if(ina2xx_ReadRegister(slave_addr, INA2xx_REG_VSHUNT, &value) != HAL_OK)
	{
		*vshunt = 0;
		return HAL_ERROR;
	}

	*vshunt = ((int16_t)value) * INA2xx_VSHUNT_LSB;

	return HAL_OK;
}

HAL_StatusTypeDef ina2xx_getShuntVoltage_mV(uint8_t slave_addr, float * vshunt)
{
	uint16_t value;
	if(ina2xx_ReadRegister(slave_addr, INA2xx_REG_VSHUNT, &value) != HAL_OK)
	{
		*vshunt = 0;
		return HAL_ERROR;
	}

	*vshunt = (float)((int16_t)value * INA2xx_VSHUNT_LSB) / 1000;

	return HAL_OK;
}

HAL_StatusTypeDef ina2xx_getCurrent_raw(uint8_t slave_addr, uint16_t * current)
{
	return ina2xx_ReadRegister(slave_addr, INA2xx_REG_VSHUNT, current);
}

HAL_StatusTypeDef ina2xx_getCurrent_mA(uint8_t slave_addr, int16_t * current)
{
	uint16_t value;
	if(ina2xx_ReadRegister(slave_addr, INA2xx_REG_CURRENT, &value) != HAL_OK)
	{
		*current = 0;
		return HAL_ERROR;
	}

	*current = (int16_t)value;

	return HAL_OK;
}

HAL_StatusTypeDef ina2xx_getCurrent_A(uint8_t slave_addr, float * current)
{
	int16_t value;
	if(ina2xx_ReadRegister(slave_addr, INA2xx_REG_CURRENT, &value) != HAL_OK)
	{
		*current = 0;
		return HAL_ERROR;
	}

	*current = (float)value / 1000;
	return HAL_OK;
}

HAL_StatusTypeDef ina2xx_getPower_mW(uint8_t slave_addr, uint16_t * power)
{
	uint16_t value;
	if(ina2xx_ReadRegister(slave_addr, INA2xx_REG_POWER, &value) != HAL_OK)
	{
		*power = 0;
		return HAL_ERROR;
	}

	*power = value * INA2xx_POWER_LSB;
	return HAL_OK;
}

HAL_StatusTypeDef ina2xx_getPower_W(uint8_t slave_addr, float * power)
{
	uint16_t value;
		if(ina2xx_ReadRegister(slave_addr, INA2xx_REG_POWER, &value) != HAL_OK)
		{
			*power = 0;
			return HAL_ERROR;
		}

		*power = (float)(value * INA2xx_POWER_LSB) / 1000;
		return HAL_OK;
}
