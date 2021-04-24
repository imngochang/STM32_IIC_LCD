/*
 * STM32_IIC_LCD.h
 *
 *  Created on: Apr 19, 2021
 *      Author: ADMIN
 */

#ifndef INC_STM32_IIC_LCD_H_
#define INC_STM32_IIC_LCD_H_

/*BEGIN Includes*/
#include "main.h"
/*BEGIN Define*/

/*BEGIN Variables*/
typedef struct {
	I2C_HandleTypeDef* i2c_handle;
	uint8_t device_address;
	uint8_t data[5];
} LCD_HandleTypeDef;

/*BEGIN Define*/

/*BEGIN function prototypes*/
LCD_HandleTypeDef LCD_init(I2C_HandleTypeDef* i2c_handle, uint8_t device_address);
void LCD_sendCommand(LCD_HandleTypeDef* lcd_handle, char cmd);
void LCD_sendData(LCD_HandleTypeDef* lcd_handle, char data);
void LCD_sendString(LCD_HandleTypeDef* lcd_handle, char* data);
void LCD_clearDisplay(LCD_HandleTypeDef* lcd_handle);
void LCD_setCursor(LCD_HandleTypeDef* lcd_handle, uint8_t row, uint8_t col);

#endif /* INC_STM32_IIC_LCD_H_ */
