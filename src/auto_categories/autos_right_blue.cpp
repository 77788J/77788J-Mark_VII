#include "auto_picker.h"
#include "autos.h"

// runs the correct auto function
void runAutoRightBlue(unsigned char variation) {
  switch (variation) {

    case 0: break;
    case 1: autoRunRight20Cone(); break;
    case 2: autoRunRight5Cone(); break;
    case 3: autoRunStationary(); break;
    case 4: autoRunRightStationary5(); break;
    case 5: autoRunRightStationaryFlip(); break;
    case 6: autoRunCone(); break;
    case 7: autoRunBullet(); break;

  }
}
