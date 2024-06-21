/*
 * ULTRASONIC.c
 *
 *  Created on: Oct 18, 2023
 *      Author: Ahmedmohamed
 */
#include"icu.h"
#include"ULTRASONIC.h"
#include <util/delay.h>
static uint16 ultrasonic_time=0;
static uint8 ultrasonic_counter=0;
void Ultrasonic_init(void)
{
	ICU_ConfigType ICU_SETUP={F_CPU_8,RAISING};
	ICU_init(&ICU_SETUP);
	ICU_setCallBack(Ultrasonic_edgeProcessing);
	GPIO_setupPinDirection(TRIGGER_PORT_ID,TRIGGER_PIN_ID,PIN_OUTPUT);
	//GPIO_setupPinDirection(ECHO_PORT_ID,ECHO_PIN_ID,PIN_INPUT);

}
void Ultrasonic_Trigger(void)
{
	GPIO_writePin(TRIGGER_PORT_ID,TRIGGER_PIN_ID,LOGIC_HIGH);
	_delay_ms(10);
	GPIO_writePin(TRIGGER_PORT_ID,TRIGGER_PIN_ID,LOGIC_LOW);
}
uint16 Ultrasonic_readDistance(void)
{
	uint16 DISTANCE_CM=0;
	Ultrasonic_Trigger();
	//polling still in while loop till counter=2
	while(ultrasonic_counter!=2);
	ultrasonic_counter=0;
	DISTANCE_CM=(ultrasonic_time)/(58.8);
	return DISTANCE_CM;
}
void Ultrasonic_edgeProcessing(void)
{
	ultrasonic_counter++;
	if(ultrasonic_counter==1)
	{
		ICU_clearTimerValue();
		ICU_setEdgeDetectionType(FALLING);
	}
	else if(ultrasonic_counter==2)
	{
		ultrasonic_time=ICU_getInputCaptureValue();
		ICU_setEdgeDetectionType(RAISING);
	}
}

