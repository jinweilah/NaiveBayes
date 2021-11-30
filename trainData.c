#include <stdio.h>
#include "naiveBayes.h"

void trainData(int *trainingPercentage, FEATINPUT *trainingFeature, int *trainingOutput, double mean[][2], double variance[][2], FEATINPUT *datarep_discfeat, double pcond_discrete_normal[][MAXDATAREP], double pcond_discrete_altered[][MAXDATAREP], double pprior_semendiag[], int p_semendiagtotal[], int matched[])
{
    /**********************************************************************************
    1. calculate discrete feature 1,3-8 conditional probabilities 
    2. calculate total actual normal and altered outcome
    3. calculate mean for continuous feature 2 and 9
    4. calculate variance for continuous feature 2 and 9
    5. calculate prior probabilities for normal and altered outcome
    **********************************************************************************/

    //counter i, a
    int i,a;

    for(i=0; i<=*trainingPercentage-1;++i)
    {
        //compute conditional probability for first loop
        condprob_firstloop(datarep_discfeat,pcond_discrete_normal,pcond_discrete_altered,trainingFeature,trainingOutput,&i,p_semendiagtotal,mean,matched);
    }
//Check if feature 1 array have any 0 values
    if(pcond_discrete_normal[0][0]==0 || pcond_discrete_normal[0][1]==0 || pcond_discrete_normal[0][2]==0 || pcond_discrete_normal[0][3]==0 || pcond_discrete_altered[0][0]==0 || pcond_discrete_altered[0][1]==0 || pcond_discrete_altered[0][2]==0 || pcond_discrete_altered[0][3]==0)
    {
        // If yes go to laplace smoothing function
        laplace(pcond_discrete_normal,0,4,p_semendiagtotal,NORMAL);
        laplace(pcond_discrete_altered,0,4,p_semendiagtotal,ALTERED);
    }
    else
    {
        // If no go to nozeroprob function to do normal conditional probability calculation 
        nozeroprob(pcond_discrete_normal,0,4,p_semendiagtotal,NORMAL);
        nozeroprob(pcond_discrete_altered,0,4,p_semendiagtotal,ALTERED);
    }
    //Check if feature 3,4 and 5 array have any 0 values
    for(a=1;a<=3;++a)
    {
        if(pcond_discrete_normal[a][0]==0 || pcond_discrete_normal[a][1]==0 || pcond_discrete_altered[a][0]==0 || pcond_discrete_altered[a][1]==0)
        {
            laplace(pcond_discrete_normal,a,2,p_semendiagtotal,NORMAL);
            laplace(pcond_discrete_altered,a,2,p_semendiagtotal,ALTERED);
        }
        else
        {
            nozeroprob(pcond_discrete_normal,a,2,p_semendiagtotal,NORMAL);
            nozeroprob(pcond_discrete_altered,a,2,p_semendiagtotal,ALTERED);
        }
    }
    //Check if feature 6 and 8 array have any 0 values
    for(a=4;a<=6;a+=2)
    {
        if(pcond_discrete_normal[a][0]==0 || pcond_discrete_normal[a][1]==0 || pcond_discrete_normal[a][2]==0 || pcond_discrete_altered[a][0]==0 || pcond_discrete_altered[a][1]==0 || pcond_discrete_altered[a][2]==0)
        {
            laplace(pcond_discrete_normal,a,3,p_semendiagtotal,NORMAL);
            laplace(pcond_discrete_altered,a,3,p_semendiagtotal,ALTERED);
        }
        else
        {
            nozeroprob(pcond_discrete_normal,a,3,p_semendiagtotal,NORMAL);
            nozeroprob(pcond_discrete_altered,a,3,p_semendiagtotal,ALTERED);
        }
    }
    //Check if feature 7 array have any 0 values
    if(pcond_discrete_normal[6][0]==0 || pcond_discrete_normal[6][1]==0 || pcond_discrete_normal[6][2]==0 || pcond_discrete_normal[6][3]==0 || pcond_discrete_normal[6][4]==0 || pcond_discrete_altered[6][0]==0 || pcond_discrete_altered[6][1]==0 || pcond_discrete_altered[6][2]==0 || pcond_discrete_altered[6][3]==0 || pcond_discrete_altered[6][4]==0)
    {
        laplace(pcond_discrete_normal,6,5,p_semendiagtotal,NORMAL);
        laplace(pcond_discrete_altered,6,5,p_semendiagtotal,ALTERED);
    }
    else
    {
        nozeroprob(pcond_discrete_normal,6,5,p_semendiagtotal,NORMAL);
        nozeroprob(pcond_discrete_altered,6,5,p_semendiagtotal,ALTERED);
    }

    //compute mean: divide numerator by denominator to complete cal
    mean[NORMAL][0] /= p_semendiagtotal[NORMAL];   //normal f2
    mean[NORMAL][1] /= p_semendiagtotal[NORMAL];   //normal f9
    mean[ALTERED][0] /= p_semendiagtotal[ALTERED];   //altered f2
    mean[ALTERED][1] /= p_semendiagtotal[ALTERED];   //altered f9

    for(i=0; i<=*trainingPercentage-1;++i)
    {
        //compute conditional probability for second loop
        condprob_secondloop(mean, variance, &i, trainingFeature, trainingOutput);
    }

    /***********************************************************
    1.divide all numerators for mean by total actual outcome
    2. calculate prior probability
    ***********************************************************/

    //compute variance: divide numerator by denominator to complete cal
    variance[NORMAL][0] /= (p_semendiagtotal[NORMAL]-1);   //normal f2
    variance[NORMAL][1] /= (p_semendiagtotal[NORMAL]-1);   //normal f9
    variance[ALTERED][0] /= (p_semendiagtotal[ALTERED]-1);   //altered f2
    variance[ALTERED][1] /= (p_semendiagtotal[ALTERED]-1);   //altered f9

    //cal prior probabilities for normal and altered
    pprior_semendiag[0] = (double) p_semendiagtotal[NORMAL] / *trainingPercentage;
    pprior_semendiag[1] = (double) p_semendiagtotal[ALTERED] / *trainingPercentage;
    
}