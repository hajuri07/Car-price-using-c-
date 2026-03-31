#pragma once
#include "LinearRegression.h"
#include "Dataset.h"

class Predictor
{
private:
    LinearRegression model;
    Dataset dataset;

public:
    Predictor(double lr = 0.01, int epochs = 1000);
    void run(const string &csvFile);
    void predictSingle();
};