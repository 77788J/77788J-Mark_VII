#include "auto_picker.h"
#include "autos.h"

// runs the correct auto function
void runAutoLeftMogo(unsigned char variation) {
  switch (variation) {

    case 0: break;
    case 1: autoRunLeft20ConeMogo(); break;
    case 2: autoRunLeft203ConeMogo(); break;
    case 3: autoRunLeft5ConeMogo(); break;
    case 4: autoRunCone(); break;
    case 5: autoRunStationary(); break;
    case 6: autoRunLeftStationary5(); break;
    case 7: autoRunLeftLandslideMogo(); break;
    case 8: autoRunLeftBulletMogo(); break;

  }
}
