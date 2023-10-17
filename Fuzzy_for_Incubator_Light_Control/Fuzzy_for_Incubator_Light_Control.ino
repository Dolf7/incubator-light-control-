#include <Wire.h>
#include <BH1750.h>
#include "fuzzySugeno.h"

// #define BH1750_DEBUG true
BH1750 lightMeter;

//PIN
#define enA 9
#define in1 7
#define in2 6

//Global Variable
const int setPoint = 22; //LUX

float sensorInput;
float LUX, sensorRawValue, sensorReadingRaw;
float errorNow = 0, errorBefore = 0, deltaError = 0;

const float bh1750_operating_voltage = 3.3;
const uint16_t ADC_RESOLUTION = 65535;

// uint16_t bh1750ADCSens; 
int output;

void calLux() {
  LUX = sensorInput;
  // if(LUX < 12) LUX = 12;
  // else if(LUX >32) LUX = 32;
}

void calErr() {
  errorNow = float(setPoint - LUX);
  deltaError = abs(errorNow - errorBefore);
  errorBefore = errorNow;
}

void setLightPWM(int pwm) {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, pwm);
}

float calADC(float raw_value){
  //Calculate Sensor Reading in mV
  return (raw_value / ADC_RESOLUTION * bh1750_operating_voltage) * 1000;
}

void printVariable() {
  
  Serial.println("++++++++++++++++");
  Serial.print("Cahaya : \t");
  Serial.print(LUX);
  Serial.println(" LUX");

  Serial.print("Error Now : \t");
  Serial.println(errorNow);

  Serial.print("Error Before : \t");
  Serial.println(errorBefore);

  Serial.print("Delta Error : \t");
  Serial.println(deltaError);

  Serial.print("PWM Output : \t");
  Serial.println(output);
  Serial.println("++++++++++++++++");
}

void printInAndOut(){
  Serial.print("Sensor Read : \t");
  Serial.print(LUX);
  Serial.println(" LUX");
  Serial.print("Output PWM : \t");
  Serial.println(output);
  
  Serial.print("Sensor Raw Value : ");
  Serial.println((int)sensorRawValue);

  Serial.print("Sensor ADC Value : ");
  Serial.print(calADC(sensorRawValue));
  Serial.println(" mV");

  Serial.println("---");
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE_2);
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  Serial.println("Begin ...");
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorInput = lightMeter.readLightLevel();
  sensorRawValue = lightMeter.readRawLightValue(); //ADC

  calLux();
  calErr();

  fuzzy fuzzy(errorNow, deltaError);
  
  output = int(fuzzy.pwmOuput);
  setLightPWM(output);
  // printVariable();
  printInAndOut();
  // fuzzy.testingOnDevice();

  delay(5000);
}
