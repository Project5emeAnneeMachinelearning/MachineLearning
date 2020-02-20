//
// Created by Kalfa on 20/02/2020.
//

#include <cstdio>
#include "API.h"
#include "Model.h"
#include "MultiLayer.h"


extern "C" {
int GiveMe42FromC()
{
    return 42;
}


Model* create(int indiceNumber){
    auto model = new Model(indiceNumber);
    return model;
}

void train_classif(Model* model,double * dataset,double * expected_output,int sizedataset,double pas,int sizeIndice,int epoch) {
    model->train_classification(dataset,expected_output,sizedataset,pas,sizeIndice,epoch);
}

void train_regression(Model* model,double * dataset,double * expected_output,int sizedataset,int sizeIndice){
    model->train_regression(dataset,expected_output,sizedataset,sizeIndice);
}

int predict_regression(Model* model ,double * values){
    return model->predict_regression(values);
}

int predict_classif(Model* model ,double * values){
    return model->predict_lineaire(values);
}


int main(int argc, char **argv) {
    int layers[4] = {3,8,2,1};
    double trainingInputs[2]={34,37};
    MultiLayer* multiLayer = new MultiLayer(layers,4,NULL);
    multiLayer->predict_classif(layers,4,trainingInputs,2,0);





}

int test_first_part(){
    auto model = new Model(2);
    double trainingInputs[6]={34,37,43,28,33,35};
    double trainingExpectedOutputs[3] ={1,-1,1};
    //double tkt = res[1];
    double predict[2]={33,35};

    model->printmodel();
    train_regression(model, trainingInputs, trainingExpectedOutputs, 6,  2);
    //train_classif(model, trainingInputs, trainingExpectedOutputs, 6, 0.01,  2, 100);
    //model->pre
    model->printmodel();
    //printf("%f",model->predict_lineaire(predict));
    printf("%f",model->predict_regression(predict));
}

}