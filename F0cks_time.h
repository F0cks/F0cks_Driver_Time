#ifndef F0CKS_TIME_H
#define F0CKS_TIME_H

#include "stdint.h"

typedef enum
{
  CLOCK_DISABLE	=  0x00U,   // Clock disable
	CLOCK_ENABLE	=  0x01U    // Clock enable

}Time_Clock_StatusTypeDef;

typedef struct
{
	Time_Clock_StatusTypeDef	status;
	uint8_t 	second;
	uint8_t		minute;
	uint16_t 	hour;

}Time_Clock_ConfigurationTypeDef;

/**
  * @brief  Time clock handle Structure definition
  */
typedef struct
{
	Time_Clock_StatusTypeDef	status;

	uint8_t		second;
	uint8_t		minute;
	uint16_t	hour;

}Time_Clock_HandleTypeDef;


/**
  * @brief  Time handle Structure definition
  */
typedef struct
{
	volatile uint8_t	timerSecInc;

	uint8_t										clockNumber;
	Time_Clock_HandleTypeDef	*handler;

}Time_HandleTypeDef;

int8_t F0cks_Time_Clock_Init(Time_Clock_HandleTypeDef *handler, Time_Clock_ConfigurationTypeDef config);
int8_t F0cks_Time_Clock_Reset(Time_Clock_HandleTypeDef *clock);
int8_t F0cks_Time_Init(Time_HandleTypeDef *handler, Time_Clock_HandleTypeDef *clock, uint8_t clockNumber );
int8_t F0cks_Time_Update(Time_HandleTypeDef *handler);

#endif //F0CKS_TIME_H
