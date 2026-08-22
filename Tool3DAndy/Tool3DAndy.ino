#include <Servo.h>

// C++ code
//

///
/// 8 middle steps stepper Motor 24byj-48 class 
/// AS: Andy's Softwares
/// by Andrés Bernárdez (2025)
///

#include"C:\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\arduino.h"

///------------------
#include "gCodeAndy.hpp"


const int BORDER_MARGIN=20;




class stepperAndy{

public:
  
int positionS=0;
int attached=0;

unsigned long delayTime=9000;
int pin1=-1;
int pin2=-1;
int pin3=-1;
int pin4=-1;
  



  stepperAndy(){
    
  }

  stepperAndy(int P1, int P2, int P3, int P4){
    
   Inicializate(P1,P2,P3,P4);
  }
  
  
  void Inicializate(int P1,int P2,int P3, int P4){
    
    pin1=P1;
	  pin2=P2;
    pin3=P3;
	  pin4=P4;
    
    pinMode(pin1,OUTPUT);
    pinMode(pin2,OUTPUT);
    pinMode(pin3,OUTPUT);
    pinMode(pin4,OUTPUT);
    
    attached=1;
    delayTime=9000;
  }

  void detach(){
    attached=0;
    pin1=-1;
    pin2=-1;
    pin3=-1;
    pin4=-1;
    delayTime=9000;
    positionS=0;
  }
  
  void Speed(unsigned long frequency){
  
    //frequency=cicles per minute. 
    //24byj-48 with 64 middle steps per motor cicle and a reduction of 1:64
	  //the 24byj-48 totaly has 4096 stpes per cicle. 
    //frequency/60=cicles per seconds
    //frequency*4096/(60)= steps per seconds
    //60*1000000/(frequency*4096)= microseconds per step.
    if(frequency>0)delayTime=((60*1000000)/(frequency*4096));
    else delayTime=9000;
    if(delayTime<=1) delayTime=2;
   
  
  }
  

  void turnOff(){
    if(pin1!=-1)digitalWrite(pin1,LOW);
    if(pin2!=-1)digitalWrite(pin2,LOW);
    if(pin3!=-1)digitalWrite(pin3,LOW);
    if(pin4!=-1)digitalWrite(pin4,LOW);

  }
  void turnOn(){
    
    if(positionS>0){
      positionS--;
    }
    else {
      positionS=7;
    }
    StepUp();

  }


  void StepUp(){
    
    switch(positionS){
      case 0:	digitalWrite(pin4,LOW);
      			digitalWrite(pin1,HIGH);
      			positionS++;
      			break;
      case 1:	digitalWrite(pin1,HIGH);
      			digitalWrite(pin2,HIGH);
      			positionS++;
      			break;
      case 2:	digitalWrite(pin1,LOW);
      			digitalWrite(pin2,HIGH);
      			positionS++;
      			break;
      case 3: 	digitalWrite(pin2,HIGH);
      			digitalWrite(pin3,HIGH);
      			positionS++;
      			break;
      case 4:	digitalWrite(pin2,LOW);
      			digitalWrite(pin3,HIGH);
      			positionS++;
      			break;
      case 5: 	digitalWrite(pin3,HIGH);
      			digitalWrite(pin4,HIGH);
      			positionS++;
      			break;
      case 6:	digitalWrite(pin3,LOW);
      			digitalWrite(pin4,HIGH);
      			positionS++;
      			break;
      case 7: 
            digitalWrite(pin4,HIGH);
      			digitalWrite(pin1,HIGH);
            positionS=0;
            break;
      
      default:

      			positionS=0;
				break;      
    }
    
    
    
  }
  
  
  void StepDown(){
    
    switch(positionS){
      case 0:	digitalWrite(pin2,LOW);
      			digitalWrite(pin1,HIGH);
      			positionS=7;
      			break;
      case 1:	digitalWrite(pin1,HIGH);
      			digitalWrite(pin2,HIGH);
      			positionS--;
      			break;
      case 2:	digitalWrite(pin3,LOW);
      			digitalWrite(pin2,HIGH);
      			positionS--;
      			break;
      case 3: 	digitalWrite(pin2,HIGH);
      			digitalWrite(pin3,HIGH);
      			positionS--;
      			break;
      case 4:	digitalWrite(pin4,LOW);
      			digitalWrite(pin3,HIGH);
      			positionS--;
      			break;
      case 5: 	digitalWrite(pin3,HIGH);
      			digitalWrite(pin4,HIGH);
      			positionS--;
      			break;
      case 6:	digitalWrite(pin1,LOW);
      			digitalWrite(pin4,HIGH);
      			positionS--;
      			break;
      case 7:
            digitalWrite(pin4,HIGH);
      			digitalWrite(pin1,HIGH);
            positionS--;
            break;
      default:

      			positionS=0;
				break;      
    }
    
    
    
  }
  
  void Steps(int stepsNumber){
    int i;
    if(stepsNumber>0){
      for(i=0;i<stepsNumber;i++){
        StepUp();
		delayMicroseconds(delayTime);
        
      }
      
    }else if(stepsNumber<0)
      for(i=0;i>stepsNumber;i--){
        StepDown();
		delayMicroseconds(delayTime);
        
      }
  }
  
  
  
  
  
  
};

/// @brief variables for pin detection
struct sensor{
  unsigned long milliSecondsWaited=0;
  int pin=2;
  int status=LOW;
  int waiting=LOW;
  int activated=LOW;
  
};
  

/// @brief digital readings can have interference, so when you read a pin you must do it at less twice.
/// @param sIn name of the sensor
/// @param delayTime min time in milliseconds between 2 detections before accept the reading.
void detectSensor(struct sensor *sIn,unsigned long delayTime){
  
  if(sIn->activated==HIGH){
    if(sIn->status==LOW){
      if(digitalRead(sIn->pin)==HIGH){
          if(sIn->waiting==LOW){
            sIn->milliSecondsWaited=millis()+delayTime;
            sIn->waiting=HIGH;
          }
          else if(millis()>sIn->milliSecondsWaited){
              sIn->status=HIGH;
          }
        }
        else{
              sIn->waiting=LOW;
        }
      }
      //if(sIn.status==HIGH)
      
      else if (digitalRead(sIn->pin)==LOW){
          if(sIn->waiting==HIGH){
            sIn->milliSecondsWaited=millis()+delayTime;
            sIn->waiting=LOW;
          }
          else if(millis()>sIn->milliSecondsWaited){
                  sIn->status=LOW;
          }
        }
        else{
                sIn->waiting=HIGH;
        }
  }
}


/// @brief Axes Mode
const int XYMode=0;
const int XZMode=1;
const int YZMode=2;
const int XYZMode=3;

/// @brief measure Mode
const int INCH_MODE=1;
const int MILIMETER_MODE=0;

/// @brief reference Mode
const int RELATIVE=0;
const int ABSOLUTE=1;

//----------

