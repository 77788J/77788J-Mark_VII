#include "recorder.h"
#include "chassis.h"
#include "lift.h"
#include "mogo.h"

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
void logChassis(unsigned char chassis) {
  switch (chassis) {

    case (CHASSIS_MODE_POSITION): printf("cp: %f,%f", chassis_left, chassis_right); break;
    case (CHASSIS_MODE_ANGLE): printf("ca: %f", chassis_angle); break;

  }
}

// log the mogo lifter data
void logMogo() {
  printf("mg: %f", pid_mogo.getTarget());
}

// log the lift height
void logLift() {
  printf("lf: %f", pid_lift.getTarget());
}

// log the current state of the bot to the console
// to be converted to code via external program
void logState(unsigned char chassis) {

  // make sure it's printing on new line
  // doesn't really matter, but helpful for readability
  print("\n");

  // log each subsystem
  logChassis(chassis);
  print("|");
  print("\n");

  logLift();
  print("|");
  print("\n");

  logMogo();
  print("|");

  // end log
  print(";\n");

}
