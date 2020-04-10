/*
5axisCAM Arduino Firmware v1.3
Control 5 motors and all the controllers state (All ON/All OFF)

updates: - Modular implemetation
         - Test and control of new geared tilt and pan
         
Compatibility: Tested with Arduino Mega 2560 + Ramps 1.6 + TMC2130 + NEMA 17(40N.cm)
tilt and pan with gear ratio 5:1 on phi and around 5:1 on theta.
 
WARNING: Always turn OFF the motor controllers before unplugging USB.

to do:
- implement description/help in main code and header files
- Parralax compensation on tilt (theta) and pan (Phi) such that speed of angle swipe match the speed of x,y,z or the average speed
- Spherical  Motion implementation
- Accelleration and decceleration ramps
- Bigger range of speed with continuous microsteping control
- Less important: implement limit switch and stop everything + print error message 
negative speed

Created by Shapes of Emergence, April 4, 2020.
////////////////////////////////////////////////////////////////////////  
*/

//////////////RAMPS PINOUTS///////////////
///////////////////////////////////
#include "RAMPS_DEFINE_pin.h"
///////////////////////////////////

//// global variable: motor, stop switch, PS2 control, Maths and parsing
#include "GlobalVariable.h"
/////////////////////////////////////////


///// Arduino libraries
#include <Regexp.h> //for speed value extraction from character Serial command
#include <math.h>
//#include <Wire.h> 
//#include <LiquidCrystal_I2C.h>

////Motors Definition
#include "MOTORS_DEFINE_TMC2130.h"

//project library
#include "Motion.h"
#include "Display_SerialComputer.h"
#include "READ_serial.h"

int Init=1; //1 to do bring the motor at the default value of R at start up. The origin correponds to the initial position of the camera when system turned on.

////LCD screen setup
//LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display


void setup() {
  //delay(1000);//TO OPTIMIZE
  SPI.begin();
  Serial.begin(115200);
  Serial2.begin(115200);//PS2 gamepad serial port

  Serial.println("Initial State: Motor controllers OFF");
  Serial.println("Turn motor controllers ON/OFF: type S1/S0");
  Serial.println("Average speed command, for V=1000: type ST1000;");
  Serial.println(" ");


  /////////////////Initialze motor driver parameters////////////////
  #include "MOTORS_INITIALIZE_TMC2130.h"
  
  ///////execute init mode= go to X=0;Y=R;Z=0;
  if (Init==1){Serial.println("Spherical intitialization in progress");Serial1.println("C03-Init;");} //print on screen       
  #include "Initialize_spherical.h"
  //if (Init==0){Serial1.println("C03-Ready;");}

  // wait a bit for the entire message to arrive
  delay(1000);//TO OPTIMIZE

  AVG_SPEED_TARGET=MIN_AVG_SPEED;

  X_Mot_Pos=X_stepper.currentPosition();
  Y_Mot_Pos=Y_stepper.currentPosition();
  Z_Mot_Pos=Z_stepper.currentPosition();
  P_Mot_Pos=P_stepper.currentPosition();
  T_Mot_Pos=T_stepper.currentPosition();

}

