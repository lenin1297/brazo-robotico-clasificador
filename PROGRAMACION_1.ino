
/*  CODIGO PARA EL CONTROL DE BRAZO ROBOTICO CLASIFICADOR DE OBJETOS SOLIDOS POR COLORES */

#include <VarSpeedServo.h>  // INCLUIMOS LA LIBRERIA SERVO LA CUAL NOS AYUDARA PARA FACILITAR LA PROGRAMACION Y CONTROLAR SU VELOCIDAD.

VarSpeedServo servo1; // CREAMOS CADA UNO DE LOS OBJETOS SERVO QUE UTILIZAMOS.
VarSpeedServo servo2;
VarSpeedServo servo3;
VarSpeedServo servo4;
VarSpeedServo servo5;
VarSpeedServo servo6;

const int s0 = 2;   // SE NOMBRA CADA UNO DE LOS PINES DEL SENSOR COMO VARIABLES.
const int s1 = 3;  
const int s2 = 4;  
const int s3 = 5;  
const int out = 6;    

int rojo = 0;  // SE CREA VARIABLE DE CADA UNO DE LOS COLORES QUE VAMOS A UTILIZAR.
int verde = 0;  
int azul = 0;  

int banda = 15; // SE COLOCA EL PIN ENCARGADO DE CONTROLAR EL FUNCIONAMIENTO DEL MOTOR DE LA BANDA TRANSPORTADORA

int presencia = 14; //PIN DEL SENSOR DE LLEGADA DE CADA UNO DE LOS CUBOS POR CENSAR.

int velocidad=30;

void setup(){  
  Serial.begin(9600); // SE INICIAL LA COMUNICACION SERIAL A 9600 BAUDIOS.

  pinMode(banda,OUTPUT); // MODO DE TRABAJO DEL PIN PARA EL CONTROL DEL MOTOR DE LA BANDA.
  pinMode(presencia,INPUT); // MODO DE TRABAJO DEL PIN PARA LA LECTURA DEL SENSOR DE PRESENCIA.
  
  pinMode(s0,OUTPUT);  // SE COLOCA EL MODO DE TRABAJO DE CADA UNO DE LOS PINES DEL SENSOR DE COLORES
  pinMode(s1,OUTPUT);  
  pinMode(s2,OUTPUT);  
  pinMode(s3,OUTPUT);  
  pinMode(out,INPUT);   
  digitalWrite(s0,HIGH);  //s0 y s1 EN HIGH PARA UNA FRECUENCIA DE SALIDA DEL 100%.
  digitalWrite(s1,HIGH);  

  servo1.attach(7); // DIGITALIZAMOS LOS PINES LOS CUALES SE ENCARGARAN DE CONTROLAR CADA UNO DE LOS SERVOMOTORES.
  servo2.attach(8);
  servo1.attach(9);
  servo2.attach(10);
  servo1.attach(11);
  servo2.attach(12);

  POSICION_INICO();  //POSICION DE INICIO DEL BRAZO ROBOTICO
    
  delay(900); // DELAY DE INICIO
}  

   
void loop(){  

  
  if (presencia==0) {

    digitalWrite(banda,LOW);
 
    //MOVIMIENTO DE BRAZO 1 (GIRAR PARA COGER)
    GIRAR_PARA_COGER();
    //MOVIMIENOT DE BRAZO 2 (AGACHARSE PARA COGER)
    AGACAHR_PARA_COGER();
    //MOVIMIENTO DE BRAZO 3 (COGER OBJETO)
    COGER_OBJETO();
    //MOVIMIENTO DE BRAZO 4 (LEVANTAR OBJETO)
    LEVANTAR_OBJETO();
    //MOVIMIENTO DE BRAZO 5 (GIRAR AL SENSOR)
    GIRO_AL_SENSOR();
    //MOVIMIETO DE BRAAZO 6 (COLOCAR OBJETO EN EL SENSOR)
    COLOCAR_OBJETO_EN_SENSOR();
     
     color();
      Serial.print("   ");  
      Serial.print(rojo, DEC);  
      Serial.print("   ");  
      Serial.print(verde, DEC);  
      Serial.print("   ");  
      Serial.print(azul, DEC);
      delay(500); 

      //MOVIMIENTO DE BRAZO 7 (LEVANTAR DEL SENSOR)
      LEVANTAR_OBJETO_DEL_SENSOR();
  
       if (rojo < azul && verde > azul && rojo < 35) 
          {  
           Serial.println("   Rojo");
           delay(500);
           
           //MOVIMIENTO DE BRAZO 8 (GIRAR AL DEPOSITO ROJO)
           GIRAR_HACIA_ROJO();
           //MOVIMIENTO DE BRAZO 9 (AGACHAR AL DEPOSITO)
           AGAHCAR_EN_ROJO();
           //MOVIMIENTO DE BRAZO 10 (SOLTAR OBJETO)
           SOLTAR_OBJETO_ROJO();
           //POSICION DE INICIO
           POSICION_INICO();
           
          }   
      else if (azul < rojo && azul < verde && verde < rojo)  
          {  
           Serial.println("   Azul");
           delay(500);
           
           //MOVIMIENTO DE BRAZO 11 (GIRAR AL DEPOSITO AZUL)
           GIRAR_HACIA_AZUL();
           //MOVIMIENTO DE BRAZO 12 (AGACHARSE AL DEPOSITO)
           AGACHAR_EN_AZUL();
           //MOVIMIENTO DE BRAZO 13 (SOLTAR OBJETO)
           SOLTAR_OBJETO_AZUL();
           //POSICION DE INICIO
           POSICION_INICO();
                  
          }  

      else if (rojo > verde && azul > verde )  
         {  
          Serial.println("   Verde");
          delay(500);
          
          //MOVIMIENTO DE BRAZO 14 (GIRAR AL DEPOSITO VERDE)
          GIRAR_HACIA_VERDE();
          //MOVIMIENTO DE BRAZO 15 (AGACHARSE AL DEPOSITO)
          AGACHAR_EN_VERDE();
          //MOVIMIENTO DE BRAZO 16 (SOLTAR OBJETO)
          SOLTAR_OBJETO_VERDE();
          //POPSICION DE INICIO
          POSICION_INICO();
          
         }
    
     
  } else {
    //MOVIMIENTO DE BRAZO 0 (posicion de inico)
    POSICION_INICO();
    digitalWrite(banda,HIGH);
  } 
  
}  
    
