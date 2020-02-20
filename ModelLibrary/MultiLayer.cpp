//
// Created by Kalfa on 20/02/2020.
//

#include <cmath>
#include "MultiLayer.h"
#include "Model.h"

MultiLayer::MultiLayer(int * layers,int size,int indiceNumber){
    this->layers = layers;
    this->layersFixed = layers;
    this->sizelayersFixed = size;
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
        // [3,2,8,1]

        if(sizeLayers ==0){
            return inputs;
        }
        double * result = new double[layers[0]+1];
        result[layers[0]] =1;
        for (int i=0;i<layers[0];i++){
            model[actualLayer][i] = new Model(inputSize);
            //APPLIQUER LA TANH ??
            double predRes = tanh(model[actualLayer][i]->predict_regression(inputs));
            model[actualLayer][i]->previousResult=predRes;
            result[i] = predRes ;
        }
        //remove first occurence of the array by incrementing pointer
        layers = layers+1;
        this->sizelayers--;
        return MultiLayer::predict_classif(layers,sizeLayers-1,result,(layers[0]+1),actualLayer+1);
}

double MultiLayer::recurse_weight_delta(int layerNumber, int modelNumber) {
    double result =0 ;
    Model* subjectModel = model[layerNumber][modelNumber];
    for(int i=0;i<layerNumber;i++){
        for (int z = 0;z<layersFixed[layerNumber+1];z++){
            Model* nextModel = model[layerNumber+1][z];
            result += subjectModel->model[z]*nextModel->delta;
        }
    }
}

double MultiLayer::calc_delta(int layerNumber,int modelNumber){
    double modelResult = model[layerNumber][modelNumber]->previousResult;
    return modelResult*(1-modelResult)*MultiLayer::recurse_weight_delta(layerNumber,modelNumber);
}




double calc_root_delta(double modelRes){
    return (1-modelRes);
}

double * MultiLayer::propagAvant(){

}

double * MultiLayer::propagArriere(double res){
        for(int i = sizelayersFixed;i-1>-1;i--){
            for(int j=0;j>layers[i];j++){
                if(i==sizelayersFixed){
                    model[i][j]->delta = calc_root_delta(model[i][j]->previousResult);
                }else{
                    model[i][j]->delta = MultiLayer::recurse_weight_delta(i,j);
                }
            }
        }
}

