
    xOut=zeros(0,20000);
    yOut=zeros(0,20000);

    k=1;


function goTo2D(X0,Y0,X1,Y1)
    
    diffX=X1-X0;
    diffY=Y1-Y0;
    
    directionX=1;
    directionY=1;
    
    if(diffX<0)then 
        directionX=-1;
    end
    
    if(diffY<0)then
        directionY=-1;
    end
    
    N=0;
    
    if(diffX*directionX<diffY*directionY) then
        N=directionY*diffY;
    else
        N=directionX*diffX;
    end


    printf("N:%f diffX:%f diffY:%f\n",N,diffX,diffY);    
    stepX=N;
    stepY=N;
    
    
    if(diffX~=0)then
        stepX=N/diffX;
    else
        stepX=N;
    end
     
    if(diffY~=0)then
        stepY=N/diffY;
    else
        stepY=N;
    end
   printf("stepX:%f stepY:%f \n",stepX,stepY);

    step_i_X=directionX*stepX;
    
    step_i_Y=directionY*stepY;
    
    nextStep_i_X=step_i_X;
    nextStep_i_Y=step_i_Y;
    

    
    currentX=X0;
    currentY=Y0;
    i=0;
    
    printf("iX:%f niX:%f \n iY:%f niY:%f \n",step_i_X,nextStep_i_X,step_i_Y,nextStep_i_Y);
    
    printf("---------------\n");
    for i=1:1:N
        
        if(i>=nextStep_i_X) then
            nextStep_i_X=nextStep_i_X+step_i_X;
            currentX=(currentX+directionX);
            //printf("nextniX:%f cX:%f \n",nextStep_i_X,nextStep_i_X);
        end
        if(i>=nextStep_i_Y) then
            nextStep_i_Y=nextStep_i_Y+step_i_Y;
            
            currentY=(currentY+directionY);
            
             //printf("nextniY:%f cY:%f \n",nextStep_i_Y,nextStep_i_Y);
        end
   
   
        xOut(k)=currentX;
        yOut(k)=currentY;
        
        printf("(X:%f,Y:%f)\n",currentX,currentY);
   
        
        k=k+1;
    end
    
//   clf();
   a=gca();

   
   a.auto_scale="off";
 
   
   a.data_bounds=[0,0;100,100];
   
   if(N>=1) then 
       plot((xOut,yOut,'*'));
   end
   
    
    
    
    
    
    
    
endfunction


function plainCircleArc(fromX,fromY,toX,toY,centerX,centerY,radius,angleDirection)
    
    auxiliar=0.0;
     currentI=0;
     currentJ=0;
     centerI=0;
     centerJ=0;
     endI=0;
     endJ=0;

    
    angle=0;
    R=0;

//    class stepperAndy *motorI,*motorJ;


    R=radius;




        goTo2D(0,0,fromX,fromY);
        //activate somthing here-------

      
        //-----------------------
      

    
    currentI=fromX;
    currentJ=fromY;
    centerI=centerX;
    centerJ=centerY;
    endI=toX;
    endJ=toY;
    
    
    
    //looking for exceptions    

    if(currentI~=centerI)then
        auxiliar=atan((currentJ-centerJ),(currentI-centerI));
        angle=180*(auxiliar/%pi);
    elseif(currentJ>centerJ)then 
        angle=90;
    else 
        angle=-90;
    end
   
printf("angle:%f\n",angle);
    if(endI~=centerI) then
        auxiliar=atan((endJ-centerJ),(endI-centerI));
        endAngle=180*(auxiliar/%pi);
    elseif (endJ>centerJ)then 
        endAngle=90;
    else 
        endAngle=-90;
    end
printf("ENDangle:%f\n=====================\n",endAngle);

              

                auxiliar=((2*angle*%pi)/360.0000000001);
                nextI=(centerI+int(R*cos(auxiliar)));
                nextJ=(centerJ+int(R*sin(auxiliar)));
    //starting the arc


    // hour way
      if(angleDirection==1)then 

        //correction:
            if(angle<endAngle)then 
                endAngle=-360+endAngle;
            end
            
 

          while(angle>endAngle)
              while((nextI-currentI==0)&&(nextJ-currentJ==0))
                  
                angle=angle-1;
                
                auxiliar=((2*angle*%pi)/360.0);
                nextI=(centerI+int(R*cos(auxiliar)));
                nextJ=(centerJ+int(R*sin(auxiliar)));
              
            end
            
          
            
            printf("angle:%f\n=====================\n",angle);
            goTo2D(currentI,currentJ,nextI,nextJ);
            currentI=nextI;
            currentJ=nextJ;
            
            
          end
          
               
        


      // anti-hour way
      elseif(angleDirection==-1)then


        //correction:
        if(angle>endAngle)then
            endAngle=+360+endAngle;
        end

        while(angle<endAngle)
            while((nextI-currentI==0)&&(nextJ-currentJ==0))
            
              angle=angle+1;
              auxiliar=2*%pi*(angle/360.0);
              nextI=(centerI+int(R*cos(auxiliar)));
              nextJ=(centerJ+int(R*sin(auxiliar)));
            
            
              end
            
        

            goTo2D(currentI,currentJ,nextI,nextJ);
            currentI=nextI;
            currentJ=nextJ;
        end
     
       end

    
endfunction




