#include "auto_picker.h"
#include "autos.h"

// runs the correct auto function
void runAutoLeftBlue(unsigned char variation) {
  switch (variation) {

    case 0: break;
    case 1: autoRunLeft20Cone(); break;
    case 2: autoRunLeft5Cone(); break;
    case 3: autoRunStationary(); break;
    case 4: autoRunLeftStationary5(); break;
    case 5: autoRunLeftStationaryFlip(); break;
    case 6: autoRunCone(); break;
    case 7: autoRunBullet(); break;

  }
}
