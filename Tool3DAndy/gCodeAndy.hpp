


#ifndef G_CODE_ANDY
#define G_CODE_ANDY






#define G0_CODE             1000                     
#define G1_CODE             1001                     
#define G2_CODE             1002                     
#define G3_CODE             1003                     
#define G17_CODE            1017                     
#define G18_CODE            1018                     
#define G19_CODE            1019                     
#define G20_CODE            1020                     
#define G21_CODE            1021                     
#define G28_CODE            1028                     
#define G90_CODE            1090                     
#define G91_CODE            1091                     
#define G4_CODE             104                     
#define G92_CODE            1092
#define G_UNDEFINED_CODE    1999                     
#define M0_CODE             2000                     
#define M3_CODE             2003                     
#define M4_CODE             2004                     
#define M5_CODE             2005                     
#define M104_CODE           2104                     
#define M109_CODE           2109                     
#define M140_CODE           2140                     
#define M190_CODE           2190                     
#define M112_CODE           2112                     
#define M999_CODE           2999                     
#define M100_CODE           2100                     
#define M17_CODE            2017                     
#define M18_CODE            2018                     
#define M105_CODE           2105                     
#define M114_CODE           2114                                                            
#define M_UNDEFINED_CODE    2999
                                                    
                                                    
                                                    


                                                  
class gCodeAndy{
    public:

    //auxiliar
    unsigned int i=0;
    unsigned int j=0;
    unsigned int k=0;
    unsigned int gLenght=0;
    double currentNumber=0;
    unsigned int returned=0;


    //inputs:
    char gString[32]="";


    //outputs:
    int     gCode=0;
    double  outX=0; 
    double  outY=0;
    double  outZ=0;
 
    
    double  outF=0;
    double  outP=0;
    double  outS=0;

    double  outI=0;
    double  outJ=0;
    double  outK=0;




    gCodeAndy();


    gCodeAndy(const char *inString);


    int setGString(const char *inString);



    int firstNumberPos();
    
    double convertNumber();

    void parseGCode();

    





};










#endif