class stepperAndy3D{

 public:

  unsigned long delayTime=9000;

  //// @brief motors
  class stepperAndy motor1;
  class stepperAndy motor2;
  class stepperAndy motor3;
  Servo servo1;

  /// @brief servo limits
  int servoPin;
  int minAngle=45;
  int maxAngle=90;

  /// @brief  limits
  struct sensor limitM11;
  struct sensor limitM12;
  struct sensor limitM21;
  struct sensor limitM22;
  struct sensor limitM31;
  struct sensor limitM32;

  /// @brief  counter is max value for each axis
  long int counterM1=27200;
  long int counterM2=24752;
  long int counterM3=204800;

  /// @brief  max longitude in real value (milimeters) for each motor
  double longitudeM1=200;
  double longitudeM2=182;
  double longitudeM3=1000;
  
  /// @brief  current position for each axis/motor
  long int positionX=0;
  long int positionY=0;
  long int positionZ=0;

  long int referenceX=0;
  long int referenceY=0;
  long int referenceZ=0;

  
  //modes
  int axesM=XYMode;
  int measureMode=MILIMETER_MODE;
  int referenceMode=RELATIVE;


  gCodeAndy gInterface;

  
  
  stepperAndy3D(){
    
  }

  /// @brief This assign the pins for each limit
  /// @param lM11 begining for X axis
  /// @param lM12 end for X axis
  /// @param lM21 begining for Y axis
  /// @param lM22 end for Y axis
  /// @param lM31 begining for Z axis
  /// @param lM32 end for Z axis
  void InicializateLimits(int lM11,int lM12,int lM21, int lM22, int lM31,int lM32){
    

    
    if(lM11>-1){
              limitM11.pin=lM11;
              pinMode(lM11,INPUT);
              limitM11.activated=HIGH;
            }
    if(lM12>-1){
              limitM12.pin=lM12;
              pinMode(lM12,INPUT);
              limitM12.activated=HIGH;
            }
    
    if(lM21>-1){
              limitM21.pin=lM21;
              pinMode(lM21,INPUT);
              limitM21.activated=HIGH;
            }
    if(lM22>-1){
              limitM22.pin=lM22;
              pinMode(lM22,INPUT);
              limitM22.activated=HIGH;
            }
                
    if(lM31>-1){
              limitM31.pin=lM31;
              pinMode(lM31,INPUT);
              limitM31.activated=HIGH;
            }
    if(lM32>-1){
              limitM32.pin=lM32;
              pinMode(lM32,INPUT);
              limitM32.activated=HIGH;
            }

    
  }
  
  
  /// @brief This fuction is same that is used by this.motorN.Inicializate(p1,p2,p3,p4) .
  /// @param number is the motorN where N go from 1 to 3.
  /// @param p1  pin1.
  /// @param p2  pin2.
  /// @param p3  pin3.
  /// @param p4  pin4.
  /// @param speed  revolutions per minute.
  void InicializateMotor(int number,int p1,int p2, int p3, int p4,unsigned long speed){
    
    if(number==1){
      
      motor1.Inicializate(p1,p2,p3,p4);
      motor1.Speed(speed);
    }
    else if(number==2){
      
      motor2.Inicializate(p1,p2,p3,p4);
      motor2.Speed(speed);
    }
    else if(number==3){
      
      motor3.Inicializate(p1,p2,p3,p4);
      motor3.Speed(speed);
    }

    
    
    
  } 
 


 /// @brief This fuction inicializate a servo
  /// @param pin  pin.
 void InicializateServo(int pin){
    servoPin=pin;

 }


 /// @brief turn on servo
 void servoOn(){

    servo1.attach(servoPin,544,2500);

 }

/// @brief stop servo
 void servoOff(){

    if(servo1.attached())servo1.detach();

 }

 /// @brief servo down
 void servoDown(){

    servo1.write(minAngle);

 }

 /// @brief servo up
 void servoUp(){

    servo1.write(maxAngle);

 }

/// @brief Stop all motors and servos
void stopMotors(){

if(motor1.attached==1)motor1.turnOff();
if(motor2.attached==1)motor2.turnOff();
if(motor3.attached==1)motor3.turnOff();

}


  /// @brief Reference in motor's steps from (0,0,0)
  /// @param absoluteX 
  /// @param absoluteY 
  /// @param absoluteZ 
  void setReferencesSteps(long int absoluteX, long int absoluteY, long int absoluteZ){

      referenceX=absoluteX;
      referenceY=absoluteY;
      referenceZ=absoluteZ;


  }

  /// @brief Reference in mm or inches from (0,0,0)
  /// @param absoluteX 
  /// @param absoluteY 
  /// @param absoluteZ 
  void setReferencesMeasure(double absoluteX, double absoluteY, double absoluteZ){

      referenceX=(long int)(absoluteX*((double)counterM1)/longitudeM1);
      referenceY=(long int)(absoluteY*((double)counterM2)/longitudeM2);
      referenceZ=(long int)(absoluteZ*((double)counterM3)/longitudeM3);


  }

  
  /// @brief The default speed is motor1.speed  It will be use for the 3 motors.
  /// @param speed 
  void Speed(unsigned long speed){

    motor1.Speed(speed);
    delayTime = motor1.delayTime;
    motor2.delayTime=delayTime;
    motor3.delayTime=delayTime;
  }
  
