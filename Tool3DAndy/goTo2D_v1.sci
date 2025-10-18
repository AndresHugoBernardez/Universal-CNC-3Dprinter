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
    
    xOut=zeros(0,N);
    yOut=zeros(0,N);
    
    currentX=X0;
    currentY=Y0;
    i=0;
    
    printf("iX:%f niX:%f \n iY:%f niY:%f \n",step_i_X,nextStep_i_X,step_i_Y,nextStep_i_Y);
    
    printf("---------------\n");
    for i=1:1:N
        
        if(i>=nextStep_i_X) then
            nextStep_i_X=nextStep_i_X+step_i_X;
            currentX=(currentX+directionX);
            printf("nextniX:%f cX:%f \n",nextStep_i_X,nextStep_i_X);
        end
        if(i>=nextStep_i_Y) then
            nextStep_i_Y=nextStep_i_Y+step_i_Y;
            
            currentY=(currentY+directionY);
            
             printf("nextniY:%f cY:%f \n",nextStep_i_Y,nextStep_i_Y);
        end
   
   
        xOut(i)=currentX;
        yOut(i)=currentY;
        
        printf("(X:%f,Y:%f)\n",currentX,currentY);
   
        
        
    end
    
   clf();
   a=gca();

   
   a.auto_scale="off";
 
   
   a.data_bounds=[0,0;100,100];
   
    
    plot((xOut,yOut,'*'));
    
    
    
    
    
    
endfunction



function plainCircleArc()
endfunction






