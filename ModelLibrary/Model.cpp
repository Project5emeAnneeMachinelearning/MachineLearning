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
    double* model;
    int weightSize;
    //Créee un tableau de poid entre -1 et 1 Random ??
    // TOUTE LES FONCTIONS DOIVENT AVOIR LE POINTEUR DU MODEL POUR POUVOIR LE MODIFIER
    Model(int weightSize){
        srand(time(NULL));
        this->model = (double *) malloc(sizeof(int*) * weightSize + 1);
        this->weightSize = weightSize+1;
        for(int i =0;i<weightSize+1;i++){
            double weight = fRand(-1.0,1.0);
            this->model[i] =weight;
        }
    }
    //somme pondéré pedict regression
    //sign
    double predict_regression(double * values){
        double result = 0;
        for (int i=0; i<weightSize;i++){
            result += values[i] * model[i];
        }
        return result;
    }

    double predict_lineaire(double * values){
        return signbit(predict_regression(values));
    }

    void printmodel(){


        for(int i =0;i<weightSize;i++){
            printf("%d",model[i]);
        }
        printf("\n");

    }

    void train_classification(double * dataset,double * expected_output,int sizedataset,double pas,int sizeIndice,int epoch){
        // pour X iter
        //  Appliquer regle de rosenblatt
        // k étant un echantillon
        // W + a(Y^K-g(X^k))X^k
        // V4 + (double * V4)
        //          V4
        for(int j=0 ;j<epoch;j++) {
            for (int i = 0; i < sizedataset/sizeIndice; i++) {
                double * array = (double *)malloc(sizeIndice+1*sizeof(double));
                array[0]=0;
                for(int z=0;z<sizeIndice;z++){
                    array[z+1] = dataset[i*sizeIndice+z];
                }
                double *modelAlteration = array_multiply(array,
                                                         pas * (expected_output[i] - predict_regression(array)),
                                                         sizeIndice);
                model = array_addition(model, modelAlteration, sizeIndice);
            }
        }
    }

    void train_regression(double ** dataset,double ** expected_output,int sizedataset,double pas,int sizeIndice,int epoch) {
       // (Transpose(X)*X)Y
       auto input_matrix = array_to_matrix(dataset,sizedataset);
        (((input_matrix.transpose()*input_matrix).inverse())*input_matrix.transpose());
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


    MatrixXd array_to_matrix(double** arr, int len) {

        MatrixXd mat = MatrixXd(len / 2, 3);

        for(int i= 0; i<len;i++)
        {
            mat << Vector3d(arr[i][0], arr[i][1], arr[i][2]);
        }

        return mat;
    }

};


   Model create(int indiceNumber){
      auto model = Model(indiceNumber);
      return model;
   }

   void train_classif(Model* model,double * dataset,double * expected_output,int sizedataset,double pas,int sizeIndice,int epoch) {
        model->train_classification(dataset,expected_output,sizedataset,pas,sizeIndice,epoch);
   }

    void train_regression(Model* model,double ** dataset,double ** expected_output,int sizedataset,double pas,int sizeIndice,int epoch){
        model->train_regression(dataset,expected_output,sizedataset,pas,sizeIndice,epoch);
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

        double trainingInputs[4]={33,35,34,37};
        double trainingExpectedOutputs[2] ={12,11};
        double * res = sliceDoubleArray(0,2,trainingInputs,4);
        double tkt = res[1];
        double predict[2]={33,35};
        /*
        model->printmodel();
        train_classif(model, trainingInputs, trainingExpectedOutputs, 2, 0.01,  2, 1);
        model->printmodel();*/
        printf("%f",model->predict_regression(predict))    ;
    }

}