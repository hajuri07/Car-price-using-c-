#pragma once
#include "MLmodel.h"
#include <iostream>

class LinearRegression : public MLModel
{
private:
    vector<double> weights;
    double bias;
    double learningrate;
    int epochs;
    double computeloss(const vector<vector<double>> &x, const vector<double> &y) const;

public:
    LinearRegression(double lr = 0.01, int epochs = 1000);
    void train(const vector<vector<double>> &X,
               const vector<double> &y) override;

    double predict(const vector<double> &features) const override;

    void evaluate(const vector<vector<double>> &X,
                  const vector<double> &y) override;
};
