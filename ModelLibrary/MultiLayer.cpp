//
// Created by Kalfa on 20/02/2020.
//

#include <cmath>
#include <windef.h>
#include "MultiLayer.h"
#include "Model.h"

MultiLayer::MultiLayer(int * layers,int size,int indiceNumber){
    this->layers = layers;
    this->sizelayers = size;
    model = new Model**[size];
    for(int i= 0;i<size;i++){
        model[i] = new Model*[layers[i]];
        for(int j = 0; j < layers[i];j++){
            //model[i][j] = new Model(indiceNumber);
        }
    }
}

double * MultiLayer::predict_classif(int * layers,int sizeLayers, double * inputs,int inputSize,int actualLayer){
        if(sizeLayers ==0){
            return inputs;
        }
        double * result = new double[layers[0]+1];
        result[layers[0]] =1;
        for (int i=0;i<layers[0];i++){
            model[actualLayer][i] = new Model(inputSize);
            //APPLIQUER LA TANH
            result[i] = tanh(model[actualLayer][i]->predict_regression(inputs));

        }
        //remove first occurence of the array by incrementing pointer
        layers = layers+1;
        this->sizelayers--;
        return MultiLayer::predict_classif(layers,sizeLayers-1,result,(layers[0]+1),actualLayer+1);
}

