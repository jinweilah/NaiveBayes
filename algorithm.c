#include <stdio.h>
#include <math.h>
#include "naiveBayes.h"

void condprob_firstloop(FEATINPUT *datarep_discfeat, double pcond_discrete_normal[][MAXDATAREP], double pcond_discrete_altered[][MAXDATAREP], FEATINPUT *trainingFeature,int *trainingOutput, int *i, int p_semendiagtotal[], double mean[][2], int matched[])
{
    //1. counted all numerators for discrete features 
    //2. sum all numerators for prior probability - p_semendiagtotal
    //3. sum all numerators for mean 
    int m;
    
    match_indicator(matched,trainingFeature,i,datarep_discfeat);

    if (trainingOutput[*i]==NORMAL)
    {
        for(m=0;m<=DISCFEATNUM-1;++m)
        {
            pcond_discrete_normal[m][matched[m]]+=1;
        }
        p_semendiagtotal[0]+=1;
        
        mean[0][0] += (trainingFeature+*i)->f2;
        mean[0][1] += (trainingFeature+*i)->f9;
    }
    else    //==ALTERED
    {
        for(m=0;m<=DISCFEATNUM-1;++m)
        {
            pcond_discrete_altered[m][matched[m]]+=1;
        }
        p_semendiagtotal[1]+=1;
        mean[1][0] += (trainingFeature+*i)->f2;
        mean[1][1] += (trainingFeature+*i)->f9;
    }
}

void condprob_secondloop(double mean[][2], double variance[][2], int *i, FEATINPUT *trainingFeature, int *trainingOutput)
{
    //1. divide all numerators for discrete features by p_semendiagtotal
    //2. divide all numerators for mean by p_semendiagtotal
    //3. calculate prior probability -> p_prior_semdiag=p_semendiagtotal/trainingPercentage
    //4. calculate variance

    if (trainingOutput[*i]==NORMAL)
    {
        variance[0][0] += pow(((trainingFeature+*i)->f2 - mean[0][0]), 2);
        variance[0][1] += pow(((trainingFeature+*i)->f9 - mean[0][1]), 2);
    }
    else    //==ALTERED
    {
        variance[1][0] += pow(((trainingFeature+*i)->f2 - mean[1][0]), 2);
        variance[1][1] += pow(((trainingFeature+*i)->f9 - mean[1][1]), 2);
    }
}

void match_indicator(int matched[], FEATINPUT *datasetFeature, int *i, FEATINPUT *datarep_discfeat)
{
    int d_indicator=0;
    int matched_all=0;
    int check_match[DISCFEATNUM]={0};

    //check against datarep
    while(matched_all<=DISCFEATNUM-1)
    {
        //datasetFeature[rownumofsize].f1==discfeature_datarep[datarep->e.g. w,s,s,f].f1
        if (check_match[0]==0 && (datasetFeature+*i)->f1==(datarep_discfeat+d_indicator)->f1)
        {
            matched[0]=d_indicator;
            check_match[0]+=1;
            matched_all+=1;
        }
        if (check_match[1]==0 && (datasetFeature+*i)->f3==(datarep_discfeat+d_indicator)->f3)
        {
            matched[1]=d_indicator;
            check_match[1]+=1;
            matched_all+=1;
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
        d_indicator+=1;
    }
}

void laplace(double pcond_discrete[][MAXDATAREP], int pcond_rownum, int datarep_colnum, int p_semendiagtotal[], int normOrAlt)
{
    int n;
    for(n=0;n<=(datarep_colnum-1);++n)
    {
        pcond_discrete[pcond_rownum][n]=(pcond_discrete[pcond_rownum][n]+1)/(p_semendiagtotal[normOrAlt]+datarep_colnum);
    }
}

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