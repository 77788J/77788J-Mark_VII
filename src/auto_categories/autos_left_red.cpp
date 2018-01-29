#include "auto_picker.h"
#include "autos.h"

// runs the correct auto function
void runAutoLeftRed(unsigned char variation) {
  switch (variation) {

    case 0: break;
    case 1: autoRunLeft20Cone(); break;
    case 2: autoRunLeft5Cone(); break;
    case 3: autoRunLeftStationary(); break;
    case 4: autoRunLeftStationaryFlip(); break;
    case 5: autoRunCone(); break;
    case 6: autoRunBullet(); break;
    case 7: autoRunSkills(); break;

  }
}
