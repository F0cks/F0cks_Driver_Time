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
