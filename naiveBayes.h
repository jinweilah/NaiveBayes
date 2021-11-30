#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define DISCFEATNUM 7   //7 features with discrete data
#define MAXDATAREP 5    //maximum number of data representation contain in input features e.g. f7 has 5
#define NORMAL 0
#define ALTERED 1
#define PI 3.141592
#define BOLDBLACK "\033[1m\033[30m" 
#define BOLDGREEN "\033[1m\033[32m" 
#define BOLDRED "\033[1m\033[31m"  
#define RESET "\033[0m"            

typedef struct 
{
    float f1;   //feature 1
    float f2;   //feature 2 
    int f3;     //feature 3 
    int f4;     //feature 4 
    int f5;     //feature 5 
    int f6;     //feature 6 
    float f7;   //feature 7 
    int f8;     //feature 8 
    float f9;   //feature 9 
} FEATINPUT;    //struct FEATINPUT typedef as FEATINPUT

// define function prototype
void readText(FEATINPUT *trainingFeature, int *trainingOutput, FEATINPUT *testingFeature, int *testingOutput, int *trainingPercentage, int *testingPercentage);
void trainData(int *trainingPercentage, FEATINPUT *trainingFeature, int *trainingOutput, double mean[][2], double variance[][2], FEATINPUT *datarep_discfeat, double pcond_discrete_normal[][MAXDATAREP], double pcond_discrete_altered[][MAXDATAREP], double pprior_semendiag[], int p_semendiagtotal[], int matched[]);
void condprob_firstloop(FEATINPUT *datarep_discfeat, double pcond_discrete_normal[][MAXDATAREP], double pcond_discrete_altered[][MAXDATAREP], FEATINPUT *trainingFeature,int *trainingOutput, int *i, int p_semendiagtotal[], double mean[][2], int matched[]);
void condprob_secondloop(double mean[][2], double variance[][2], int *i, FEATINPUT *trainingFeature, int *trainingOutput);
void laplace(double pcond_discrete[][MAXDATAREP], int pcond_rownum, int datarep_colnum, int p_semendiagtotal[], int normOrAlt);
void nozeroprob(double pcond_discrete[][MAXDATAREP], int pcond_rownum, int datarep_colnum, int p_semendiagtotal[], int normOrAlt);
void match_indicator(int matched[], FEATINPUT *datasetFeature, int *i, FEATINPUT datarep_discfeature[]);
void predictData(int *datasetPercentage, FEATINPUT *datasetFeature, int *datasetOutput, FEATINPUT *datarep_discfeat, double pcond_discrete_normal[][MAXDATAREP],  double pcond_discrete_altered[][MAXDATAREP], double mean[][2], double variance[][2], double pprior_semendiag[], int matched[], int confusionMatrix[], double *errorprob_dataset);
void geterror(int *predictedY, int *output, int *trainingpercentage,double *errorprob_dataset);
void confMatrixFunc(int *predictedY, int *output, int *matrix, int *datasetPercentage);
void printConfusionMatrix(char *setName, int *datasetPercentage, int *confusionMatrix, double *errorprob_dataset);
// void getPlot(double *EPtraining,double *EPtesting);