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






    //Créee un tableau de poid entre -1 et 1 Random ??
    // TOUTE LES FONCTIONS DOIVENT AVOIR LE POINTEUR DU MODEL POUR POUVOIR LE MODIFIER
    Model::Model(int weightSize){
        srand(time(NULL));
        this->model = new double[weightSize + 1];
//        this->model = (double *) malloc(sizeof(double) * (weightSize + 1));
        this->weightSize = weightSize+1;
        for(int i =0;i<this->weightSize;i++){
            double weight = fRand(-1.0,1.0);
            this->model[i] =weight;
        }
    }

    double Model::predict_regression(double * values){
        double result = model[0];
        for (int i=0; i<weightSize-1;i++){
            result += values[i] * model[i + 1];
        }
        return result;
    }

    double Model::predict_lineaire(double * values){
        return predict_regression(values) > 0 ? 1 : -1;
    }


    void Model::print_array(double * array,int size){
        cout << "array";
        for(int i=0;i<size;i++){
            cout << " "<<array[i] <<" " ;
        }
        cout <<endl;

    }
    void Model::printmodel(){

        printf("--- Affichage model ----- \n");
        for(int i =0;i<weightSize;i++){
            //printf("poid %d : %f \n",i,model[i]);
            cout << "poid "<< i<< ":   " << model[i] << endl;
        }
        printf("\n");
        printf("----------------------------------- \n");
    }

    void Model::train_classification(double * dataset,double * expected_output,int sizedataset,double pas,int sizeIndice,int epoch){
        // pour X iter
        //  Appliquer regle de rosenblatt
        // k étant un echantillon
        // W + a(Y^K-g(X^k))X^k
        // V4 + (double * V4)
        //          V4
        for(int j=0 ;j<epoch;j++) {
                int example = rand()% sizedataset/sizeIndice;
                double array[sizeIndice+1];
                array[0]=1;
                for(int z=0;z<sizeIndice;z++){
                    array[z+1] = dataset[example*sizeIndice+z];
                }
                 array_multiply(array,
                                                         pas * (expected_output[example] - predict_lineaire(array)),
                                                         sizeIndice+1);
                ;
                array_addition(model, array, sizeIndice+1);
               
        }
    }

    void Model::train_regression(double * dataset,double * expected_output,int sizedataset,int sizeIndice) {
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
                model[i] = result(i,0);
            }
    }

        double Model::fRand(double fMin, double fMax)
    {
        double f = (double)rand() / RAND_MAX;
        return fMin + f * (fMax - fMin);
    }


    void Model::array_addition(double* array1,double* array2,int size){
        for(int i =0;i<size;i++){
            array1[i] += array2[i];
        }
    }

    void Model::array_multiply(double * array1,double factor,int size){

        for(int i =0;i<size;i++){
            array1[i] = array1[i]*factor;
        }
    }






