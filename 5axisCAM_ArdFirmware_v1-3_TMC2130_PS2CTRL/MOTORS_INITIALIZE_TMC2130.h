/*
  MOTORS_INITIALIZE_TMC2130 - Initialize all pins and parametere of TMC2130
  Created by B Saintyves, April 4, 2020.
*/

#ifndef MOTORS_INITIALIZE_TMC2130_h
#define MOTORS_INITIALIZE_TMC2130_h


#include <arduino.h>

///////////////PINS SETUP////////////////////////
pinMode(SWITCH_ON, INPUT_PULLUP);

///TO UNCOMMENT IF YOU USE SWITCH!!!!
//////// Prepare stop switch pins
//  pinMode(X_MIN_PIN , INPUT);
//  pinMode(X_MAX_PIN , INPUT);
//  pinMode(Y_MIN_PIN , INPUT);
//  pinMode(Y_MAX_PIN , INPUT);
//  pinMode(Z_MIN_PIN , INPUT);
//  pinMode(Z_MAX_PIN , INPUT);
////////////////////////////////

////// Prepare pins steppers
  pinMode(X_ENABLE_PIN, OUTPUT);
  pinMode(X_STEP_PIN, OUTPUT);
  pinMode(X_CS_PIN, OUTPUT);

  pinMode(Y_ENABLE_PIN, OUTPUT);
  pinMode(Y_STEP_PIN, OUTPUT);
  pinMode(Y_CS_PIN, OUTPUT);

  pinMode(Z_ENABLE_PIN, OUTPUT);
  pinMode(Z_STEP_PIN, OUTPUT);
  pinMode(Z_CS_PIN, OUTPUT);

  pinMode(P_ENABLE_PIN, OUTPUT);
  pinMode(P_STEP_PIN, OUTPUT);
  pinMode(P_CS_PIN, OUTPUT);

  pinMode(T_ENABLE_PIN, OUTPUT);
  pinMode(T_STEP_PIN, OUTPUT);
  pinMode(T_CS_PIN, OUTPUT);
//////////////////////////////

////// Prepare pins fan
  pinMode(FAN_1_PIN, OUTPUT);
  pinMode(FAN_2_PIN, OUTPUT);
//////////////////////////////////

//////////////////////////
//////////////////////////

///////Motors initial parameters

  ////driver control
      digitalWrite(X_CS_PIN, HIGH);
      X_driver.begin();             // Initiate pins and registeries
      X_driver.rms_current(800);    // Set stepper current to 600mA. The command is the same as command TMC2130.setCurrent(600, 0.11, 0.5);
      X_driver.en_pwm_mode(1);      // Enable extremely quiet stepping
      X_driver.pwm_autoscale(1);
      X_driver.microsteps(X_MicroS);

      digitalWrite(Y_CS_PIN, HIGH);
      Y_driver.begin();             // Initiate pins and registeries
      Y_driver.rms_current(800);    // Set stepper current to 600mA. The command is the same as command TMC2130.setCurrent(600, 0.11, 0.5);
      Y_driver.en_pwm_mode(1);      // Enable extremely quiet stepping
      Y_driver.pwm_autoscale(1);
      Y_driver.microsteps(Y_MicroS);

      digitalWrite(Z_CS_PIN, HIGH);
      Z_driver.begin();             // Initiate pins and registeries
      Z_driver.rms_current(800);    // Set stepper current to 600mA. The command is the same as command TMC2130.setCurrent(600, 0.11, 0.5);
      Z_driver.en_pwm_mode(1);      // Enable extremely quiet stepping
      Z_driver.pwm_autoscale(1);
      Z_driver.microsteps(Z_MicroS);

      digitalWrite(P_CS_PIN, HIGH);
      P_driver.begin();             // Initiate pins and registeries
      P_driver.rms_current(600);    // Set stepper current to 600mA. The command is the same as command TMC2130.setCurrent(600, 0.11, 0.5);
      P_driver.en_pwm_mode(1);      // Enable extremely quiet stepping
      P_driver.pwm_autoscale(1);
      P_driver.microsteps(P_MicroS);

      digitalWrite(T_CS_PIN, HIGH);
      T_driver.begin();             // Initiate pins and registeries
      T_driver.rms_current(600);    // Set stepper current to 600mA. The command is the same as command TMC2130.setCurrent(600, 0.11, 0.5);
      T_driver.en_pwm_mode(1);      // Enable extremely quiet stepping
      T_driver.pwm_autoscale(1);
      T_driver.microsteps(T_MicroS);
  //////////

    X_stepper.setMaxSpeed(4000);
    X_stepper.setEnablePin(X_ENABLE_PIN);
    X_stepper.setPinsInverted(false, false, true);

    Y_stepper.setMaxSpeed(4000);
    Y_stepper.setEnablePin(Y_ENABLE_PIN);
    Y_stepper.setPinsInverted(false, false, true);

    Z_stepper.setMaxSpeed(6000);
    Z_stepper.setEnablePin(Z_ENABLE_PIN);
    Z_stepper.setPinsInverted(false, false, true);

    P_stepper.setMaxSpeed(4000);
    P_stepper.setEnablePin(P_ENABLE_PIN);
    P_stepper.setPinsInverted(false, false, true);

    T_stepper.setMaxSpeed(4000);
    T_stepper.setEnablePin(T_ENABLE_PIN);
    T_stepper.setPinsInverted(false, false, true);


     //motor controllers are initially OFF when program is loaded. They have to be turned ON by sending "1;" in Serial com
     X_stepper.disableOutputs();
     Y_stepper.disableOutputs();
     Z_stepper.disableOutputs();
     P_stepper.disableOutputs();
     T_stepper.disableOutputs();    


#endif
