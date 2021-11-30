#include <stdio.h>
#include "naiveBayes.h"

void trainData(int *trainingPercentage, FEATINPUT *trainingFeature, int *trainingOutput, double mean[][2], double variance[][2], FEATINPUT *datarep_discfeat, double pcond_discrete_normal[][MAXDATAREP], double pcond_discrete_altered[][MAXDATAREP], double pprior_semendiag[], int p_semendiagtotal[], int matched[])
{
    //counter i, j, k
    int i,a;
    //initialize array with all entries to zero

    for(i=0; i<=*trainingPercentage-1;++i)
    {
        condprob_firstloop(datarep_discfeat,pcond_discrete_normal,pcond_discrete_altered,trainingFeature,trainingOutput,&i,p_semendiagtotal,mean,matched);
    }

    if(pcond_discrete_normal[0][0]==0 || pcond_discrete_normal[0][1]==0 || pcond_discrete_normal[0][2]==0 || pcond_discrete_normal[0][3]==0 || pcond_discrete_altered[0][0]==0 || pcond_discrete_altered[0][1]==0 || pcond_discrete_altered[0][2]==0 || pcond_discrete_altered[0][3]==0)
    {
        laplace(pcond_discrete_normal,0,4,p_semendiagtotal,NORMAL);
        laplace(pcond_discrete_altered,0,4,p_semendiagtotal,ALTERED);
    }
    else
    {
        nozeroprob(pcond_discrete_normal,0,4,p_semendiagtotal,NORMAL);
        nozeroprob(pcond_discrete_altered,0,4,p_semendiagtotal,ALTERED);
    }
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

    mean[0][0] /= p_semendiagtotal[0];   //normal f2
    mean[0][1] /= p_semendiagtotal[0];   //normal f9
    mean[1][0] /= p_semendiagtotal[1];   //altered f2
    mean[1][1] /= p_semendiagtotal[1];   //altered f9

    for(i=0; i<=*trainingPercentage-1;++i)
    {
        condprob_secondloop(mean, variance, &i, trainingFeature, trainingOutput);
    }
    variance[0][0] /= (p_semendiagtotal[0]-1);   //normal f2
    variance[0][1] /= (p_semendiagtotal[0]-1);   //normal f9
    variance[1][0] /= (p_semendiagtotal[1]-1);   //altered f2
    variance[1][1] /= (p_semendiagtotal[1]-1);   //altered f9

    pprior_semendiag[0] = (double) p_semendiagtotal[0] / *trainingPercentage;
    pprior_semendiag[1] = (double) p_semendiagtotal[1] / *trainingPercentage;
    
}