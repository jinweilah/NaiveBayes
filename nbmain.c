#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "naiveBayes.h"

int main()
{
    clock_t start, elapsed;
    float secs;
    start = clock(); //start record current time 

    FEATINPUT *trainingFeature,*testingFeature;
    int *trainingOutput,*testingOutput;   
    FEATINPUT *datarep_discfeat = calloc(MAXDATAREP, sizeof(FEATINPUT));
    datarep_discfeat[NORMAL].f1=-1;datarep_discfeat[ALTERED].f1=-0.33;datarep_discfeat[2].f1=0.33;datarep_discfeat[3].f1=1;
    datarep_discfeat[NORMAL].f3=0;datarep_discfeat[ALTERED].f3=1;
    datarep_discfeat[NORMAL].f4=0;datarep_discfeat[ALTERED].f4=1;
    datarep_discfeat[NORMAL].f5=0;datarep_discfeat[ALTERED].f5=1;
    datarep_discfeat[NORMAL].f6=-1;datarep_discfeat[ALTERED].f6=0;datarep_discfeat[2].f6=1;
    datarep_discfeat[NORMAL].f7=0.2;datarep_discfeat[ALTERED].f7=0.4;datarep_discfeat[2].f7=0.6;datarep_discfeat[3].f7=0.8;datarep_discfeat[4].f7=1;
    datarep_discfeat[NORMAL].f8=-1;datarep_discfeat[ALTERED].f8=0;datarep_discfeat[2].f8=1;

    static char *trainingName ={"Training"};
    static char *testingName ={"Testing"};  
    int confusionMatrix[4];
    double errorprob_trainingset, errorprob_testingset; 
    // double trainingerrorprob[5], testingerrorprob[5];

    int trainingPercentage = 50;
    int testingPercentage = 50;
    int iteration_set;

    printf("\nNB classifer training...");
    printf(BOLDGREEN "\n\n========= Confusion Matrix NB Classifer =========" RESET);
    for(iteration_set = 0;iteration_set<5;++iteration_set)
    {
        double mean[2][2]={0},variance[2][2]={0},pprior_semendiag[2]={0};
        int p_semendiagtotal[2]={0};
        int matched[DISCFEATNUM]={0};
        double pcond_discrete_normal[DISCFEATNUM][MAXDATAREP]={0},pcond_discrete_altered[DISCFEATNUM][MAXDATAREP]={0};

        // dynamically memory allocate for struct array of size
        trainingFeature = calloc(trainingPercentage, sizeof(FEATINPUT));
        trainingOutput = calloc(trainingPercentage, sizeof(int));
        testingFeature = calloc(testingPercentage, sizeof(FEATINPUT));
        testingOutput = calloc(testingPercentage, sizeof(int));

        readText(trainingFeature, trainingOutput, testingFeature, testingOutput, &trainingPercentage, &testingPercentage);
        trainData(&trainingPercentage, trainingFeature, trainingOutput, mean, variance, datarep_discfeat, pcond_discrete_normal, pcond_discrete_altered, pprior_semendiag, p_semendiagtotal, matched);
        
        predictData(&trainingPercentage, trainingFeature, trainingOutput, datarep_discfeat, pcond_discrete_normal, pcond_discrete_altered, mean, variance, pprior_semendiag, matched, confusionMatrix, &errorprob_trainingset);
        printConfusionMatrix(trainingName, &trainingPercentage, confusionMatrix, &errorprob_trainingset);
        // trainingerrorprob[iteration_set] = errorprob_trainingset;

        predictData(&testingPercentage, testingFeature, testingOutput, datarep_discfeat, pcond_discrete_normal, pcond_discrete_altered, mean, variance, pprior_semendiag, matched, confusionMatrix, &errorprob_testingset);
        printConfusionMatrix(testingName, &testingPercentage, confusionMatrix, &errorprob_testingset);
        // testingerrorprob[iteration_set] = errorprob_testingset;

        free(trainingFeature);
        free(trainingOutput);
        free(testingFeature);
        free(testingOutput);

        trainingPercentage+=10;
        testingPercentage-=10;
    }
    free(datarep_discfeat);

    elapsed = (clock() - start) * 1000 / CLOCKS_PER_SEC; //cal difference between current time and start time(in ms)
    secs = elapsed / 1000.0;                             //convert ms into seconds
    printf("\n\nTime taken: %.2fseconds(%ldms)\n\n", secs, elapsed);

    // getPlot(trainingerrorprob,testingerrorprob);

}
