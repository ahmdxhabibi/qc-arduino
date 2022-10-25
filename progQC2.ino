#include "global.h"
#include "pid.h"
#include "millisventi.h"
#include "looprun.h"
#include <SoftwareSerial.h>
SoftwareSerial mySerial(0, 1);


int fes = A1;
int hon = A0;
//int val = 0;
//float vFes = 0;
//float vHon = 0;
//float inVal = 0;
//float cmVal = 0;
//float bar = 0;
//float mbar = 0;
int val = random(0,100);
float vFes = random(0,100);
float vHon = random(0,100);
float inVal = random(0,100);
float cmVal = random(0,100);
float bar = random(0,100);
float mbar = random(0,100);
uint16_t adc = 0;
unsigned long lcon, lsen;


float mapPecahan(long x, long fromLow, long fromHigh, float toLow, float toHigh)
{
  return (x - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
}

void setup()
{
  mySerial.begin(115200);
  Serial.begin(9600);
  pinMode (6, OUTPUT);
  pinMode (7, OUTPUT);

  //digitalWrite (6, HIGH);
  //digitalWrite (7, LOW);
  setWait(0, 20);
}

void loop()
{
  
  if (millis () - lcon > 5)
  {
    // sensor SPAN Festo
     adc = analogRead(fes);
    //val = analogRead(a);
    vFes = (adc * 5.00) / 1023.0;
    mbarVal = (5 - vFes) * 125;

    //Sensor HoneyWell
    val = analogRead(hon);
    vHon = (val * 5.00) / 1024.0;
    mbarH = (vHon - 2.5) / 0.02;

    float x1 = map(adc, 255, 1023, -1 * 100, 1 * 100) / 100.0;
    float x2 = mapPecahan(adc, 255, 1023, -500, 0);
    mbar = (x2 * 1000);
    looprun();
    lcon = millis();
  }

  if (millis() - lsen > 500)
  {
    Serial.print("val : ");
    Serial.print (adc);
//    mySerial.print("nFlow.val=");
//    mySerial.print();
//    mySerial.write("0xff");
//    mySerial.write("0xff");
//    mySerial.write("0xff");
    mySerial.print("nPressure.val=");
    mySerial.print(mbarVal);
    mySerial.write("0xff");
    mySerial.write("0xff");
    mySerial.write("0xff");
    Serial.print("    ||voltage : ");
    Serial.print (vFes);
    Serial.print("    ||mbarVal1 : ");
    Serial.print (mbarVal);
    Serial.print("    ||mbarH : ");
    Serial.print (mbarH);
    Serial.print("    ||E: ");
    Serial.print(error);
    Serial.print("    ||Ex: ");
    Serial.print(Ex);
    Serial.print("    ||u : ");
    Serial.print(u);
    Serial.print ("   ||Target   : " );
    Serial.print (target);
    Serial.print ("   ||PWM : ");
    Serial.print(PWM);
    Serial.print ("   ||VAC : ");
    Serial.print(VAC);
    Serial.print ("   ||PEEP : ");
    Serial.print(PEEP);
    Serial.print ("   ||Pdrop : ");
    Serial.print(Pdrop);
    Serial.print ("   ||C : ");
    Serial.print(c);
    Serial.print ("   ||State : ");
    Serial.println (state_now);
    lsen = millis();
  }

}
