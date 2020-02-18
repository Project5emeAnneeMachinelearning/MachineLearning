#include "Model.h"

class Model {
public:
    // NB DENTREE +1
    double* weightArray;
    int weightSize;
    Matrix2d mat;
    //Crée un tableau de poid entre -1 et 1 Random ??
    // TOUTE LES FONCTIONS DOIVENT AVOIR LE POINTEUR DU MODEL POUR POUVOIR LE MODIFIER
    void create_model(double** entryValue, int weightSize) {
        /*this->entryValue = (double**) malloc(sizeof(double*)*listsize);
        for(int i =0;i<arraysize;i++){
            this->entryValue[i] = (double*) malloc(sizeof(double*)*arraysize);
        }*/
        this->weightSize = weightSize + 1;
        srand(time(NULL));
        this->weightArray = (double *) malloc(sizeof(int*)*weightSize+1);
        double weight = fRand(-1.0, 1.0);
    }
    //somme pondéré pedict regression
    //sign
    double predict_regression(double* values) {
        double result = 0;
        for (int i = 0; i < weightSize; i++) {
            result += values[i] * weightArray[i];
        }
        return result;
    }

    double predict_classification(double* values) {
        //SIGN
        return sign(predict_regression(values));
    }

    void train_regression(double *in_dataset, double *expected_outputs, int size_dataset, double pas) {
        // pour X iter
        //  Appliquer regle de rosenblatt
        // k étant un echantillon
        // W + a(Y^K-g(X^k))X^k
        // V4 + (double * V4)
        //          V4
        for(int i = 0; i < size_dataset; i++) {
            weightArray = (pas*(dataset[i]) - predict_regression(dataset[i])) * dataset[i];
            predict_regression(dataset[i]);
        }
        Map<MatrixXd> X = 33;
    }

    void train_classification(double *in_dataset, double *expected_outputs, int alpha, int nb_iter, int previous_weight) {

    }

    double fRand(double fMin, double fMax) {
        double f = (double)rand() / RAND_MAX;
        return fMin + f * (fMax - fMin);
    }

    double sign(double x) {
        return 1.0 / (1.0 + exp(-x));
    }
};