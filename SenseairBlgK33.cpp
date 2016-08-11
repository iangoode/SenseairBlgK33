/*
	SenseairBlgK33.h library for Senseair CO2 sensor: 0-20% BLG K33
	Created by Ian G. Goode, August 11, 2016.
	Adapted from "CO2 meter K-series Example Interface" by Andrew Robinson, April 1, 2011
	CO2 Meter <co2meter.com> URL: http://co2meters.com/Documentation/AppNotes/AN113-K33MicroComm.pdf
	Reseased to public domain.
*/

#if ARDUINO >= 100
  	#include "Arduino.h"
#else
  	#include "WProgram.h"
  	#include "pins_arduino.h"
  	#include "WConstants.h"
	#include "Wire.h"
#endif

#include "SenseairBlgK33.h"
#include "Wire.h"

BLG::BLG() {
	_address = 0x68; // default I2C address of BLG sensor
}

void BLG::begin() {
	Wire.begin();
}

void BLG::wakeSensor() {
	TWCR &= ~(1 << 2); // disable I2C engine
  	DDRC |= (1 << 4); // set pin to OUTPUT
  	PORTC &= ~(1 << 4); // pull pin LOW
  	delay(1);
  	PORTC |= (1 << 4); // pill pin HIGH
  	TWCR |= (1 << 2); // enable I2C
  	delay(1);
}

void BLG::initPoll() {
	Wire.beginTransmission(_address);
  	Wire.write(0x11);
  	Wire.write(0x00);
  	Wire.write(0x60);
  	Wire.write(0x35);
  	Wire.write(0xA6);
  	Wire.endTransmission();
  	delay(20);
  	Wire.requestFrom(_address, 2);

    byte i = 0;
    byte bufferArray[2] = {0, 0};

    while (Wire.available()) {
      bufferArray[i] = Wire.read();
      i++;
    }
}

double BLG::readCO2() {
  	Wire.beginTransmission(_address);
  	Wire.write(0x22);
  	Wire.write(0x00);
  	Wire.write(0x08);
  	Wire.write(0x2A);
  	Wire.endTransmission();

  	delay(20); // wait for sensor to write data to RAM

 	 Wire.requestFrom(_address, 4);

 	 byte i = 0;
 	 byte bufferArray[4] = {0, 0, 0, 0};

	while (Wire.available()) {
	  bufferArray[i] = Wire.read();
	  i++;
	}

	tempVal = 0;
	tempVal |= bufferArray[1] & 0xFF;
	tempVal = tempVal << 8;
	tempVal |= bufferArray[2] & 0xFF;

	byte sum = 0;   // for checksum
	sum = bufferArray[0] + bufferArray [1] + bufferArray[2];  // overflow check

	if (sum == bufferArray[3]) { 
		// success condition
		return ((double) tempVal / (double) 1);
	} else {
		// failure condition
		return (double) - 1;
	}
}

double BLG::readTemp() {

	Wire.beginTransmission(_address);
	Wire.write(0x22);
	Wire.write(0x00);
	Wire.write(0x12);
	Wire.write(0x34);
	Wire.endTransmission();

	delay(20);

	Wire.requestFrom(_address, 4);

	byte i = 0;
	byte bufferArray[4] = {0, 0, 0, 0};

	while (Wire.available()) {
		bufferArray[i] = Wire.read();
		i++;
	}

	tempVal = 0;
	tempVal |= bufferArray[1] & 0xFF;
	tempVal = tempVal << 8;
	tempVal |= bufferArray[2] & 0xFF;

	byte sum = 0;
	sum = bufferArray[0] + bufferArray[1] + bufferArray[2];

	if (sum == bufferArray[3]) {
		// success condition
		return ((double) tempVal / (double) 100);
	} else {
		// failure condition
		return (double)-1;
	}
}

double BLG::readRh() {
	Wire.beginTransmission(_address);
	Wire.write(0x22);
	Wire.write(0x00);
	Wire.write(0x14);
	Wire.write(0x36);
	Wire.endTransmission();

	delay(20);

	Wire.requestFrom(_address, 4);

	byte i = 0;
	byte bufferArray[4] = {0, 0, 0, 0};

	while (Wire.available()) {
		bufferArray[i] = Wire.read();
		i++;
	}

	tempVal = 0;
	tempVal |= bufferArray[1] & 0xFF;
	tempVal = tempVal << 8;
	tempVal |= bufferArray[2] & 0xFF;

	byte sum = 0;
	sum = bufferArray[0] + bufferArray[1] + bufferArray[2];

	if (sum == bufferArray[3]) {
		return ((double) tempVal / (double) 100);
	} else {
		return (double)-1;
	}
}

void calibrate() {
	// DO NOT USE, this function needs further research for proper implementation
	// URL: https://cdn.shopify.com/s/files/1/0019/5952/files/calibration_procedure.pdf?1243553821
	wakeSensor();
	Wire.beginTransmission(BLGK33);
	Wire.write(0x12);
	Wire.write(0x00);
	Wire.write(0x42);
	Wire.write(0x7C);
	Wire.write(0x06);
	Wire.write(0xD6);
	Wire.endTransmission();

}