  /// @brief When you calibrate there shouldn't be a piece in the machine.
  void Calibrate(){
    
    int finished=1;
    int beginM1=0,beginM2=0,beginM3=0;
    int i,j,k;
    int finishM1=0,finishM2=0,finishM3=0;
    int directionM1=0,directionM2=0,directionM3=0;
  
    
    counterM1=0;
    counterM2=0;
    counterM3=0;
    
    //motor1
    while(finished){
      
      //m1
      if(directionM1==0){
        motor1.StepUp();
      }else if(directionM1==1){
        motor1.StepDown();
        counterM1++;
      }
      //m2
      if(directionM2==0){
        motor2.StepUp();
      }else if(directionM2==1){
        motor2.StepDown();
        counterM2++;
      }
      
      //m3
      if(directionM3==0){
        motor3.StepUp();
      }else if(directionM3==1){
        motor3.StepDown();
        counterM3++;
      }
      
      
      ///  limits detection
      detectSensor(&limitM11,200);
      detectSensor(&limitM12,200);
      detectSensor(&limitM21,200);
      detectSensor(&limitM22,200);
      detectSensor(&limitM31,200);
      detectSensor(&limitM32,200);
      
      delay(9);
      
      detectSensor(&limitM11,200);
      detectSensor(&limitM12,200);
      detectSensor(&limitM21,200);
      detectSensor(&limitM22,200);
      detectSensor(&limitM31,200);
      detectSensor(&limitM32,200);
      
      
      
      
      
     /// limits readings: 
      
      if(limitM11.status==HIGH){
        
        if(directionM1==0){
          directionM1=1;
          i=1001;
          
        } else if(directionM1==1){
            if(i>0){
              i--;
            }
            else{
              directionM1=2;
              finishM1=1;
              positionX=1;
            }
        }
          
      }
      
      if(limitM12.status==HIGH){
        
        if(directionM1==0){
          i=1001;
          directionM1=1;
          
        } else if(directionM1==1){
          if(i>0){
              i--;
            }
            else{
              directionM1=2;
              finishM1=1;
              positionX=1;
            }
        }
          
      }
      
      if(limitM21.status==HIGH){
        
        if(directionM2==0){
          directionM2=1;
          j=1001;
          
        } else if(directionM2==1){

          if(j>0){
              j--;
            }
            else{
              directionM2=2;
              finishM2=1;
              positionY=1;
            }
        }
          
      }
      
      if(limitM22.status==HIGH){
        
        if(directionM2==0){
          directionM2=1;
          j=1001;
          
        } else if(directionM2==1){
          if(j>0){
              j--;
            }
          else{
            directionM2=2;
            positionY=1;
            finishM2=1;
          }
        }
          
      }
      
      if(limitM31.status==HIGH){
        
        if(directionM3==0){
          directionM3=1;
          k=1001;
          
        } else if(directionM3==1){
          if(k>0){
              k--;
            }
          else{
            directionM3=2;
            positionZ=1;
            finishM3=1;
          }
        }
          
      }
      
      if(limitM32.status==HIGH){
        
        if(directionM3==0){
          directionM3=1;
          k=1001;
        } else if(directionM3==1){

          if(k>0){
              k--;
            }
          else{
            directionM3=2;
            positionZ=1;
            finishM3=1;
          }
        }
          
      }
      
     	///all detections finished?
      
      if(finishM1&&finishM2&&finishM3){
        finished=0;
      }
      
      
      
      
    }
    

    motor1.turnOff();
    motor2.turnOff();
    motor3.turnOff();

    counterM1++;
    counterM2++;
    counterM3++;

    
  }


  void setMeasureMode(int msrMode){

    if(measureMode==MILIMETER_MODE && msrMode==INCH_MODE){

      longitudeM1=longitudeM1/25.4;
      longitudeM2=longitudeM2/25.4;
      longitudeM3=longitudeM3/25.4;
      
      measureMode=INCH_MODE;

    }
    else if(measureMode==INCH_MODE && msrMode==MILIMETER_MODE){

      longitudeM1=longitudeM1*25.4;
      longitudeM2=longitudeM2*25.4;
      longitudeM3=longitudeM3*25.4;
      
      measureMode=MILIMETER_MODE;

    }



  }



  /// @brief This mode can calibrate only 2 axes, letting the 3rd one free for porpouses like plotting in 2D. The user should create another way to calibrate the 3rd axis in order the application.
  /// @param AxesMode it could be XYMode YZMode or XZMode
  void Calibrate(int AxesMode){
    
    int finished=1;
    int beginM1=0,beginM2=0,beginM3=0;
    int finishM1=0,finishM2=0,finishM3=0;
    int directionM1=0,directionM2=0,directionM3=0;
    int i=0,j=0,k=0;

    

    switch (AxesMode)
    {
    case YZMode:
                counterM2=0;
                counterM3=0;
                break;
     case XZMode:
                counterM1=0;
                counterM3=0;
                break;
    
    case XYMode:
                counterM1=0;
                counterM2=0;
                break;
    case XYZMode:
    default: 
                counterM1=0;
                counterM2=0;
                counterM3=0;
                break;
    

    }


    
    //motor1
    while(finished){
      
      //m1
      if(AxesMode!=YZMode){
            if(directionM1==0){
              motor1.StepUp();
            }else if(directionM1==1){
              motor1.StepDown();
              counterM1++;
            }

      }
      //m2
      if(AxesMode!=XZMode){
            if(directionM2==0){
              motor2.StepUp();
            }else if(directionM2==1){
              motor2.StepDown();
              counterM2++;
            }
      }
      //m3
      if(AxesMode!=XYMode){
          if(directionM3==0){
            motor3.StepUp();
          }else if(directionM3==1){
            motor3.StepDown();
            counterM3++;
          }
      }
      
      
      ///  limits detection
      detectSensor(&limitM11,200);
      detectSensor(&limitM12,200);
      detectSensor(&limitM21,200);
      detectSensor(&limitM22,200);
      detectSensor(&limitM31,200);
      detectSensor(&limitM32,200);
      
      delay(9);// velocidad 1rpm
      
      detectSensor(&limitM11,200);
      detectSensor(&limitM12,200);
      detectSensor(&limitM21,200);
      detectSensor(&limitM22,200);
      detectSensor(&limitM31,200);
      detectSensor(&limitM32,200);
      
      
      
      
      
     /// limits readings: 
      
  
     /// limits readings: 
      
      if(limitM11.status==HIGH){
        
        if(directionM1==0){
          directionM1=1;
          i=1001;
          
        } else if(directionM1==1){
            if(i<=0){
              directionM1=2;
              finishM1=1;
              positionX=0;
            }
        }
          
      }
      
      if(limitM12.status==HIGH){
        
        if(directionM1==0){
          i=1001;
          directionM1=1;
          
        } else if(directionM1==1){
          if(i<=0){
              directionM1=2;
              finishM1=1;
              positionX=0;
            }
        }
          
      }
      
      if(limitM21.status==HIGH){
        
        if(directionM2==0){
          directionM2=1;
          j=1001;
          
        } else if(directionM2==1){

          if(j<=0){
              directionM2=2;
              finishM2=1;
              positionY=0;
            }
        }
          
      }
      
      if(limitM22.status==HIGH){
        
        if(directionM2==0){
          directionM2=1;
          j=1001;
          
        } else if(directionM2==1){
          if(j<=0){
            directionM2=2;
            positionY=0;
            finishM2=1;
          }
        }
          
      }
      
      if(limitM31.status==HIGH){
        
        if(directionM3==0){
          directionM3=1;
          k=1001;
          
        } else if(directionM3==1){
          if(k<=0){
            directionM3=2;
            positionZ=0;
            finishM3=1;
          }
        }
          
      }
      
      if(limitM32.status==HIGH){
        
        if(directionM3==0){
          directionM3=1;
          k=1001;
        } else if(directionM3==1){

          if(k<=0){
            directionM3=2;
            positionZ=0;
            finishM3=1;
          }
        }
          
      }

      if(i)i--;
      if(j)j--;
      if(k)k--;
      
     	///all detections finished?
      switch (AxesMode)
      {
      case XYMode:
                  if(finishM1&&finishM2){
                    finished=0;
                  }
                  break;
      case YZMode:
                  if(finishM2&&finishM3){
                    finished=0;
                  }
                  break;
      case XZMode:

                  if(finishM1&&finishM3){
                    finished=0;
                  }
                  break;
      case XYZMode:
      default:    if(finishM1&&finishM2&&finishM3){
                     finished=0;
                  }
                  break;
                 
      }


     
    

      switch (AxesMode)
      {
      case XYMode:
                counterM1++;
                counterM2++;

                break;



      case YZMode:
                counterM2++;
                counterM3++;
                break;
      
      case XZMode:
                counterM1++;
                counterM3++;
                break;
      case XYZMode:
      default:  
                counterM1++;
                counterM2++;
                counterM3++;
                break;
                
      }

      
    }
    
      switch (AxesMode)
      {
      case XYMode:
                motor1.turnOff();
                motor2.turnOff();
                break;



      case YZMode:
                motor2.turnOff();
                motor3.turnOff();
                break;
      
      case XZMode:
                motor1.turnOff();
                motor3.turnOff();
                break;
      case XYZMode:
      default: 
               motor1.turnOff();
               motor2.turnOff();
               motor3.turnOff();
               break;
       
       
        break;
      }

  }


  
  /// @brief Here there should be the real longitude value betwen the limits
  /// @param longM1 max longitude for X
  /// @param longM2 max longitude for Y
  /// @param longM3 max longitude for Z
  void assignMeassure(double longM1,double longM2, double longM3){
    longitudeM1=longM1;
    longitudeM2=longM2;
    longitudeM3=longM3;
    
    
  }






