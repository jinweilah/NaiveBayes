#include <stdio.h>
#include "naiveBayes.h"

void confMatrixFunc(int *predictedY, int *output, int *matrix, int *datasetPercentage)
{
    //predictedY = Predicted Output Array, output = Real Output Array, matrix = Confusion matrix array, datasetPercentage = number of elements in dataset
    matrix[0] = 0; //initialize each element to 0
    matrix[1] = 0; //matrix[0] = True Negative, matrix[1] = True Positive,matrix[2] = False Negative,matrix[3] = False Positive
    matrix[2] = 0;
    matrix[3] = 0;

    for(int i=0;i<=(*datasetPercentage-1);i++) //Determine the confusion matrix for current dataset
    {
        if(predictedY[i]==ALTERED && output[i]==ALTERED)// True Positive
        {
            matrix[1] += 1;
        }
        else if (predictedY[i]==NORMAL && output[i]==NORMAL) // True Negative 
        {
            matrix[0] += 1;
        }
        else if (predictedY[i]==ALTERED && output[i]==NORMAL) // False Positive 
        {
            matrix[3] += 1;
        }
        else if (predictedY[i]==NORMAL && output[i]==ALTERED) // False Negative
        {
             matrix[2] += 1;
        }
    }
}

void printConfusionMatrix(char *setName, int *datasetPercentage, int *confusionMatrix, double *errorprob_dataset)
{
    printf(BOLDBLACK "\n\nConfusion Matrix for %d %s set",*datasetPercentage,setName);  //Print training testing ratio
    printf("" RESET);
    printf("\nTrue Positive  : %d \nTrue Negative : %d \nFalse Positive  : %d \nFalse Negative : %d ", confusionMatrix[1],confusionMatrix[0],confusionMatrix[3],confusionMatrix[2]);
    printf("\n-------------------");
    printf("\nError probability: %lf",*errorprob_dataset); //print error probability for current dataset
}