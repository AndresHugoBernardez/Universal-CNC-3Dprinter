// C++ code
//

///
/// 8 middle steps stepper Motor 24byj-48 class 
/// AS: Andy's Softwares
/// by Andrés Bernárdez (2025)
///

#include"C:\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\arduino.h"

///------------------
#include<cmath>
class stepperAndy{

public:
  
int positionS=0;

long int delayTime=10000;
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
  
  void Speed(long int frequency){
  
    //frequency=cicles per minute. 
    //24byj-48 with 64 middle steps per motor cicle and a reduction of 1:64
	  //the 24byj-48 totaly has 4096 stpes per cicle. 
    //frequency/60=cicles per seconds
    //frequency*4096/(60)= steps per seconds
    //60*1000000/(frequency*4096)= microseconds per step.
    if(frequency>0)delayTime=((60*1000000)/(frequency*4096));
    else delayTime=1000;
    
   
  
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
      case 7: 	digitalWrite(pin4,HIGH);
      			digitalWrite(pin1,HIGH);
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
      case 7: 	digitalWrite(pin4,HIGH);
      			digitalWrite(pin1,HIGH);
      			positionS--;
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
  long int microSecondsWaited=0;
  int pin=2;
  int status=LOW;
  int waiting=LOW;
  
};
  

/// @brief digital readings can have interference, so when you read a pin you must do it at less twice.
/// @param sIn name of the sensor
/// @param delayTime min time between 2 detections before accept the reading.
void detectSensor(struct sensor *sIn,long int delayTime){
  
  if(sIn->status==LOW){
    if(digitalRead(sIn->pin)==HIGH){
    	if(sIn->waiting==LOW){
    		sIn->microSecondsWaited=millis()+delayTime;
    		sIn->waiting=HIGH;
  		}
  		else if(millis()>sIn->microSecondsWaited){
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
    		sIn->microSecondsWaited=millis()+delayTime;
    		sIn->waiting=LOW;
  		}
		else if(millis()>sIn->microSecondsWaited){
      			sIn->status=LOW;
    	}
	}
  	else{
      		sIn->waiting=HIGH;
    }
}


/// @brief AxesMode
int XYMode=0;
int XZMode=1;
int YZMode=2;

//----------

class stepperAndy3D{

 public:

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
  void InicializateMotor(int number,int p1,int p2, int p3, int p4,long int speed){
    
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
 
  
  /// @brief The default speed is motor1.speed  It will be use for the 3 motors.
  /// @param speed 
  void Speed(long int speed){

    motor1.Speed(speed);
    motor2.Speed(speed);
    motor3.Speed(speed);
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
  
  /// @brief  This is the heart of the machine. All movement is recomended to made with goTo3D
  /// @param toX next X position
  /// @param toY next Y position
  /// @param toZ next Z position
  /// @return 
  int goTo3D(long int toX,long int toY,long int toZ){
    
    long int diffX=0,diffY=0,diffZ=0;
    long int stepX=1,stepY=1,stepZ=1;
    long int addX=0,addY0,addZ=0;
    long int extraX=0,extraY=0,extraZ=0;
    long int nextExtraX=0,nextExtraY=0,nextExtraZ=0;
    long int borderX,borderY,borderZ;
    long int i,N;
    int error=0;
    
    int finished=1;
    
    int directionX=0,directionY=0,directionZ=0;

    int activateDelay=0;
    int activateDelayBorder=0;
    

    //detectLimits when it is near the border...
    borderX=counterM1-20;
    borderY=counterM2-20;
    borderZ=counterM3-20;

    
    //calculate distance
    diffX=toX-positionX;
    diffY=toY-positionY;
    diffZ=toZ-positionZ;
    
    //obtain direction;
    if(diffX<0){
      diffX=-diffX;
      directionX=1;
    }
    if(diffY<0){
      diffY=-diffY;
      directionY=1;
    }
    if(diffZ<0){
      diffZ=-diffZ;
      directionZ=1;
    }
    
    //find the bigger.
    if(diffX>diffY){
      if(diffX>diffZ)N=diffX;
      else N=diffZ;
    } else{
      if(diffY>diffZ)N=diffY;
      else N=diffZ;
    }
    


    
    //steps
    if(diffX!=0)stepX=N/diffX;else stepX=0;
    if(diffY!=0)stepY=N/diffY;else stepY=0;
    if(diffZ!=0)stepZ=N/diffZ;else stepZ=0;
    //residue
    if(diffX!=0)addX=N%diffX;else addX=0;
    if(diffY!=0)addY=N%diffY;else addY=0;
    if(diffZ!=0)addZ=N%diffZ;else addZ=0;
    //extra steps
    
    if(addX!=0)extraX=N/(addX+1);
    else extraX=0;
    if(addY!=0)extraY=N/(addY+1);
    else extraY=0;
    if(addZ!=0)extraZ=N/(addZ+1);
    else extraZ=0;
    
    //next extra step
    
    if(extraX>0)nextExtraX=extraX;
    if(extraY>0)nextExtraY=extraY;
    if(extraZ>0)nextExtraZ=extraZ;
    
    
    finished=1;
    
    
    
   for(i=1;i<=N&&error==0;i++){
     activateDelay=0;


      
     ///--------------BORDER WATCHDOG (if it is near borders it must try to detect limits)
      if(positionX<20||positionX>borderX){
   
        detectSensor(&limitM11,4);
        detectSensor(&limitM12,4);
        activateDelayBorder=1;
    
      }

       if(positionY<20||positionY>borderY){
   
        detectSensor(&limitM21,4);
        detectSensor(&limitM22,4);
        activateDelayBorder=1;
    
      }
      
       if(positionZ<20||positionY>borderZ){
   
        detectSensor(&limitM31,4);
        detectSensor(&limitM32,4);
        activateDelayBorder=1;
    
      }

      //delay
      if(activateDelayBorder){
        delay(5);
        activateDelayBorder=0;
      }

      ///new detection (it avoids iterference errors)
      if(positionX<20||positionX>borderX){
   
        detectSensor(&limitM11,4);
        detectSensor(&limitM12,4);
        activateDelayBorder=1;
    
      }

       if(positionY<20||positionY>borderY){
   
        detectSensor(&limitM21,4);
        detectSensor(&limitM22,4);
        activateDelayBorder=1;
    
      }
      
       if(positionZ<20||positionY>borderZ){
   
        detectSensor(&limitM31,4);
        detectSensor(&limitM32,4);
        activateDelayBorder=1;
    
      }


      if((limitM11.status==HIGH|| limitM12.status==HIGH )&&positionX<20) positionX=1;
      else if((limitM11.status==HIGH|| limitM12.status==HIGH )&&positionX>borderX) counterM1=positionX+1;
      if((limitM21.status==HIGH|| limitM22.status==HIGH )&&positionY<20) positionY=1;
      else if((limitM21.status==HIGH|| limitM22.status==HIGH )&&positionY>borderY) counterM2=positionY+1;
      if((limitM31.status==HIGH|| limitM32.status==HIGH )&&positionZ<20) positionZ=1;
      else if((limitM31.status==HIGH|| limitM32.status==HIGH )&&positionZ>borderZ) counterM3=positionZ+1;

      ///------------------end Border watchdog
      

     if(stepX) if(!(i%stepX)&&positionX>0&&positionX<counterM1){
       if(!directionX){
         motor1.StepUp();
         positionX++;
         activateDelay=1;

       }
       else {
         motor1.StepDown();
         positionX--;
         activateDelay=1;
       }
       
       
     }
     else if(!(positionX>0&&positionX<counterM1)) error=1001;
     
     if(stepY) if(!(i%stepY)&&positionY>0&&positionY<counterM2){
       if(!directionY){
         motor2.StepUp();
         positionY++;
         activateDelay=1;
       }
       else {
         motor2.StepDown();
         positionY--;
         activateDelay=1;
       }
       
       
     }
     else if(!(positionY>0&&positionY<counterM2)) error=1002;
     
     if(stepZ) if(!(i%stepZ)&&positionZ>0&&positionZ<counterM3){
       if(!directionZ){
         motor3.StepUp();
         positionZ++;
         activateDelay=1;
       }
       else {
         motor3.StepDown();
         positionZ--;
         activateDelay=1;
       }
       
     }
     else if(!(positionZ>0&&positionZ<counterM3)) error=1003;

     if(activateDelay)delayMicroseconds(motor1.delayTime);

     activateDelay=0;
     if(extraX>0||extraY>0||extraZ>0){
       if(extraX>0&&positionX>0&&positionX<counterM1){
         if(nextExtraX==i){
            if(!directionX){
               motor1.StepUp();
               positionX++;
               activateDelay=1;
             }
             else {
               motor1.StepDown();
               positionX--;
               activateDelay=1;
             }
         	nextExtraX+=extraX;
        }
       }
       else if(!(positionX>0&&positionX<counterM1))error=1011;
       
       if(extraY>0&&positionY>0&&positionY<counterM2){
         if(nextExtraY==i){
            if(!directionY){
               motor2.StepUp();
               positionY++;
               activateDelay=1;
             }
             else {
               motor2.StepDown();
               positionY--;
               activateDelay=1;
             }
         	nextExtraY+=extraY;
        }
       }
       else if(!(positionY>0&&positionY<counterM2))error=1012;
       
        if(extraZ>0&&positionZ>0&&positionZ<counterM3){
         if(nextExtraZ==i){
         	 if(!directionZ){
               motor3.StepUp();
               positionZ++;
               activateDelay=1;
             }
             else {
               motor3.StepDown();
               positionZ--;
               activateDelay=1;
             }
         	nextExtraZ+=extraZ;
       }
      }
       else if(!(positionZ>0&&positionZ<counterM3)) error=1013;

      if(activateDelay) delayMicroseconds(motor1.delayTime);
      
     }
      
     
     
     ///--------------BORDER WATCHDOG (if it is near borders it must try to detect limits)
      if(positionX<20||positionX>borderX){
   
        detectSensor(&limitM11,4);
        detectSensor(&limitM12,4);
        activateDelayBorder=1;
    
      }

       if(positionY<20||positionY>borderY){
   
        detectSensor(&limitM21,4);
        detectSensor(&limitM22,4);
        activateDelayBorder=1;
    
      }
      
       if(positionZ<20||positionY>borderZ){
   
        detectSensor(&limitM31,4);
        detectSensor(&limitM32,4);
        activateDelayBorder=1;
    
      }

      //delay
      if(activateDelayBorder){
        delay(5);
        activateDelayBorder=0;
      }

      ///new detection (it avoids iterference errors)
      if(positionX<20||positionX>borderX){
   
        detectSensor(&limitM11,4);
        detectSensor(&limitM12,4);
        activateDelayBorder=1;
    
      }

       if(positionY<20||positionY>borderY){
   
        detectSensor(&limitM21,4);
        detectSensor(&limitM22,4);
        activateDelayBorder=1;
    
      }
      
       if(positionZ<20||positionY>borderZ){
   
        detectSensor(&limitM31,4);
        detectSensor(&limitM32,4);
        activateDelayBorder=1;
    
      }


      if((limitM11.status==HIGH|| limitM12.status==HIGH )&&positionX<20) positionX=1;
      else if((limitM11.status==HIGH|| limitM12.status==HIGH )&&positionX>borderX) counterM1=positionX+1;
      if((limitM21.status==HIGH|| limitM22.status==HIGH )&&positionY<20) positionY=1;
      else if((limitM21.status==HIGH|| limitM22.status==HIGH )&&positionY>borderY) counterM2=positionY+1;
      if((limitM31.status==HIGH|| limitM32.status==HIGH )&&positionZ<20) positionZ=1;
      else if((limitM31.status==HIGH|| limitM32.status==HIGH )&&positionZ>borderZ) counterM3=positionZ+1;

      ///------------------end Border watchdog
      
    }
    
    
    return(error);
    
    
  }
  
  

  /// @brief Line movement.
  /// @param fromX 
  /// @param toX 
  /// @param fromY 
  /// @param toY 
  /// @param fromY 
  /// @param toZ 
  void line3D(long int fromX,long int toX,long int fromY,long int toY,long int fromY,long int toZ){
    
    goTo3D(fromX,fromY,fromZ)
      
    //You could activate something here-----
    
    
    //----------
      
    goto3D(toX,toY,toZ);
    
  }
    

  /// @brief Circle Arc movement
  /// @param fromX     origin X
  /// @param toX       destination X
  /// @param fromY     origin Y
  /// @param toY       destination Y
  /// @param fromZ     origin Z
  /// @param toZ       destination Z
  /// @param centerX   centerX
  /// @param centerY   centerY
  /// @param centerZ   centerZ
  /// @param radius    Radius 
  /// @param angleDirection 
  void plainCircleArc(long int fromX,long int toX,long int fromY,long int toY,long int fromZ,long int toZ,long int centerX,long int centerY, long int centerZ, long int radius,int angleDirection){

      // Do you still remember Algebra?? ohhh yeah, dude! Here is where you will use it! haha!

      // system 3D plane+sphere (not used)
      // x^2+y^2+z^2=r^2
      // x+y+z+C=0

      //2D parametric circumference 
      // x=x0+radius*cos(t)
      // y=y0+radius*sin(t)

      //3D parametric circumference  (not used)
      // x=x0​+r(ux​*cost+vx​*sint)
      //y=y0​+r(uy​*cost+vy​*sint)
      //z=z0​+r(uz​*cost+vz*​sint)​
      // u and v are versors of the plane.

      //2D parametric circle for g-code

    long int currentI,currentJ,currentK,centerI,centerJ,endI,endJ;

    double angle,R;

    class stepperAndy *motorI,*motorJ;


    R=(double)radius;




        goTo3D(fromX,fromY,fromZ);
        //activate somthing here-------

      
        //-----------------------
      

      //configurating mode  
      switch(mode){
      
      
            case XZMode: currentI=positionX;
                        currentJ=positionZ;
                        currentK=positionY;
                        centerI=centerX;
                        centerJ=centerZ;
                        endI=toX;
                        endJ=toZ;
                        motorI=&motor1;
                        motorJ=&motor3;

                        
                        break;
            case YZMode: currentI=positionY;
                        currentJ=positionZ;
                        currentK=positionX;
                        centerI=centerY;
                        centerJ=centerZ;
                        endI=toY;
                        endJ=toZ;
                        motorI=&motor2;
                        motorJ=&motor3;
                        break;
            case XYMode:       
            default:     currentI=positionX;
                        currentJ=positionY;
                        currentK=positionZ;
                        centerI=centerX;
                        centerJ=centerY;
                        endI=toX;
                        endJ=toY;
                        motorI=&motor1;
                        motorJ=&motor2;
                        break;     
      
      
      }


    //looking for exceptions

    if(currentJ!=centerJ)angle=atang((currentI-centerI)/(currentJ-centerJ));
    else if(currentI>centerI)angle=0;else angle=PI;

    if(endJ!=centerJ) endAngle=atang((endI-centerI)/(endJ-centerJ));
    else if (endI>centerI)endAngle=0;else endAngle=PI;



    //starting the arc


    // hour way
      if(angleDirection==1){

        //correction:
        if(angle<endAngle)endAngle=-2*PI+endAngle;


          while(angle>endAngle){
              while((nextI-currentI==0)&&(nextJ-currentJ==0))
              {   
                angle--;
                nextI=centerI+(long int)(R*cos(angle));
                nextJ=centerJ+(long int)(R*sin(angle));
              
              }
            
            switch(mode){
              case XZMode:  goTo3D(nextI,currentK,nextJ);
                            break;
              case YZMode:  goTo3d(currentK,nextI,nextJ);
                            break;
              case XYMode:  
              default:      goTo3d(nextI,nextJ,currentK);
                            break;
              }
            }
      }


      // anti-hour way
      else if(angleDirection==-1){


        //correction:
        if(angle>endAngle)endAngle=+2*PI+endAngle;



        while(angle<endAngle){
            while((nextI-currentI==0)&&(nextJ-currentJ==0))
            {   
              angle++;
              nextI=centerI+(long int)(R*cos(angle));
              nextJ=centerJ+(long int)(R*sin(angle));
            
            }
          
          switch(mode){
            case XZMode:  goTo3D(nextI,currentK,nextJ);
                          break;
            case YZMode:  goTo3d(currentK,nextI,nextJ);
                          break;
            case XYMode:  
            default:      goTo3d(nextI,nextJ,currentK);
                          break;
            }
          }


      }



    


  }


};



















void setup()
{
  Serial.begin(9600);






  
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
}
