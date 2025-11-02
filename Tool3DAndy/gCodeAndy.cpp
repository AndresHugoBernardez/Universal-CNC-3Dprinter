
#include "gCodeAndy.hpp"                                               
                                                    


    gCodeAndy::gCodeAndy(){

    }

    gCodeAndy::gCodeAndy(char inString[]){




        for(k=0;k<32&&inString[k]!='\n'&&inString[k]!='\0';k++){
            gString[k]=inString[k];



        }
        gString[k]='\0';
        gLenght=k;
        i=0;
        returned=(int)k;
    }


    int gCodeAndy::setGString(char inString[]){

        i=0;
        j=0;
        k=0;
        gLenght=0;
        currentNumber=0;
        returned=0;
        gCode=0;
        outX=0; 
        outY=0;
        outZ=0;

        outF=0;
        outP=0;
        outS=0;
        outI=0;
        outJ=0;
        outK=0;

        
        for(k=0;k<32&&inString[k]!='\n'&&inString[k]!='\0';k++){
            gString[k]=inString[k];



        }
        gString[k]='\0';
        i=0;
        returned=(int)k;
        return(returned);
    }



    /// @brief 
    /// @var this.gString 
    /// @var i
    /// @return  this.returned
    int gCodeAndy::firstNumberPos(){
    int init=0;

    //If there is no number it will return 
    init=i;

    //looking for a number: i will increase until there is a number.


    while(  
            //it must not be end of line or end of string
            gString[i]!='\n' && gString[i]!='\0'  &&  
           (   
                // if it is not a number go forward
                (gString[i]<'0' || gString[i]>'9')    ||   
                // if it is '.' or '-' there must be a number in the next character if not ignore and go forward
                (  (gString[i]=='-'||gString[i]=='.') && (gString[i+1]<'0' || gString[i+1]>'9')    )
            ) 
        ){

       
        i++;
         
    }
    
    //if a number appeared "i" is the first character of this number.

    // if end is reached finish there is no number forward.
    if(gString[i]=='\0'||gString[i]=='\n') returned=-1;
    else returned=1;

    return(returned);

    }


    

    double gCodeAndy::convertNumber(){
      
        char outWord[16]="";
        double number=0,denominator=1;
        int sign=1;



        
        

        //detecting sign
        if(gString[i]=='-'){
            sign=-1;
            i++;
        }
        //detecting Entire numbers
        k=0;
        while( gString[i]>='0' && gString[i]<='9'){
            outWord[k]=gString[i];
            i++;
            k++;
        }

        // detecting floating part
        if(gString[i]=='.'&&gString[i+1]>='0' && gString[i+1]<='9'){

            outWord[k]='.';
            i++;
            k++;
            while( gString[i]>='0' && gString[i]<='9'){
                outWord[k]=gString[i];
                i++;
                k++;
            }

        }


        outWord[k]='\0';

        k=0;
        number=0;
        //converting to long int
            while(outWord[k]!='\0'&&outWord[k]!='.'){
                number*=10;
                number+=(double) (outWord[k]-'0');
                k++;
            }
            if(outWord[k]=='.'){
                denominator=1;
                while(outWord[k]!='\0'){
                denominator*=10;
                number+=((double) (outWord[k]-'0'))/denominator;
                k++;
            }



        }

      

        //return double number
        if(sign==1)currentNumber=number;
        else currentNumber=-number;

        // return the ammount of characters converted.
        returned=k;
        return(returned);
    }









    void gCodeAndy::parseGCode(){

        
 
        i=0;
        gCode=-1;


        while (gString[i]!='\n'&&gString[i]!='\0'){
  
            switch(gString[i]){

                case 'X':
                case 'x':
                            
                            returned=firstNumberPos();
                            outX=0;
                            if(returned>=0){
                                convertNumber();
                                outX=currentNumber;
                            }

                        
                            
                            break;


                case 'Y':
                case 'y':
                            
                            returned=firstNumberPos();
                            outY=0;
                            if(returned>=0){
                                convertNumber();
                                outY=currentNumber;
                            }

                        
                            
                            break;
                case 'Z':
                case 'z':
                            
                            returned=firstNumberPos();
                            outZ=0;
                            if(returned>=0){
                                convertNumber();
                                outZ=currentNumber;
                            }

                
                            
                            break;
        
                case 'I':
                case 'i':
                        
                            returned=firstNumberPos();
                            outI=0;
                            if(returned>=0){
                                convertNumber();
                                outI=currentNumber;
                            }

                        
                            
                            break;
                case 'J':
                case 'j':
                            
                            returned=firstNumberPos();
                            outJ=0;
                            if(returned>=0){
                                convertNumber();
                                outJ=currentNumber;
                            }

                        
                            
                            break;
                case 'K':
                case 'k':
                        
                            returned=firstNumberPos();
                            outK=0;
                            if(returned>=0){
                                convertNumber();
                                outK=currentNumber;
                            }

                        
                            
                            break;
                case 'F':
                case 'f':
                        
                            returned=firstNumberPos();
                            outF=0;
                            if(returned>=0){
                                convertNumber();
                                outF=currentNumber;
                            }

                        
                            
                            break;

                case 'P':
                case 'p':
                            
                            returned=firstNumberPos();
                            outP=0;
                            if(returned>=0){
                                convertNumber();
                                outP=currentNumber;
                            }

                        
                            
                            break;


                case 'S':
                case 's':
                            
                            returned=firstNumberPos();
                            outS=0;
                            if(returned>=0){
                                convertNumber();
                                outS=currentNumber;
                            }

                        
                            
                            break;
                                        

                        
                        

                case 'G':
                case 'g':
                        returned=firstNumberPos();
                        currentNumber=-1;
                        if(returned>=0){
                            convertNumber();
                            
                            switch ((int)currentNumber)
                            {
                            case 0:  gCode=G0_CODE;break;
                            case 1:  gCode=G1_CODE;break;
                            case 2:  gCode=G2_CODE;break;
                            case 3:  gCode=G3_CODE;break;
                            case 17: gCode=G17_CODE;break;
                            case 18: gCode=G18_CODE;break;
                            case 19: gCode=G19_CODE;break;
                            case 20: gCode=G20_CODE;break;
                            case 21: gCode=G21_CODE;break;
                            case 28: gCode=G28_CODE;break;
                            case 90: gCode=G90_CODE;break;
                            case 91: gCode=G91_CODE;break;
                            case 4:  gCode=G4_CODE;break;
                            case 92: gCode=G92_CODE;break;

                            default: gCode=G_UNDEFINED_CODE;break;
                            }
                        


                        }

                        break;

                case 'M':
                case 'm':
                        returned=firstNumberPos();
                        currentNumber=-1;
                        if(returned>=0){
                            convertNumber();
                            
                            switch ((int)currentNumber)
                            {
                            case 0  : gCode=M0_CODE;break;
                            case 3  : gCode=M3_CODE;break;
                            case 4  : gCode=M4_CODE;break;
                            case 5  : gCode=M5_CODE;break;
                            case 104: gCode=M104_CODE;break;
                            case 109: gCode=M109_CODE;break;
                            case 140: gCode=M140_CODE;break;
                            case 190: gCode=M190_CODE;break;
                            case 112: gCode=M112_CODE;break;
                            case 999: gCode=M999_CODE;break;
                            case 100: gCode=M100_CODE;break;
                            case 17 : gCode=M17_CODE;break;
                            case 18 : gCode=M18_CODE;break;
                            case 105: gCode=M105_CODE;break;
                            case 114: gCode=M114_CODE;break;


                            default:  gCode=M_UNDEFINED_CODE;break;
                            }
                        


                        }

                        break;


                case ' ':
                default: i++;
                        break;



            }

        }


    }







