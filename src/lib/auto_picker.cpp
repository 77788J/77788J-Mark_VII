#include "auto_picker.h"
#include "io_control.h"
#include "lcd.h"

// init variables to defaults
unsigned char auto_side = LEFT;
unsigned char auto_color = BLUE;
unsigned char auto_variation = 0;

// array of autonomous variations
#define AUTO_COUNT 7  // 'NONE' is zero, so it's the count of actual variations
const char * autos[] = {
//"                " // 16 characters, size of an LCD line
  "      NONE      ",
  "    20 CONE     ",
  "     5 CONE     ",
  "   STATIONARY   ",
  "STATIONARY FLIP ",
  "      CONE      ",
  "     BULLET     ",
  "     SKILLS     "
};

// stages of auto picker
unsigned char stage = 0;
#define STAGE_INIT 0
#define STAGE_SIDE 1
#define STAGE_COLOR 2
#define STAGE_VARIATION 3

// runs one iteration of the picker
void autoPickerRun() {

  // update the LCD buttons
  lcd.updateButtons();

  // run the right stage
  switch (stage) {

    // inits the LCD with the correct text
    case (STAGE_INIT): {

      // set the text
      lcd.setText(0, "      SIDE      ");
      lcd.setText(1, "LEFT       RIGHT");

      // go to first stage next iteration
      stage++;

    }; break;



    case (STAGE_SIDE): {

      // if either side button is pressed...
      if (lcd.btn_l_new == 1 || lcd.btn_r_new == 1) {

        // update side variable
        if (lcd.btn_l_new == 1) auto_side = LEFT;
        if (lcd.btn_r_new == 1) auto_side = RIGHT;

        // next stage
        lcd.setText(0, "      COLOR     ");
        lcd.setText(1, "BLUE  BACK   RED");
        stage++;

      }
    }; break;



    case (STAGE_COLOR): {

      // if the middle button is pressed, go back a stage
      if (lcd.btn_m_new == 1) {
        lcd.setText(0, "      SIDE      ");
        lcd.setText(1, "LEFT       RIGHT");
        stage--;
      }

      // otherwise, if either side button is pressed...
      else if (lcd.btn_l_new == 1 || lcd.btn_r_new == 1) {

        // update side variable
        if (lcd.btn_l_new == 1) auto_color = BLUE;
        if (lcd.btn_r_new == 1) auto_color = RED;

        // next stage
        lcd.setText(0, autos[auto_variation]);
        lcd.setText(1, "<     BACK     >");
        stage++;

      }
    }; break;



    case (STAGE_VARIATION): {

        // if the middle button is pressed, go back a stage
        if (lcd.btn_m_new == 1) {
          lcd.setText(0, "      COLOR     ");
          lcd.setText(1, "BLUE  BACK   RED");
          stage--;
        }

        // if the left button is pressed
        // and there's still an option to the left,
        // go left one option
        if (lcd.btn_l_new == 1 && auto_variation >= 1) {
          auto_variation--;
          lcd.setText(0, autos[auto_variation]);
        }

        // if the right button is pressed
        // and there's still an option to the right,
        // go right one option
        if (lcd.btn_r_new == 1 && auto_variation < AUTO_COUNT) {
          auto_variation++;
          lcd.setText(0, autos[auto_variation]);
        }

    }; break;
  }
}

void autoPickerStart(void * parameter) {
  while (true) {

    autoPickerRun();
    delay(20);

  }
}
