
   global xOut;
   global    yOut;
   global    zOut;
    
 xOut=zeros(0,100000);
 yOut=zeros(0,100000);
 zOut=zeros(0,100000);
   global   k;
global k=1;



function goTo3D(X0,Y0,Z0,X1,Y1,Z1)
    
    
    global k;
    global xOut;
    global zOut;
    global yOut
    diffX=X1-X0;
    diffY=Y1-Y0;
    diffZ=Z1-Z0;    
    
    directionX=1;
    directionY=1;
    directionZ=1;
    
    if(diffX<0)then 
        directionX=-1;
    end
    
    if(diffY<0)then
        directionY=-1;
    end
    
    if(diffZ<0)then
        directionZ=-1;
    end
    
    N=0;
    
    if(diffX*directionX<diffY*directionY) then

        if(diffZ*directionZ<diffY*directionY)then
            N=directionY*diffY;
        else
            N=directionZ*diffZ;
        end
    else
        if(diffZ*directionZ>diffX*directionX)
            N=directionZ*diffZ;
        else
           
            N=directionX*diffX;
        end
    end


    printf("N:%f diffX:%f diffY:%f diffZ:%f\n",N,diffX,diffY,diffZ);    
    stepX=N;
    stepY=N;
    stepZ=N;
    
    
    if(diffX~=0)then
        stepX=N/diffX;
    else
        stepX=N+1;
    end
     
    if(diffY~=0)then
        stepY=N/diffY;
    else
        stepY=N+1;
    end
    
    if(diffZ~=0)then
        stepZ=N/diffZ;
    else
        stepZ=N+1;
    end
    
   printf("stepX:%f stepY:%f stepZ:%f \n",stepX,stepY,stepZ);

    step_i_X=directionX*stepX;
    
    step_i_Y=directionY*stepY;
    
    step_i_Z=directionZ*stepZ;
    
    nextStep_i_X=step_i_X;
    nextStep_i_Y=step_i_Y;
    nextStep_i_Z=step_i_Z;
    

    
    currentX=X0;
    currentY=Y0;
    currentZ=Z0;
    i=0;
    
    printf("iX:%f niX:%f \n iY:%f niY:%f \n iZ:%f niZ:%f \n",step_i_X,nextStep_i_X,step_i_Y,nextStep_i_Y,step_i_Z,nextStep_i_Z);
    
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
        if(i>=nextStep_i_Z) then
            nextStep_i_Z=nextStep_i_Z+step_i_Z;
            
            currentZ=(currentZ+directionZ);
            
             //printf("nextniY:%f cY:%f \n",nextStep_i_Y,nextStep_i_Y);
        end
   
   
        xOut(k)=currentX;
        yOut(k)=currentY;
        zOut(k)=currentZ;        
        
        printf("k=%f(X:%f,Y:%f,Z:%f)\n",k,currentX,currentY,currentZ);
   
        
        k=k+1
    end
    
//   clf();
   a=gca();

   
   a.auto_scale="off";
 
   
   a.data_bounds=[0,0,0;100,100,100];
   //p=get("hdl");
   //p.line_mode="off";
   
   XX=xOut;
   YY=yOut;
   ZZ=zOut;
   if(N>=1) then 
       plot3d((XX,YY,ZZ),'*');
   end
   
    
    
    
    
    
    
    
endfunction





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
     beforeOriginI=0;
     beforeOriginJ=0;
     beforeI=0;
     beforeJ=0;
     centerI=0;
     centerJ=0;
     endI=0;
     endJ=0;
     diffCNI=0;
     diffCNJ=0;
     diffBNI=0;
     diffBNJ=0;
     activateI=0;
     activateJ=0;
     CosI=0;
     SinJ=0;
     PI2=%pi/2;
     PI32=3*%pi/2;     

    
    angle=0;
    R=0;

