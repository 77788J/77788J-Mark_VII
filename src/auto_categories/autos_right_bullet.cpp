#include "auto_picker.h"
#include "autos.h"

// runs the correct auto function
void runAutoRightBullet(unsigned char variation) {
  switch (variation) {

    case 0: break;
    case 1: autoRunRight20ConeMogo(); break;
    case 2: autoRunRight5ConeMogo(); break;
    case 3: autoRunCone(); break;
    case 4: autoRunBullet(); break;
    case 5: autoRunRightStationary5(); break;
    case 6: autoRunRightLandslideMogo(); break;
    case 7: autoRunBullet(); break;

  }
}
