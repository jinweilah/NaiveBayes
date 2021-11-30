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
        postprob_normal_train[i]=1;     //initilize posterior probability to 1
        postprob_altered_train[i]=1;    

        //call match indicator for computation of posterior probability for the current patient's row iterated
        match_indicator(matched,datasetFeature,&i,datarep_discfeat); 
   
        //iterate all matched conditional probabilities for 7 discrete feature
        for(m=0;m<=DISCFEATNUM-1;++m)
        {
            //computing posterior probalility prediction for matched 7 discrete feature into posterior prob array for normal
            postprob_normal_train[i]*=pcond_discrete_normal[m][matched[m]];
        }

        for(m=0;m<=DISCFEATNUM-1;++m)
        {
            //computing posterior probalility prediction for matched 7 discrete feature into posterior prob array for normal
            postprob_altered_train[i]*=pcond_discrete_altered[m][matched[m]];
        }

        /* Using standard gaussian distribution to get conditional probability of feature 2 (Normal) */
        zscore = (((datasetFeature+i)->f2- mean[NORMAL][0])/(sqrt(variance[NORMAL][0])));
        /* Multipy in the feature 2 (Normal) conditional probability into the posterior probability (Normal) */
        postprob_normal_train[i]*=(1/sqrt(2*PI))*expl(-0.5*pow(zscore,2));
        /* Using standard gaussian distribution to get conditional probability of feature 9 (Normal) */       
        zscore = (((datasetFeature+i)->f9- mean[NORMAL][1])/(sqrt(variance[NORMAL][1])));
        /* Multipy in the feature 9 (Normal) conditional probability into the posterior probability (Normal) */
        postprob_normal_train[i]*=(1/sqrt(2*PI))*expl(-0.5*pow(zscore,2));

        /* Multipy in the Normal prior probability into the posterior probability (Normal) */
        postprob_normal_train[i]*= pprior_semendiag[NORMAL];

        /* Using standard gaussian distribution to get conditional probability of feature 2 (Altered) */
        zscore = (((datasetFeature+i)->f2- mean[ALTERED][0])/(sqrt(variance[ALTERED][0])));
        /* Multipy in the feature 2 (Altered) conditional probability into the posterior probability (Altered) */
        postprob_altered_train[i]*=(1/sqrt(2*PI))*expl(-0.5*pow(zscore,2));
        /* Using standard gaussian distribution to get conditional probability of feature 9 (Altered) */
        zscore = (((datasetFeature+i)->f9- mean[ALTERED][1])/(sqrt(variance[ALTERED][1])));
        /* Multipy in the feature 9 (Altered) conditional probability into the posterior probability (Altered) */
        postprob_altered_train[i]*=(1/sqrt(2*PI))*expl(-0.5*pow(zscore,2));

        /* Multipy in the Altered prior probability into the posterior probability (Altered) */
        postprob_altered_train[i]*= pprior_semendiag[ALTERED];

        /* Log base e the posterior probability to prevent underflow for Normal and Altered */
        log(postprob_normal_train[i]);
        log(postprob_altered_train[i]);

        /* Compare the difference of posterior probability for Normal and Altered */
        diff = postprob_normal_train[i] - postprob_altered_train[i];

        /* If difference more than or equal to 0 put value 0 into the predictedY array else put value 1 */
        if(diff >= 0)
        {
            predictedY[i]=0;
        }
        else
        {
            predictedY[i]=1;
        }
    }

    /* Go to geterror function to get the error probability */
    geterror(predictedY,datasetOutput,datasetPercentage,errorprob_dataset);

    /* Go to confMatrixFunc function get get the confusion matrix table */
    confMatrixFunc(predictedY,datasetOutput,confusionMatrix,datasetPercentage);
    
    /* Free the calloc allocated memory */
    free(postprob_normal_train);
    free(postprob_altered_train);
    free(predictedY);
}