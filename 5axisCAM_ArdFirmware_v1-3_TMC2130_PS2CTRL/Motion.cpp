#include "Arduino.h"
#include "Motion.h"
#include <math.h>

fclass::fclass(){
}

void fclass::Cartesian(int & VX, int & VY, int & VZ, int & VP, int & VT, float V,int r,float LX, float LY, float LZ, float RX,float RY){   
  
  float a1=0.0;
  float a2=0.0;
  float a3=0.0;
  float b1=0.0;
  float b2=0.0;
  const float Zfactor=2.5;//(=40mm/16mm)factor to multiply the z distance and speed values to match the ones on X and Y.
  
    if (abs(LX)<20){LX=0;}
    if (abs(LY)<20){LY=0;}
     
    a2=LX/(abs(LX)+abs(LY)+abs(LZ));
    a1=LY/(abs(LX)+abs(LY)+abs(LZ));
    a3=LZ/(abs(LX)+abs(LY)+abs(LZ));
  
    if (LX==0 && LY==0 && LZ==0){
      a1=0;a2=0;a3=0;
       VX=0;//X
       VY=0;//Y
       VZ=0;//Z 
    }
  
    else {
    
      if (a1>0){VX=-1*sqrt(sq(V)-sq(a2*V)-sq(a3*V));}
      if (a1<0){VX=sqrt(sq(V)-sq(a2*V)-sq(a3*V));}//X
      if (a1==0){VX=0;}
      
      if (a2>0){VY=sqrt(sq(V)-sq(a1*V)-sq(a3*V));}
      if (a2<0){VY=-1*sqrt(sq(V)-sq(a1*V)-sq(a3*V));}//Y
      if (a2==0){VY=0;}
     
      if (a3>0){VZ=sqrt(sq(V)-sq(a1*V)-sq(a2*V))*Zfactor*10;}
      if (a3<0){VZ=-1*sqrt(sq(V)-sq(a1*V)-sq(a2*V))*Zfactor*10;}//Z
      if (a3==0){VZ=0;} 
    
    }
  
   if (abs(RX)<10){RX=0;}
      if (abs(RY)<10){RY=0;}
  
   if (RX==0 & RY==0){b1=0;b2=0;
      VP=0;//P
      VT=0;//T
      }
    
    else{
      b1=RX/(abs(RX)+abs(RY));
      b2=RY/(abs(RX)+abs(RY));
      VP=b1*V*150/r;
      VT=b2*(V/4)*150/r;        
      }

}

void fclass::Spherical(long int X, long int Y, long int Z, int & VX, int & VY, int & VZ, int & VP, int & VT, float V,int r, int R, float LX, float LY, float LZ, float RX, float RY){  

  const float Zfactor=2.5;//(=40mm/16mm)factor to multiply the z distance and speed values to match the ones on X and Y.const float Zfactor=2.5;//(=40mm/16mm)factor to multiply the z distance and speed values to match the ones on X and Y.
  int flipZ;
  float a1=0.0;
  float a2=0.0;
  float a3=0.0;
  float b1=0.0;
  float b2=0.0;
  float theta;
  float phi;
  float V_Phi;
  float V_Theta;
  
  if (Y<0){
      phi= (2*M_PI)+atan2((double)Y,(double)X);
       }///implement modulo 2pi
  //  phi= (2*M_PI)+atan2((double)Y_stepper.currentPosition(),(double)X_stepper.currentPosition()); }///implement modulo 2pi
  else {
      phi= atan2((double)Y,(double)X);
    //phi= atan2((double)Y_stepper.currentPosition(),(double)X_stepper.currentPosition());
       }
  
    theta=acos((double)Z/(abs(R)*Zfactor));// implement modulo pi
  //  theta=acos((double)Z_stepper.currentPosition()/(abs(R)*Zfactor));// implement modulo pi
  
  ////to remove effect of 0 offset du to small noise/bias on the arduino pin. Also allow to easily reach a mono axis regime(V_theta or V_phi=0)
  if (abs(LX)<20){LX=0;}
  if (abs(LY)<20){LY=0;}
  
  a1=LX/(abs(LX)+abs(LY));
  a2=LY/(abs(LX)+abs(LY));
  
  if (LX==0 && LY==0){a1=0;a2=0;};
  
  /////////Math to move on a sphere of radius R at a speed AVG_SPEED_TARGET
  
  if (LX>0 && LY>0){
   V_Phi=V/sqrt(1+sq( (1-a1) /a1 ));
   V_Theta=V/sqrt(1+sq( (1-a2) / a2 ));}
  
  if (LX<0 && LY>0){
   V_Phi=-V/sqrt(1+sq( (1+a1) /a1 ));
   V_Theta=V/sqrt(1+sq( (1-a2) / a2 ));}
  
  if (LX>0 && LY<0){
   V_Phi=V/sqrt(1+sq((1-a1) /a1 ) );
   V_Theta=-V/sqrt(1+sq((1+a2) / a2 ) );}
  
  if (LX<0 && LY<0){
   V_Phi=-V/sqrt(1+sq( (1+a1) /a1 ));
   V_Theta=-V/sqrt(1+sq( (1+a2) / a2 ));
   }
   
  if (LX==0 && LY==0){V_Phi=0;                                          V_Theta=0;}
  if (LX==0 && LY>0){V_Phi=0;                                           V_Theta=V/sqrt(1+sq( (1-a2) / a2 ));}
  if (LX>0 && LY==0){V_Phi=V/sqrt(1+sq( (1-a1) /a1 ));   V_Theta=0;}
  if (LX==0 && LY<0){V_Phi=0;                                           V_Theta=-V/sqrt(1-sq((1+a2) / a2 ) );}
  if (LX<0 && LY==0){V_Phi=-V/sqrt(1+sq( (1+a1) /a1 ));  V_Theta=0;}
  
  
  //
  //Serial.print("; Y=");Serial.println(Y_stepper.currentPosition());
  
  VX=(V_Theta*cos(theta)*cos(phi) - V_Phi*sin(phi));//X
  VY=(V_Theta*cos(theta)*sin(phi) + V_Phi*cos(phi));//Y
  
  //SPEED[3]=-V_Theta*sin(theta)*2.5;//Z
  
  if (theta==0){
    VZ=-1*VZ;//last non zero value of speed(3)
    phi=phi+M_PI;
    VX=(V_Theta/Zfactor)*cos(theta)*cos(phi) - V_Phi*sin(phi);//X
    VY=(V_Theta/Zfactor)*cos(theta)*sin(phi) + V_Phi*cos(phi);//Y
    
    if (VZ>0) {flipZ=1;Serial.print("flipZ= ");Serial.print(flipZ);Serial.println(";");
     }
    else if (VZ<0) {flipZ=0;Serial.print("flipZ= ");Serial.print(flipZ);Serial.println(";");
     }
     }//Z
    else if (flipZ==1){VZ=-V_Theta*sin(theta)*2.5;}//Z}
    else if (flipZ==0){VZ=V_Theta*sin(theta)*2.5;}//Z}
  //   
  
  //Camera pointing to the object at the center of the sphere
  VP=V_Phi/(abs(R)*sin(theta));
  VT=V_Theta/(abs(R));


}

fclass Motion = fclass();
