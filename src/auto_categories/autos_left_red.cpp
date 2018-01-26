#include "auto_picker.h"
#include "autos.h"

// runs the correct auto function
void runAutoLeftRed(unsigned char variation) {
  switch (variation) {

    case 0: break;
    case 1: autoRunLeftRed20Cone(); break;
    case 2: autoRunLeftStationary(); break;
    case 3: autoRunLeftStationaryFlip(); break;
    case 4: autoRunCone(); break;
    case 5: autoRunBullet(); break;
    case 6: autoRunSkills(); break;

  }
}
