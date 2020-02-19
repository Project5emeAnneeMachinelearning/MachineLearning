//
// Created by theo on 17/02/2020.
//

#include "Model.h"

#include <cstdlib>
#include <time.h>
#include <cmath>
#include "Eigen/Dense"
#include <iostream>
using namespace std;
using namespace Eigen;

extern "C"{
   int GiveMe42FromC() {
         return 42;
    }



class Model {
public:
    // NB DENTREE +1
    double* model;
    int weightSize;
    //Créee un tableau de poid entre -1 et 1 Random ??
    // TOUTE LES FONCTIONS DOIVENT AVOIR LE POINTEUR DU MODEL POUR POUVOIR LE MODIFIER
    Model(int weightSize){
        srand(time(NULL));
        this->model = new double[weightSize + 1];
//        this->model = (double *) malloc(sizeof(double) * (weightSize + 1));
        this->weightSize = weightSize+1;
        for(int i =0;i<this->weightSize;i++){
            double weight = fRand(-1.0,1.0);
            this->model[i] =weight;
        }
    }
    //somme pondéré pedict regression
    //sign
    double predict_regression(double * values){
        double result = model[0];
        for (int i=0; i<weightSize-1;i++){
            result += values[i] * model[i + 1];
        }
        return result;
    }

    double predict_lineaire(double * values){
        return predict_regression(values) > 0 ? 1 : -1;
    }


    void print_array(double * array,int size){
        cout << "array";
        for(int i=0;i<size;i++){
            cout << " "<<array[i] <<" " ;
        }
        cout <<endl;

    }
    void printmodel(){

        printf("--- Affichage model ----- \n");
        for(int i =0;i<weightSize;i++){
            //printf("poid %d : %f \n",i,model[i]);
            cout << "poid "<< i<< ":   " << model[i] << endl;
        }
        printf("\n");
        printf("----------------------------------- \n");
    }

    void train_classification(double * dataset,double * expected_output,int sizedataset,double pas,int sizeIndice,int epoch){
        // pour X iter
        //  Appliquer regle de rosenblatt
        // k étant un echantillon
        // W + a(Y^K-g(X^k))X^k
        // V4 + (double * V4)
        //          V4
        for(int j=0 ;j<epoch;j++) {
                int example = rand()% sizedataset/sizeIndice;
                double * array = (double *)malloc(sizeIndice+1*sizeof(double));
                array[0]=1;
                for(int z=0;z<sizeIndice;z++){
                    array[z+1] = dataset[example*sizeIndice+z];
                }
                print_array(array,sizeIndice+1);
                double *modelAlteration = array_multiply(array,
                                                         pas * (expected_output[example] - predict_lineaire(array)),
                                                         sizeIndice+1);
                ;
                model = array_addition(model, modelAlteration, sizeIndice+1);
                //print_array(modelAlteration,sizeIndice+1);
        }
    }

    void train_regression(double * dataset,double * expected_output,int sizedataset,int sizeIndice) {
       // (Transpose(X)*X)Y {x1,z1,x2,z2}
       int size= sizedataset/sizeIndice;
       MatrixXd X(size, sizeIndice + 1);
       for(int i = 0; i < size; i++){
            X(i, 0) = 1;
            for(int j = 1; j < sizeIndice + 1; j++){
                X(i,j) = dataset[i * sizeIndice + j - 1];
            }
        }

        MatrixXd Y(size,  1);
            for(int j = 0; j < size; j++){
                Y(j,0) = expected_output[j];
            }

        MatrixXd result = (((X.transpose()*X).inverse())*X.transpose())*Y;
            for(int i = 0;i<sizeIndice+1;i++){
                weightSize = result(i,0);
            }
    }

        double fRand(double fMin, double fMax)
    {
        double f = (double)rand() / RAND_MAX;
        return fMin + f * (fMax - fMin);
    }

    double sigmoid(double x)
    {
        return 1.0 / (1.0 + exp(-x));
    }

    double* array_addition(double* array1,double* array2,int size){
        double * result = (double*)malloc(sizeof(double)*size);
        for(int i =0;i<size;i++){
            result[i] = array1[i] + array2[i];
        }
        return result;
    }

    double* array_multiply(double * array1,double factor,int size){
        double * result = (double*)malloc(sizeof(double)*size);
        for(int i =0;i<size;i++){
            result[i] = array1[i]*factor;
        }
        return result;
    }

    double * add_biais(double * array,int size){
        double result[size+1];
        result[0]=0;
        for (int i = 0;i<size;i++){
            result[i+1] = array[i];
        }
    }


    void print_matrix(MatrixXd mat){
        cout <<  mat << endl;
    }

};


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

    double* sliceDoubleArray(int start, int end, double* arr, int len) {

        int cmpt = 0;
        double* res = new double[end - start + 1];
        for (size_t i = 0; i < len; i++)
        {
            if (i >= start) {
                res[cmpt] = arr[i];
                cmpt++;
            }

            if (i > end) {
                return res;
            }
        }
        return NULL;
    }


    int main(int argc, char **argv) {
        auto model = new Model(2);

        double trainingInputs[6]={33,35,34,37,43,28};
        double trainingExpectedOutputs[3] ={1,-1,1};
        double * res = sliceDoubleArray(0,2,trainingInputs,4);
        //double tkt = res[1];
        //double predict[2]={33,35};

        model->printmodel();
        //train_regression(model, trainingInputs, trainingExpectedOutputs, 4,  2);
        train_classif(model, trainingInputs, trainingExpectedOutputs, 6, 0.01,  2, 100);
        //model->pre
        model->printmodel();
        //printf("%f",model->predict_lineaire(predict))    ;
    }

}