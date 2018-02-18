#include "auto_picker.h"
#include "autos.h"

// runs the correct auto function
void runAutoLeftBullet(unsigned char variation) {
  switch (variation) {

    case 0: break;
    case 1: autoRunLeft20ConeMogo(); break;
    case 2: autoRunLeft5ConeMogo(); break;
    case 3: autoRunCone(); break;
    case 4: autoRunBullet(); break;
    case 5: autoRunLeftStationary5(); break;
    case 6: autoRunLeftLandslideMogo(); break;
    case 7: autoRunBullet(); break;

  }
}
