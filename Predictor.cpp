#include "Predictor.h"
#include <iostream>
using namespace std;

Predictor::Predictor(double lr, int epochs) : model(lr, epochs) {}

void Predictor::run(const string &csvFile)
{
    cout << "=== Car Price Predictor ===\n\n";

    if (!dataset.loadfromCSV(csvFile))
        return;

    dataset.normalize();

    Dataset trainSet, testSet;
    dataset.traintestsplit(trainSet, testSet, 0.8);

    cout << "Training on " << trainSet.size() << " samples...\n\n";
    model.train(trainSet.getfeatures(), trainSet.getlabels());

    cout << "\nTesting on " << testSet.size() << " samples...\n";
    model.evaluate(testSet.getfeatures(), testSet.getlabels());

    predictSingle();
}

void Predictor::predictSingle()
{
    cout << "\n--- Try a prediction ---\n";

    cout << "Kitni puraani gaadi hai wese ? (years): ";
    double age;
    cin >> age;

    cout << "Kitnaa deti hai gaadi yeah (km): ";
    double mileage;
    cin >> mileage;

    cout << "Engine size (1.0 / 1.6 / 2.0 etc): ";
    double engine;
    cin >> engine;

    cout << "Petrol khaati hai kya  (Petrol/Diesel/Electric/Hybrid): ";
    string fuel;
    cin >> fuel;

    cout << "Manual ya automatic hai? (Manual/Automatic): ";
    string trans;
    cin >> trans;

    cout << "Second hand haikya ?(1/2/3): ";
    double owners;
    cin >> owners;

    cout << "Gaadi me sab badiya to haina?? (Excellent/Good/Fair/Poor): ";
    string condition;
    cin >> condition;

    vector<double> input = {
        age, mileage, engine,
        dataset.encodeFuel(fuel),
        (trans == "Automatic" ? 1.0 : 0.0),
        owners,
        dataset.encodeCondition(condition)};

    double normalizedPred = model.predict(input);
    double realPrice = normalizedPred * dataset.getLabelStd() + dataset.getLabelMean();

    cout << "\nPredicted price: $" << realPrice << "\n";
}