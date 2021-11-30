#include <stdio.h>
#include <stdlib.h>
#include "naiveBayes.h"

void readText(FEATINPUT *trainingFeature, int *trainingOutput, FEATINPUT *testingFeature, int *testingOutput, int *trainingPercentage, int *testingPercentage)
{
    // Declaration of file paths
    FILE *fertility_diagnosis_file;
    const char *filename="fertility_Diagnosis_Data_Group1_4.txt";
    fertility_diagnosis_file = fopen(filename, "r");
    int i;

    if(fertility_diagnosis_file == NULL)
    {
        printf("\nFile is not found\n");
        exit(-1);
    }
    
    for(i=0;i<=*trainingPercentage-1;++i)
    {
       fscanf(fertility_diagnosis_file,"%f, %f, %d ,%d, %d, %d, %f ,%d, %f, %d", &(trainingFeature+i)->f1,&(trainingFeature+i)->f2,&(trainingFeature+i)->f3,&(trainingFeature+i)->f4,&(trainingFeature+i)->f5,&(trainingFeature+i)->f6,&(trainingFeature+i)->f7,&(trainingFeature+i)->f8,&(trainingFeature+i)->f9,&trainingOutput[i]);
    }
    for(i=0;i<=*testingPercentage-1;++i)
    {
       fscanf(fertility_diagnosis_file,"%f, %f, %d ,%d, %d, %d, %f ,%d, %f, %d", &(testingFeature+i)->f1,&(testingFeature+i)->f2,&(testingFeature+i)->f3,&(testingFeature+i)->f4,&(testingFeature+i)->f5,&(testingFeature+i)->f6,&(testingFeature+i)->f7,&(testingFeature+i)->f8,&(testingFeature+i)->f9,&testingOutput[i]);
    }
    fclose(fertility_diagnosis_file);

    // for(i=0;i<=*trainingPercentage-1;++i)
    // {
    //     printf("\n%f\t%f\t%d\t%d\t%d\t%d\t%f\t%d\t%f\t%d\t", (trainingFeature+i)->f1,(trainingFeature+i)->f2,(trainingFeature+i)->f3,(trainingFeature+i)->f4,(trainingFeature+i)->f5,(trainingFeature+i)->f6,(trainingFeature+i)->f7,(trainingFeature+i)->f8,(trainingFeature+i)->f9,trainingOutput[i]);
    // }
}