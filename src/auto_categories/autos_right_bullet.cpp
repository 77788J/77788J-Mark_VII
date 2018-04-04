#include "auto_picker.h"
#include "autos.h"

// runs the correct auto function
void runAutoRightBullet(unsigned char variation) {
  switch (variation) {

    case 0: break;
    case 1: autoRunRight20ConeMogo(); break;
    case 2: autoRunRight203ConeMogo(); break;
    case 3: autoRunRight5ConeMogo(); break;
    case 4: autoRunCone(); break;
    case 5: {
      if (auto_cone) autoRunRightStationary2();
      else autoRunStationary();
    } break;
    case 6: autoRunRightStationary5(); break;
    case 7: autoRunRightLandslideMogo(); break;
    case 8: autoRunBullet(); break;

  }
}
