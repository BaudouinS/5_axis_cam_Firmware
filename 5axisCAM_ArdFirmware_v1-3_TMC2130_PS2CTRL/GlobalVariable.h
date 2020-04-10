/*
  GlobalVaiable - 
  Created by B Saintyves, April 4, 2020.
*/

#ifndef GlobalVariable_h
#define GlobalVariable_h

////////////DISPLAY VARIABLES///////////////
//Display variable, timer for serial monitor 
unsigned long previousMillis1 = 0; // store previous millis readout (for SInterval)
unsigned long previousMillis2 = 0; // store previous millis readout (for PosInterval)
///char variables for LCD display
//char XVAL[5];
//char YVAL[5];
//char ZVAL[5];

////int variables for LCD display
//int XVAL;
//int YVAL;
//int ZVAL;
////////////////////////


////////////PARSING VARIABLES///////////////
//Parsing variables from serial monitor
char rxChar_computer;//char variable for serial commands
char rxText_computer[50];
int rxN_computer=0; // Number of chars received
//
//Parsing variables from PS2 gamepad
char rxChar_PS2;//char variable for serial commands
char rxText_PS2[50];
int rxN_PS2=0; // Number of chars received
////////////////////////


//////////CONTROL VARIABLES////////////
///PS2 control variable
float lx=0.0;
float ly=0.0;
float lz=0.0;
float rx=0.0;
float ry=0.0;
int St=0;
int R1;
int R2;
int R3=0;
int L3;
/////////////////


//// Motor Parameter Variables//////////
///////////////////////
int X_MicroS=64;//microsteps division
int Y_MicroS=64;//microsteps division
int Z_MicroS=64;//microsteps division
int P_MicroS=64;//microsteps division
int T_MicroS=32;//microsteps division

long int X_round=200*X_MicroS;
long int Y_round=200*Y_MicroS;
long int Z_round=200*Z_MicroS;
long int P_round=200*P_MicroS;
long int T_round=200*T_MicroS;

constexpr int steps_per_round = 200*16;
constexpr uint32_t steps_per_mm = 800;//X,Y

long int X_Mot_Pos;
long int Y_Mot_Pos;
long int Z_Mot_Pos;
long int P_Mot_Pos;
long int T_Mot_Pos;
///////////////////////


//// Motor speed variables and parameters
///////////////////////
//int SPEED[6];//Axis speed vector (steps per second)
//int Motor_speed[6];//Axis speed vector (steps per second)
int Motor_speed_X, Motor_speed_Y, Motor_speed_Z, Motor_speed_P, Motor_speed_T;
int Motor_SWITCH=0;

int MAX_AVG_SPEED=1000; //max speed for AVG_SPEED_TARGET. is bounded by the Z axis as it has to turn more for same distance.
                        //If this max is not realisitic, motors won t reach their target and all motion will be wrong
int MIN_AVG_SPEED=70;
float AVG_SPEED_TARGET; //command line 1;ST1000; for tunring on the motor and fix the average speed at 1000 step/s
float V=0.0;
///////////////////////


///   Math variable/////
///////////////////////
long int R=5000;//radius of the displacement sphere in step. to do: Write an initialisation procedure to set the initial value of R
long int Z_obj=150; //*10^-1 cm distance between lens and filmed object
long int R_MAX=20000;
long int Z_obj_MAX=250;

/////Stop Switchs/////
/////////////////////////
//int X_switch0;
//int X_switch1;
//
//int Y_switch0;
//int Y_switch1;
//
//int Z_switch0;
//int Z_switch1;
//
//int Switch_State=0;
//int Previous_Switch_State=1;
///////


#endif
