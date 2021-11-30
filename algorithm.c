#include <stdio.h>
#include <math.h>
#include "naiveBayes.h"

//conditional probability first loop
void condprob_firstloop(FEATINPUT *datarep_discfeat, double pcond_discrete_normal[][MAXDATAREP], double pcond_discrete_altered[][MAXDATAREP], FEATINPUT *trainingFeature,int *trainingOutput, int *i, int p_semendiagtotal[], double mean[][2], int matched[])
{
    /***************************************************************
    1. counted all numerators for discrete feature 1,3-8 conditional probabilities 
    2. sum all numerators for prior probability - p_semendiagtotal
    3. sum all numerators for mean
    ***************************************************************/

    int m;  //counter m
    
    //call match_indicator
    match_indicator(matched,trainingFeature,i,datarep_discfeat);

    if (trainingOutput[*i]==NORMAL)
    {
        for(m=0;m<=DISCFEATNUM-1;++m)   //for 7 discrete feature conditional probabilities
        {
            /*count all 7 matched discrete feature of current patient's row iterated which are NORMAL in conditional prob array*/
            pcond_discrete_normal[m][matched[m]]+=1;    
        }

        p_semendiagtotal[NORMAL]+=1;     //cal total actual normal outcome
        
        mean[NORMAL][0] += (trainingFeature+*i)->f2;    //sum mean numerator for feature 2 normal
        mean[NORMAL][1] += (trainingFeature+*i)->f9;    //sum mean numerator for feature 9 normal
    }
    else    //==ALTERED
    {
        for(m=0;m<=DISCFEATNUM-1;++m)
        {
            /*count all 7 matched discrete feature of current patient's row iterated which are ALTERED in conditional prob array*/
            pcond_discrete_altered[m][matched[m]]+=1; 
        }

        p_semendiagtotal[ALTERED]+=1;    //cal total actual normal outcome

        mean[ALTERED][0] += (trainingFeature+*i)->f2;   //sum mean numerator for feature 2 altered
        mean[ALTERED][1] += (trainingFeature+*i)->f9;   //sum mean numerator for feature 9 altered
    }
}

//conditional probability second loop
void condprob_secondloop(double mean[][2], double variance[][2], int *i, FEATINPUT *trainingFeature, int *trainingOutput)
{
    /*calculate sum of all numerators for variance*/

    if (trainingOutput[*i]==NORMAL)
    {
        variance[NORMAL][0] += pow(((trainingFeature+*i)->f2 - mean[NORMAL][0]), 2);
        variance[NORMAL][1] += pow(((trainingFeature+*i)->f9 - mean[NORMAL][1]), 2);
    }
    else    //==ALTERED
    {
        variance[ALTERED][0] += pow(((trainingFeature+*i)->f2 - mean[ALTERED][0]), 2);
        variance[ALTERED][1] += pow(((trainingFeature+*i)->f9 - mean[ALTERED][1]), 2);
    }
}

void match_indicator(int matched[], FEATINPUT *datasetFeature, int *i, FEATINPUT *datarep_discfeat)
{
    int d_indicator=0;
    int matched_all=0;
    int check_match[DISCFEATNUM]={0};

    //check if all 7 matches are found for discrete feature 1,3-8
    while(matched_all<=DISCFEATNUM-1)
    {
        //check if match is done already //check if training/testing dataset each patient's 7 feature match with data rep struct array
        if (check_match[0]==0 && (datasetFeature+*i)->f1==(datarep_discfeat+d_indicator)->f1)
        {
            matched[0]=d_indicator;     //store index of feature data rep
            check_match[0]+=1;          //matched f1 for if condition
            matched_all+=1;             //matched f1 for total counting while loop
        }
        if (check_match[1]==0 && (datasetFeature+*i)->f3==(datarep_discfeat+d_indicator)->f3)
        {
            matched[1]=d_indicator;     //store index of feature data rep
            check_match[1]+=1;          //matched f2 for if condition
            matched_all+=1;             //matched f2 for total counting while loop
        }
        if (check_match[2]==0 && (datasetFeature+*i)->f4==(datarep_discfeat+d_indicator)->f4)
        {
            matched[2]=d_indicator;
            check_match[2]+=1;
            matched_all+=1;
        }
        if (check_match[3]==0 && (datasetFeature+*i)->f5==(datarep_discfeat+d_indicator)->f5)
        {
            matched[3]=d_indicator;
            check_match[3]+=1;
            matched_all+=1;
        }
        if (check_match[4]==0 && (datasetFeature+*i)->f6==(datarep_discfeat+d_indicator)->f6)
        {
            matched[4]=d_indicator;
            check_match[4]+=1;
            matched_all+=1;
        }
        if (check_match[5]==0 && (datasetFeature+*i)->f7==(datarep_discfeat+d_indicator)->f7)
        {
            matched[5]=d_indicator;
            check_match[5]+=1;
            matched_all+=1;
        }
        if (check_match[6]==0 && (datasetFeature+*i)->f8==(datarep_discfeat+d_indicator)->f8)
        {
            matched[6]=d_indicator;
            check_match[6]+=1;
            matched_all+=1;
        }
        d_indicator+=1;     //iterating data rep struct array for matching
    }
}
/* Laplace smoothing function where we add 1 to everything for normal and divide by the total number of normal plus the number of 1s added in to get the conditional probability*/
/* Repeat for altered also */
void laplace(double pcond_discrete[][MAXDATAREP], int pcond_rownum, int datarep_colnum, int p_semendiagtotal[], int normOrAlt)
{
    int n;
    for(n=0;n<=(datarep_colnum-1);++n)
    {
        pcond_discrete[pcond_rownum][n]=(pcond_discrete[pcond_rownum][n]+1)/(p_semendiagtotal[normOrAlt]+datarep_colnum);
    }
}
/* Normal conditional probability method */
void nozeroprob(double pcond_discrete[][MAXDATAREP], int pcond_rownum, int datarep_colnum, int p_semendiagtotal[], int normOrAlt)
{
    int n;
    for(n=0;n<=(datarep_colnum-1);++n)
    {
        pcond_discrete[pcond_rownum][n]=pcond_discrete[pcond_rownum][n]/p_semendiagtotal[normOrAlt];
    }
}

void geterror(int *predictedY, int *output, int *trainingpercentage, double *errorprob_dataset)
{
    *errorprob_dataset = 0;
    for(int i=0;i<=(*trainingpercentage-1);i++)
    {
        if(predictedY[i]!=output[i])
        {
             *errorprob_dataset += 1;
        }
    }
    *errorprob_dataset /= *trainingpercentage;
}