  /// @brief This function scan if the current position is near a border.
  /// @param isInBorder If the current position is in a border it will be 1. If not, 0.
  void borderWatchdog(int * isInBorder){

    int activateDelayBorder=*isInBorder;

    
    if((axesM!=YZMode)&&(positionX<BORDER_MARGIN||positionX>counterM1-BORDER_MARGIN)){
   
        detectSensor(&limitM11,200);
        detectSensor(&limitM12,200);
        activateDelayBorder=1;
    
      }

       if((axesM!=XZMode)&&(positionY<BORDER_MARGIN||positionY>counterM2-BORDER_MARGIN)){
   
        detectSensor(&limitM21,200);
        detectSensor(&limitM22,200);
        activateDelayBorder=1;
    
      }
      
       if((axesM!=XYMode)&&(positionZ<BORDER_MARGIN||positionZ>counterM3-BORDER_MARGIN)){
   
        detectSensor(&limitM31,200);
        detectSensor(&limitM32,200);
        activateDelayBorder=1;
    
      }


      *isInBorder=activateDelayBorder;
  }



/// @brief it move all the motors to the X1,Y1,Z1 position
/// @param X1 X destiny
/// @param Y1 Y destiny
/// @param Z1 Z destiny
void goTo3D(long int X1,long int Y1,long int Z1){
    

    long int diffX=X1-positionX;
    long int diffY=Y1-positionY;
    long int diffZ=Z1-positionZ;    
    
    int directionX=1;
    int directionY=1;
    int directionZ=1;
    int N=0;
    int activateDelayBorder=0;

    long int stepX=0;
    long int stepY=0;
    long int stepZ=0;
    
    long int step_i_X=0;
    
    long int step_i_Y=0;
    
    long int step_i_Z=0;
    
    long int nextStep_i_X=0;
    long int nextStep_i_Y=0;
    long int nextStep_i_Z=0;
    

    long int i=0;

 
   



    if(diffX<0){
        directionX=-1;
    }
    
    if(diffY<0){
        directionY=-1;
    }
    
    if(diffZ<0){
        directionZ=-1;
    }
    
   
    
    if(diffX*directionX<diffY*directionY) {

            if(diffZ*directionZ<diffY*directionY){
                  N=directionY*diffY;
            }
            else{
               N=directionZ*diffZ;
            }
        }
    else{
            if(diffZ*directionZ>diffX*directionX){
                N=directionZ*diffZ;
            }
            else{
              
                N=directionX*diffX;
            }
    }

    
    
    stepX=N;
    stepY=N;
    stepZ=N;
    
    
    if(diffX!=0){
        stepX=N/(diffX*directionX);
    }
    else{
        stepX=N+1;
    }
     
    if(diffY!=0){
        stepY=N/(diffY*directionY);
    }
    else{
        stepY=N+1;
    }
    
    if(diffZ!=0){
        stepZ=N/(diffZ*directionZ);
    }
    else{
        stepZ=N+1;
    }
    
   

    step_i_X=stepX;
    
    step_i_Y=stepY;
    
    step_i_Z=stepZ;
    
    nextStep_i_X=step_i_X;
    nextStep_i_Y=step_i_Y;
    nextStep_i_Z=step_i_Z;
    

   
    
    
    for (i=1;i<=N;i++){
        

      
      
     ///--------------BORDER WATCHDOG (if it is near borders it must try to detect limits)
      

      borderWatchdog(&activateDelayBorder);

     
      //delay
      if(activateDelayBorder){
        delay(5);
        activateDelayBorder=0;
      }

      borderWatchdog(&activateDelayBorder);

      if( axesM!=YZMode){
          if((limitM11.status==HIGH|| limitM12.status==HIGH )&&positionX<BORDER_MARGIN) positionX=0;
          else if((limitM11.status==HIGH|| limitM12.status==HIGH )&&positionX>counterM1-BORDER_MARGIN) positionX=counterM1;
      }
      if( axesM!=XZMode){
          if((limitM21.status==HIGH|| limitM22.status==HIGH )&&positionY<BORDER_MARGIN) positionY=0;
          else if((limitM21.status==HIGH|| limitM22.status==HIGH )&&positionY>counterM2-BORDER_MARGIN) positionY=counterM2;
      }
      if( axesM!=XYMode){
          if((limitM31.status==HIGH|| limitM32.status==HIGH )&&positionZ<BORDER_MARGIN) positionZ=0;
          else if((limitM31.status==HIGH|| limitM32.status==HIGH )&&positionZ>counterM3-BORDER_MARGIN) positionZ=counterM3;
      }

      ///------------------end Border watchdog





       if( axesM!=YZMode){
      
          if(i>=nextStep_i_X ) {
              nextStep_i_X=nextStep_i_X+step_i_X;
            

              if(directionX==1 && positionX<counterM1){
              
                motor1.StepUp();
                positionX++;

              }
              else if(directionX==-1 && positionX>0)  {
        
                motor1.StepDown();
                positionX--;
              }
  
          }
       }
       if( axesM!=XZMode){
      
          if(i>=nextStep_i_Y) {
              nextStep_i_Y=nextStep_i_Y+step_i_Y;
              
              if(directionY==1 && positionY<counterM2){
           
                motor2.StepUp();
                positionY++;

              }
              else if(directionY==-1 && positionY>0) {
              
                motor2.StepDown();
                positionY--;
              }

              
          }
       }

       if( axesM!=XYMode){
          if(i>=nextStep_i_Z ) {
              nextStep_i_Z=nextStep_i_Z+step_i_Z;
              
              if(directionZ==1 && positionZ<counterM3 ){
                motor3.StepUp();
                positionZ++;

              }
              else if(directionZ==-1 && positionZ>0) {
                motor3.StepDown();
                positionZ--;
              }
              
          }
       }

        
        delayMicroseconds(delayTime);
   
   
      }



    

}







