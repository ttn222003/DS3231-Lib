#include "main.h"
#include "stdio.h"
#define DS3231_Address	0XD0
extern I2C_HandleTypeDef hi2c1;
/* If you want to use these variable below, please call them again and use extern before use them */
uint8_t seconds;
uint8_t minutes;
uint8_t hours;
uint8_t day;
uint8_t date;
uint8_t months;
uint8_t years;
uint8_t time1[20];
uint8_t time2[20];
/**************************************************/
// Convert normal decimal numbers to binary numbers
uint8_t decToBcd(int val)
{
	return (uint8_t)((val / 10 * 16) + (val % 10));
}
// Convert binary numbers to normal decimal numbers
int bcdToDec(uint8_t val)
{
	return (int)((val / 16 * 10) + (val % 16));
}
/**************************************************/
/**************************************************/
// The register pointer is written before the initiation of read mode
void SetTime(uint8_t second, uint8_t minute, uint8_t hour, uint8_t day, uint8_t date, uint8_t month, uint8_t year)
{
	uint8_t start_mem = 0X00;
	uint8_t data_write[7];
	data_write[0] = decToBcd(second);
	data_write[1] = decToBcd(minute);
	data_write[2] = decToBcd(hour);
	data_write[3] = decToBcd(day);
	data_write[4] = decToBcd(date);
	data_write[5] = decToBcd(month);
	data_write[6] = decToBcd(year);
	HAL_I2C_Mem_Write(&hi2c1,DS3231_Address,start_mem,1,data_write,7,1000);
}

void GetTime()
{
	uint8_t start_mem = 0X00;
	uint8_t data_read[7];
	HAL_I2C_Mem_Read(&hi2c1,DS3231_Address,start_mem,1,data_read,7,1000);
	seconds = bcdToDec(data_read[0]);
	minutes = bcdToDec(data_read[1]);
	hours = bcdToDec(data_read[2]);
	day = bcdToDec(data_read[3]);
	date = bcdToDec(data_read[4]);
	months = bcdToDec(data_read[5]);
	years = bcdToDec(data_read[6]);
}
// You just need to use this function below to display the time. Or you can do it by yourself
void StringTime()
{
	GetTime();
	sprintf((char*)time1,"%02d:%02d:%02d",hours,minutes,seconds);
	sprintf((char*)time2,"%02d-%02d-%02d",date,months,years);
}
/****************************************************/