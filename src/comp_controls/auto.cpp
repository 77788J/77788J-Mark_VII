#include "main.h"
#include "controller.h"
#include "auto_picker.h"
#include "autos.h"

// declare timeout varaibles
unsigned int timeout;
unsigned int max_timeout;

void autonomous() {

  // start background tasks
  startTimer();
  startController();

  // reset timeout
  timeout = 0;
  max_timeout = 0;

  // pick the side/color combo to run
  switch (auto_side) {

    case (LEFT): {
      switch (auto_color) {
        case (BLUE): runAutoLeftBlue(auto_variation);
        case (RED): runAutoLeftRed(auto_variation);
      }
    }; break;

    case (RIGHT): {
      switch (auto_color) {
        case (BLUE): runAutoRightBlue(auto_variation);
        case (RED): runAutoRightRed(auto_variation);
      }
    }; break;

  }
}
