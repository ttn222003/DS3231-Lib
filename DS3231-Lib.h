#include "main.h"

uint8_t decToBcd(int val);
int bcdToDec(uint8_t val);
void SetTime(uint8_t second, uint8_t minute, uint8_t hour, uint8_t day, uint8_t date, uint8_t month, uint8_t year);
void GetTime();
void StringTime();