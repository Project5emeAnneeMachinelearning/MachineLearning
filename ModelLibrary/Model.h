//
// Created by theo on 17/02/2020.
//

#ifndef MACHINELEARNING_LIB_H
#define MACHINELEARNING_LIB_H

class Model
{
public:
    explicit Model(int weightSize);

    double *model;
    int weightSize;

    void array_multiply(double *array1, double factor, int size);

    void array_addition(double *array1, double *array2, int size);

    void train_regression(double *dataset, double *expected_output, int sizedataset, int sizeIndice);

    void train_classification(double *dataset, double *expected_output, int sizedataset, double pas, int sizeIndice,
                              int epoch);

    double predict_lineaire(double *values);

    double predict_regression(double *values);

    void printmodel();

    double fRand(double fMin, double fMax);

    void print_array(double *array, int size);
};
#endif //MACHINELEARNING_LIB_H
