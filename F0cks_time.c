#include "F0cks_time.h"

int8_t F0cks_Time_Clock_Init(Time_Clock_HandleTypeDef *handler, Time_Clock_ConfigurationTypeDef config)
{
	int8_t error = 0;

	handler->status	=	config.status;
	handler->second	=	config.second;
	handler->minute	= config.minute;
	handler->hour		= config.hour;

	return error;
}

int8_t F0cks_Time_Clock_Reset(Time_Clock_HandleTypeDef *clock)
{
	int8_t error = 0;

	clock->second = 0;
	clock->minute	= 0;
	clock->hour		= 0;

	return error;
}

int8_t F0cks_Time_Init(Time_HandleTypeDef *handler, Time_Clock_HandleTypeDef *clock, uint8_t clockNumber )
{
	int8_t error = 0;

	handler->timerSecInc = 0;

	handler->clockNumber = clockNumber;

	handler->handler = clock;

	return error;
}

int8_t F0cks_Time_Update(Time_HandleTypeDef *handler)
{
	int8_t error = 0;

	uint8_t i = 0;
	Time_Clock_HandleTypeDef *p = handler->handler;

	/* Nothing to update */
	if( handler->timerSecInc <= 0 )
	{
		return -1;
	}

	for(i=0; i<handler->clockNumber; i++)
	{
		if(p->status == CLOCK_ENABLE)
		{
			/* Add elapsed seconds */
			p->second += handler->timerSecInc;

			/* Calculate minutes and remaining seconds */
			p->minute += p->second / 60;
			p->second = p->second % 60;

			/* Calculate hours and remaining minutes */
			p->hour += p->minute / 60;
			p->minute = p->minute % 60;

		}
		p++;
	}

	/* Empty elapsed seconds counter */
	handler->timerSecInc = 0;

	return error;
}

/* Check if clock is over (or equal) a specific time */
int8_t F0cks_Time_Compare(Time_Clock_HandleTypeDef *handler, Time_Clock_HandleTypeDef time )
{
	int8_t error = -1;

	Time_Clock_HandleTypeDef *p = handler;
	uint32_t secondsHandler = 0;
	uint16_t secondsTime    = 0;

	/* Convert all in seconds */
	secondsHandler = p->second + p->minute*60 +p->hour*3600;
	secondsTime    = time.second + time.minute*60 +time.hour*3600;

	/* Compare */
	if( secondsHandler >= secondsTime)
	{
		/* clk is over or equal specified time */
		error = 1;
	}
	else if( secondsHandler < secondsTime)
	{
		/* clk is under specified time */
		error = 0;
	}

	/* Error */
	return error;
}

