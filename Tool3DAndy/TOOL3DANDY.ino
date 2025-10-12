// C++ code
//

///
/// 8 middle steps stepper Motor 24byj-48 class 
/// AS: Andy's Softwares
/// by Andrés Bernárdez (2025)
///

#include"C:\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\arduino.h"

class stepperAndy{

public:
  
int position=0;

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
    delayTime=((60*1000000)/(frequency*4096));
    
   
  
  }
  
  void StepUp(){
    
    switch(position){
      case 0:	digitalWrite(pin4,LOW);
      			digitalWrite(pin1,HIGH);
      			position++;
      			break;
      case 1:	digitalWrite(pin1,HIGH);
      			digitalWrite(pin2,HIGH);
      			position++;
      			break;
      case 2:	digitalWrite(pin1,LOW);
      			digitalWrite(pin2,HIGH);
      			position++;
      			break;
      case 3: 	digitalWrite(pin2,HIGH);
      			digitalWrite(pin3,HIGH);
      			position++;
      			break;
      case 4:	digitalWrite(pin2,LOW);
      			digitalWrite(pin3,HIGH);
      			position++;
      			break;
      case 5: 	digitalWrite(pin3,HIGH);
      			digitalWrite(pin4,HIGH);
      			position++;
      			break;
      case 6:	digitalWrite(pin3,LOW);
      			digitalWrite(pin4,HIGH);
      			position++;
      			break;
      case 7: 	digitalWrite(pin4,HIGH);
      			digitalWrite(pin1,HIGH);
      			position=0;
				break;      
    }
    
    
    
  }
  
  
  void StepDown(){
    
    switch(position){
      case 0:	digitalWrite(pin2,LOW);
      			digitalWrite(pin1,HIGH);
      			position--;
      			break;
      case 1:	digitalWrite(pin1,HIGH);
      			digitalWrite(pin2,HIGH);
      			position--;
      			break;
      case 2:	digitalWrite(pin3,LOW);
      			digitalWrite(pin2,HIGH);
      			position--;
      			break;
      case 3: 	digitalWrite(pin2,HIGH);
      			digitalWrite(pin3,HIGH);
      			position--;
      			break;
      case 4:	digitalWrite(pin4,LOW);
      			digitalWrite(pin3,HIGH);
      			position--;
      			break;
      case 5: 	digitalWrite(pin3,HIGH);
      			digitalWrite(pin4,HIGH);
      			position--;
      			break;
      case 6:	digitalWrite(pin1,LOW);
      			digitalWrite(pin4,HIGH);
      			position--;
      			break;
      case 7: 	digitalWrite(pin4,HIGH);
      			digitalWrite(pin1,HIGH);
      			position--;
				break;      
    }
    
    
    
  }
  
  void Steps(int stepsNumber){
    int i;
    if(stepsNumber>0){
      for(i=0;i<stepsNumbers;i++){
        StepUp();
		delayMicroseconds(delayTime);
        
      }
      
    }else if(stepsNumber<0)
      for(i=0;i>stepsNumbers;i--){
        StepDown();
		delayMicroseconds(delayTime);
        
      }
  }
  
  
  
  
  
  
}


struct sensor{
  long int microsecondsWaited=0;
  int pin=2;
  int status=LOW;
  int waiting=LOW;
  
}
  


int detectSensor(struct sensor sIn,long int delayTime){
  
  if(sIn.status==LOW){
    if(digitalRead(sIn.pin)==HIGH){
    	if(sIn.waiting==LOW){
    		sIn.microWaited=millis()+delayTime;
    		sIn.waiting=HIGH;
  		}
  		else if(millis()>sIn.microWaited){
      		sIn.status=HIGH;
    	}
    
  	}
	else{
      		sIn.waiting=LOW;
		}
	}
  //if(sIn.status==HIGH)
else if (digitalRead(sIn.pin)==LOW){
    	if(sIn.waiting==HIGH){
    		sIn.microWaited==millis()+delayTime;
    		sIn.waiting==LOW;
  		}
		else if(millis()>sIn.microWaited){
      			sIn.status=LOW;
    	}
	}
  	else{
      		sIn.waiting=HIGH;
    }
}


///CircleMode
///
int XYMode=0;
int XZMode=1;
int YZMode=2;

//----------

class stepperAndy3D{
 public:
  class stepperAndy motor1;
  class stepperAndy motor2;
  class stepperAndy motor3;
  struct sensor limitM11;
  struct sensor limitM12;
  struct sensor limitM21;
  struct sensor limitM22;
  struct sensor limitM31;
  struct sensor limitM32;
  long int counterM1=204800;
  long int counterM2=204800;
  long int counterM3=204800;
  double longitudeM1=1000;
  double longitudeM2=1000;
  double longitudeM3=1000;
  
