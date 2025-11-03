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

unsigned long delayTime=10000;
int pin1;
int pin2;
int pin3;
int pin4;
  

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
    
    delayTime=2000;
  }
  
  void Speed(unsigned long frequency){
  
    //frequency=cicles per minute. 
    //24byj-48 with 64 middle steps per motor cicle and a reduction of 1:64
	  //the 24byj-48 totaly has 4096 stpes per cicle. 
    //frequency/60=cicles per seconds
    //frequency*4096/(60)= steps per seconds
    //60*1000000/(frequency*4096)= microseconds per step.
    if(frequency>0)delayTime=((60*1000000)/(frequency*4096));
    else delayTime=1000;
    if(delayTime<=1) delayTime=2;
   
  
  }
  

  void turnOff(){
    digitalWrite(pin1,LOW);
    digitalWrite(pin2,LOW);
    digitalWrite(pin3,LOW);
    digitalWrite(pin4,LOW);

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
  
};
  

/// @brief digital readings can have interference, so when you read a pin you must do it at less twice.
/// @param sIn name of the sensor
/// @param delayTime min time in milliseconds between 2 detections before accept the reading.
void detectSensor(struct sensor *sIn,unsigned long delayTime){
  
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


/// @brief Axes Mode
const int XYMode=0;
const int XZMode=1;
const int YZMode=2;

/// @brief measure Mode
const int INCH_MODE=0;
const int MILIMETER_MODE=0;

/// @brief reference Mode
const int RELATIVE=0;
const int ABSOLUTE=1;

//----------

class stepperAndy3D{

 public:

  unsigned long delayTime=2000;

  //// @brief motors
  class stepperAndy motor1;
  class stepperAndy motor2;
  class stepperAndy motor3;

  /// @brief  limits
  struct sensor limitM11;
  struct sensor limitM12;
  struct sensor limitM21;
  struct sensor limitM22;
  struct sensor limitM31;
  struct sensor limitM32;

  /// @brief  counter is max value for each axis
  long int counterM1=204800;
  long int counterM2=204800;
  long int counterM3=204800;

  /// @brief  max longitude in real value (milimeters) for each motor
  double longitudeM1=1000;
  double longitudeM2=1000;
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
    limitM11.pin=lM11;
    limitM12.pin=lM12;
    limitM21.pin=lM21;
    limitM22.pin=lM22;
    limitM31.pin=lM31;
    limitM32.pin=lM32;
    
    pinMode(lM11,INPUT);
    pinMode(lM12,INPUT);
    pinMode(lM21,INPUT);
    pinMode(lM22,INPUT);
    pinMode(lM31,INPUT);
    pinMode(lM32,INPUT);
    
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
      detectSensor(&limitM11,4);
      detectSensor(&limitM12,4);
      detectSensor(&limitM21,4);
      detectSensor(&limitM22,4);
      detectSensor(&limitM31,4);
      detectSensor(&limitM32,4);
      
      delay(5);
      
      detectSensor(&limitM11,4);
      detectSensor(&limitM12,4);
      detectSensor(&limitM21,4);
      detectSensor(&limitM22,4);
      detectSensor(&limitM31,4);
      detectSensor(&limitM32,4);
      
      
      
      
      
     /// limits readings: 
      
      if(limitM11.status==HIGH){
        
        if(directionM1==0){
          directionM1=1;
          
        } else if(directionM1==1){
          directionM1=2;
          finishM1=1;
        }
          
      }
      
      if(limitM12.status==HIGH){
        
        if(directionM1==0){
          directionM1=1;
          
        } else if(directionM1==1){
          directionM1=2;
          finishM1=1;
        }
          
      }
      
      if(limitM21.status==HIGH){
        
        if(directionM2==0){
          directionM2=1;
          
        } else if(directionM2==1){
          directionM2=2;
          finishM2=1;
        }
          
      }
      
      if(limitM22.status==HIGH){
        
        if(directionM2==0){
          directionM2=1;
          
        } else if(directionM2==1){
          directionM2=2;
          positionX=1;
          finishM2=1;
        }
          
      }
      
      if(limitM31.status==HIGH){
        
        if(directionM3==0){
          directionM3=1;
          
        } else if(directionM3==1){
          directionM3=2;
          positionY=1;
          finishM3=1;
        }
          
      }
      
      if(limitM32.status==HIGH){
        
        if(directionM3==0){
          directionM3=1;
          
        } else if(directionM3==1){
          directionM3=2;
          positionZ=1;
          finishM3=1;
        }
          
      }
      
     	///all detections finished?
      
      if(finishM1&&finishM2&&finishM3){
        finished=0;
      }
      
      
      
      
    }
    
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
    default:
                counterM1=0;
                counterM2=0;
                break;
    }


    
    //motor1
    while(finished){
      
      //m1
      if(AxesMode==XYMode||AxesMode==XZMode){
            if(directionM1==0){
              motor1.StepUp();
            }else if(directionM1==1){
              motor1.StepDown();
              counterM1++;
            }

      }
      //m2
      if(AxesMode==XYMode||AxesMode==YZMode){
            if(directionM2==0){
              motor2.StepUp();
            }else if(directionM2==1){
              motor2.StepDown();
              counterM2++;
            }
      }
      //m3
      if(AxesMode==XYMode||AxesMode==XZMode){
          if(directionM3==0){
            motor3.StepUp();
          }else if(directionM3==1){
            motor3.StepDown();
            counterM3++;
          }
      }
      
      
      ///  limits detection
      detectSensor(&limitM11,4);
      detectSensor(&limitM12,4);
      detectSensor(&limitM21,4);
      detectSensor(&limitM22,4);
      detectSensor(&limitM31,4);
      detectSensor(&limitM32,4);
      
      delay(5);
      
      detectSensor(&limitM11,4);
      detectSensor(&limitM12,4);
      detectSensor(&limitM21,4);
      detectSensor(&limitM22,4);
      detectSensor(&limitM31,4);
      detectSensor(&limitM32,4);
      
      
      
      
      
     /// limits readings: 
      
      if(limitM11.status==HIGH){
        
        if(directionM1==0){
          directionM1=1;
          
        } else if(directionM1==1){
          directionM1=2;
          finishM1=1;
        }
          
      }
      
      if(limitM12.status==HIGH){
        
        if(directionM1==0){
          directionM1=1;
          
        } else if(directionM1==1){
          directionM1=2;
          finishM1=1;
        }
          
      }
      
      if(limitM21.status==HIGH){
        
        if(directionM2==0){
          directionM2=1;
          
        } else if(directionM2==1){
          directionM2=2;
          finishM2=1;
        }
          
      }
      
      if(limitM22.status==HIGH){
        
        if(directionM2==0){
          directionM2=1;
          
        } else if(directionM2==1){
          directionM2=2;
          positionX=1;
          finishM2=1;
        }
          
      }
      
      if(limitM31.status==HIGH){
        
        if(directionM3==0){
          directionM3=1;
          
        } else if(directionM3==1){
          directionM3=2;
          positionY=1;
          finishM3=1;
        }
          
      }
      
      if(limitM32.status==HIGH){
        
        if(directionM3==0){
          directionM3=1;
          
        } else if(directionM3==1){
          directionM3=2;
          positionZ=1;
          finishM3=1;
        }
          
      }
      
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
      default:

                  if(finishM1&&finishM3){
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
      default:
                counterM1++;
                counterM3++;
                break;
        break;
      }

      
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

    if(positionX<BORDER_MARGIN||positionX>counterM1-BORDER_MARGIN){
   
        detectSensor(&limitM11,4);
        detectSensor(&limitM12,4);
        activateDelayBorder=1;
    
      }

       if(positionY<BORDER_MARGIN||positionY>counterM2-BORDER_MARGIN){
   
        detectSensor(&limitM21,4);
        detectSensor(&limitM22,4);
        activateDelayBorder=1;
    
      }
      
       if(positionZ<BORDER_MARGIN||positionZ>counterM3-BORDER_MARGIN){
   
        detectSensor(&limitM31,4);
        detectSensor(&limitM32,4);
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
    
   

    step_i_X=directionX*stepX;
    
    step_i_Y=directionY*stepY;
    
    step_i_Z=directionZ*stepZ;
    
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

      if((limitM11.status==HIGH|| limitM12.status==HIGH )&&positionX<BORDER_MARGIN) positionX=1;
      else if((limitM11.status==HIGH|| limitM12.status==HIGH )&&positionX>counterM1-BORDER_MARGIN) counterM1=positionX+1;
      if((limitM21.status==HIGH|| limitM22.status==HIGH )&&positionY<BORDER_MARGIN) positionY=1;
      else if((limitM21.status==HIGH|| limitM22.status==HIGH )&&positionY>counterM2-BORDER_MARGIN) counterM2=positionY+1;
      if((limitM31.status==HIGH|| limitM32.status==HIGH )&&positionZ<BORDER_MARGIN) positionZ=1;
      else if((limitM31.status==HIGH|| limitM32.status==HIGH )&&positionZ>counterM3-BORDER_MARGIN) counterM3=positionZ+1;

      ///------------------end Border watchdog






        if(i>=nextStep_i_X &&positionX>0&&positionX<counterM1) {
            nextStep_i_X=nextStep_i_X+step_i_X;
           

            if(directionX==1){
              motor1.StepUp();
              positionX++;

            }
            else if(directionX==-1) {
              motor1.StepDown();
              positionX--;
            }




         
        }
        if(i>=nextStep_i_Y&&positionY>0&&positionY<counterM2) {
            nextStep_i_Y=nextStep_i_Y+step_i_Y;
            
            if(directionY==1){
              motor2.StepUp();
              positionY++;

            }
            else if(directionY==-1) {
              motor2.StepDown();
              positionY--;
            }

            
        }
        if(i>=nextStep_i_Z &&positionZ>0&&positionZ<counterM3) {
            nextStep_i_Z=nextStep_i_Z+step_i_Z;
            
            if(directionZ==1){
              motor3.StepUp();
              positionZ++;

            }
            else if(directionZ==-1) {
              motor3.StepDown();
              positionZ--;
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

    
}


int gCodeHandler(char gCodeString[]){

  long int newX=0,newY=0,newZ=0,centerX=0,centerY=0,centerZ=0;
  double radius;

  gInterface.setGString(gCodeString);


  gInterface.parseGCode();

  switch(gInterface.gCode){

    case G0_CODE: 

                  delayTime=300;


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
                
                    
                    
                    if(newX>0&&newX<counterM1 && newY>0&&newY<counterM2 && newZ>0&&newZ<counterM3){
                        goTo3D(newX,newY,newZ);

                        return(1);

                    }
                    else return(-1001);
                  }
                  else return(-501);

                  break;           
    case G1_CODE: 
    
                  
                  if(gInterface.outF>0&&counterM1>0&&counterM1>0&&gInterface.outF>0){


                    delayTime=(unsigned long)((60*1000000)/(((double)counterM1/longitudeM1)*gInterface.outF));




                  }
    
                  else delayTime=300;

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
                




                    
                    if(newX>0&&newX<counterM1 && newY>0&&newY<counterM2 && newZ>0&&newZ<counterM3){
                        goTo3D(newX,newY,newZ);

                        return(1);

                    }
                    else return(-1002);
                  }
                  else return(-501);

                  break;           
    case G2_CODE: 

                  if(gInterface.outF>0&&counterM1>0&&counterM1>0&&gInterface.outF>0){


                    delayTime=(unsigned long)((60*1000000)/(  ((double)counterM1)/longitudeM1)*gInterface.outF);




                  }
    
                  else delayTime=300;



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
                                        centerX=positionX;
                                        centerY=positionY;
                                        centerZ=positionZ;
                                      }
                                      else if (referenceMode==ABSOLUTE){
                                        newX+= referenceX;
                                        newY+= referenceY;
                                        newZ+= positionZ;
                                        centerX+= referenceX;
                                        centerY+= referenceY;
                                        centerZ+= positionZ;
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
                                        centerY=positionY;
                                        centerZ=positionZ;
                                      }
                                      else if (referenceMode==ABSOLUTE){
                                        newX+= positionX;
                                        newY+= referenceY;
                                        newZ+= referenceZ;
                                        centerX+= positionX;
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
                                        centerX=positionX;
                                        centerY=positionY;
                                        centerZ=positionZ;
                                      }
                                      else if (referenceMode==ABSOLUTE){
                                        newX+= referenceX;
                                        newY+= positionY;
                                        newZ+= referenceZ;
                                        centerX+= referenceX;
                                        centerY+= positionY;
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
    
                    if(gInterface.outF>0&&counterM1>0&&counterM1>0&&gInterface.outF>0){


                    delayTime=(unsigned long)((60*1000000)/(((double)counterM1/longitudeM1)*gInterface.outF));




                  }
    
                  else delayTime=300;



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
                    Calibrate();
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
       
    case M100_CODE: //set Longitudes
                    newX=0;
                    newY=0;
                    newZ=0;
                    if(gInterface.outX>0){
                       longitudeM1=gInterface.outX;
                       newX=1;
                    }
                    if(gInterface.outY>0){
                       longitudeM1=gInterface.outX;
                       newY=1;
                    }
                    if(gInterface.outZ>0){
                       longitudeM1=gInterface.outX;
                       newZ=1;
                    }

                    if(newX||newY||newZ) return(1);
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
    default: break;







  }





}






};














stepperAndy3D tool3D;








void setup()
{
  Serial.begin(9600);

  tool3D.InicializateMotor(1,3,4,5,6,120);
  tool3D.InicializateMotor(2,9,10,11,12,120);
  tool3D.InicializateMotor(3,A1,A2,A3,A4,120);
  tool3D.InicializateLimits(2,7,8,13,A0,A6);
  tool3D.setMeasureMode(MILIMETER_MODE);
  tool3D.referenceMode=RELATIVE;
  tool3D.setReferencesSteps(0,0,0);
  tool3D.assignMeassure(1000,1000,1000);
  tool3D.Speed(120);
  delay(1000);
  tool3D.Calibrate();

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
    Serial.println(returned);
  }
  //errors:
  else if(returned<0){
     Serial.print("E");
     Serial.println(returned);
  }

  
  delay(20);

}
