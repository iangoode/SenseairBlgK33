# SenseairBlgK33
Arduino library for Senseair CO2 sensor 0-20% BLG K33

Library handles communication with BLG-K33 sensor board including:
  - proper wakeup procedure by toggling I2C line high-low (check registers for different microprocessors)
  - request for readings (initPoll)
  - reads CO2 concentration in ppm
  - reads Temperature in degC
  - reads Relative Humidity in %RH
  - checksum on I2C data (returns -1 if there is an error)

Future work:
  - calibration routine: implemented but recommend DO NOT USE

Developed on Moteino R4 using ATMega328p

Helpful tips:
  - make sure BLG K33 board is powered by external 9-12V supply between G0 and VBatt
  - leave 16 seconds between request for reading (initPoll) and reading CO2, Temp and Humidity values
  - leave >25 seconds between each reading request to allow air in chamber to cool down
  - hardware connections are as follows:
    BLG K33 G0 --> Arduino GND
    BLG K33 SDA --> Arduino A4(SDA) - change as required for board
    BLG K33 CLK --> Arduino A5(SCK) - change as required for board
    BLG K33 G0 --> GND power source
    BLG K33 VBatt --> V+ power source (9-12V DC)
