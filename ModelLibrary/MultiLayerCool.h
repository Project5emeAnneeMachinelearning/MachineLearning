#ifndef MULTILAYERCOOL_H
#define MULTILAYERCOOL_H

#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <ctime>
#include <algorithm>


class MultilayerPerceptron {

    struct WeightMatrix {
        int inputDim;
        int outputDim;
        std::vector<float> w;

        WeightMatrix(int inputDim_, int outputDim_) {
            w.clear();
            inputDim = inputDim_;
            outputDim = outputDim_;

            // JE NE SAIS PAS ENCORE COMMENT INITIALISER LE TABLEAU DE POIDS :(((
            for (int k = 0; k < inputDim_ /* --> NOMBRE DE POIDS DANS LE TABLEAU*/; ++k) {
                double f = (double)rand() / RAND_MAX;
                w.push_back( fMin + f * (fMax - fMin) /* --> VALEURS (PEUT-ÊTRE) ALÉATOIRES DE POIDS */);
            }
        }
    };

    struct Layer {
        int dim;
        std::vector<float> in;
        std::vector<float> out;
        std::vector<float> err;

        Layer(int dim_) {
            dim = dim_;
            for (int k = 0; k < dim; ++k) {
                in.push_back(0);
                out.push_back(0);
                err.push_back(0);
            }
        }
    };

public:

    struct TrainingElement {
        std::vector<float> in;
        std::vector<float> out;

        TrainingElement(std::vector<float> in_, std::vector<float> out_) {
            in = in_;
            out = out_;
        }
    };


    MultilayerPerceptron(int inputDimension_, int outputDimension_);
    ~MultilayerPerceptron();

    void init();
    void resetWeights();

    std::vector<float> classify(std::vector<float> x_);
    void setTrainingSet(std::vector<TrainingElement> trainingSet_);
    float train(float eta_);

private:

    void calcLayerInput(int l_);
    void calcLayerOutput(int l_);
    void calcLayerError(int l_);
    void updateWeights(int l_);

    int L;
    int inputDimension;
    int outputDimension;

    std::vector<WeightMatrix> weights;
    std::vector<Layer> layers;
    std::vector<TrainingElement> trainingSet;

};

#endif //MULTILAYERCOOL_H