#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "naiveBayes.h"

/********************************************************
9 feature/members of struct array:
.f1=Season of analysis
.f2=Age of Analysis
.f3=Childish Disease
.f4=Accident or serious trauma
.f5=Surgical Intervention
.f6=High fevers in last year
.f7=Frequency of alcohol consumption
.f8=Smoking Habit
.f9=Number of hours spent sitting per day

Outcome in output array:
[0]=Semen Diagnosis Normal
[1]=Semen Diagnosis Altered
********************************************************/

/************************************************Navie Bayes Classifier*****************************************************************/

int main()
{
    clock_t start, elapsed;
    float secs;
    start = clock(); //start timing

    FEATINPUT *trainingFeature,*testingFeature;
    int *trainingOutput,*testingOutput;   
    //create dynamic struct array for data representation of discrete feature 1,3-8
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
    //four classes of confusion matrix
    int confusionMatrix[4];
    double errorprob_trainingset, errorprob_testingset; 
    // double trainingerrorprob[5], testingerrorprob[5];

    //start iteration from split 50:50 ratio
    int trainingPercentage = 50;
    int testingPercentage = 50;
    int iteration_set;

    printf("\nNB classifier training...");
    printf(BOLDGREEN "\n\n========= NB Classifier Confusion Matrix =========" RESET);
    //iterate 5 times from 50:50 to 90:10 training:testing
    for(iteration_set = 0;iteration_set<5;++iteration_set)
    {
        double mean[2][2]={0},variance[2][2]={0},pprior_semendiag[2]={0};
        int p_semendiagtotal[2]={0};
        int matched[DISCFEATNUM]={0};   //match algo of discrete 7 feature to compute conditional probabilities and posterior probabiliies
        double pcond_discrete_normal[DISCFEATNUM][MAXDATAREP]={0},pcond_discrete_altered[DISCFEATNUM][MAXDATAREP]={0};

        // dynamically memory allocate for arrays
        trainingFeature = calloc(trainingPercentage, sizeof(FEATINPUT));
        trainingOutput = calloc(trainingPercentage, sizeof(int));
        testingFeature = calloc(testingPercentage, sizeof(FEATINPUT));
        testingOutput = calloc(testingPercentage, sizeof(int));

        readText(trainingFeature, trainingOutput, testingFeature, testingOutput, &trainingPercentage, &testingPercentage);

        //NB classifer training
        trainData(&trainingPercentage, trainingFeature, trainingOutput, mean, variance, datarep_discfeat, pcond_discrete_normal, pcond_discrete_altered, pprior_semendiag, p_semendiagtotal, matched);
        
        predictData(&trainingPercentage, trainingFeature, trainingOutput, datarep_discfeat, pcond_discrete_normal, pcond_discrete_altered, mean, variance, pprior_semendiag, matched, confusionMatrix, &errorprob_trainingset);
        
        //print confusion matrix and error probability for training set
        printConfusionMatrix(trainingName, &trainingPercentage, confusionMatrix, &errorprob_trainingset);
        // trainingerrorprob[iteration_set] = errorprob_trainingset;

        predictData(&testingPercentage, testingFeature, testingOutput, datarep_discfeat, pcond_discrete_normal, pcond_discrete_altered, mean, variance, pprior_semendiag, matched, confusionMatrix, &errorprob_testingset);
        
        //print confusion matrix and error probability for testing set
        printConfusionMatrix(testingName, &testingPercentage, confusionMatrix, &errorprob_testingset);
        // testingerrorprob[iteration_set] = errorprob_testingset;

        //frees the dynamically allocated memory 
        free(trainingFeature);
        free(trainingOutput);
        free(testingFeature);
        free(testingOutput);

        //increment training:testing by 10 for next iteration
        trainingPercentage+=10;
        testingPercentage-=10;
    }
    free(datarep_discfeat);

    elapsed = (clock() - start) * 1000 / CLOCKS_PER_SEC; //end timing(in ms)
    secs = elapsed / 1000.0;                             //convert ms into seconds
    printf("\n\nTime taken: %.2fseconds(%ldms)\n\n", secs, elapsed);

    // getPlot(trainingerrorprob,testingerrorprob);

}
