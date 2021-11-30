#include <stdio.h>
#include "naiveBayes.h"

void confMatrixFunc(int *predictedY, int *output, int *matrix, int *datasetPercentage)
{
    matrix[0] = 0;
    matrix[1] = 0;
    matrix[2] = 0;
    matrix[3] = 0;

    for(int i=0;i<=(*datasetPercentage-1);i++)
    {
        if(predictedY[i]==0 && output[i]==0)// True Negative 
        {
            matrix[0] += 1;
        }
        else if (predictedY[i]==1 && output[i]==1) // True Positive 
        {
            matrix[1] += 1;
        }
        else if (predictedY[i]==0 && output[i]==1) // False Negative 
        {
            matrix[2] += 1;
        }
        else if (predictedY[i]==1 && output[i]==0) // False Positive 
        {
             matrix[3] += 1;
        }
    }
}

void printConfusionMatrix(char *setName, int *datasetPercentage, int *confusionMatrix, double *errorprob_dataset)
{
    printf(BOLDBLACK "\n\nConfusion Matrix for %d %s set",*datasetPercentage,setName);
    printf("" RESET);
    printf("\nTrue Positive  : %d \nFalse Positive : %d \nTrue Negative  : %d \nFalse Negative : %d ", confusionMatrix[0],confusionMatrix[1],confusionMatrix[2],confusionMatrix[3]);
    printf("\n-------------------");
    printf("\nError probability: %lf",*errorprob_dataset);
}