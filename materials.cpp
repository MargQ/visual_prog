#include "materials.h"
#include "heatmap.h"

float materials::delay(float f, int n) { //n-номер места в массиве за определённый материал
    if (n == 3) {
        return 23+0.3*f;
    }
    if (n == 2) {
        return 2+0.2*f;
    }
    if (n == 0) {
        return 5+4*f;
    }
    if (n == 1) {
        return 4.85+0.12*f;
    }
    else {
        return 0;
    }
}
