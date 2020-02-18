//
// Created by theo on 17/02/2020.
//

#include "Model.h"

#include <cstdlib>
#include <time.h>
#include <cmath>
#include "Eigen/Dense"
using namespace std;
using namespace Eigen;

extern "C"{
   int GiveMe42FromC() {
         return 42;
    }



class Model {
public:
    // NB DENTREE +1
    double* weightArray;
    int weightSize;
    Matrix2d mat ;
    //Créee un tableau de poid entre -1 et 1 Random ??
    // TOUTE LES FONCTIONS DOIVENT AVOIR LE POINTEUR DU MODEL POUR POUVOIR LE MODIFIER
    Model(double** entryValue,int weightSize){
        /*this->entryValue = (double**) malloc(sizeof(double*)*listsize);
        for(int i =0;i<arraysize;i++){
            this->entryValue[i] = (double*) malloc(sizeof(double*)*arraysize);
        }*/
        this->weightSize = weightSize+1;
        srand(time(NULL));
        this->weightArray = (double *) malloc(sizeof(int*)*weightSize+1);
        for(int i =0;i<weightSize;i++){
            double weight = fRand(-1.0,1.0);
            weightArray[i] =weight;
        }
        weightArray[0]=1;
    }
    //somme pondéré pedict regression
    //sign
    double predict_regression(double * values){
        double result = 0;
        for (int i=0; i<weightSize;i++){
            result += values[i] * weightArray[i];
        }
        return result;
    }

    double predict_lineaire(double * values){
        //SIGN
        return signbit(predict_regression(values));
    }

    void train(double ** dataset,double * expected_output,int sizedataset,double pas,int sizeIndice){
        // pour X iter
        //  Appliquer regle de rosenblatt
        // k étant un echantillon
        // W + a(Y^K-g(X^k))X^k
        // V4 + (double * V4)
        //          V4
        for(int i=0; i<sizedataset;i++){
            dataset[i] = add_biais(dataset[i],sizeIndice);
            double * modelAlteration = array_multiply(dataset[i],pas*(expected_output[i]-predict_regression(dataset[i])),sizeIndice);
            weightArray = array_addition(weightArray,modelAlteration,sizeIndice);
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
        double result[size];
        for(int i =0;i<size;i++){
            result[i] = array1[i] + array2[i];
        }
        return result;
    }

    double* array_multiply(double * array1,double factor,int size){
        double result[size];
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
};

}