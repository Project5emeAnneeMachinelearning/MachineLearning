#include "MultiLayerCool.h"

using namespace std;

MultilayerPerceptron::MultilayerPerceptron(int inputDimension_, int outputDimension_) {
    inputDimension = inputDimension_;
    outputDimension = outputDimension_;

    layers.push_back(Layer(inputDimension));
    L = 1;
}

MultilayerPerceptron::~MultilayerPerceptron() {

}

void MultilayerPerceptron::init() {
    layers.push_back(Layer(outputDimension));
    L++;

    resetWeights();

    WeightMatrix * weightMatrix;
    for(int l = 0; l < L-1; ++l) {
        weightMatrix = &(weights[l]);
    }

}


void MultilayerPerceptron::resetWeights() {
    weights.clear();
    int l;
    int dim0, dim1;
    for(l = 0; l < L-1; ++l) {
        dim0 = layers[l].dim;
        dim1 = layers[l+1].dim;
        weights.push_back(WeightMatrix(dim0, dim1, 0f)); // JE SAIS PAS
    }
}


void MultilayerPerceptron::calcLayerInput(int h_) {

}


void MultilayerPerceptron::calcLayerOutput(int h_) {
    for(int i = 0; i < layers[h_].dim; ++i) {
        layers[h_].out[i] = sigmoid(layers[h_].in[i]);
    }
}


vector<float> MultilayerPerceptron::classify(vector<float> x_) {
    int l;
    int i;
    if(x_.size() == inputDimension) {
        for(i=0; i<inputDimension; ++i) {
            layers[0].out[i] = x_[i];
        }
        for(l=1; l<L; ++l) {
            calcLayerInput(l);
            calcLayerOutput(l);
        }
        return layers[L-1].out;
    }
    return x_;
}


void MultilayerPerceptron::calcLayerError(int h_) {

    // TODO
}


void MultilayerPerceptron::updateWeights(int h_) {

    // TODO
}


// activation function
float MultilayerPerceptron::sigmoid(float x_) {

    // TODO
}


void MultilayerPerceptron::setTrainingSet(vector<TrainingElement> trainingSet_) {
    trainingSet = trainingSet_;
}


// training with the backpropagation algorithm
float MultilayerPerceptron::train() {

    float trainingSetError = 0;
    int l;

        // backpropagate the error
        for(l = L-2; l >= 0; l--) {
            calcLayerError(l);
        }

        for(l = 1; l < L; ++l) {
            updateWeights(l);
        }
    }

    return trainingSetError;
}