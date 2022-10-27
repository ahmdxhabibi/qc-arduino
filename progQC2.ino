#include "global.h"
#include "pid.h"
#include "millisventi.h"
#include "looprun.h"
#include "EasyNextionLibrary.h"
EasyNex myNex(Serial);

int Number_read ;

int fes = A1;
int hon = A0;
int flow = A2;
int val = 0;
float vFes = 0;
float vHon = 0;
float inVal = 0;
float cmVal = 0;
float bar = 0;
float mbar = 0;
double nflow = 0;
double flowmap = 0;
double teg = 0;
uint16_t adc = 0;
unsigned long lcon, lsen;

float mapPecahan(long x, long fromLow, long fromHigh, float toLow, float toHigh)
{
  return (x - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
}

void setup()
{
  mySerial.begin(115200);
  pinMode (A0, INPUT);
  pinMode (A1, INPUT);
  pinMode (A2, INPUT);
  pinMode (6, OUTPUT);
  pinMode (5, OUTPUT);
  pinMode (4, OUTPUT);
  //digitalWrite (6, HIGH);
  //digitalWrite (7, LOW);
  setWait(0, 20);
}

void loop()
{

  if (millis () - lcon > 50)
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

    // Flow Sensor
    nflow = analogRead (flow);
    flowmap = map (nflow, 204, 1023, 0, 100);
    lmin = flowmap / 1.5;

    looprun();
    lcon = millis();

  }

  if (millis() - lsen > 500)
  {
    myNex.writeStr("nflow.txt", String(lmin));
    myNex.writeStr("npressure.txt", String(mbarVal));
    Number_read = myNex.readNumber("n0.val");

    if (Number_read == 100) {
      myNex.writeStr("nflow.txt", String(100));
      myNex.writeStr("npressure.txt", String(100));
    }
    else if (Number_read == 200) {
      myNex.writeStr("nflow.txt", String(200));
      myNex.writeStr("npressure.txt", String(200));
    }

    mySerial.print("val : ");
    mySerial.print (adc);
    mySerial.print("    ||voltage : ");
    mySerial.print (vFes);
    mySerial.print("    ||mbarVal1 : ");
    mySerial.print (mbarVal);
    mySerial.print("    ||mbarH : ");
    mySerial.print (mbarH);
    mySerial.print("    ||E: ");
    mySerial.print(error);
    mySerial.print("    ||Ex: ");
    mySerial.print(Ex);
    mySerial.print("    ||u : ");
    mySerial.print(u);
    mySerial.print ("   ||Target   : " );
    mySerial.print (target);
    mySerial.print ("   ||PWM : ");
    mySerial.print(PWM);
    mySerial.print ("   ||VAC : ");
    mySerial.print(VAC);
    mySerial.print ("   ||PEEP : ");
    mySerial.print(PEEP);
    mySerial.print ("   ||Pdrop : ");
    mySerial.print(Pdrop);
    mySerial.print ("   ||C : ");
    mySerial.print(c);
    mySerial.print (" Dflow : ");
    mySerial.print (nflow);
    mySerial.print (" || teg : ");
    mySerial.print (teg);
    mySerial.print (" || lmin : ");
    mySerial.println (lmin);
    mySerial.print ("   ||State : ");
    mySerial.println (state_now);
    lsen = millis();
  }


}
