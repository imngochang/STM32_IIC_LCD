/*
 * STM32_IIC_LCD.c
 *
 *  Created on: Apr 19, 2021
 *      Author: ADMIN
 */

/*BEGIN Includes*/
#include "STM32_IIC_LCD.h"
/*BEGIN Define*/

/*BEGIN Variables*/

/*BEGIN Define*/

/*BEGIN function define*/
LCD_HandleTypeDef LCD_init(I2C_HandleTypeDef* i2c_handle, uint8_t device_address)
{
	LCD_HandleTypeDef LCD;
	LCD.i2c_handle = i2c_handle;
	LCD.device_address = device_address;
	HAL_Delay(50);
	LCD_sendCommand (&LCD, 0x33); /* set 4-bits interface */
	LCD_sendCommand (&LCD, 0x32);
	HAL_Delay(5);
	LCD_sendCommand (&LCD, 0x28); /* start to set LCD function */ // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
	HAL_Delay(5);
	LCD_sendCommand (&LCD, 0x01); /* clear display */
	HAL_Delay(5);
	LCD_sendCommand (&LCD, 0x06); /* set entry mode */
	HAL_Delay(5);
	LCD_sendCommand (&LCD, 0x0c); /* set display to on */
	HAL_Delay(5);
	LCD_sendCommand (&LCD, 0x02); /* move cursor to home and set data address to 0 */
	HAL_Delay(5);
	LCD_sendCommand (&LCD, 0x80);
	return LCD;
}

void LCD_sendCommand(LCD_HandleTypeDef* lcd_handle, char cmd)
{
	char data_u, data_l = 0;
	data_u = (cmd&0xf0);
	data_l = ((cmd<<4)&0xf0);
	lcd_handle->data[0] = data_u|0x0C;  //en=1, rs=0
	lcd_handle->data[1] = data_u|0x08;  //en=0, rs=0
	lcd_handle->data[2] = data_l|0x0C;  //en=1, rs=0
	lcd_handle->data[3] = data_l|0x08;  //en=0, rs=0
	HAL_I2C_Master_Transmit(lcd_handle->i2c_handle, lcd_handle->device_address, (uint8_t *) lcd_handle->data, 4, 100);
}

void LCD_sendData(LCD_HandleTypeDef* lcd_handle, char data)
{
	char data_u, data_l = 0;
	data_u = (data&0xf0);
	data_l = ((data<<4)&0xf0);
	lcd_handle->data[0] = data_u|0x0D;  //en=1, rs=0
	lcd_handle->data[1] = data_u|0x09;  //en=0, rs=0
	lcd_handle->data[2] = data_l|0x0D;  //en=1, rs=0
	lcd_handle->data[3] = data_l|0x09;  //en=0, rs=0
	HAL_I2C_Master_Transmit(lcd_handle->i2c_handle, lcd_handle->device_address, (uint8_t *) lcd_handle->data, 4, 100);
}

void LCD_sendString(LCD_HandleTypeDef* lcd_handle, char* data)
{
	while(*data) LCD_sendData(lcd_handle, *data++);
}

void LCD_clearDisplay(LCD_HandleTypeDef* lcd_handle)
{
	LCD_sendCommand(lcd_handle, 0x01); //clear display
}

void LCD_setCursor(LCD_HandleTypeDef* lcd_handle, uint8_t row, uint8_t col)
{
	uint8_t pos_Addr = 0;
	if(row == 1)
	{
		pos_Addr = 0x80 + row + col;
	}
	else
	{
		pos_Addr = 0x80 | (0x40 + col);
	}
	LCD_sendCommand(lcd_handle, pos_Addr);
}
