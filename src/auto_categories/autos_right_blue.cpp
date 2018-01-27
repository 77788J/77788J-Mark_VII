#include "auto_picker.h"
#include "autos.h"

// runs the correct auto function
void runAutoRightBlue(unsigned char variation) {
  switch (variation) {

    case 0: break;
    case 1: autoRunRight20Cone(); break;
    case 2: autoRunRightStationary(); break;
    case 3: autoRunRightStationaryFlip(); break;
    case 4: autoRunCone(); break;
    case 5: autoRunBullet(); break;
    case 6: autoRunSkills(); break;

  }
}
