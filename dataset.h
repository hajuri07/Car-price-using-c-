#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class Dataset
{
private:
    vector<vector<double>> features;
    vector<double> labels;
    vector<double> featureMeans;
    vector<double> featureSTD;
    double labelMean = 0.0;
    double labelStd = 0.0;

public:
    bool loadfromCSV(const string &filename);
    void normalize();
    void traintestsplit(Dataset &train, Dataset &test, double ratio = 0.8);

    const vector<vector<double>> getfeatures() const { return features; }
    const vector<double> &getlabels() const { return labels; }
    double getLabelMean() const
    {
        return labelMean;
    }
    double getLabelStd() const
    {
        return labelStd;
    }
    int size() const
    {
        return labels.size();
    }

    inline double encodeFuel(const string &f)
    {
        if (f == "Electric")
            return 3;
        if (f == "Hybrid")
            return 2;
        if (f == "Diesel")
            return 1;
        return 0;
    }

    inline double encodeCondition(const string &c)
    {
        if (c == "Excellent")
            return 3;
        if (c == "Good")
            return 2;
        if (c == "Fair")
            return 1;
        return 0;
    }
};