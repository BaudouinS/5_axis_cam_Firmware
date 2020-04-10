#include "Display_SerialComputer.h"
#include <arduino.h>

fclass2::fclass2(){
}


void fclass2::Cartesian(){
  
    extern int Motor_speed_X, Motor_speed_Y, Motor_speed_Z, Motor_speed_P, Motor_speed_T;
    extern float lx;
    extern float ly;
    extern float lz;
    extern float rx;
    extern float ry;     
    extern long int Z_obj;
    extern long int X_Mot_Pos, Y_Mot_Pos, Z_Mot_Pos, P_Mot_Pos, T_Mot_Pos;

    Serial.print("LX=");Serial.print(lx);Serial.print(";");Serial.print("LY=");Serial.print(ly);Serial.print(";");Serial.print("LZ=");Serial.print(lz);Serial.println(";");
    Serial.print("RX=");Serial.print(rx);Serial.print(";");Serial.print("RY=");Serial.print(ry);Serial.println(";");
    
    
 //   Serial.print("a1=");Serial.print(a1);Serial.print(";");Serial.print("a2=");Serial.print(a2);Serial.print(";");Serial.print("a3=");Serial.print(a3);Serial.println(";");
 //  Serial.print("b1");Serial.print(b1);Serial.print(";");Serial.print("b2");Serial.print(b2);Serial.println(";");

    Serial.println("Cart Mode");
    Serial.print("X=");Serial.print(X_Mot_Pos);Serial.print(";");
    Serial.print("Y=");Serial.print(Y_Mot_Pos);Serial.print(";");
    Serial.print("Z=");Serial.print(Z_Mot_Pos);Serial.println(";");
    Serial.print("P=");Serial.print(P_Mot_Pos);Serial.println(";");
    Serial.print("T=");Serial.print(T_Mot_Pos);Serial.println(";");
    Serial.println(" ");
   
    Serial.print("V_x=");Serial.print(Motor_speed_X);Serial.print(";");
    Serial.print("V_y=");Serial.print(Motor_speed_Y);Serial.print(";");
    Serial.print("V_z=");Serial.print(Motor_speed_Z);Serial.println(";");
    Serial.print("V_p=");Serial.print(Motor_speed_P);Serial.println(";");
    Serial.print("V_t=");Serial.print(Motor_speed_T);Serial.println(";");
    Serial.print("Z_obj");Serial.print(Z_obj);Serial.println(";");
    Serial.println(" ");
    
    
    }

    void fclass2::Spherical(){
      
    extern int Motor_speed_X, Motor_speed_Y, Motor_speed_Z, Motor_speed_P, Motor_speed_T;
    extern float lx;
    extern float ly;
    extern float lz;
    extern float rx;
    extern float ry;     
    extern long int Z_obj;
    extern long int X_Mot_Pos, Y_Mot_Pos, Z_Mot_Pos, P_Mot_Pos, T_Mot_Pos;

    Serial.print("LX=");Serial.print(lx);Serial.print(";");Serial.print("LY=");Serial.print(ly);Serial.print(";");Serial.print("LZ=");Serial.print(lz);Serial.println(";");
    Serial.print("RX=");Serial.print(rx);Serial.print(";");Serial.print("RY=");Serial.print(ry);Serial.println(";");
    
    
 //   Serial.print("a1=");Serial.print(a1);Serial.print(";");Serial.print("a2=");Serial.print(a2);Serial.print(";");Serial.print("a3=");Serial.print(a3);Serial.println(";");
 //  Serial.print("b1");Serial.print(b1);Serial.print(";");Serial.print("b2");Serial.print(b2);Serial.println(";");

    Serial.println("Sph Mode");
    Serial.print("X=");Serial.print(X_Mot_Pos);Serial.print(";");
    Serial.print("Y=");Serial.print(Y_Mot_Pos);Serial.print(";");
    Serial.print("Z=");Serial.print(Z_Mot_Pos);Serial.println(";");
    Serial.print("P=");Serial.print(P_Mot_Pos);Serial.println(";");
    Serial.print("T=");Serial.print(T_Mot_Pos);Serial.println(";");
    Serial.println(" ");
   
    Serial.print("V_x=");Serial.print(Motor_speed_X);Serial.print(";");
    Serial.print("V_y=");Serial.print(Motor_speed_Y);Serial.print(";");
    Serial.print("V_z=");Serial.print(Motor_speed_Z);Serial.println(";");
    Serial.print("V_p=");Serial.print(Motor_speed_P);Serial.println(";");
    Serial.print("V_t=");Serial.print(Motor_speed_T);Serial.println(";");
    // Serial.print("Z_obj");Serial.print(Z_obj);Serial.println(";");
    Serial.println(" ");
    
//    Serial.print(" theta=");Serial.print(theta);Serial.print(";");
//    Serial.print(" phi=");Serial.print(phi);Serial.println(";");
//    Serial.print(" X=");Serial.print((double)X_stepper.currentPosition());Serial.print(" Y=");Serial.print((double)Y_stepper.currentPosition());Serial.print(" Z=");Serial.print((double)Z_stepper.currentPosition()/Zfactor);Serial.print(" R=");Serial.println(R);
//    
//    Serial.print("V_Theta=");Serial.print(V_Theta);Serial.print(";");
//    Serial.print("V_Phi=");Serial.print(V_Phi);Serial.print(";");
//    Serial.print("V=sqrt(V_Phi^2+V_Theta^2)=");Serial.print(sqrt(V_Phi*V_Phi+V_Theta*V_Theta));Serial.print("; ");Serial.print("Speed target parameter= ");Serial.println(AVG_SPEED_TARGET);
//    Serial.println(" ");
    
    } 
  

  fclass2 Display_SerialComputer = fclass2(); 
