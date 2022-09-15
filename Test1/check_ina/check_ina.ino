#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while(!Serial){
    delay(1);
  }

  uint32_t currentFreq;
  if(!ina219.begin()){
    Serial.println("INA219 Not Found");
    while(1){delay(10);}
  }

  Serial.println("INA219 Active");
}

void loop() {
  // put your main code here, to run repeatedly:
  float shuntV = 0;
  float busV = 0;
  float current_mA = 0;
  float power_mW = 0;
  float loadV = 0;
  
  shuntV = ina219.getShuntVoltage_mV();
  busV = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  power_mW = ina219.getPower_mW();
  loadV = busV + (shuntV / 1000);

  Serial.print("Bus Voltage:   "); Serial.print(busV); Serial.println(" V");
  Serial.print("Shunt Voltage: "); Serial.print(shuntV); Serial.println(" mV");
  Serial.print("Load Voltage:  "); Serial.print(loadV); Serial.println(" V");
  Serial.print("Current:       "); Serial.print(current_mA); Serial.println(" mA");
  Serial.print("Power:         "); Serial.print(power_mW); Serial.println(" mW");
  Serial.println("");

  delay(2000);
}
