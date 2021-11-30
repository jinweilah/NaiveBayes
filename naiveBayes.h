#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define DISCFEATNUM 7
#define MAXDATAREP 5
#define NORMAL 0
#define ALTERED 1
#define PI 3.141592
#define BOLDBLACK "\033[1m\033[30m" //black print colour
#define BOLDGREEN "\033[1m\033[32m" //green print colour
#define BOLDRED "\033[1m\033[31m"   //red print colour
#define RESET "\033[0m"             //reset print colour

typedef struct 
{
    float f1;
    float f2;
    int f3;
    int f4;
    int f5;
    int f6;
    float f7;
    int f8;
    float f9;
} FEATINPUT;

void readText(FEATINPUT *trainingFeature, int *trainingOutput, FEATINPUT *testingFeature, int *testingOutput, int *trainingPercentage, int *testingPercentage);
void trainData(int *trainingPercentage, FEATINPUT *trainingFeature, int *trainingOutput, double mean[][2], double variance[][2], FEATINPUT *datarep_discfeat, double pcond_discrete_normal[][MAXDATAREP], double pcond_discrete_altered[][MAXDATAREP], double pprior_semendiag[], int p_semendiagtotal[], int matched[]);
void condprob_firstloop(FEATINPUT *datarep_discfeat, double pcond_discrete_normal[][MAXDATAREP], double pcond_discrete_altered[][MAXDATAREP], FEATINPUT *trainingFeature,int *trainingOutput, int *i, int p_semendiagtotal[], double mean[][2], int matched[]);
void condprob_secondloop(double mean[][2], double variance[][2], int *i, FEATINPUT *trainingFeature, int *trainingOutput);
void laplace(double pcond_discrete[][MAXDATAREP], int pcond_rownum, int datarep_colnum, int p_semendiagtotal[], int normOrAlt);
void nozeroprob(double pcond_discrete[][MAXDATAREP], int pcond_rownum, int datarep_colnum, int p_semendiagtotal[], int normOrAlt);
void predictData(int *datasetPercentage, FEATINPUT *datasetFeature, int *datasetOutput, FEATINPUT *datarep_discfeat, double pcond_discrete_normal[][MAXDATAREP],  double pcond_discrete_altered[][MAXDATAREP], double mean[][2], double variance[][2], double pprior_semendiag[], int matched[], int confusionMatrix[], double *errorprob_dataset);
void match_indicator(int matched[], FEATINPUT *datasetFeature, int *i, FEATINPUT datarep_discfeature[]);
void geterror(int *predictedY, int *output, int *trainingpercentage,double *errorprob_dataset);
void confMatrixFunc(int *predictedY, int *output, int *matrix, int *datasetPercentage);
void printConfusionMatrix(char *setName, int *datasetPercentage, int *confusionMatrix, double *errorprob_dataset);
// void getPlot(double *EPtraining,double *EPtesting);