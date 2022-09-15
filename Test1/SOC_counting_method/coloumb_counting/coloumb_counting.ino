class coloumb_counting
{
  public :
    coloumb_counting(double init_state,double batt_capacity,double update_period)
    {
      charge_state = init_state;
      count_period = update_period;
      battery_capacity = batt_capacity;    
    }

    double count_state(double current)
    {
      charge_state = charge_state-current*count_period/(battery_capacity*3600.0);
      return charge_state;
    }
  private :
    double charge_state = 100;
    double battery_capacity;
    double count_period;
};
//================================================================================
#include <Wire.h>
#include <Adafruit_INA219.h>

  unsigned long currentTime = millis();
  unsigned long previousTime = 0;

  float shuntV = 0;
  float busV = 0;
  float current_mA = 0;
  float power_mW = 0;
  float loadV = 0;
  float charge_state;

  const long checkPeriod = 0.001;
  unsigned long count = 0;

  Adafruit_INA219 ina219;
  coloumb_counting batt1(100.0, 300.0, checkPeriod);

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  while(!Serial){
    delay(1);
  }

  if(!ina219.begin()){
    Serial.println("INA219 Not Found");
    while(1){delay(10);}
  }

  Serial.println("INA219 Active");
}

void loop() {
  // put your main code here, to run repeatedly:

  shuntV = ina219.getShuntVoltage_mV();
  busV = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  power_mW = ina219.getPower_mW();
  loadV = busV + (shuntV / 1000);
  
  if(currentTime - previousTime > checkPeriod)
  {
    previousTime = currentTime;
    count++;

    charge_state = batt1.count_state(current_mA);
  }

  if(count == 2000)
  {
    count = 0;
    Serial.print("Capacity State:   "); Serial.print(charge_state); Serial.println(" %");
    Serial.println("");
  }

  currentTime = millis();
  //checking
  //Serial.println(currentTime - previousTime);
}
