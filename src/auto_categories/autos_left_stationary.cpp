#include "auto_picker.h"
#include "autos.h"

// runs the correct auto function
void runAutoLeftStationary(unsigned char variation) {
  switch (variation) {

    case 0: break;
    case 1: autoRunLeft20ConeStationary(); break;
    case 2: autoRunLeft5ConeStationary(); break;
    case 3: autoRunCone(); break;
    case 4: autoRunStationary(); break;
    case 5: autoRunLeftStationary5(); break;
    case 6: autoRunLeftLandslideStationary(); break;
    case 7: autoRunLeftBulletStationary(); break;

  }
}