//    class stepperAndy *motorI,*motorJ;


    R=radius;




        goTo2D(0,0,fromX,fromY);
        //activate somthing here-------

      
        //-----------------------
      

    
    currentI=fromX;
    currentJ=fromY;
    currentOriginI=fromX;
    currentOriginJ=fromY;
    centerI=centerX;
    centerJ=centerY;
    endI=toX;
    endJ=toY;
    

    
    
    
    //looking for exceptions    

    if(currentI~=centerI)then
        auxiliar=atan((currentJ-centerJ),(currentI-centerI));
        angle=180*R*(auxiliar/%pi);
    elseif(currentJ>centerJ)then 
        angle=90*R;
    else 
        angle=-90*R;
    end
   
printf("angle:%f\n",angle);
    if(endI~=centerI) then
        auxiliar=atan((endJ-centerJ),(endI-centerI));
        endAngle=180*R*(auxiliar/%pi);
    elseif (endJ>centerJ)then 
        endAngle=90*R;
    else 
        endAngle=-90*R;
    end
printf("ENDangle:%f\n=====================\n",endAngle);

              

                auxiliar=((2*angle*%pi)/(R*360.0000000001));
                nextI=(centerI+round(R*cos(auxiliar)));
                nextJ=(centerJ+round(R*sin(auxiliar)));
                beforeI=nextI;
                beforeJ=nextJ;
                currentI=nextI;
                currentJ=nextJ;
                beforeOriginI=nextI;
                beforeOriginJ=nextJ;
    //starting the arc


    // hour way
      if(angleDirection==1)then 

        //correction:
            if(angle<endAngle)then 
                endAngle=-360*R+endAngle;
            end
            
 
                

          while(angle>=endAngle)
              while((nextI-currentI==0)&&(nextJ-currentJ==0))
                  
                angle=angle-1;
                
                auxiliar=((2*angle*%pi)/(R*360.0));

                
                                   cosI=round(R*cos(auxiliar));
                    sinJ=round(R*sin(auxiliar));
                nextI=centerI+cosI;
                nextJ=centerJ+sinJ;
                
               
              
            end
            
          
            
            printf("angle:%f\n=====================\n",angle);
            
           
            diffCNI=nextI-currentI;
            diffCNJ=nextJ-currentJ;
            diffBNI=nextI-beforeI;
            diffBNJ=nextJ-beforeJ;
            
            if((diffCNI>0)&&(diffBNI>diffCNI)) then
                activateI=1;
            elseif ((diffCNI<0)&&(diffBNI<diffCNI)) then
                activateI=1;
            end
            
            
             if((diffCNJ>0)&&(diffBNJ>diffCNJ)) then
                activateJ=1;
             
            elseif ((diffCNJ<0)&&(diffBNJ<diffCNJ)) then
                activateJ=1;
            end
                            
            if(activateI==1||activateJ==1) then
                 goTo2D(beforeI,beforeJ,currentI,currentJ);
                 //sleep(100);
                 
                 
            end
            
           
            if(activateI==1)then
                beforeI=nextI;
  

            end
            if(activateJ==1)then
                   beforeJ=nextJ;
                   

        end
        
            
            activateI=0;
            activateJ=0;
            
           
    
            
           // beforeI=currentI;
            //beforeJ=currentJ;
            currentI=nextI;
            currentJ=nextJ;
            
            
          end
          
               
        


      // anti-hour way
      elseif(angleDirection==-1)then


        //correction:
        if(angle>endAngle)then
            endAngle=+360*R+endAngle;
        end

        while(angle<endAngle)
            while((nextI-currentI==0)&&(nextJ-currentJ==0))
            
              angle=angle+1;
              auxiliar=2*%pi*(angle/(R*360.0));
              nextI=(centerI+round(R*cos(auxiliar)));
              nextJ=(centerJ+round(R*sin(auxiliar)));
            
            
              end
            
            diffCNI=nextI-currentI;
            diffCNJ=nextJ-currentJ;
            diffBNI=nextI-beforeI;
            diffBNJ=nextJ-beforeJ;
            
            if((diffCNI>0)&&(diffBNI>diffCNI)) then
                activateI=1;
            elseif ((diffCNI<0)&&(diffBNI<diffCNI)) then
                activateI=1;
            end
            
            
             if((diffCNJ>0)&&(diffBNJ>diffCNJ)) then
                activateJ=1;
             
            elseif ((diffCNJ<0)&&(diffBNJ<diffCNJ)) then
                activateJ=1;
            end
                            
            if(activateI==1||activateJ==1) then
                 goTo2D(beforeI,beforeJ,currentI,currentJ);
                // sleep(100);
                 
            end
            
           
            if(activateI==1)then
                beforeI=currentI;

            end
            if(activateJ==1)then
                   beforeJ=currentJ;

        end
        
            
            activateI=0;
            activateJ=0;
            
           
    
            
           // beforeI=currentI;
            //beforeJ=currentJ;
            currentI=nextI;
            currentJ=nextJ;
            
        end
     
       end

    
