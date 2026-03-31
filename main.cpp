#include "Predictor.h"

int main()
{
    Predictor predictor(0.01, 1000);
    predictor.run("cars.csv");
    return 0;
}