void loop() {

unsigned long currentMillis = millis();
//Serial.println(digitalRead(11));


 if(Serial.available()>0){  ////read serial port 0 (USB computer)


    rxChar_computer = Serial.read();   

    READ_serial.CreateString(rxChar_computer, rxText_computer, rxN_computer);

    READ_serial.SERIAL_MONITOR(rxText_computer, rxN_computer, MAX_AVG_SPEED, MIN_AVG_SPEED, AVG_SPEED_TARGET, Motor_SWITCH);


 if (Motor_SWITCH==1){

      X_stepper.enableOutputs();
      Y_stepper.enableOutputs();
      Z_stepper.enableOutputs();
      P_stepper.enableOutputs();
      T_stepper.enableOutputs();
      Serial.println("Motors ON");
    }


 if (Motor_SWITCH==0){

      X_stepper.disableOutputs();
      Y_stepper.disableOutputs();
      Z_stepper.disableOutputs();
      P_stepper.disableOutputs();
      T_stepper.disableOutputs();
      Serial.println("Motors OFF");
    }
  }///end if serial.available() 

  
  if(Serial2.available()>0){   ////read serial port from PS2 controller
    
    // Get next character
     rxChar_PS2 = Serial2.read();
    //  Serial.print("Characters received in serial port=");Serial.println(rxChar);      


     READ_serial.CreateString(rxChar_PS2, rxText_PS2, rxN_PS2);
   
     READ_serial.GAMEPAD(rxText_PS2, rxN_PS2, St, L3, lx, ly, lz, rx, ry, R3, MAX_AVG_SPEED, MIN_AVG_SPEED, AVG_SPEED_TARGET, Z_obj, Z_obj_MAX);
       //Serial.print("R3=");Serial.println(R3);

     if (R3==1){
        //Serial.print("R3=");Serial.println(R3);
        X_stepper.setCurrentPosition(0);
        Y_stepper.setCurrentPosition(0);
        Z_stepper.setCurrentPosition(0);
        P_stepper.setCurrentPosition(0);
        T_stepper.setCurrentPosition(0);  
        Serial.println("NEW ORIGIN SET AT THIS POSITION");
        R3=0;
        }

  }//end if serial2.available() 
  
 else {L3=0;
  // Serial.print("L3=");Serial.println(L3);
  }


 if (St==0){ //Cartesian mode

    if (L3==0){
        V=AVG_SPEED_TARGET;}
    else {V=MAX_AVG_SPEED;
    //Serial.print("V=");Serial.println(V);
    }


    Motion.Cartesian(Motor_speed_X, Motor_speed_Y,Motor_speed_Z,Motor_speed_P, Motor_speed_T,V,Z_obj,lx,ly,lz,rx,ry);


    X_Mot_Pos=X_stepper.currentPosition();
    Y_Mot_Pos=Y_stepper.currentPosition();
    Z_Mot_Pos=Z_stepper.currentPosition();
    P_Mot_Pos=P_stepper.currentPosition();
    T_Mot_Pos=T_stepper.currentPosition();

 //   
   if (currentMillis - previousMillis2 >= Display_Timer){
    // Save timestamp
    previousMillis2 = currentMillis;

    Display_SerialComputer.Cartesian();

      } 
  
  }// end Cartesian mode



 if (St==1){ //Spherical mode 


   if (L3==0){
        V=AVG_SPEED_TARGET;}
    else {V=MAX_AVG_SPEED;
    //Serial.print("V=");Serial.println(V);
   }

   X_Mot_Pos=X_stepper.currentPosition();
   Y_Mot_Pos=Y_stepper.currentPosition();
   Z_Mot_Pos=Z_stepper.currentPosition();

   Motion.Spherical(X_Mot_Pos, Y_Mot_Pos, Z_Mot_Pos, Motor_speed_X, Motor_speed_Y,Motor_speed_Z,Motor_speed_P, Motor_speed_T,V,Z_obj, R,lx,ly,lz,rx,ry);

   X_Mot_Pos=X_stepper.currentPosition();
   Y_Mot_Pos=Y_stepper.currentPosition();
   Z_Mot_Pos=Z_stepper.currentPosition();
   P_Mot_Pos=P_stepper.currentPosition();
   T_Mot_Pos=T_stepper.currentPosition();         

 //   
   if (currentMillis - previousMillis2 >= 1000){
    // Save timestamp
    previousMillis2 = currentMillis;

    Display_SerialComputer.Spherical();
    }
    
 } //end Spherical mode 


/////// put * here for LCD screen and limiot switches update

 //set motor speed
 X_stepper.setSpeed(Motor_speed_X);
 Y_stepper.setSpeed(Motor_speed_Y);
 Z_stepper.setSpeed(Motor_speed_Z);//Zfactor because lead screw need more step for the same displacement
 P_stepper.setSpeed(Motor_speed_P);
 T_stepper.setSpeed(Motor_speed_T);


 //run motors
 X_stepper.runSpeed();
 Y_stepper.runSpeed();
 Z_stepper.runSpeed();
 P_stepper.runSpeed();
 T_stepper.runSpeed();
   
}// end of main loop 







