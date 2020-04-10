/*
  MOTORS_DEFINE_TMC2130 - Setup 5 axis Motors, setup accelstepper functions
  Created by B Saintyves, April 4, 2020.
*/
#ifndef MOTORS_DEFINE_TMC2130_h
#define MOTORS_DEFINE_TMC2130_h


#include <AccelStepper.h> //to run several stepper at a time
#include <TMCStepper.h>                       // Include library for TMC steppers
//#include "MOTORS_INITIALIZE_TMC2130.h"

TMC2130Stepper X_driver = TMC2130Stepper(X_CS_PIN, R_SENSE);
TMC2130Stepper Y_driver = TMC2130Stepper(Y_CS_PIN, R_SENSE);
TMC2130Stepper Z_driver = TMC2130Stepper(Z_CS_PIN, R_SENSE);
TMC2130Stepper P_driver = TMC2130Stepper(P_CS_PIN, R_SENSE);
TMC2130Stepper T_driver = TMC2130Stepper(T_CS_PIN, R_SENSE);

                                                  
AccelStepper X_stepper = AccelStepper(X_stepper.DRIVER, X_STEP_PIN, X_DIR_PIN);
AccelStepper Y_stepper = AccelStepper(Y_stepper.DRIVER, Y_STEP_PIN, Y_DIR_PIN);
AccelStepper Z_stepper = AccelStepper(Z_stepper.DRIVER, Z_STEP_PIN, Z_DIR_PIN);
AccelStepper P_stepper = AccelStepper(P_stepper.DRIVER, P_STEP_PIN, P_DIR_PIN);
AccelStepper T_stepper = AccelStepper(T_stepper.DRIVER, T_STEP_PIN, T_DIR_PIN);

#endif
