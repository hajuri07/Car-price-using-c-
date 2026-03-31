#include "Dataset.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <string>

bool Dataset::loadfromCSV(const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "ARee yaar bhai kuch dikkat arahi hai " << filename << endl;
        return false;
    }

    string line;
    getline(file, line); // skip header

    while (getline(file, line))
    {
        stringstream ss(line);
        string val;
        vector<double> row;

        getline(ss, val, ','); // skip brand

        getline(ss, val, ',');
        row.push_back(stod(val)); // age
        getline(ss, val, ',');
        row.push_back(stod(val)); // mileage
        getline(ss, val, ',');
        row.push_back(stod(val)); // engine_size

        getline(ss, val, ',');
        row.push_back(encodeFuel(val)); // fuel
        getline(ss, val, ',');
        row.push_back(val == "Automatic" ? 1.0 : 0.0); // transmission
        getline(ss, val, ',');
        row.push_back(stod(val)); // owners
        getline(ss, val, ',');
        row.push_back(encodeCondition(val)); // condition

        getline(ss, val, ',');
        labels.push_back(stod(val)); // price

        features.push_back(row);
    }

    cout << "Badiya hogaya bhai kaam apna " << labels.size() << " rows.\n";
    return true;
}

void Dataset::normalize()
{
    int n = features.size();
    int m = features[0].size();

    featureMeans.assign(m, 0.0);
    featureSTD.assign(m, 0.0);

    // normalize features
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            featureMeans[j] += features[i][j];
    for (int j = 0; j < m; j++)
        featureMeans[j] /= n;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            featureSTD[j] += pow(features[i][j] - featureMeans[j], 2);
    for (int j = 0; j < m; j++)
        featureSTD[j] = sqrt(featureSTD[j] / n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (featureSTD[j] > 1e-8)
                features[i][j] = (features[i][j] - featureMeans[j]) / featureSTD[j];

    // normalize labels too!
    for (double val : labels)
        labelMean += val;
    labelMean /= n;

    for (double val : labels)
        labelStd += pow(val - labelMean, 2);
    labelStd = sqrt(labelStd / n);

    for (double &val : labels)
        val = (val - labelMean) / labelStd;
}

void Dataset::traintestsplit(Dataset &train, Dataset &test, double ratio)
{
    int splitAt = features.size() * ratio;

    for (int i = 0; i < (int)features.size(); i++)
    {
        if (i < splitAt)
        {
            train.features.push_back(features[i]);
            train.labels.push_back(labels[i]);
        }
        else
        {
            test.features.push_back(features[i]);
            test.labels.push_back(labels[i]);
        }
    }
}