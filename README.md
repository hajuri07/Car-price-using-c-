# 🚗 Car Price Predictor
**Machine Learning Project using C++ and OOP**

![Language](https://img.shields.io/badge/Language-C%2B%2B-blue?style=flat-square) ![Concepts](https://img.shields.io/badge/OOP%20%7C%20Linear%20Regression%20%7C%20Gradient%20Descent-green?style=flat-square)

---

## 1. Project Overview

This project implements a Machine Learning model in **C++ from scratch** using Object Oriented Programming (OOP) concepts. The goal is to predict the price of a used car based on features like age, mileage, engine size, fuel type, transmission, number of owners and condition.

> No external ML libraries are used. Everything — from data loading to gradient descent — is written manually in C++.

---

## 2. OOP Concepts Used

| Concept | Where Used | What it Does |
|---|---|---|
| Abstraction | `MLModel.h` | Defines virtual `train()`, `predict()`, `evaluate()` — hides implementation details |
| Encapsulation | `Dataset.h`, `LinearRegression.h` | Private data (weights, features) with public getters only |
| Inheritance | LinearRegression extends MLModel | Child class gets base class structure and must implement virtual functions |
| Polymorphism | `override` keyword on `train()` and `predict()` | Same function call runs different code depending on which model is used |
| File I/O | `Dataset.cpp loadFromCSV()` | Reads 15000 rows from cars.csv using `ifstream` and `stringstream` |
| Constructor Init List | `LinearRegression(lr, epochs)` | Initializes member variables efficiently using `: syntax` |

---

## 3. Project Structure

| File | Type | Purpose |
|---|---|---|
| `MLModel.h` | Header | Abstract base class — defines the ML interface |
| `Dataset.h / .cpp` | Header + Source | Loads CSV, normalizes data, splits into train/test |
| `LinearRegression.h / .cpp` | Header + Source | Implements gradient descent training and prediction |
| `Predictor.h / .cpp` | Header + Source | Connects everything — runs the full pipeline |
| `main.cpp` | Source | Entry point — creates Predictor and starts the program |
| `cars.csv` | Data | 15,000 rows of synthetic car data with 9 columns |

---

## 4. Dataset

The dataset was generated with **15,000 rows** of realistic synthetic car data. Each row represents one used car listing.

| Column | Type | Example | How Used |
|---|---|---|---|
| brand | Text | Toyota, BMW | Skipped (not used) |
| age | Number | 3.5 years | Feature — direct |
| mileage | Number | 48000 km | Feature — direct |
| engine_size | Number | 2.0 L | Feature — direct |
| fuel_type | Text | Petrol/Diesel/Electric/Hybrid | Feature — encoded to 0/1/2/3 |
| transmission | Text | Manual/Automatic | Feature — encoded to 0/1 |
| owners | Number | 1, 2, 3 | Feature — direct |
| condition | Text | Excellent/Good/Fair/Poor | Feature — encoded to 3/2/1/0 |
| price | Number | 15000.00 USD | Label — what we predict |

**Total features used:** 7 | **Label:** price | **Train set:** 12,000 rows | **Test set:** 3,000 rows

---

## 5. Feature Encoding

Since ML models only understand numbers, text columns were converted to numbers using encoding functions defined in `Dataset.h`:

```
Fuel Type:    Electric → 3  |  Hybrid → 2  |  Diesel → 1  |  Petrol → 0
Condition:    Excellent → 3 |  Good → 2    |  Fair → 1    |  Poor → 0
Transmission: Automatic → 1 |  Manual → 0
```

---

## 6. Mathematical Formulas

### 6.1 Linear Regression (Prediction Formula)

The model learns a linear relationship between features and price:

```
y = w1*x1 + w2*x2 + w3*x3 + ... + w7*x7 + b
```

- `y` = predicted car price (normalized)
- `x1...x7` = input features (age, mileage, engine size, fuel, transmission, owners, condition)
- `w1...w7` = weights (learned during training)
- `b` = bias (the base offset, also learned)

### 6.2 Mean Squared Error (Loss Function)

MSE measures how wrong the predictions are. Lower MSE = better model:

```
MSE = (1/n) * SUM( (predicted - actual)² )
```

- `n` = number of training samples
- We square the error so positive and negative errors don't cancel out
- Starting MSE was ~0.99, final MSE came down to ~0.29 after training

### 6.3 Gradient Descent (Training Algorithm)

Gradient descent is how the model learns. It adjusts weights step by step to reduce the loss:

```
error  = predicted - actual
dW[j]  = (1/n) * SUM( error * X[i][j] )
dB     = (1/n) * SUM( error )
w[j]   = w[j] - lr * dW[j]
b      = b    - lr * dB
```

- `lr` = learning rate (set to 0.01) — controls how big each update step is
- This runs for **1000 epochs** (1000 full passes over training data)
- Each epoch the weights get slightly better at predicting price

### 6.4 Normalization (Feature Scaling)

Before training, all values are scaled to a small range using Z-score normalization. This prevents large values like mileage (50000) from dominating small values like engine size (2.0):

```
x_normalized = (x - mean) / std_deviation
```

- `mean` = average of all values in that column
- `std_deviation` = how spread out the values are
- Result: all features end up in range roughly -3 to +3
- Labels (prices) are also normalized — this was critical to stop NaN errors

### 6.5 Denormalization (Converting Back to Real Price)

After prediction, the normalized output is converted back to a real dollar price:

```
real_price = (normalized_pred * labelStd) + labelMean
```

### 6.6 Evaluation Metrics

| Metric | Formula | Our Result | Meaning |
|---|---|---|---|
| MSE | `(1/n) * SUM((pred-actual)²)` | 0.292 | Average squared error (normalized) |
| MAE | `(1/n) * SUM(\|pred-actual\|)` | 0.378 | Average absolute error (normalized) |
| R² Score | `1 - (SS_res / SS_tot)` | **0.691** | Model explains 69% of price variation |

> R² of 0.69 means the model is a decent predictor. 1.0 = perfect, 0.0 = random guessing.

---

## 7. How to Compile and Run

**Requirements**
- MinGW-w64 (x86_64, version 15+) — 64-bit compiler
- VS Code or any terminal
- `cars.csv` in the same folder as the `.cpp` files

**Compile**
```bash
g++ -o carpredictor main.cpp Dataset.cpp LinearRegression.cpp Predictor.cpp
```

**Run**
```bash
./carpredictor
```

**Sample Output**
```
=== Car Price Predictor ===
Loaded 15000 rows.
Training on 12000 samples...
Epoch 0   | MSE Loss: 0.990342
Epoch 100 | MSE Loss: 0.367420
...
Epoch 900 | MSE Loss: 0.325934
Training complete!

--- Evaluation ---
MSE  : 0.292397
MAE  : 0.378782
R2   : 0.691828
```

---

## 8. Summary

This project successfully demonstrates the use of OOP concepts in C++ to build a working Machine Learning model without any external libraries.

- ✅ Built a full Linear Regression model from scratch in C++
- ✅ Used Abstraction, Encapsulation, Inheritance and Polymorphism
- ✅ Loaded and processed a real 15,000 row CSV dataset
- ✅ Implemented Gradient Descent with proper normalization
- ✅ Achieved R² score of **0.69** — model genuinely learned from data
- ✅ User can input car details and get a real price prediction
