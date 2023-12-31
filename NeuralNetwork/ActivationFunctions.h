#pragma once
#include <math.h>

namespace ActivationFunctions
{
    double sigmoid(double x) {
        return 1 / (1 + exp(-x));
    }
}