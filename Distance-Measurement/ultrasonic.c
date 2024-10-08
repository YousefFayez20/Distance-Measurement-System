/*
 * ultrasonic.c
 *
 *  Created on: Jul 13, 2024
 *      Author: DELL
 */
#include "icu.h"
#include "gpio.h"
#include "ultrasonic.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include <util/delay.h> /* For the delay functions */
#include <avr/io.h> /* For the delay functions */

uint8 edgeCount = 0;
uint16 DistanceTime = 0;

/*
 * • Description
➢ Initialize the ICU driver as required.
➢ Setup the ICU call back function.
➢ Setup the direction for the trigger pin as output pin through the
GPIO driver.
• Inputs: None
• Return: None
 *
 */


void Ultrasonic_init(void){
	ICU_ConfigType ICU_Configurations = {F_CPU_8,RAISING};
	ICU_init(&ICU_Configurations);
	ICU_setCallBack(Ultrasonic_edgeProcessing);
	GPIO_setupPinDirection(Trigger_PORT,Trigger_PIN,PIN_OUTPUT);
	SREG |= (1<<7);
}



/*
 *
 * • Description
➢ Send the Trigger pulse to the ultrasonic.
• Inputs: None
• Return: None
 *
 *
 *
 */
void Ultrasonic_Trigger(void){
	GPIO_writePin(Trigger_PORT, Trigger_PIN, LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(Trigger_PORT, Trigger_PIN, LOGIC_LOW);
}


/*
 * • Description
➢ Send the trigger pulse by using Ultrasonic_Trigger function.
➢ Start the measurements by the ICU from this moment.
• Inputs: None
• Return: The measured distance in Centimeter
 *
 */
uint16 Ultrasonic_readDistance(void){
	uint16 distance = 0;
	uint16 TimeCount = 0;
	 Ultrasonic_Trigger();
	 TimeCount = DistanceTime;
	 distance = TimeCount / 58 +1 ;
	 return distance;
}

/*
 * • Description
➢ This is the call back function called by the ICU driver.
➢ This is used to calculate the high time (pulse time) generated by
the ultrasonic sensor.
• Inputs: None
• Return: None
 *
 */

void Ultrasonic_edgeProcessing(void){
	edgeCount++;
	if(edgeCount == 1){
		ICU_clearTimerValue();
		ICU_setEdgeDetectionType(FALLING);
	}
	else if(edgeCount == 2){
		DistanceTime = ICU_getInputCaptureValue();
		ICU_setEdgeDetectionType(RAISING);
		edgeCount = 0;
	}
}







