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

    Model(double** entryValue, int weightSize);
    double predict_regression(double * values);
    double predict_linear(double * values);
    void train(double * dataset, double * expected_output, int sizedataset, double pas);
    double fRand(double fMin, double fMax);
}

#endif MODEL_H