//////////////////  * pieces of code for further update: print on LCD screen and limiot switches
/////PRINT SCREEN COMMENTS STARTS HERE
//
/////////////////////////PRINT INFOS ON LCD SCREEN BY SENDING CHAR TO SERIAL PORT 1 (to an other arduino with sketch LCD_Screen.ino)/////////////////////////////////////////////////////////
////////format: C01-X100 Y345 Z425; as C[colum][line]-[string to display];
////////C00; give the position in the LCD screen where the string is writen C00=colum 0, line 0.
//
//     // lcd.clear();
//     // lcd.backlight();
//if (currentMillis - previousMillis2 >= 1000){
//    // Save timestamp
//    previousMillis2 = currentMillis;
//         //char bufferCOOR[30];
//
//         char bufferX[6];
//         char bufferY[6];
//         char bufferZ[6];
////         char bufferP[6];
////         char bufferT[6];
////         char bufferV[6];
////         
//        // sprintf(bufferCOOR,"X%+05dY%+05dZ%+05d",X_stepper.currentPosition(),Y_stepper.currentPosition(),Z_stepper.currentPosition());
//         
//         sprintf(bufferX, "X%+05d",X_stepper.currentPosition());
//         sprintf(bufferY, "Y%+05d",Y_stepper.currentPosition());
//         sprintf(bufferZ, "Z%+05d",Z_stepper.currentPosition());
//
//
//
//
//
//        // sprintf(bufferP, "P%+05d",phi);
//        // sprintf(bufferT, "T%+05d",theta);
//        // sprintf(bufferV, "V%04d",AVG_SPEED_TARGET);
//
//      if (St==0 && SPEED[0]==0){
//        
//
////
////        Serial1.print("C00-MOTORS OFF;"); 
////        Serial1.print("C01-X");Serial1.print(X_stepper.currentPosition());
////        Serial1.print(" Y");Serial1.print(Y_stepper.currentPosition());
////        Serial1.print(" Z");Serial1.print(Z_stepper.currentPosition());Serial1.print(";");
////        Serial1.println("C02-CARTESIAN MODE;");     
//        
//
////        Serial1.print("C00-MOTORS OFF;");
////        Serial1.print("C01-");Serial1.print(bufferX);Serial1.print(bufferY);Serial1.print(bufferZ);Serial1.print(";");
////        Serial1.print("C02-CARTESIAN MODE;");     
////        Serial1.print("C03-");Serial1.print(bufferP);//Serial1.print(bufferT);
////        //Serial1.print(bufferV);
////        //Serial1.println(";");
////
////        Serial1.print("C00-MOTORS OFF;");
////        Serial1.print("C01-");Serial1.print(bufferCOOR);//Serial1.print(bufferX);Serial1.print(bufferY);Serial1.print(bufferZ);
////        Serial1.print(";");
////        Serial1.println("C02-CARTESIAN MODE;");     
////  
////  
////          Serial1.print("C00-MOTORS OFF;");
////          Serial1.print("C01-X");Serial1.print(X_stepper.currentPosition());Serial1.print(";");
////          Serial1.print("C81-Y");Serial1.print(Y_stepper.currentPosition());Serial1.print(";");
////         // Serial1.print("C151-Z");Serial1.print(Z_stepper.currentPosition());Serial1.print(";");
////          Serial1.println("C02-CARTESIAN MODE;");  
////     
////        Serial.print("C00-MOTORS OFF;");
////        Serial.print("C01-X");Serial.print(X_stepper.currentPosition());Serial.print(";");
////        Serial.print("C81-Y");Serial.print(Y_stepper.currentPosition());Serial.print(";");
////       // Serial1.print("C151-Z");Serial1.print(Z_stepper.currentPosition());Serial1.print(";");
////        Serial.println("C02-CARTESIAN MODE;");  
//
////
//        Serial1.print("C00-MOTORS OFF;");
//        Serial1.print("C01-");//Serial.print(bufferCOOR);
//        Serial1.print(bufferX);Serial1.print(bufferY);Serial1.print(bufferZ);Serial1.print(";");
//        Serial1.println("C02-CARTESIAN MODE;");  
//
//
////        Serial.print("C00-MOTORS OFF;");
////        Serial.print("C01-");Serial.print(bufferX);Serial.print(bufferY);Serial.print(bufferZ);Serial.print(";");
////        Serial.println("C02-CARTESIAN MODE;");    
//        
//       // Serial.print("C03-");//Serial.print(bufferP);//Serial.print(bufferT);
//        //Serial.print(bufferV);
//      //  Serial.println(";");
//        
////        Serial.print("C00-MOTORS OFF;");Serial.print("C01-");  
////        Serial.print(bufferX);Serial.print(bufferY);Serial.print(bufferZ);Serial.print(";");
////        Serial.println("C02-CARTESIAN MODE;");     
//
//          }
//      
//   
//      if (St==1 && SPEED[0]==0){
////        
//
//         
//         
//        Serial1.print("C00-MOTORS OFF;");//Serial1.print("C01-");  
//        //Serial1.print(bufferX);Serial1.print(bufferY);Serial1.print(bufferZ);Serial1.print(";");
//        Serial1.print("C01-");//Serial1.print(bufferCOOR);
//        Serial1.print(bufferX);Serial1.print(bufferY);Serial1.print(bufferZ);
//        Serial1.print(";");
//        Serial1.println("C02-SPHERICAL MODE;");  
//
////        Serial1.print("C00-Motors OFF;"); 
////        Serial1.print("C01-X");Serial1.print(X_stepper.currentPosition());
////        Serial1.print(" Y");Serial1.print(Y_stepper.currentPosition());
////        Serial1.print(" Z");Serial1.print(Z_stepper.currentPosition());Serial1.print(";");
////        Serial1.println("C02-SPHERICAL MODE;");
//          }
//
//
//      if (St==0 && SPEED[0]==1){
//
//        Serial1.print("C00-MOTORS ON ;");//Serial1.print("C01-");  
//        //Serial1.print(bufferX);Serial1.print(bufferY);Serial1.print(bufferZ);Serial1.print(";");
//        Serial1.print("C01-");//Serial1.print(bufferCOOR);
//        Serial1.print(bufferX);Serial1.print(bufferY);Serial1.print(bufferZ);
//        Serial1.print(";");
//        Serial1.println("C02-CARTESIAN MODE;");
////         Serial1.print("C00-Motors ON ;"); 
////         Serial1.print("C01-X");Serial1.print(X_stepper.currentPosition());
////         Serial1.print(" Y");Serial1.print(Y_stepper.currentPosition());
////         Serial1.print(" Z");Serial1.print(Z_stepper.currentPosition());Serial1.print(";");
////         Serial1.println("C02-CARTESIAN MODE;");
//          }
//      
//   
//      if (St==1 && SPEED[0]==1){
//
//
//        Serial1.print("C00-MOTORS ON ;");//Serial1.print("C01-");  
//      //  Serial1.print(bufferX);Serial1.print(bufferY);Serial1.print(bufferZ);Serial1.print(";");
//        Serial1.print("C01-");//Serial1.print(bufferCOOR);
//        Serial1.print(bufferX);Serial1.print(bufferY);Serial1.print(bufferZ);Serial1.print(";");
//        Serial1.println("C02-SPHERICAL MODE;");
////         Serial1.print("C00-Motors ON ;"); 
////         Serial1.print("C01-X");Serial1.print(X_stepper.currentPosition());
////         Serial1.print(" Y");Serial1.print(Y_stepper.currentPosition());
////         Serial1.print(" Z");Serial1.print(Z_stepper.currentPosition());Serial1.print(";");
////         Serial1.println("C02-SPHERICAL MODE;");
//          }
//
//}
////////////////////////////////////////////////////////////////////////////  
//
/////PRINT SCREEN COMMENTS ENDS HERE


