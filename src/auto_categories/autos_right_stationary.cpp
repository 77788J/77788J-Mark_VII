#include "auto_picker.h"
#include "autos.h"

// runs the correct auto function
void runAutoRightStationary(unsigned char variation) {
  switch (variation) {

    case 0: break;
    case 1: autoRunRight20ConeStationary(); break;
    case 2: autoRunRight5ConeStationary(); break;
    case 3: autoRunCone(); break;
    case 4: autoRunStationary(); break;
    case 5: autoRunRightStationary5(); break;
    case 6: autoRunRightLandslideStationary(); break;
    case 7: autoRunRightBulletStationary(); break;

  }
}
