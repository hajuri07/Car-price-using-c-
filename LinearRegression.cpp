#include "LinearRegression.h"
#include <iostream>
#include <cmath>
#include <numeric>

LinearRegression::LinearRegression(double lr, int epochs)
    : learningrate(lr), epochs(epochs), bias(0.0) {}

double LinearRegression::computeloss(const vector<vector<double>> &X,
                                     const vector<double> &y) const
{
    double loss = 0.0;
    for (int i = 0; i < (int)X.size(); i++)
    {
        double pred = predict(X[i]);
        loss += pow(pred - y[i], 2);
    }
    return loss / X.size(); // Mean Squared Error
}

void LinearRegression::train(const vector<vector<double>> &X,
                             const vector<double> &y)
{
    int n = X.size();
    int m = X[0].size();

    // Initialize weights to 0
    weights.assign(m, 0.0);
    bias = 0.0;

    // Gradient Descent
    for (int epoch = 0; epoch < epochs; epoch++)
    {
        vector<double> dW(m, 0.0);
        double dB = 0.0;

        // Compute gradients
        for (int i = 0; i < n; i++)
        {
            double error = predict(X[i]) - y[i];
            for (int j = 0; j < m; j++)
                dW[j] += error * X[i][j];
            dB += error;
        }

        // Update weights
        for (int j = 0; j < m; j++)
            weights[j] -= learningrate * dW[j] / n;
        bias -= learningrate * dB / n;

        // Print loss every 100 epochs
        if (epoch % 100 == 0)
        {
            cout << "Epoch " << epoch
                 << " | MSE Loss: " << computeloss(X, y) << "\n";
        }
    }
    cout << "Hogaya bhai kaam\n";
}

double LinearRegression::predict(const vector<double> &features) const
{
    double result = bias;
    for (int j = 0; j < (int)weights.size(); j++)
        result += weights[j] * features[j];
    return result;
}

void LinearRegression::evaluate(const vector<vector<double>> &X,
                                const vector<double> &y)
{
    double mse = computeloss(X, y);
    double mae = 0.0, ssRes = 0.0, ssTot = 0.0;
    double yMean = 0.0;

    for (double val : y)
        yMean += val;
    yMean /= y.size();

    for (int i = 0; i < (int)X.size(); i++)
    {
        double pred = predict(X[i]);
        mae += abs(pred - y[i]);
        ssRes += pow(pred - y[i], 2);
        ssTot += pow(y[i] - yMean, 2);
    }

    cout << "\nAbb dekhte hai kesa chala hai apna kaam\n";
    cout << "MSE  : " << mse << "\n";
    cout << "MAE  : " << mae / X.size() << "\n";
    cout << "R²   : " << 1 - (ssRes / ssTot) << "\n";
}