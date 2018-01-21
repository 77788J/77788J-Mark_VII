#include "auto_picker.h"
#include "autos.h"

// runs the correct auto function
void runAutoRightRed(unsigned char variation) {
  switch (variation) {

    case 0: break;
    case 1: autoRunRightRed20Cone(); break;
    case 2: autoRunRightRedStationary(); break;
    case 3: autoRunCone(); break;
    case 4: autoRunBullet(); break;
    case 5: autoRunSkills(); break;

  }
}