endfunction

//plainCircleArc(25,50,25,49,50,50,25,1)





function plainCircleArc3(fromX,fromY,fromZ,toX,toY,toZ,centerX,centerY,centerZ,modeAxis,radius,angleDirection)
    
    auxiliar=0.0;
     currentI=0;
     currentJ=0;
     beforeOriginI=0;
     beforeOriginJ=0;
     beforeI=0;
     beforeJ=0;
     centerI=0;
     centerJ=0;
     centerK=0;
     endI=0;
     endJ=0;
     diffCNI=0;
     diffCNJ=0;
     diffBNI=0;
     diffBNJ=0;
     activateI=0;
     activateJ=0;
     CosI=0;
     SinJ=0;
     PI2=%pi/2;
     PI32=3*%pi/2;     

    
    angle=0;
    R=0;

//    class stepperAndy *motorI,*motorJ;


    R=radius;




        goTo3D(0,0,0,fromX,fromY,fromZ);
        //activate somthing here-------

      
        //-----------------------
       print(" printing %f %f %f",xOut(1),xOut(2),xOut(3));
       



if(modeAxis==1) then
    
    
    currentI=fromX;
    currentJ=fromY;
    currentOriginI=fromX;
    currentOriginJ=fromY;
    centerI=centerX;
    centerJ=centerY;
    centerK=centerZ;
    endI=toX;
    endJ=toY;
elseif (modeAxis==2) then
        
    currentI=fromY;
    currentJ=fromZ;
    currentOriginI=fromY;
    currentOriginJ=fromZ;
    centerI=centerY;
    centerJ=centerZ;
    centerK=centerX;
    endI=toY;
    endJ=toZ;
elseif (modeAxis==3) then
    currentI=fromX;
    currentJ=fromZ;
    currentOriginI=fromX;
    currentOriginJ=fromZ;
    centerI=centerX;
    centerJ=centerZ;
    centerK=centerY;
    endI=toX;
    endJ=toZ;

end
    
    
    //looking for exceptions    

    if(currentI~=centerI)then
        auxiliar=atan((currentJ-centerJ),(currentI-centerI));
        angle=180*R*(auxiliar/%pi);
    elseif(currentJ>centerJ)then 
        angle=90*R;
    else 
        angle=-90*R;
    end
   
printf("angle:%f\n",angle);
    if(endI~=centerI) then
        auxiliar=atan((endJ-centerJ),(endI-centerI));
        endAngle=180*R*(auxiliar/%pi);
    elseif (endJ>centerJ)then 
        endAngle=90*R;
    else 
        endAngle=-90*R;
    end
