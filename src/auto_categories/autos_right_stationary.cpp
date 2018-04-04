#include "auto_picker.h"
#include "autos.h"

// runs the correct auto function
void runAutoRightStationary(unsigned char variation) {
  switch (variation) {

    case 0: break;
    case 1: autoRunRight20ConeStationary(); break;
    case 2: autoRunRight203ConeMogo(); break;
    case 3: autoRunRight5ConeStationary(); break;
    case 4: autoRunCone(); break;
    case 5: autoRunStationary(); break;
    case 6: autoRunRightStationary5(); break;
    case 7: autoRunRightLandslideStationary(); break;
    case 8: autoRunRightBulletStationary(); break;

  }
}