///TO PUT BACK WHEN LIMIT SWITCHES ARE INSTALLED!!!!
//////Stop switch state
//    X_switch0= char(digitalRead(X_MIN_PIN));
//    X_switch1= char(digitalRead(X_MAX_PIN));
//    
//    Y_switch0= char(digitalRead(Y_MIN_PIN));
//    Y_switch1= char(digitalRead(Y_MAX_PIN));
//    
//    Z_switch0= char(digitalRead(Z_MIN_PIN));
//    Z_switch1= char(digitalRead(Z_MAX_PIN));
//
//  ////if switch on=evrything turned of
//    if (X_switch0+X_switch1+Y_switch0+Y_switch1+Z_switch0+Z_switch1>=1)
//  {

  
//   // SPEED[0]=0; if you want the limit switch to en
//    SPEED[1]=0;
//    SPEED[2]=0;
//    SPEED[3]=0;
//    SPEED[4]=0;
//    SPEED[5]=0;
    
//
//    X_stepper.disableOutputs();
//    Y_stepper.disableOutputs();
//    Z_stepper.disableOutputs();
//    P_stepper.disableOutputs();
//    T_stepper.disableOutputs();
//    digitalWrite(P_ENABLE_PIN, HIGH);
//    digitalWrite(T_ENABLE_PIN, HIGH); 

//    SwC=SwC+1;
//
//    if (SwC<2){
//    Serial.print("Error: switch "); 
//    Serial.print(X_switch0);
//    Serial.print(X_switch1);
//    Serial.print(Y_switch0);
//    Serial.print(Y_switch1);
//    Serial.print(Z_switch0);
//    Serial.print(Z_switch1);
//    Serial.println(" touching the stage"); }  
//  } 
//  else { 
//  SwC=0;
//  }
  
//    ///send state to PC via serial every 
//
//     if (currentMillis - previousMillis1 >= SInterval){
//    // Save timestamp
//    previousMillis1 = currentMillis;
//    Serial.print("S");
//    Serial.print(X_switch0);
//    Serial.print(X_switch1);
//    Serial.print(Y_switch0);
//    Serial.print(Y_switch1);
//    Serial.print(Z_switch0);
//    Serial.print(Z_switch1);
//    Serial.println(";");
//     }
//    /////////////////////////// 