printf("ENDangle:%f\n=====================\n",endAngle);

              

                auxiliar=((2*angle*%pi)/(R*360.0000000001));
                nextI=(centerI+round(R*cos(auxiliar)));
                nextJ=(centerJ+round(R*sin(auxiliar)));
                beforeI=nextI;
                beforeJ=nextJ;
                currentI=nextI;
                currentJ=nextJ;
                beforeOriginI=nextI;
                beforeOriginJ=nextJ;
    //starting the arc


    // hour way
      if(angleDirection==1)then 

        //correction:
            if(angle<endAngle)then 
                endAngle=-360*R+endAngle;
            end
            
 
                

          while(angle>=endAngle)
              while((nextI-currentI==0)&&(nextJ-currentJ==0))
                  
                angle=angle-1;
                
                auxiliar=((2*angle*%pi)/(R*360.0));

                
                                   cosI=round(R*cos(auxiliar));
                    sinJ=round(R*sin(auxiliar));
                nextI=centerI+cosI;
                nextJ=centerJ+sinJ;
                
               
              
            end
            
          
            
            printf("angle:%f\n=====================\n",angle);
            
           
            diffCNI=nextI-currentI;
            diffCNJ=nextJ-currentJ;
            diffBNI=nextI-beforeI;
            diffBNJ=nextJ-beforeJ;
            
            if((diffCNI>0)&&(diffBNI>diffCNI)) then
                activateI=1;
            elseif ((diffCNI<0)&&(diffBNI<diffCNI)) then
                activateI=1;
            end
            
            
             if((diffCNJ>0)&&(diffBNJ>diffCNJ)) then
                activateJ=1;
             
            elseif ((diffCNJ<0)&&(diffBNJ<diffCNJ)) then
                activateJ=1;
            end
                            
            if(activateI==1||activateJ==1) then
                if(modeAxis==1) goTo3D(beforeI,beforeJ,centerK,currentI,currentJ,centerK);
                elseif(modeAxis==2) goTo3D(centerI,beforeI,beforeJ,centerI,currentI,currentJ);
                elseif(modeAxis==3) goTo3D(beforeI,centerJ,beforeJ,currentI,centerJ,currentJ);
                 //sleep(100);
                end
                 
                 
            end
            
           
            if(activateI==1)then
                beforeI=nextI;
  

            end
            if(activateJ==1)then
                   beforeJ=nextJ;
                   

        end
        
            
            activateI=0;
            activateJ=0;
            
           
    
            
           // beforeI=currentI;
            //beforeJ=currentJ;
            currentI=nextI;
            currentJ=nextJ;
            
            
          end
          
               
        


      // anti-hour way
      elseif(angleDirection==-1)then


        //correction:
        if(angle>endAngle)then
            endAngle=+360*R+endAngle;
        end

        while(angle<endAngle)
            while((nextI-currentI==0)&&(nextJ-currentJ==0))
            
              angle=angle+1;
              auxiliar=2*%pi*(angle/(R*360.0));
              nextI=(centerI+round(R*cos(auxiliar)));
              nextJ=(centerJ+round(R*sin(auxiliar)));
            
            
              end
            
            diffCNI=nextI-currentI;
            diffCNJ=nextJ-currentJ;
            diffBNI=nextI-beforeI;
            diffBNJ=nextJ-beforeJ;
            
            if((diffCNI>0)&&(diffBNI>diffCNI)) then
                activateI=1;
            elseif ((diffCNI<0)&&(diffBNI<diffCNI)) then
                activateI=1;
            end
            
            
             if((diffCNJ>0)&&(diffBNJ>diffCNJ)) then
                activateJ=1;
             
            elseif ((diffCNJ<0)&&(diffBNJ<diffCNJ)) then
                activateJ=1;
            end
                            
            if(activateI==1||activateJ==1) then
                   if(modeAxis==1) goTo3D(beforeI,beforeJ,centerK,currentI,currentJ,centerK);
                elseif(modeAxis==2) goTo3D(centerK,beforeI,beforeJ,centerK,currentI,currentJ);
                elseif(modeAxis==3) goTo3D(beforeI,centerK,beforeJ,currentI,centerK,currentJ);

                // sleep(100);
                end
                 
            end
            
           
            if(activateI==1)then
                beforeI=currentI;

            end
            if(activateJ==1)then
                   beforeJ=currentJ;

        end
        
            
            activateI=0;
            activateJ=0;
            
           
    
            
           // beforeI=currentI;
            //beforeJ=currentJ;
            currentI=nextI;
            currentJ=nextJ;
            
        end
     
       end

    
endfunction



