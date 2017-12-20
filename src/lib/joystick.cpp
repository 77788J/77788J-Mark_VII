#include "joystick.h"

// default initializer
Joystick :: Joystick() {}

// "factory" that inits a Joystick
void Joystick :: init(int joystick_) {
  joystick = joystick_;
}

// updates the joystick variables
void Joystick :: update() {

  // save raw joystick button data
  bool raw_5U = joystickGetDigital(joystick, 5, JOY_UP);
  bool raw_5D = joystickGetDigital(joystick, 5, JOY_DOWN);
  bool raw_6U = joystickGetDigital(joystick, 6, JOY_UP);
  bool raw_6D = joystickGetDigital(joystick, 6, JOY_DOWN);
  bool raw_7U = joystickGetDigital(joystick, 7, JOY_UP);
  bool raw_7D = joystickGetDigital(joystick, 7, JOY_DOWN);
  bool raw_7L = joystickGetDigital(joystick, 7, JOY_LEFT);
  bool raw_7R = joystickGetDigital(joystick, 7, JOY_RIGHT);
  bool raw_8U = joystickGetDigital(joystick, 8, JOY_UP);
  bool raw_8D = joystickGetDigital(joystick, 8, JOY_DOWN);
  bool raw_8L = joystickGetDigital(joystick, 8, JOY_LEFT);
  bool raw_8R = joystickGetDigital(joystick, 8, JOY_RIGHT);

  // determine new button presses
  btn5U_new = (raw_5U && !btn5U) - (!raw_5U && btn5U);
  btn5D_new = (raw_5D && !btn5D) - (!raw_5D && btn5D);
  btn6U_new = (raw_6U && !btn6U) - (!raw_6U && btn6U);
  btn6D_new = (raw_6D && !btn6D) - (!raw_6D && btn6D);
  btn7U_new = (raw_7U && !btn7U) - (!raw_7U && btn7U);
  btn7D_new = (raw_7D && !btn7D) - (!raw_7D && btn7D);
  btn7L_new = (raw_7L && !btn7L) - (!raw_7L && btn7L);
  btn7R_new = (raw_7R && !btn7R) - (!raw_7R && btn7R);
  btn8U_new = (raw_8U && !btn8U) - (!raw_8U && btn8U);
  btn8D_new = (raw_8D && !btn8D) - (!raw_8D && btn8D);
  btn8L_new = (raw_8L && !btn8L) - (!raw_8L && btn8L);
  btn8R_new = (raw_8R && !btn8R) - (!raw_8R && btn8R);

  // update public raw button presses
  btn5U = raw_5U;
  btn5D = raw_5D;
  btn6U = raw_6U;
  btn6D = raw_6D;
  btn7U = raw_7U;
  btn7D = raw_7D;
  btn7L = raw_7L;
  btn7R = raw_7R;
  btn8U = raw_8U;
  btn8D = raw_8D;
  btn8L = raw_8L;
  btn8R = raw_8R;

  // update analog sticks
  analogRH = joystickGetAnalog(joystick, 1);
  analogRV = joystickGetAnalog(joystick, 2);
  analogLV = joystickGetAnalog(joystick, 3);
  analogLH = joystickGetAnalog(joystick, 4);

}