/*
Auxiliar text by Grok:


| **Código** | **Uso Tradicional** |
|------------|---------------------|
| **G0** | Movimiento rápido (no interpolado) a una posición especificada. Usado para reposicionamiento sin acción de corte o extrusión. Ejemplo: `G0 X100 Y100 Z10` mueve rápidamente a (100, 100, 10) mm. |
| **G1** | Movimiento lineal controlado a una posición especificada, con velocidad definida por `F` (mm/min). Usado para movimientos precisos durante corte (CNC) o extrusión (impresora 3D). Ejemplo: `G1 X100 Y100 Z10 F1000`. |
| **G2** | Movimiento en arco en sentido horario en el plano seleccionado (XY, YZ, XZ). Requiere parámetros `I`, `J`, `K` para el centro del arco. Ejemplo: `G2 X50 Y50 I25 J0 F1000` (arco en plano XY). |
| **G3** | Movimiento en arco en sentido antihorario en el plano seleccionado. Similar a `G2`. Ejemplo: `G3 X50 Y50 I25 J0 F1000`. |
| **G17** | Selecciona el plano XY para movimientos circulares (`G2`, `G3`). Estándar para la mayoría de los movimientos 2D en CNC e impresoras 3D. |
| **G18** | Selecciona el plano XZ para movimientos circulares. Usado en aplicaciones CNC específicas. |
| **G19** | Selecciona el plano YZ para movimientos circulares. Menos común, pero útil para ciertas aplicaciones CNC. |
| **G20** | Establece unidades en pulgadas. Cambia la interpretación de todas las coordenadas a pulgadas. |
| **G21** | Establece unidades en milímetros (estándar en impresoras 3D). Ejemplo: `G21` asegura que todas las medidas se interpreten en mm. |
| **G28** | Autocalibración (homing). Mueve los ejes a sus finales de carrera para establecer el origen (0, 0, 0). Ejemplo: `G28 X Y Z` o `G28 X` para un solo eje. |
| **G90** | Activa el modo de posicionamiento absoluto. Las coordenadas se interpretan respecto al origen (0, 0, 0). Estándar para la mayoría de los trabajos. |
| **G91** | Activa el modo de posicionamiento relativo. Las coordenadas se interpretan como desplazamientos desde la posición actual. Útil para movimientos incrementales. |
| **M0** | Parada incondicional. Detiene la máquina y espera intervención manual o un nuevo comando para continuar. Usado para pausas programadas. |
| **M3** | Enciende el husillo en sentido horario (CNC). Parámetro `S` define la velocidad en RPM. Ejemplo: `M3 S1000`. |
| **M4** | Enciende el husillo en sentido antihorario (CNC). Similar a `M3`. Ejemplo: `M4 S1000`. |
| **M5** | Apaga el husillo (CNC). Usado al finalizar un trabajo o antes de reposicionar. |
| **M104** | Establece la temperatura del extrusor (impresora 3D) sin esperar. Ejemplo: `M104 S200` calienta el extrusor a 200°C. |
| **M109** | Establece la temperatura del extrusor y espera a que se alcance antes de continuar. Ejemplo: `M109 S200`. |
| **M140** | Establece la temperatura de la cama calefactada (impresora 3D) sin esperar. Ejemplo: `M140 S60`. |
| **M190** | Establece la temperatura de la cama y espera a que se alcance. Ejemplo: `M190 S60`. |
| **M112** | Parada de emergencia (kill). Detiene todos los motores y bloquea la máquina. Puede requerir reinicio físico o comando de desbloqueo (como `$X` en Grbl). |
| **M999** | Comando no estándar (sugerido). Reinicia el sistema después de una parada de emergencia. Útil para implementaciones personalizadas en Arduino. |

### Códigos adicionales útiles
- **G4**: Pausa temporal (dwell). Detiene la ejecución por un tiempo especificado (en milisegundos con `P` o segundos con `S`). Ejemplo: `G4 P500` pausa 500 ms.
- **G92**: Establece la posición actual como un nuevo punto de referencia sin mover los motores. Ejemplo: `G92 X0 Y0 Z0` redefine la posición actual como (0, 0, 0).
- **M17**: Habilita los motores paso a paso (activa los controladores). Útil para encender los motores después de apagarlos.
- **M18** o **M84**: Deshabilita los motores paso a paso (desactiva los controladores). Útil para ahorrar energía o permitir movimientos manuales.
- **M105**: Reporta las temperaturas actuales (impresora 3D). Usado para monitorear el extrusor y la cama.
- **M114**: Reporta la posición actual de los ejes. Útil para depuración. Ejemplo: `M114` devuelve algo como `X:10 Y:20 Z:5`.

### Notas para tu implementación en Arduino
1. **Motores 24BYJ48**:
   - Estos motores tienen una resolución baja (4096 pasos por revolución en modo full-step), así que asegúrate de calcular los pasos por mm según tu sistema mecánico (husillos, correas, etc.).
   - Los comandos `G0` y `G1` deben coordinar los motores usando interpolación lineal (por ejemplo, algoritmo de Bresenham) para movimientos suaves.
   - Para arcos (`G2`, `G3`), aproxima los movimientos circulares dividiendo el arco en pequeños segmentos lineales, ya que los 24BYJ48 no son ideales para movimientos complejos debido a su velocidad limitada.

2. **Parser de G-code**:
   - Implementa un parser en Arduino para interpretar los comandos y parámetros (`X`, `Y`, `Z`, `I`, `J`, `K`, `F`, `S`, etc.). Puedes usar una librería como `Grbl` o escribir un parser simple que divida las cadenas recibidas por serial.
   - Ejemplo de pseudocódigo para parsear:
     ```cpp
     if (comando.startsWith("G0") || comando.startsWith("G1")) {
       float x = parseParam(comando, 'X', posicionActualX);
       float y = parseParam(comando, 'Y', posicionActualY);
       float z = parseParam(comando, 'Z', posicionActualZ);
       float f = parseParam(comando, 'F', velocidadActual);
       moverLineal(x, y, z, f);
     }
     ```

3. **Firmware y software**:
   - Considera usar un firmware como Grbl (para CNC) o Marlin (para impresoras 3D) como base, ya que soportan la mayoría de estos comandos y son compatibles con Arduino.
   - Comunica los comandos desde un software como Pronterface, Cura o Universal G-code Sender a través del puerto serial (115200 baudios recomendado).

4. **Seguridad y límites**:
   - Usa el comando `M100` (o similar) para definir los límites de los ejes y validar que los movimientos no excedan el volumen de trabajo.
   - Implementa finales de carrera para `G28` y verifica que los motores no intenten moverse más allá de los límites físicos.

5. **Consideraciones para CNC e impresoras 3D**:
   - Para CNC: Los comandos `M3`, `M4`, `M5` son esenciales para controlar el husillo. Puedes conectar un relé a un pin digital del Arduino para activarlo/desactivarlo.
   - Para impresoras 3D: Si planeas agregar un extrusor, implementa `M104`, `M109`, `M140`, `M190` para controlar la temperatura. Necesitarás un termistor y un elemento calefactor.

### Ejemplo de secuencia completa
Para iniciar un trabajo, reiniciar después de una parada y realizar un movimiento típico:
```
G21 ; Unidades en milímetros
G90 ; Posicionamiento absoluto
M100 X300 Y200 Z150 ; Define dimensiones (no estándar)
G28 ; Homing
G0 Z10 ; Sube Z para evitar colisiones
M3 S1000 ; Enciende husillo (CNC)
G1 X50 Y50 Z0 F1000 ; Mueve a posición inicial
G17 ; Selecciona plano XY
G2 X100 Y50 I25 J0 F1000 ; Arco en sentido horario
M0 ; Pausa
; (Enviar siguiente comando para reanudar, por ejemplo:)
G0 X0 Y0 Z0 ; Vuelve al origen
M5 ; Apaga husillo
```




*/
