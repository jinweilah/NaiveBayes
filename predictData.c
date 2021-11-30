#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "naiveBayes.h"

void predictData(int *datasetPercentage, FEATINPUT *datasetFeature, int *datasetOutput, FEATINPUT *datarep_discfeat, double pcond_discrete_normal[][MAXDATAREP],  double pcond_discrete_altered[][MAXDATAREP], double mean[][2], double variance[][2], double pprior_semendiag[], int matched[], int confusionMatrix[], double *errorprob_dataset)
{
    //1. transformGaussian -> cal z-score then cal standard gaussian
    //2. allocate standard gaussian into 3rd column of p_conditional
    //3. p_posterior=pcond_discrete_normal x 9 features within x p_prior_normal
    //4. diff = p_posterior_normal - p_posterior_altered
    //5. if diff >= 0 then predictedY=normal(0) else(or) predictedY=altered(1)
    //6. predictedY[i] vs output[i]<-actual output
    //7. error probability
    //8. confusion matrix
    int i, m;
    double zscore;
    long double diff;
    int *predictedY = calloc(*datasetPercentage, sizeof(int));
    long double *postprob_normal_train = calloc(*datasetPercentage,sizeof(long double));
    long double *postprob_altered_train = calloc(*datasetPercentage,sizeof(long double));

    for(i=0; i<=*datasetPercentage-1;++i)
    {
        postprob_normal_train[i]=1;
        postprob_altered_train[i]=1;
        match_indicator(matched,datasetFeature,&i,datarep_discfeat); 
   
        for(m=0;m<=DISCFEATNUM-1;++m)
        {
            postprob_normal_train[i]*=pcond_discrete_normal[m][matched[m]];
        }

        for(m=0;m<=DISCFEATNUM-1;++m)
        {
            postprob_altered_train[i]*=pcond_discrete_altered[m][matched[m]];
        }

        zscore = (((datasetFeature+i)->f2- mean[0][0])/(sqrt(variance[0][0])));
        postprob_normal_train[i]*=(1/sqrt(2*PI))*expl(-0.5*pow(zscore,2));
        // printf("\n%lf", zscore);
        zscore = (((datasetFeature+i)->f9- mean[0][1])/(sqrt(variance[0][1])));
        postprob_normal_train[i]*=(1/sqrt(2*PI))*expl(-0.5*pow(zscore,2));
        postprob_normal_train[i]*= pprior_semendiag[0];
                // testing1=postprob_normal_train[i];
                // printf("\nrwoth%d read out %lf", i, testing1);
        
        //ALTERED
        zscore = (((datasetFeature+i)->f2- mean[1][0])/(sqrt(variance[1][0])));
        postprob_altered_train[i]*=(1/sqrt(2*PI))*expl(-0.5*pow(zscore,2));

        zscore = (((datasetFeature+i)->f9- mean[1][1])/(sqrt(variance[1][1])));
        postprob_altered_train[i]*=(1/sqrt(2*PI))*expl(-0.5*pow(zscore,2));
        postprob_altered_train[i]*= pprior_semendiag[1];
        log(postprob_normal_train[i]);
        log(postprob_altered_train[i]);

        diff = postprob_normal_train[i] - postprob_altered_train[i];
        if(diff >= 0)
        {
            predictedY[i]=0;
        }
        else
        {
            predictedY[i]=1;
        }
    }
    geterror(predictedY,datasetOutput,datasetPercentage,errorprob_dataset);
    confMatrixFunc(predictedY,datasetOutput,confusionMatrix,datasetPercentage);

    free(postprob_normal_train);
    free(postprob_altered_train);
    free(predictedY);
}