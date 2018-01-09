#include "recorder.h"
#include "chassis.h"
#include "lift.h"
#include "mogo.h"
#include "claw.h"

/*

ENCODING FORMAT:
ca: b, c, d|
e: f;

a and e = subsystem and mode
b, c, d and f = values (generally PID targets), continues indefititely

SUBSYSTEM MODES:
cp: chassis position
ca: chassis angle/orientation
mg: mogo
lf: lift height

METACHARACTERS:
':' = delimeter between subsytem and value(s)
',' = delimeter between different values
'|' = delimeter between different groups of subsytem/values
';' = delimeter between 'lines'

all whitespace is ignored

*/

// log chassis data
float prev_pos_l = 0;
float prev_pos_r = 0;
float prev_angle = 0;
void logChassis(unsigned char chassis) {
  switch (chassis) {
    case (CHASSIS_MODE_POSITION): printf("cp: %f,%f", (chassis_left - prev_pos_l) / CHASSIS_SCALE_DISTANCE, (chassis_right - prev_pos_r) / CHASSIS_SCALE_DISTANCE); break;
    case (CHASSIS_MODE_ANGLE): printf("ca: %f", chassis_angle - prev_angle); break;
  }

  prev_pos_l = chassis_left;
  prev_pos_r = chassis_right;
  prev_angle = chassis_angle;
}

// log the mogo lifter data
void logMogo() {
  printf("mg: %f", pid_mogo.getTarget());
}

// log the lift height
void logLift() {
  printf("lf: %f", pid_lift.getTarget());
}

// log the claw angle
void logClaw() {
  printf("cl: %f", pid_claw.getTarget());
}

// log the current state of the bot to the console
// to be converted to code via external program
void logState(unsigned char chassis) {

  // make sure it's printing on new line
  // doesn't really matter, but helpful for readability
  print("\n");

  // log chassis
  logChassis(chassis);
  print("|\n");

  // log lift
  logLift();
  print("|\n");

  // log mogo lifter
  logMogo();
  print("|\n");

  // log the claw
  logClaw();

  // end log
  print(";\n");

}
