#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include <main.h>

class Joystick {

public:

  // raw joystick button values
  bool btn5U;
  bool btn5D;
  bool btn6U;
  bool btn6D;
  bool btn7U;
  bool btn7D;
  bool btn7L;
  bool btn7R;
  bool btn8U;
  bool btn8D;
  bool btn8L;
  bool btn8R;

  // registers NEW button pressed
  bool btn5U_new;
  bool btn5D_new;
  bool btn6U_new;
  bool btn6D_new;
  bool btn7U_new;
  bool btn7D_new;
  bool btn7L_new;
  bool btn7R_new;
  bool btn8U_new;
  bool btn8D_new;
  bool btn8L_new;
  bool btn8R_new;

  // analog stick values (left/right, horizontal/vertical)
  int analogRH;
  int analogRV;
  int analogLV;
  int analogLH;

  // default initializer
  // MAKE SURE TO FULLY INITIALIZE WITH <Joystick>.init()
  Joystick();

  // actually initializes the joystick
  void init(int joystick_);

  // updates the button readings
  void update();

private:

  // whether this refers to a primary or partner joystick
  int joystick;

};

#endif
