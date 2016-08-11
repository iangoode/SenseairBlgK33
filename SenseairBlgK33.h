/*
	SenseairBlgK33.h library for Senseair CO2 sensor: 0-20% BLG K33
	Created by Ian G. Goode, August 11, 2016.
	Adapted from "CO2 meter K-series Example Interface" by Andrew Robinson, April 1, 2011
	CO2 Meter <co2meter.com> URL: http://co2meters.com/Documentation/AppNotes/AN113-K33MicroComm.pdf
	Reseased to public domain.
*/

#ifndef SenseairBlgK33_h
#define SenseairBlgK33_h
 
#if ARDUINO >= 100
  	#include "Arduino.h"
#else
  	#include "WProgram.h"
  	#include "pins_arduino.h"
  	#include "WConstants.h"
	#include "Wire.h"
#endif
 
class BLG 
{
	public:
		BLG();
		void wakeSensor();
		void begin();
		void initPoll();
		double readCO2();
		double readTemp();
		double readRh();
		void calibrate(); // DO NOT USE, this function needs further research for proper implementation
		// URL: https://cdn.shopify.com/s/files/1/0019/5952/files/calibration_procedure.pdf?1243553821
	private:
		int _address;
		int co2_value;
		int tempVal;
		byte i;
		byte bufferArray;
};
 
#endif