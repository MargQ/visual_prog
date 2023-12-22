#include "propagation_model.h"
#include "heatmap.h"
#include "mainwindow.h"
#include <iostream>
#include <math.h>

float propagation_model::PL(float f, float d)
{
        return 28 + 22 * log10(d) + 20*log10(f);
 }