  /// @brief Line movement.
  /// @param fromX 
  /// @param toX 
  /// @param fromY 
  /// @param toY 
  /// @param fromY 
  /// @param toZ 
  void line3D(long int fromX,long int fromY,long int fromZ,long int toX,long int toY,long int toZ){
    
    goTo3D(fromX,fromY,fromZ);
      
    //You could activate something here-----
    
    
    //----------
      
    goTo3D(toX,toY,toZ);
    stopMotors();
    
  }
    


/// @brief This function draw a Circle arc in two axes (XY,YZ or XZ). "from" position must be diferent that "to" position.
/// @param fromX initial X
/// @param fromY initial Y
/// @param fromZ initial Z
/// @param toX   X destination
/// @param toY   Y destination
/// @param toZ   Z destination
/// @param centerX  X center of the arc
/// @param centerY Y center of the arc
/// @param centerZ Z center of the arc
/// @param modeAxis indicates the axes of the arc (XYmode,YZmode or XZmode)
/// @param radius radius of the arc
/// @param angleDirection 1 is hour direction, -1 is anti-hour direction
void  plainCircleArc(long int fromX,long int fromY,long int fromZ,long int toX,long int toY,long int toZ,long int centerX,long int centerY,long int centerZ,int modeAxis,double radius,int angleDirection){
    
    
    long int currentI=0;
    long int currentJ=0;
    long int beforeI=0;
    long int beforeJ=0;
    long int nextI=0;
    long int nextJ=0;
    long int centerI=0;
    long int centerJ=0;
    long int centerK=0;
    long int endI=0;
    long int endJ=0;
    long int diffCNI=0;
    long int diffCNJ=0;
    long int diffBNI=0;
    long int diffBNJ=0;
    int activateI=0;
    int activateJ=0;
    

    //double CosI=0;
    //double SinJ=0;
    //double PI2=PI/2;
    //double PI32=3*PI/2;     

    double auxiliar=0.0;
    double angle=0;
    double endAngle=0;
    double R=0;

//    class stepperAndy *motorI,*motorJ;


    R=radius;



        if(positionX!=fromX || positionY!=fromY || positionZ!=fromZ )
        goTo3D(fromX,fromY,fromZ);
        //activate somthing here-------

      
        //-----------------------
  
       



      if(modeAxis==XYMode) {
          currentI=fromX;
          currentJ=fromY;
          centerI=centerX;
          centerJ=centerY;
          centerK=centerZ;
          endI=toX;
          endJ=toY;
      }
      else if (modeAxis==YZMode) {
          currentI=fromY;
          currentJ=fromZ;
          centerI=centerY;
          centerJ=centerZ;
          centerK=centerX;
          endI=toY;
          endJ=toZ;
      }
      else if (modeAxis==XZMode) {
          currentI=fromX;
          currentJ=fromZ;
          centerI=centerX;
          centerJ=centerZ;
          centerK=centerY;
          endI=toX;
          endJ=toZ;
      }
          
    
    //looking for exceptions    

    if(currentI!=centerI){
        auxiliar=atan2((currentJ-centerJ),(currentI-centerI));
        angle=180*R*(auxiliar/PI);
    }
    else{ 
      if(currentJ>centerJ){ 
        angle=90*R;
      }
      else{ 
        angle=-90*R;
      }
    }
   

    if(endI!=centerI) {
        auxiliar=atan2((endJ-centerJ),(endI-centerI));
        endAngle=180*R*(auxiliar/PI);
    }
    else {
      if (endJ>centerJ){
        endAngle=90*R;
      }
      else {
        endAngle=-90*R;
      }
    }

              

                auxiliar=((2*angle*PI)/(R*360));
                nextI=(centerI+round(R*cos(auxiliar)));
                nextJ=(centerJ+round(R*sin(auxiliar)));
                beforeI=nextI;
                beforeJ=nextJ;
                currentI=nextI;
                currentJ=nextJ;

    //starting the arc


    // hour way
      if(angleDirection==1){

        //correction:
            if(angle<endAngle){
                endAngle=-360*R+endAngle;
            }
            
 
                

          while(angle>=endAngle){
              while((nextI-currentI==0)&&(nextJ-currentJ==0)){
                  
                angle=angle-1;
                
                auxiliar=((2*angle*PI)/(R*360.0));

                

                nextI=(centerI+round(R*cos(auxiliar)));
                nextJ=(centerJ+round(R*sin(auxiliar)));
                
               
              
              }
            
          
            
            
            
           
            diffCNI=nextI-currentI;
            diffCNJ=nextJ-currentJ;
            diffBNI=nextI-beforeI;
            diffBNJ=nextJ-beforeJ;
            
            if((diffCNI>0)&&(diffBNI>diffCNI)) {
                activateI=1;
            }
            else if ((diffCNI<0)&&(diffBNI<diffCNI)) {
                activateI=1;
            }
            
            
            if((diffCNJ>0)&&(diffBNJ>diffCNJ)) {
                activateJ=1;
            }
            else if ((diffCNJ<0)&&(diffBNJ<diffCNJ)) {
                activateJ=1;
            }
                            
            if(activateI==1||activateJ==1) {
                if     (modeAxis==XYMode) goTo3D(currentI,currentJ,centerK);
                else if(modeAxis==YZMode) goTo3D(centerK,currentI,currentJ);
                else if(modeAxis==XZMode) goTo3D(currentI,centerK,currentJ);
                 
            
                 
                 
            }
            
           
            if(activateI==1)
                beforeI=nextI;
  

            
            if(activateJ==1)
                   beforeJ=nextJ;
                   

        
        
            
            activateI=0;
            activateJ=0;
            
           
            currentI=nextI;
            currentJ=nextJ;
            
            
          
        }
          
               
        

      }
      // anti-hour way
      else if(angleDirection==-1){


        //correction:
        if(angle>endAngle){
            endAngle=+360*R+endAngle;
          }

        while(angle<endAngle){
            while((nextI-currentI==0)&&(nextJ-currentJ==0)){
            
              angle=angle+1;
              auxiliar=2*PI*(angle/(R*360.0));
              nextI=(centerI+round(R*cos(auxiliar)));
              nextJ=(centerJ+round(R*sin(auxiliar)));
            
            }
              
            
           
            
           
            diffCNI=nextI-currentI;
            diffCNJ=nextJ-currentJ;
            diffBNI=nextI-beforeI;
            diffBNJ=nextJ-beforeJ;
            
            if((diffCNI>0)&&(diffBNI>diffCNI)) {
                activateI=1;
            }
            else if ((diffCNI<0)&&(diffBNI<diffCNI)) {
                activateI=1;
            }
            
            
            if((diffCNJ>0)&&(diffBNJ>diffCNJ)) {
                activateJ=1;
            }
            else if ((diffCNJ<0)&&(diffBNJ<diffCNJ)) {
                activateJ=1;
            }
                            
            if(activateI==1||activateJ==1) {
                if     (modeAxis==XYMode) goTo3D(currentI,currentJ,centerK);
                else if(modeAxis==YZMode) goTo3D(centerK,currentI,currentJ);
                else if(modeAxis==XZMode) goTo3D(currentI,centerK,currentJ);
                 
                 
            }
            
           
            if(activateI==1)
                beforeI=nextI;
  

            
            if(activateJ==1)
                   beforeJ=nextJ;
            
            activateI=0;
            activateJ=0;
            
           
            currentI=nextI;
            currentJ=nextJ;
            
            
          
        }
     
      }

    stopMotors();
    
}


int gCodeHandler(char gCodeString[]){

  long int newX=0,newY=0,newZ=0,centerX=0,centerY=0,centerZ=0;
  double radius;

  gInterface.setGString(gCodeString);


  gInterface.parseGCode();

  switch(gInterface.gCode){

    case G0_CODE: 

                  delayTime=5000;


                  if(longitudeM1>0&&longitudeM2>0&&longitudeM3>0){
                    newX= (long int)(gInterface.outX*((double)counterM1)/longitudeM1);
                    newY= (long int)(gInterface.outY*((double)counterM2)/longitudeM2);
                    newZ= (long int)(gInterface.outZ*((double)counterM3)/longitudeM3);   
                  
                  
                  if(referenceMode==RELATIVE){
                    newX+= positionX;
                    newY+= positionY;
                    newZ+= positionZ;
                  }
                  else if (referenceMode==ABSOLUTE){
                    newX+= referenceX;
                    newY+= referenceY;
                    newZ+= referenceZ;
                  }
                
                    
                    
                   if(axesM==XYMode){
                    
                      if(newX>=0&&newX<=counterM1 && newY>=0&&newY<=counterM2 ){
                          goTo3D(newX,newY,positionZ);
                          stopMotors();

                          return(1);

                      }
                      else return(-1002);
                    }
                    if(axesM==XZMode){
                    
                      if(newX>=0&&newX<=counterM1 && newZ>=0&&newZ<=counterM3 ){
                          goTo3D(newX,positionY,newZ);
                          stopMotors();
                          return(1);

                      }
                      else return(-1002);
                    }
                    if(axesM==YZMode){
                    
                      if(newY>=0&&newY<=counterM2 && newZ>=0&&newZ<=counterM3 ){
                          goTo3D(positionX,newY,newZ);
                          stopMotors();
                          return(1);

                      }
                      else return(-1002);
                    }
                    if(axesM==XYZMode){
                    
                      if(newX>=0&&newX<=counterM1 && newY>=0&&newY<=counterM2 && newZ>=0&&newZ<=counterM3 ){
                          goTo3D(positionX,newY,newZ);
                          stopMotors();
                          return(1);

                      }
                      else return(-1002);
                    }

                  }
                  else return(-501);

                  break;           
    case G1_CODE: 
    
                  
                  if(gInterface.outF>0&&counterM1>0){


                    delayTime=(unsigned long)((60*1000000)/(((double)counterM1/longitudeM1)*gInterface.outF));




                  }
    
                  else delayTime=9000;

                 if(longitudeM1>0&&longitudeM2>0&&longitudeM3>0){

                  
                    newX=(long int)(gInterface.outX*((double)counterM1)/longitudeM1);
                    newY=(long int)(gInterface.outY*((double)counterM2)/longitudeM2);
                    newZ=(long int)(gInterface.outZ*((double)counterM3)/longitudeM3);                  
                    
                    if(referenceMode==RELATIVE){
                      newX+= positionX;
                      newY+= positionY;
                      newZ+= positionZ;
                    }
                    else if (referenceMode==ABSOLUTE){
                      newX+= referenceX;
                      newY+= referenceY;
                      newZ+= referenceZ;
                    }
                



                    if(axesM==XYMode){
                    
                      if(newX>=0&&newX<=counterM1 && newY>=0&&newY<=counterM2 ){
                          goTo3D(newX,newY,positionZ);
                          stopMotors();
                          return(1);

                      }
                      else return(-1002);
                    }
                    if(axesM==XZMode){
                    
                      if(newX>=0&&newX<=counterM1 && newZ>=0&&newZ<=counterM3 ){
                          goTo3D(newX,positionY,newZ);
                          stopMotors();

                          return(1);

                      }
                      else return(-1002);
                    }
                    if(axesM==YZMode){
                    
                      if(newY>=0&&newY<=counterM2 && newZ>=0&&newZ<=counterM3 ){
                          goTo3D(positionX,newY,newZ);
                          
                          stopMotors();

                          return(1);

                      }
                      else return(-1002);
                    }
                    if(axesM==XYZMode){
                    
                      if(newX>=0&&newX<=counterM1 && newY>=0&&newY<=counterM2 && newZ>=0&&newZ<=counterM3 ){
                          goTo3D(positionX,newY,newZ);
                         stopMotors();

                          return(1);

                      }
                      else return(-1002);
                    }



                  }
                  else return(-501);

                  break;           
    case G2_CODE: 

                  if(gInterface.outF>0&&counterM1>0){


                    delayTime=(unsigned long)((60*1000000)/(  ((double)counterM1)/longitudeM1)*gInterface.outF);




                  }
    
                  else delayTime=4000;



                  switch (axesM)
                        {
                        case XYMode:
                                   
                                    if(longitudeM1>0&&longitudeM2>0){

                                    
                                      newX=(long int)(gInterface.outX*((double)counterM1)/longitudeM1);
                                      newY=(long int)(gInterface.outY*((double)counterM2)/longitudeM2);
                                                      
                                      centerX=(long int)(gInterface.outI*((double)counterM1)/longitudeM1);
                                      centerY=(long int)(gInterface.outJ*((double)counterM2)/longitudeM2);
                                      
                                      
                                      if(referenceMode==RELATIVE){
                                        newX+= positionX;
                                        newY+= positionY;
                                        newZ+= positionZ;
                                        centerX+=positionX;
                                        centerY+=positionY;
                                        centerZ=positionZ;
                                      }
                                      else if (referenceMode==ABSOLUTE){
                                        newX+= referenceX;
                                        newY+= referenceY;
                                        newZ+= positionZ;
                                        centerX+= referenceX;
                                        centerY+= referenceY;
                                        centerZ= positionZ;
                                      }





                                      radius=sqrt( pow((double)(newX-centerX),2)  + pow((double)(newY-centerY),2)  );


                                      if(newX>0&&newX<counterM1 && newY>0&&newY<counterM2 &&  radius>0){
                                          
                                           plainCircleArc(positionX,positionY,positionZ,newX,newY,newZ,centerX,centerY,centerZ,axesM,radius,1);
                                           return(1);
                                      }
                                      else return(-1003);
                                    }
                                    else return(-501);
                          break;

                          case YZMode:
                                   
                                    if(longitudeM2>0&&longitudeM3>0){

                                    
                                     
                                      newY=positionY+ (long int)(gInterface.outY*((double)counterM2)/longitudeM2);
                                      newZ=positionZ+ (long int)(gInterface.outZ*((double)counterM3)/longitudeM3);              
                                      
                                      centerY=positionY+(long int)(gInterface.outJ*((double)counterM2)/longitudeM2);
                                      centerZ=positionZ+ (long int)(gInterface.outK*((double)counterM3)/longitudeM3);
                                      

                                      if(referenceMode==RELATIVE){
                                        newX+= positionX;
                                        newY+= positionY;
                                        newZ+= positionZ;
                                        centerX=positionX;
                                        centerY+=positionY;
                                        centerZ+=positionZ;
                                      }
                                      else if (referenceMode==ABSOLUTE){
                                        newX+= positionX;
                                        newY+= referenceY;
                                        newZ+= referenceZ;
                                        centerX= positionX;
                                        centerY+= referenceY;
                                        centerZ+= referenceZ;
                                      }


                                      radius=sqrt( pow((double)(newY-centerY),2)  + pow((double)(newZ-centerZ),2)  );


                                      if( newY>0&&newY<counterM2 && newZ>0&&newZ<counterM3 && radius>0){
                                          
                                           plainCircleArc(positionX,positionY,positionZ,newX,newY,newZ,centerX,centerY,centerZ,axesM,radius,1);
                                           return(1);
                                      }
                                      else return(-1003);
                                    }
                                    else return(-501);
                          break;

                          case XZMode:
                                   
                                    if(longitudeM1>0&&longitudeM3>0){

                                    
                                      newX=positionX+ (long int)(gInterface.outX*((double)counterM1)/longitudeM1);
                                      
                                      newZ=positionZ+ (long int)(gInterface.outZ*((double)counterM3)/longitudeM3);                               
                                      centerX=positionX+(long int)(gInterface.outI*((double)counterM1)/longitudeM1);
                                      
                                      centerZ=positionZ+ (long int)(gInterface.outK*((double)counterM3)/longitudeM3);
                                      

                                      if(referenceMode==RELATIVE){
                                        newX+= positionX;
                                        newY+= positionY;
                                        newZ+= positionZ;
                                        centerX+=positionX;
                                        centerY=positionY;
                                        centerZ+=positionZ;
                                      }
                                      else if (referenceMode==ABSOLUTE){
                                        newX+= referenceX;
                                        newY+= positionY;
                                        newZ+= referenceZ;
                                        centerX+= referenceX;
                                        centerY= positionY;
                                        centerZ+= referenceZ;
                                      }




                                      radius=sqrt( pow((double)(newX-centerX),2)  + pow((double)(newZ-centerZ),2)  );


                                      if(newX>0&&newX<counterM1 && newZ>0&&newZ<counterM3 && radius>0){
                                          
                                           plainCircleArc(positionX,positionY,positionZ,newX,newY,newZ,centerX,centerY,centerZ,axesM,radius,1);
                                           return(1);
                                      }
                                      else return(-1003);
                                    }
                                    else return(-501);
                          break;
                        
                        default:
                                    return(-502);
                          break;
                        }
                        





                  

                  break;  

                          
    case G3_CODE: 
    
                    if(gInterface.outF>0&&counterM1>0){


                    delayTime=(unsigned long)((60*1000000)/(((double)counterM1/longitudeM1)*gInterface.outF));




                  }
    
                  else delayTime=4000;



                  switch (axesM)
                        {
                        case XYMode:
                                   
                                    if(longitudeM1>0&&longitudeM2>0){

                                    
                                      newX=positionX+ (long int)(gInterface.outX*((double)counterM1)/longitudeM1);
                                      newY=positionY+ (long int)(gInterface.outY*((double)counterM2)/longitudeM2);
                                      newZ=positionZ;                  
                                      centerX=positionX+(long int)(gInterface.outI*((double)counterM1)/longitudeM1);
                                      centerY=positionY+(long int)(gInterface.outJ*((double)counterM2)/longitudeM2);
                                      centerZ=positionZ;
                                      
                                      radius=sqrt( pow((double)(newX-centerX),2)  + pow((double)(newY-centerY),2)  );


                                      if(newX>0&&newX<counterM1 && newY>0&&newY<counterM2 &&  radius>0){
                                          
                                           plainCircleArc(positionX,positionY,positionZ,newX,newY,newZ,centerX,centerY,centerZ,axesM,radius,-1);
                                          
                                           return(1);
                                      }
                                      else return(-1003);
                                    }
                                    else return(-501);
                          break;

                          case YZMode:
                                   
                                    if(longitudeM2>0&&longitudeM3>0){

                                    
                                      newX=positionX;
                                      newY=positionY+ (long int)(gInterface.outY*((double)counterM2)/longitudeM2);
                                      newZ=positionZ+ (long int)(gInterface.outZ*((double)counterM3)/longitudeM3);              
                                      centerX=positionX;
                                      centerY=positionY+(long int)(gInterface.outJ*((double)counterM2)/longitudeM2);
                                      centerZ=positionZ+ (long int)(gInterface.outK*((double)counterM3)/longitudeM3);
                                      
                                      radius=sqrt( pow((double)(newY-centerY),2)  + pow((double)(newZ-centerZ),2)  );


                                      if( newY>0&&newY<counterM2 && newZ>0&&newZ<counterM3 && radius>0){
                                          
                                           plainCircleArc(positionX,positionY,positionZ,newX,newY,newZ,centerX,centerY,centerZ,axesM,radius,-1);
                                         
                                           return(1);
                                      }
                                      else return(-1003);
                                    }
                                    else return(-501);
                          break;

                          case XZMode: 
                                   
                                    if(longitudeM1>0&&longitudeM3>0){

                                    
                                      newX=positionX+ (long int)(gInterface.outX*((double)counterM1)/longitudeM1);
                                      newY=positionY;
                                      newZ=positionZ+ (long int)(gInterface.outZ*((double)counterM3)/longitudeM3);                               
                                      centerX=positionX+(long int)(gInterface.outI*((double)counterM1)/longitudeM1);
                                      centerY=positionY;
                                      centerZ=positionZ+ (long int)(gInterface.outK*((double)counterM3)/longitudeM3);
                                      
                                      radius=sqrt( pow((double)(newX-centerX),2)  + pow((double)(newZ-centerZ),2)  );


                                      if(newX>0&&newX<counterM1 && newZ>0&&newZ<counterM3 && radius>0){
                                          
                                           plainCircleArc(positionX,positionY,positionZ,newX,newY,newZ,centerX,centerY,centerZ,axesM,radius,-1);
                                       
                                           return(1);
                                      }
                                      else return(-1003);
                                    }
                                    else return(-501);
                          break;
                        
                        default:
                                    return(-502);
                          break;
                        }
                        





                  

                  break;         
    case G17_CODE: 
                    axesM=XYMode;
                    return(1);
                    break;          
    case G18_CODE: 
                    axesM=XYMode;
                    return(1);
                    break;   
    case G19_CODE: 
                    axesM=XYMode;
                    return(1);
                    break;   
    case G20_CODE: 
                    setMeasureMode(INCH_MODE);
                    return(1);
                    break;          
    case G21_CODE: 
                    setMeasureMode(MILIMETER_MODE);
                    return(1);
                    break; 
    case G28_CODE: 
                    Calibrate(axesM);
                    return(1);
                    break;          
    case G90_CODE: 
                    referenceMode=ABSOLUTE;
                    return(1);
                    break;          
    case G91_CODE: 
                    referenceMode=RELATIVE;
                    return(1);
                    break;          
    case G4_CODE: 
                    //pause miliseconds
                    if(gInterface.outP>=1) {
                      delay((unsigned long)gInterface.outP);
                      return(1);
                    }
                    else return(-504);
                    
                    break;           
    case G92_CODE: 
                    if(longitudeM1>0&&longitudeM2>0&&longitudeM3>0){

                  
                      newX=(long int)(gInterface.outX*((double)counterM1)/longitudeM1);
                      newY=(long int)(gInterface.outY*((double)counterM2)/longitudeM2);
                      newZ=(long int)(gInterface.outZ*((double)counterM3)/longitudeM3);                  

                      setReferencesSteps(newX,newY,newZ);
                      return(1);

                    }
                    else return(-501);
                    
                    break;          
    case G_UNDEFINED_CODE: 
    
                          return(-510);
                          break;  
         
   

    case M0_CODE:         
    case M112_CODE: 
                    //Emergency stop: restart is needed!!
                    motor1.turnOff();
                    motor2.turnOff();
                    motor3.turnOff();

                    // infinity loop
                    while(1==1){
                      delay(666);

                    }
                    return(-666);
                    break;     
    case M6_CODE:  // set minAngle and maxAngle
                  
                  newX=0;
                  
                  if(gInterface.outJ>0){
                       minAngle=gInterface.outJ;
                       newX=1;
                    }


                   if(gInterface.outK>0){
                       maxAngle=gInterface.outK;
                       newX=1;
                    } 

                    if(newX) {
                      return(1);
                      break;
                    }
                    else{
                      return(-606);
                    }
    case M7_CODE:  // servo down
                    servoOn();
		            delay(500);
                    servoDown();
                    delay(1000);
                    servoOff();
                    return(1);
                    break;
    
     case M8_CODE:  // servo up
                    servoOn();
		            delay(500);
                    servoUp();
                    delay(1000);
                    servoOff();
                    return(1);
                    break;
       
    case M100_CODE: //set Longitudes
                    newX=0;
                    newY=0;
                    newZ=0;
                    if(gInterface.outX>0){
                       longitudeM1=gInterface.outX;
                       newX=1;
                    }
                    if(gInterface.outY>0){
                       longitudeM2=gInterface.outY;
                       newY=1;
                    }
                    if(gInterface.outZ>0){
                       longitudeM3=gInterface.outZ;
                       newZ=1;
                    }

                    if(newX||newY||newZ) {

                       Serial.print("CounterM1:");
                       Serial.print(counterM1);
                       Serial.print(" LongitudeM1:");
                       Serial.println(longitudeM1);
                       Serial.print("CounterM2:");
                       Serial.print(counterM2);
                       Serial.print(" LongitudeM2:");
                       Serial.println(longitudeM2);
                       Serial.print("CounterM3:");
                       Serial.print(counterM3);
                       Serial.print(" LongitudeM3:");
                       Serial.println(longitudeM3);
                
                      return(1);
                      }
                    else return(-404);

                    break;         
    case M17_CODE:  
                    motor1.turnOn();
                    motor2.turnOn();
                    motor3.turnOn();
                    return(1);
                    break;          
    case M18_CODE: 
                    motor1.turnOff();
                    motor2.turnOff();
                    motor3.turnOff();
                    return(1);
                    break;          
    
    case M114_CODE: 
                     //send postition
                    return(114);
                    break;         
    case M_UNDEFINED_CODE: 
                            return(-511);
                            break;  
    default: 
               return(-1024);
               break;







  }





}






};