void color()  
{    
  digitalWrite(s2, LOW);  //PROGRAMACION PARA EL TRABAJO DEL SENSOR DE COLORES.
  digitalWrite(s3, LOW);   
  rojo = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  digitalWrite(s3, HIGH);   
  azul = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  digitalWrite(s2, HIGH);    
  verde = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
}

void POSICION_INICO() { //PRIMERA POSICION DE BRAZO ALZADO
  servo1.write(90,velocidad,true);
  servo2.write(55,velocidad,true);
  servo3.write(70,velocidad,true);
  servo4.write(10,velocidad,true);
  servo5.write(90,velocidad,true);
  servo6.write(180,velocidad,true);
}


void GIRAR_PARA_COGER() { // GIRAR PARA COGER OBJETO
  servo1.write(0,velocidad,true);
  servo2.write(60,velocidad,true);
  servo3.write(120,velocidad,true);
  servo4.write(50,velocidad,true);
  servo5.write(90,velocidad,true);
  servo6.write(90,velocidad,true);
}

void AGACAHR_PARA_COGER() {  //AGACHARSE A COGER EL OBJETO
  servo1.write(0,velocidad,true);
  servo2.write(90,velocidad,true);
  servo3.write(90,velocidad,true);
  servo4.write(45,velocidad,true);
  servo5.write(90,velocidad,true);
  servo6.write(90,velocidad,true);
}


void COGER_OBJETO() { //AGARRAR OBJETO 
  servo1.write(0,velocidad,true);
  servo2.write(90,velocidad,true);
  servo3.write(90,velocidad,true);
  servo4.write(45,velocidad,true);
  servo5.write(90,velocidad,true);
  servo6.write(150,velocidad,true);
}

void LEVANTAR_OBJETO() { //LEVANTAR OBJETO
  servo1.write(0,velocidad,true);
  servo2.write(60,velocidad,true);
  servo3.write(120,velocidad,true);
  servo4.write(50,velocidad,true);
  servo5.write(90,velocidad,true);
  servo6.write(150,velocidad,true);
}

void GIRO_AL_SENSOR() { //GIRAR AL SENSOR
  servo1.write(90,velocidad,true);
  servo2.write(60,velocidad,true);
  servo3.write(120,velocidad,true);
  servo4.write(50,velocidad,true);
  servo5.write(90,velocidad,true);
  servo6.write(150,velocidad,true);
}

