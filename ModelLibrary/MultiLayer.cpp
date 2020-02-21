//
// Created by Kalfa on 20/02/2020.
//

#include <cmath>
#include <cstdio>
#include <iostream>
#include "MultiLayer.h"
#include "Model.h"

using namespace std;

MultiLayer::MultiLayer(int * layers,int size,int indiceNumber){
    this->layers = layers;
    this->layersFixed = layers;
    this->sizelayersFixed = size;
    this->sizelayers = size;
    model = new Model**[size];
    for(int i= 0;i<size;i++){
        cout << "|||||||||||||||||| layer : "<< i<< " |||||||||";
        model[i] = new Model*[layers[i]];
        for(int j = 0; j < layers[i];j++){
            model[i][j]= new Model(layers[i]);
            model[i][j]->printmodel();
        }
    }
}

double * MultiLayer::predict_regress(int * layersArray,int sizeLayers, double * inputs,int inputSize,int actualLayer){
        // [2,3,2,1]
        // input 2 -1
        if(sizeLayers ==0){
            return inputs;
        }
        //[0,0,1]
        double * result = new double[layersArray[0]+1];
        result[0]=1;
        for (int i=0;i<layersArray[0];i++){
            //model[actualLayer][i] = new Model(inputSize);
            double predRes = model[actualLayer][i]->predict_regression(inputs);
            if ( this->sizelayers!=1){
                predRes = tanh(predRes);
            }
            model[actualLayer][i]->previousResult=predRes;
            result[i+1] = predRes ;
        }
        //remove first occurence of the array by incrementing pointer
        layersArray = layersArray+1;
        this->sizelayers--;
        return MultiLayer::predict_regress(layersArray,sizeLayers-1,result,(layersArray[0]+1),actualLayer+1);
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
    return result;
}

double MultiLayer::calc_delta(int layerNumber,int modelNumber,double awaitres){
    cout<<"model "<< "x : "<<layerNumber-1 << "y :"<<modelNumber <<endl;
    double modelResult = model[layerNumber-1][modelNumber]->previousResult;
    return modelResult*(awaitres-(modelResult*modelResult))*MultiLayer::recurse_weight_delta(layerNumber,modelNumber);
}//YA PAS DE PANNEAU




double calc_root_delta(double modelRes,double awaitres){
    return (modelRes-awaitres)*(1-(modelRes*modelRes));
}



double * MultiLayer::propagAvant(int * layersArray,int sizeLayers,double pas,double * inputs,double awaitres){
    for (int i=0;i<sizeLayers;i++){
        for (int j=0;j<layersArray[i];j++){
            for(int z=0;z<layersArray[i]+1;z++){
                model[i][j]->model[z]=model[i][j]->model[z]+pas*inputs[j]*model[i][j]->delta;
            }
        }
    }
}

void  MultiLayer::propagArriere(double res,double awaitres){
    for(int j=0;j>layers[sizelayersFixed-1];j++){
            model[sizelayersFixed-1][j]->delta = calc_root_delta(model[sizelayersFixed-1][j]->previousResult, awaitres);
    }
        for(int i = sizelayersFixed-2;i>=0;i--){
            for(int j=0;j<layers[i]-1;j++){
                    int a = layers[i];
                    //model[i][j]->delta = MultiLayer::calc_delta(i,j,awaitres);
            }
        }
}

double * MultiLayer::training(int * layersArray,int sizeLayers, double * inputs,int inputSize,double awaitres ,double pas){
        double * res = predict_regress(layersArray,sizeLayers,inputs,inputSize,0);
        propagArriere(res[0],awaitres);
        propagAvant(layersArray,sizeLayers,pas,inputs,awaitres);
        this->sizelayers = sizelayersFixed;
}

