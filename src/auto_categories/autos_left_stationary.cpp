#include "auto_picker.h"
#include "autos.h"

// runs the correct auto function
void runAutoLeftStationary(unsigned char variation) {
  switch (variation) {

    case 0: break;
    case 1: autoRunLeft20ConeStationary(); break;
    case 2: autoRunLeft203ConeMogo(); break;
    case 3: autoRunLeft5ConeStationary(); break;
    case 4: autoRunCone(); break;
    case 5: autoRunStationary(); break;
    case 6: autoRunLeftStationary5(); break;
    case 7: autoRunLeftLandslideStationary(); break;
    case 8: autoRunLeftBulletStationary(); break;

  }
}