void COLOCAR_OBJETO_EN_SENSOR() { //COLOCAR EL OBJETO EN EL SENSOR
  servo1.write(100,velocidad,true);
  servo2.write(115,velocidad,true);
  servo3.write(90,velocidad,true);
  servo4.write(43,velocidad,true);
  servo5.write(90,velocidad,true);
  servo6.write(150,velocidad,true);
}

void LEVANTAR_OBJETO_DEL_SENSOR() { //LEVANTAR OBJETO DEL SENSOR
  servo1.write(100,velocidad,true);
  servo2.write(110,velocidad,true);
  servo3.write(145,velocidad,true);
  servo4.write(25,velocidad,true);
  servo5.write(90,velocidad,true);
  servo6.write(150,velocidad,true);
}

void GIRAR_HACIA_ROJO(){ //GIRAR HACIA EL DEPOSITO ROJO EN CASSO DE SER DE COLOR ROJO
  servo1.write(110,velocidad,true);
  servo2.write(110,velocidad,true);
  servo3.write(145,velocidad,true);
  servo4.write(25,velocidad,true);
  servo5.write(90,velocidad,true);
  servo6.write(150,velocidad,true);
}

void GIRAR_HACIA_VERDE() { //GIRAR AL DEPOSITO VERDE EN CASO DE SER DE COLOR VERDE
  servo1.write(145,velocidad,true);
  servo2.write(110,velocidad,true);
  servo3.write(145,velocidad,true);
  servo4.write(25,velocidad,true);
  servo5.write(90,velocidad,true);
  servo6.write(150,velocidad,true);
}

void GIRAR_HACIA_AZUL() { //GIRAR AL DEPOSITO AZUL EN CASO DE SER DE COLOR AZUL
  servo1.write(165,velocidad,true);
  servo2.write(110,velocidad,true);
  servo3.write(145,velocidad,true);
  servo4.write(25,velocidad,true);
  servo5.write(90,velocidad,true);
  servo6.write(150,velocidad,true);
}

void AGAHCAR_EN_ROJO() { //BAJAR PINZA EN CASO DE SER DE COLOR ROJO
  servo1.write(110,velocidad,true);
  servo2.write(165,velocidad,true);
  servo3.write(165,velocidad,true);
  servo4.write(70,velocidad,true);
  servo5.write(90,velocidad,true);
  servo6.write(150,velocidad,true);
}

void AGACHAR_EN_VERDE() { //BAJAR PINZA EN CASO DE SER VERDE
   servo1.write(145,velocidad,true);
  servo2.write(170,velocidad,true);
  servo3.write(175,velocidad,true);
  servo4.write(50,velocidad,true);
  servo5.write(90,velocidad,true);
  servo6.write(150,velocidad,true);
}

void AGACHAR_EN_AZUL() { //BAJAR PINZA EN CASO DE SER AZUL
   servo1.write(165,velocidad,true);
  servo2.write(120,velocidad,true);
  servo3.write(100,velocidad,true);
  servo4.write(50,velocidad,true);
  servo5.write(90,velocidad,true);
  servo6.write(150,velocidad,true);
}

void SOLTAR_OBJETO_ROJO() { //ABRIR PINZA PARA SOLTAR EL OBJETO
  servo1.write(110,velocidad,true);
  servo2.write(165,velocidad,true);
  servo3.write(165,velocidad,true);
  servo4.write(70,velocidad,true);
  servo5.write(90,velocidad,true);
  servo6.write(90,velocidad,true);
}

void SOLTAR_OBJETO_VERDE() { //ABRIR PINZA PARA SOLTAR EL OBJETO
  servo1.write(145,velocidad,true);
  servo2.write(170,velocidad,true);
  servo3.write(175,velocidad,true);
  servo4.write(50,velocidad,true);
  servo5.write(90,velocidad,true);
  servo6.write(90,velocidad,true);
}

void SOLTAR_OBJETO_AZUL() { //ABRIR PINZA PARA SOLTAR EL OBJETO
   servo1.write(165,velocidad,true);
  servo2.write(120,velocidad,true);
  servo3.write(100,velocidad,true);
  servo4.write(50,velocidad,true);
  servo5.write(90,velocidad,true);
  servo6.write(90,velocidad,true);
}
