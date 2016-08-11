#include <SenseairBlgK33.h>

BLG blg;

void setup() {
  Serial.begin(9600);
  blg.begin();
  pinMode(5, OUTPUT);
  analogWrite(5, 255);
  Serial.println("RESET");
}

void loop() {
  Serial.println("Request reading");
  blg.wakeSensor();
  blg.initPoll();
  
  Serial.println("wait 16s for reading ");
  delay(16000);
  
  blg.wakeSensor();
  double CO2 = blg.readCO2();
  blg.wakeSensor();
  double Temp = blg.readTemp();
  blg.wakeSensor();
  double Rh = blg.readRh();
  
  Serial.print("CO2: ");Serial.print(CO2);Serial.print(" ppm, ");
  Serial.print("Temp: ");Serial.print(Temp);Serial.print(" C, ");
  Serial.print("Rh: ");Serial.print(Rh);Serial.println(" %");
  
  Serial.println("wait further 9s to cool down"); // keep >25s between initPoll()
  delay(9000);
}

