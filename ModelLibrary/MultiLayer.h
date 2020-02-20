//
// Created by Kalfa on 20/02/2020.
//

#ifndef MACHINE_LEARNING_LIB_MULTILAYER_H
#define MACHINE_LEARNING_LIB_MULTILAYER_H


#include "Model.h"

class MultiLayer
{
public:
    Model *** model;
    int * layers;
    int sizelayers;
    explicit MultiLayer(int * layers,int size,int indiceNumber);
    double * predict_classif(int * layers,int sizeLayers, double * inputs,int inputSize,int actualLayer);
};


#endif //MACHINE_LEARNING_LIB_MULTILAYER_H