stepperAndy3D tool3D;








void setup()
{
  Serial.begin(9600);

  tool3D.InicializateMotor(1,3,4,5,6,2);
  //tool3D.InicializateMotor(2,9,10,11,12,120);
  tool3D.InicializateMotor(2,A1,A2,A3,A4,2);
  tool3D.InicializateLimits(2,7,A0,A5,-1,-1);

  tool3D.InicializateServo(9);
  //tool3D.servoOn();
  //tool3D.servoDown();
  tool3D.axesM=XYMode;
  tool3D.setMeasureMode(MILIMETER_MODE);
  tool3D.referenceMode=RELATIVE;
  tool3D.setReferencesSteps(0,0,0);
  tool3D.assignMeassure(200,182,1000);
  tool3D.Speed(2);
  delay(1000);
  //tool3D.Calibrate(XYMode);

   Serial.println("3D Tool ready!");
  
}


char stringIn[32]="";
char character=0;
int ready=1;
int i=0;
int returned=-1;


void loop()
{

 
  Serial.println("Insert G-Code command:");
  
  i=0;
  ready=1;
  while(ready){

    if(Serial.available()){

      character=Serial.read();
      if(character=='\0'||character=='\n'||i>31){
        ready=0;
        stringIn[i]='\0';
      }
      else{

        stringIn[i]=character;
        i++;
      }


    }
    

  }

  Serial.print("gCode:<");
  Serial.print(stringIn);
  Serial.println(">");
  

  returned=tool3D.gCodeHandler(stringIn);

  //print Current Position
  if(returned==114){

    Serial.println("Pos:");
    Serial.print("X");
    Serial.println(  ((double)tool3D.positionX)*tool3D.longitudeM1/((double)tool3D.counterM1) );
    Serial.print("Y");
    Serial.println(  ((double)tool3D.positionY)*tool3D.longitudeM2/((double)tool3D.counterM2) );
    Serial.print("Z");
    Serial.println(  ((double)tool3D.positionZ)*tool3D.longitudeM3/((double)tool3D.counterM3) );

  }
    //other:
  else if(returned==1){
    Serial.print("OK:");
    Serial.println(returned);
  }
  //errors:
  else if(returned<0){
     Serial.print("Error:");
     Serial.println(returned);
  }

  
  delay(20);

}

//25544 30635 220     28089.5  127    139
//22380 27254 182     24817      136   149
//27388  200  136
//25475  182  139
