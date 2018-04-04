#include "auto_picker.h"
#include "autos.h"

// runs the correct auto function
void runAutoLeftBullet(unsigned char variation) {
  switch (variation) {

    case 0: break;
    case 1: autoRunLeft20ConeMogo(); break;
    case 2: autoRunLeft203ConeMogo(); break;
    case 3: autoRunLeft5ConeMogo(); break;
    case 4: autoRunCone(); break;
    case 5: {
      if (auto_cone) autoRunLeftStationary2();
      else autoRunStationary();
    } break;
    case 6: autoRunLeftStationary5(); break;
    case 7: autoRunLeftLandslideMogo(); break;
    case 8: autoRunBullet(); break;

  }
}
