//
// Created by Kalfa on 20/02/2020.
//

#include "MultiLayer.h"
#include "Model.h"

MultiLayer::MultiLayer(int * layers,int size,int indiceNumber){
    Model*** model = new Model**[size];
    for(int i= 0;i<size;i++){
        model[i] = new Model*[layers[i]];
        for(int j = 0; j < layers[i];j++){
            model[i][j] = new Model(indiceNumber);
        }
    }
}



