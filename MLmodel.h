#pragma once
#include <vector>
using namespace std;

class MLModel
{
public:
    virtual void train(const vector<vector<double>> &x,
                       const vector<double> &y) = 0;

    virtual double predict(const vector<double> &features) const = 0;

    virtual void evaluate(const vector<vector<double>> &X,
                          const vector<double> &y) = 0;
};