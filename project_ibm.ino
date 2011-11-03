#define RED_LED 9
#define GREEN_LED 10
#define BLUE_LED 11

#define MIN_CO2 447
#define GOOD_CO2 457
#define MAX_CO2 467

#define MIN_TEMP 21
#define MAX_TEMP 23

void setup() {                
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
}

int mapBrightness(float temp) {
  float tempTemp = temp - 20;
  tempTemp = tempTemp * 64;
  return tempTemp;
}

void goLeds(float r, float g, float b, int bright) {
  analogWrite(RED_LED, 255 - (bright * r));
  analogWrite(GREEN_LED, 255 - (bright * g));
  analogWrite(BLUE_LED, 255 - (bright * b));
}

float merryGoLoop = MIN_CO2; // max is MAX_CO2
float merryGoLoop2 = MAX_TEMP; // max is MAX_TEMP
int merryGoDir = 1;
int merryGoDir2 = 1;

float fetchTemperature() {
  // temp fetch code here
  // degrees C
  //return 23.69;
  return constrain(merryGoLoop2, MIN_TEMP, MAX_TEMP);
}

float fetchCO2() {
  // co2 fetch code here
  // ppm
  //return 457.20;
  return constrain(merryGoLoop, MIN_CO2, MAX_CO2);
}

void loop() {
  float currentTemperature = fetchTemperature();
  float currentCarbonDioxide = fetchCO2();
  
  // LED brightness corresponds to the current temperature
  // 22C maps to 127 PWM
  // relative: 1C is 63 PWM
  int ledBrightness = mapBrightness(currentTemperature);
  
  // let's work out each led
  // these should ADD UP TO 1
  float red = 0, green = 0, blue = 0;
  if (currentCarbonDioxide < MIN_CO2) {
    red = 1;
  } else if (currentCarbonDioxide > MAX_CO2) {
    blue = 1;
  } else if (currentCarbonDioxide < GOOD_CO2) {
    green = (currentCarbonDioxide - MIN_CO2) / (GOOD_CO2 - MIN_CO2);
    red = 1 - green;
  } else {
    blue = (currentCarbonDioxide - GOOD_CO2) / (MAX_CO2 - GOOD_CO2);
    green = 1 - blue;
  }
  
  // now set the leds!
  goLeds(red, green, blue, ledBrightness);
  
  delay(50);
  
  // mockup code
  merryGoLoop += 0.1 * merryGoDir;
  merryGoLoop2 += 0.05 * merryGoDir2;
  
  if (merryGoLoop > MAX_CO2 || merryGoLoop < MIN_CO2) 
    merryGoDir = -merryGoDir;
    
  if (merryGoLoop2 > MAX_TEMP || merryGoLoop2 < MIN_TEMP)
    merryGoDir2 = -merryGoDir2;
  // end mockup code
}
