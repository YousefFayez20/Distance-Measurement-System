/*
 * ultrasonic.h
 *
 *  Created on: Jul 13, 2024
 *      Author: DELL
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_
#include "std_types.h"


#define Trigger_PORT     PORTB_ID
#define Trigger_PIN      PIN5_ID
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
void Ultrasonic_init(void);
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
void Ultrasonic_Trigger(void);



/*
 * • Description
➢ Send the trigger pulse by using Ultrasonic_Trigger function.
➢ Start the measurements by the ICU from this moment.
• Inputs: None
• Return: The measured distance in Centimeter
 *
 */
uint16 Ultrasonic_readDistance(void);


/*
 * • Description
➢ This is the call back function called by the ICU driver.
➢ This is used to calculate the high time (pulse time) generated by
the ultrasonic sensor.
• Inputs: None
• Return: None
 *
 */

void Ultrasonic_edgeProcessing(void);


#endif /* ULTRASONIC_H_ */
