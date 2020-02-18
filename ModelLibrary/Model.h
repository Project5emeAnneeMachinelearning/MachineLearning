#ifndef MODEL_H
#define MODEL_H


#include <cstdlib>
#include <time.h>
#include <cmath>
#include "Eigen/Dense"

using namespace Eigen;

class Model {
public:
    // NB DENTREE +1
    double* weightArray;
    int weightSize;
    Matrix2d mat;

    void create_model(double** entryValue, int weightSize);
    double predict_regression(double * values);
    double predict_linear(double * values);
    void train_regression(double *in_dataset, double *expected_outputs, int size_dataset, double pas);
    void train_classification(double *in_dataset, double *expected_outputs, int alpha, int nb_iter, int previous_weight);
    double fRand(double fMin, double fMax);
    double sign(double x);
}

#endif MODEL_H
