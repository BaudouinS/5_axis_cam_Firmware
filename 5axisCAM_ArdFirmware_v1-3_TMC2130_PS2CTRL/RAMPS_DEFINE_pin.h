/*
  RAMPS_DEFINE_pin - RAMPS PINOUTS for 5 axis camera system
  Created by B Saintyves, April 4, 2020.
*/

#ifndef RAMPS_DEFINE_pin_h
#define RAMPS_DEFINE_pin_h

#define SWITCH_ON          11

// Steppers ON RAMP ( pinout from from Marlin 1.1 Firmware, pin_RAMPS.h)
//
#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38
#define X_CS_PIN           53

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56
#define Y_CS_PIN           49

#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       62
#define Z_CS_PIN           40

#define P_STEP_PIN        26
#define P_DIR_PIN         28
#define P_ENABLE_PIN      24
#define P_CS_PIN          42

#define T_STEP_PIN        36
#define T_DIR_PIN         34
#define T_ENABLE_PIN      30
#define T_CS_PIN          44

#define R_SENSE    0.1 // Match to your driver
///////////////////////////////////////////

//
// Limit Switches
//
#define X_MIN_PIN           3
#define X_MAX_PIN           2
#define Y_MIN_PIN          14
#define Y_MAX_PIN          15
//#define Z_MIN_PIN          18 //PIN 18(TX1) 19(RX1) used for serial com to the LCD screen
//#define Z_MAX_PIN          19
///////////////////////////////////////////

////Fans
#define FAN_1_PIN          8 //PIN D8 on RAMPS 1.6. This pin is connected to a MOSFET.
#define FAN_2_PIN          9 //PIN D9 on RAMPS 1.6. This pin is connected to a MOSFET.
//////////////////////

#endif
