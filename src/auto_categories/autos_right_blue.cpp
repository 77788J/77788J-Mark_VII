#include "auto_picker.h"
#include "autos.h"

// runs the correct auto function
void runAutoRightBlue(unsigned char variation) {
  switch (variation) {

    case 0: break;
    case 1: autoRunRight20Cone(); break;
    case 2: autoRunRight5Cone(); break;
    case 3: autoRunRightStationary(); break;
    case 4: autoRunRightStationaryFlip(); break;
    case 5: autoRunCone(); break;
    case 6: autoRunBullet(); break;
    case 7: autoRunSkills(); break;

  }
}