  long int positionX=0;
  long int positionY=0;
  long int positionZ=0;
  

  
  stepperAndy3D(){
    
  }






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
  
  
  void Calibrate(){
    
    int finished=1;
    int beginM1=0,beginM2=0,beginM3=0;
    int finishM1=0,finishM2=0,finishM3=0;
    int directionM1=0,directionM2=0,directionM3=0;
    int delayTime=1000;
    
    
    delayTime=motor1.delayTime;
    
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
      detectSensor(limitM11,4);
      detectSensor(limitM12,4);
      detectSensor(limitM21,4);
      detectSensor(limitM22,4);
      detectSensor(limitM31,4);
      detectSensor(limitM32,4);
      
      delay(5);
      
      detectSensor(limitM11,4);
      detectSensor(limitM12,4);
      detectSensor(limitM21,4);
      detectSensor(limitM22,4);
      detectSensor(limitM31,4);
      detectSensor(limitM32,4);
      
      
      
      
      
     /// limits readings: 
      
      if(limitM11.status==HIGH){
        
        if(directionM1==0){
          directionM1=1;
          
        } else(directionM1==1){
          directionM1=2;
          finishM1=1;
        }
          
      }
      
      if(limitM12.status==HIGH){
        
        if(directionM1==0){
          directionM1=1;
          
        } else(directionM1==1){
          directionM1=2;
          finishM1=1;
        }
          
      }
      
      if(limitM21.status==HIGH){
        
        if(directionM2==0){
          directionM2=1;
          
        } else(directionM2==1){
          directionM2=2;
          finishM2=1;
        }
          
      }
      
      if(limitM22.status==HIGH){
        
        if(directionM2==0){
          directionM2=1;
          
        } else(directionM2==1){
          directionM2=2;
          positionX=0;
          finishM2=1;
        }
          
      }
      
      if(limitM31.status==HIGH){
        
        if(directionM3==0){
          directionM3=1;
          
        } else(directionM3==1){
          directionM3=2;
          positionY=0;
          finishM3=1;
        }
          
      }
      
      if(limitM32.status==HIGH){
        
        if(directionM3==0){
          directionM3=1;
          
        } else(directionM3==1){
          directionM3=2;
          positionZ=0;
          finishM3=1;
        }
          
      }
      
     	///all detections finished?
      
      if(finishM1&&finishM2&&finishM3){
        finished=0;
      }
      
      
      
      
    }
    
    
    
  }
  
  void assignMeassure(double longM1,double longM2, double longM3){
    longitudeM1=longM1;
    longitudeM2=longM2;
    longitudeM3=longM3;
    
    
  }
  
  
  void goTo3D(double toX,double toY,double toZ){
    
    long int diffX=0,diffY=0,diffZ=0;
    long int stepX=1,stepY=1,stepZ=1;
    long int addX=0,addY=,addZ=0;
    long int extraX=0,extraY=0,extraZ=0;
    long int nextExtraX=0,nextExtraY=0,nextExtra=0;
    long int i,N;
    
    int finished=1;
    
    int directionX=0,directionY=0,directionZ=0;
    
    
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
    stepX=N/diffX;
    stepY=N/diffY;
    stepZ=N/diffZ;
    //residue
    addX=N%diffX;
    addY=N%diffY;
    addZ=N%diffZ;
    //extra steps
    
    if(addX!=0)extraX=N/(addX+1);
    else extraX=0;
    if(addY!=0)extraY=N/(addY+1);
    else extraX=0;
    if(addZ!=0)extraZ=N/(addZ+1);
    else extraZ=0;
    
    //next extra step
    
    if(extraX>0)nextExtraX=extraX;
    if(extraY>0)nextExtraY=extraY;
    if(extraZ>0)nextExtraZ=extraZ;
    
    
    finished=1;
    
    
    
   for(i=1;i<=N;i++){
     
     if(i%stepX){
       if(!directionX){
         motor1.StepUp();
         positionX++;
       }
       else {
         motor1.StepDown();
         positionX--;
       }
       
       
     }
     if(i%stepY){
       if(!directionY){
         motor2.StepUp();
         positionY++;
       }
       else {
         motor2.StepDown();
         positionY--;
       }
       
       
     }
     if(i%stepZ){
       if(!directionZ){
         motor3.StepUp();
         positionZ++;
       }
       else {
         motor3.StepDown();
         positionZ--;
       }
       
     }
      
     if(i<N){
       if(extraX>0)
         if(nextExtraX==i){
            if(!directionX){
               motor1.StepUp();
               positionX++;
             }
             else {
               motor1.StepDown();
               positionX--;
             }
         	nextExtraX+=ExtraX;
       }
       if(extraY>0)
         if(nextExtraY==i){
            if(!directionY){
               motor2.StepUp();
               positionY++;
             }
             else {
               motor2.StepDown();
               positionY--;
             }
         	nextExtraY+=ExtraY;
       }
        if(extraY>0)
         if(nextExtraZ==i){
         	 if(!directionZ){
               motor3.StepUp();
               positionZ++;
             }
             else {
               motor3.StepDown();
               positionZ--;
             }
         	nextExtraZ+=ExtraZ;
       }
     }
      
      delayMicroseconds(delayTime);
      
    }
    
    
    
    
    
  }
  
  
  void line3D(double fromX,double toX,double fromY,double toY,double fromY,double toZ){
    
    goTo3D(fromX,fromY,fromZ)
      
    //activate something here-----
    
    
    //----------
      
    goto3D(toX,toY,toZ);
    
  }
  
  
  
}


void plainCircleArcNextPoint(double centerX,double centerY,double centerZ,int mode, int radius, int direction){

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

int currentI,currentJ,currentK,CenterI,CenterJ;




switch(mode):

case XYMode: currentI=
case XZMode=1;
case YZMode=2;
default:
switch()








}


void plainCircleArc(double fromX,double toX,double fromY,double toY,double fromY,double toZ,double centerX,double centerY, double centerZ, double radius,int direction){

    goTo3D(fromX,fromY,fromZ);
    //activate somthing here-------

    //-----------------------


    //still programming



}









void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
}
