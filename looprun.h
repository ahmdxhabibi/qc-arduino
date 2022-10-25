//FSM VAC STECHOQ
//
#define TOTAL_STATE 3
//

int state_now = 0;
float target = 100;
float targetH =5;
void looprun(){
//Serial.print (state_now);
  switch(state_now){
    case 0  : { state_now = 1;
                //motorInit();
                setWait (0,10);
                //digitalWrite (motor,HIGH);
                //digitalWrite (valve,LOW);
                break;
    }
    case 1  : {           //proses vakum menuju target
                //kendali
                //nilai sebelum divakum .\, presss H sebelum divakum
                PWM = getPID(mbarVal, target);
                 //analogWrite (motor,PWM);
                if ( mbarVal > target * 1.2)
                 {
                  PWM = 0;
                  analogWrite(m1, 0);
                  analogWrite(m2, PWM);
                // analogWrite (motor,PWM);
                 }
                if ( mbarVal < target *0.5)
                  {
                  PWM = PWM;
                  analogWrite(m1, 0);
                  analogWrite(m2, PWM);
                 }
                  analogWrite(m1, 0);
                  analogWrite(m2, PWM);
                  digitalWrite (valve,HIGH);
                  PEEP = mbarH;
               if ( isBeeping (0) && mbarH < 7 &&  mbarVal >(0.8 * target)) //honeywell < 7 &&
               {
                state_now = 2;
                setWait(0,1);
                //VAC = 10000;
               }
                break;
    }
    case 2  :  { //buka valve
              
                digitalWrite (valve,LOW);
                //setWait(0,5);
                //VACpress = min() VAC,mbarH;
                //VACpress = min(VAC,mbarH);
                VAC = min(VAC,mbarH);
                if (isBeeping (0) && mbarVal < 80 )
                {
                  state_now = 3;
                  setWait(0,1); 
                }
                break;
    } 
    case 3  :     { // tutup valve
                digitalWrite (valve,HIGH);
                state_now = 1;
                Pdrop = PEEP - VAC;
                Pdrop = constrain (Pdrop, 0.5, 100); //0.5
                
                c = targetH/Pdrop;
                
                target = pow(c,0.06) * target; //0.06
                target = constrain (target, 50, 500);
                setWait(0,10);
    }
    default : break;
  }
}
