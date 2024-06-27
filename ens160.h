/**
 * @file: ens160.h
 * @Created on: 10.03.2024
 * @Author: rRaufToprak
 * @Description: ENS160 gas sensor driver header file
 * @Copyright: MIT License
*/

#ifndef _ENS_160_H_
#define _ENS_160_H_

#include "spi.h"
#include "i2c.h"
#include "stdint.h"
#include "stdbool.h"
#include "stm32f4xx_hal.h"
#include "gpio.h"

/*----------------------ENS160 Register Defines---------------*/
#define ENS160_PART_ID																	0x00
#define ENS160_OPMODE																	0x10
#define ENS160_CONFIG																	0x11
#define ENS160_COMMAND																	0x12
#define ENS160_TEMP_IN																	0x13
#define ENS160_RH_IN																	0x15
#define ENS160_DEV_STATUS																0x20
#define ENS160_DATA_AQI																	0x21
#define ENS160_DATA_TVOC																0x22
#define ENS160_DATA_ECO2																0x24
#define ENS160_DATA_TEMP																0x30
#define ENS160_DATA_RH																	0x32
#define ENS160_DATA_MISR																0x38
#define ENS160_GPR_WRITE																0x40
#define ENS160_GPR_READ																	0x48
/*----------------------ENS160 Command definitions---------------*/
typedef enum{
	DEEP_SLEEP_MODE = 0x00,
	IDLE_MODE	= 0x01,
	STANDARD_MODE	= 0x02,
	RESET_MODE      = 0xF0
}ENS160_OpModeCommand;
/*----------------------ENS160 Data Structure--------------------*/
typedef struct {
    uint8_t AQI_data;
    uint16_t TVOC_data;
    uint16_t ECO2_data;
}SensorData;
/**
 *Checks sensor ID
 *@retval: If the id check is done correctly, it returns true, otherwise it returns false
 */
bool ENS160_Control_ID(void);

/**
 *Sets the operating mode of the sensor
 *@param: Takes command variable of type ENS160_OpModeCommand
 *@retval: Returns true if the operating mode is set successfully, otherwise returns false
 */
bool ENS160_SetOpMode(ENS160_OpModeCommand command);

/**
 *Writes the specified value to the specified register
 *@param:Specified register address
 *@param:Specified 8bit data
 *@retval:Returns true if the write operation is successful.
 */
bool ENS160_Write_Register(uint8_t register_address, uint8_t data);

/**
 *Reads the data from specified register
 *@param:Specified register address
 *@retval:16 bit value read from register
 */
uint16_t ENS160_Read_Register(uint8_t register_address);

/**
 *Reads the data from specified register
 *@param:Specified register address
 *@retval:8 bit value read from register
 */
uint8_t ENS160_Read_Single_Register(uint8_t register_address);

/**
 *Reads sensor data from the ENS160 sensor and stores it in the provided SensorData structure
 *@param:Pointer to a SensorData structure where the sensor data will be stored.This structure should be allocated by the caller.
 *@retval:None             
 */
void ENS160_Read_Datas(SensorData *data);

/**
 * Updates the compensation values for temperature and humidity in the ENS160 sensor
 *
 * @param temp Compensation value for temperature, in uint16_t format
 * @param hum Compensation value for humidity, in uint16_t format
 * @retval None
 */
void ENS160_Update_Comp_Val(uint16_t temp, uint16_t hum);




#endif /* _ENS_160_H_ */

