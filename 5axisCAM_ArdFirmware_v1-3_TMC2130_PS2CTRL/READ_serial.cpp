#include <Arduino.h>
#include <Regexp.h>
#include "READ_serial.h"
//#include "MOTORS_DEFINE_TMC2130.h"


fclass3::fclass3(){
}


void fclass3::CreateString(char RXCHAR, char (&RXTEXT)[50], int & RXN){

    // Add normal character
    if(RXCHAR!='\n'){
      RXTEXT[RXN]=RXCHAR;
      RXN++;
    }
    // Text is done -> extract speed values as integers and Print results
    if(RXCHAR=='\n') {
      RXTEXT[RXN]='\0'; // Terminate the string
 //     Serial.print("char read at ");Serial.println(millis());      
      RXN = 0; // Reset the receive counter
    }      
     //Serial.print("Characters detected=");Serial.println(rxText);      

}


void fclass3::GAMEPAD(char (&RXTEXT)[50], int RXN, int & St_local, int & L3_local, float & LX, float & LY, float & LZ, float & RX,float & RY, int & R3_local, int MAX_SPEED, int MIN_SPEED, float & V, long int & r, long int r_max)
{

      if (RXN==0){
        
      // match state object
     MatchState ms;
     ms.Target(RXTEXT);      

//      if (AVG_SPEED_TARGET>MAX_AVG_SPEED){
//        AVG_SPEED_TARGET=MAX_AVG_SPEED;
//         Serial.print("Max limit V reached => ");
//         }
    
     ///Start button= switch mode cartesian/spherical
     char resultSt=ms.Match ("(St)(%d)",0);
      if (resultSt == REGEXP_MATCHED){
        char captureBuf [10];
        St_local=atoi(ms.GetCapture (captureBuf,1)); 
        if (St_local==1){Serial.print("SPHERICAL MODE, St="); Serial.println(St_local);}
        else      {Serial.print("CARTESIAN MODE, St="); Serial.println(St_local);}

      }

     //////Lock move in spherical mode
      char resultL3=ms.Match ("(L3)",0);
      if (resultL3 == REGEXP_MATCHED){
        //char captureBuf [10];
        L3_local=1; 
        Serial.print("L3=");Serial.println(L3_local);
      } 
      ////////joystick L
     char resultLX=ms.Match ("(LX)(%d+)(;)",0);
      if (resultLX == REGEXP_MATCHED){
        char captureBuf [10];
        LX=map(atoi(ms.GetCapture (captureBuf,1)), 0, 255, -128, 128); 
      //  LX=atoi(ms.GetCapture (captureBuf,1)); 
      //  Serial.print("LX="); Serial.println(LX);
      }


      char resultLY=ms.Match ("(LY)(%d+)(;)",0);
      if (resultLY == REGEXP_MATCHED){
        char captureBuf [10];
        LY=-1*map(atoi(ms.GetCapture (captureBuf,1)), 0, 255, -128, 128); 
        //LY=atoi(ms.GetCapture (captureBuf,1)); 

      //  Serial.print("LY="); Serial.println(LY);
      }

     char resultLZ=ms.Match ("(LZ)(%d+)(;)",0);
      if (resultLZ == REGEXP_MATCHED){
        char captureBuf [10];
        LZ=-1*map(atoi(ms.GetCapture (captureBuf,1)), 0, 255, -128, 128); 
      //  Serial.print(";LZ="); Serial.println(LZ);
      } 
      ///////////////////////////////////

      ////////joystick R
     char resultRX=ms.Match ("(RX)(%d+)(;)",0);
      if (resultRX == REGEXP_MATCHED){
        char captureBuf [10];
        RX=map(atoi(ms.GetCapture (captureBuf,1)), 0, 255, -128, 128); 
        //Serial.print("RX="); Serial.println(RX);
      }


      char resultRY=ms.Match ("(RY)(%d+)(;)",0);
      if (resultRY == REGEXP_MATCHED){
        char captureBuf [10];
        RY=-1*map(atoi(ms.GetCapture (captureBuf,1)), 0, 255, -128, 128); 
       // Serial.print("RY="); Serial.println(RY);
      }
     ///////////////////////////////////



//      /////////////////R1-R2 = move camera/object in Z
//      char resultR1=ms.Match ("(R1)(%d)",0);
//      if (resultR1 == REGEXP_MATCHED){
//       char captureBuf [10];
//        R1=atoi(ms.GetCapture (captureBuf,1)); 
//        if (R1==1){Serial.println("Z MOVE UP");}// Serial.println(R1);}
//        else      {Serial.println("Z Stop ");}// Serial.println(R1);}
//        //R1=1;
//     //   Serial.println("R1");// Serial.println(R1);
//      }// else {R1=0;}
//
//      char resultR2=ms.Match ("(R2)(%d)",0);
//      if (resultR2 == REGEXP_MATCHED){
//        char captureBuf [10];
//         R2=atoi(ms.GetCapture (captureBuf,1)); 
//        if (R2==1){Serial.println("Z MOVE DOWN");}// Serial.println(R1);}
//        else      {Serial.println("Z Stop ");}// Serial.println(R1);}
//      //  R2=1; 
//       // Serial.println("R2");// Serial.println(R2);
//      } // else {R2=0;}
//      //////////////////////////////////////////////////

     ////////////R3 update origin////////
      char resultR3=ms.Match ("(R3)",0);
      if (resultR3 == REGEXP_MATCHED){
       // char captureBuf [10];
        R3_local=1;//atoi(ms.GetCapture (captureBuf,1)); 
//        X_stepper.setCurrentPosition(0);
//        Y_stepper.setCurrentPosition(0);
//        Z_stepper.setCurrentPosition(0);
//        P_stepper.setCurrentPosition(0);
//        T_stepper.setCurrentPosition(0);  
//        Serial.println("NEW ORIGIN SET AT THIS POSITION");
      }
     //////////////

      ////////////////////COLOR BUTTON////////////////
     char resultG=ms.Match ("(G)",0);
     if (resultG == REGEXP_MATCHED){
        V=V+10;
        if (V>MAX_SPEED){
         V=MAX_SPEED;
         Serial.print("Max limit V reached => ");
         }        
        Serial.print("Average Speed=");Serial.println(V);
      } 

     char resultB=ms.Match ("(B)",0);
     if (resultB == REGEXP_MATCHED){
        if (V>MIN_SPEED){V=V-10;}
        else {V=MIN_SPEED;}
        Serial.print("Average Speed=");Serial.println(V);
      } 



     ////////////read r////////////
     
     char resultP=ms.Match ("(P)",0);
     if (resultP == REGEXP_MATCHED){
     // if (St==0) {
        if (r>10){r=r-1;}else{r=10;}
           Serial.print("VR=");Serial.print(r);Serial.println(" mm");
     //  }
     // if (St==1) {
     //  if (R>0){R=R-1;}else{R=0;}
     //  Serial.print("R=");Serial.println(R);
     //}
        
      }

     char resultRe=ms.Match ("(Re)",0);
     if (resultRe == REGEXP_MATCHED){
      //  if (St==0) {
          if (r<r_max){r=r+1;}else{r=r_max;}
           Serial.print("VR=");Serial.print(r);Serial.println(" mm");
      //    }
      //  if (St==1) {
      //    if (R<R_MAX){R=R+1;}else{R=R_MAX;}
      //     Serial.print("R=");Serial.println(R);
      // }
      }

      ////////////////////////////////////////


              
//        
//        R=R+1;
//         if (R>R_MAX){
//         R=R_MAX;
//         Serial.print("Max limit R reached => ");
//         }        
//        Serial.print("R=");Serial.println(R);}


//     //////TEST FOR NEW ORIGIN IN SPHERICAL MODE
//     char resultR3=ms.Match ("(R3)",0);
//     if (resultR3 == REGEXP_MATCHED){
//        X_stepper.currentPosition()=0;
//        Y_stepper.currentPosition()=0;
//        Z_stepper.currentPosition()=0;
//        P_stepper.currentPosition()=0;
//        T_stepper.currentPosition()=0;  
//        Serial.println("NEW ORIGIN SET AT THIS POSITION");
//      }
//       ///////////////////////////////////////////////////////

      
      
//      Serial.print("SPEED vector created at ");Serial.println(millis());

////      // original command received
//       Serial.print ("State=");Serial.print (SPEED[0]);Serial.print (" ");
//       Serial.print ("Speeds in Steps/seconde:");
//       Serial.print ("Vx=");Serial.print (SPEED[1]);Serial.print (" ");
//       Serial.print ("Vy=");Serial.print (SPEED[2]);Serial.print (" ");
//       Serial.print ("Vz=");Serial.print (SPEED[3]);Serial.print (" ");
//       Serial.print ("Vp=");Serial.print (SPEED[4]);Serial.print (" ");
//       Serial.print ("Vt=");Serial.print (SPEED[5]);Serial.println (" ");
//      
//      if(SPEED[0]==0){
//      
//      X_stepper.disableOutputs();
//      Y_stepper.disableOutputs();
//      Z_stepper.disableOutputs();
//      P_stepper.disableOutputs();
//      T_stepper.disableOutputs();
//    //  digitalWrite(P_ENABLE_PIN, HIGH);
//    //  digitalWrite(T_ENABLE_PIN, HIGH);
//      //Serial.print("Motor controllers OFF at ");
//    // Serial.print("C");Serial.print(millis());Serial.println(";");
//      }
//
//      if(SPEED[0]==1){
//      X_stepper.enableOutputs();
//      Y_stepper.enableOutputs();
//      Z_stepper.enableOutputs();
//      P_stepper.enableOutputs();
//      T_stepper.enableOutputs();
//    //  digitalWrite(P_ENABLE_PIN, LOW);
//    //  digitalWrite(T_ENABLE_PIN, LOW);
//      //Serial.print("Motor controllers ON at ");
//     // Serial.print("C");Serial.print(millis());Serial.println(";");
//      }
   
     // Serial.print("C");Serial.print(millis());Serial.println(";");
  
 }

}
 

void fclass3::SERIAL_MONITOR(char (&RXTEXT)[50], int RXN, int MAX_SPEED, int MIN_SPEED, float & V, int & SWITCH){
   
   if (RXN==0){
        
      // match state object
     MatchState ms;
     ms.Target(RXTEXT); 

      char resultST=ms.Match ("(ST)(%-?%+?%d+)(;)",0);
      if (resultST == REGEXP_MATCHED){
        char captureBuf [10];
        V=atoi(ms.GetCapture (captureBuf,1)); 
        
        if (V>MAX_SPEED){V=MAX_SPEED; Serial.print("MAX limit V reached => ");}
        if (V<MIN_SPEED){V=MIN_SPEED; Serial.print("MIN limit V reached => ");}  
              
        Serial.print("Average Speed=");Serial.println(V);
       }

      char resultSWITCH=ms.Match ("(S)(%d)",0);
      if (resultSWITCH == REGEXP_MATCHED){
        char captureBuf [10];
        SWITCH=atoi(ms.GetCapture (captureBuf,1));      
       }     
   }
}

 fclass3 READ_serial = fclass3();
