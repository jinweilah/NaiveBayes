#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "naiveBayes.h"


void getPlot(double *EPtraining,double *EPtesting)
{
    //EPtraining = Error Probability Array which includes all Training error probabilities
    //EPtesting = Error Probability Array which includes all Testing error probabilities

    const char *x[5]; //Create const char x and set values for the x axis of graph
    x[0] = "50:50";
    x[1] = "60:40";
    x[2] = "70:30";
    x[3] = "80:20";
    x[4] = "90:10";
    FILE *fp = NULL; //Initialize file pointer for temporary data file
    FILE *gnupipe = NULL; //Initialize file pointer for gnuplot commands

    //gnu plot commands(set y axis range, set x axis label, set y axis label, set title,plot exact Training points,plot exact Testing axis points, plot Training line,plot Testing line)
    const char *GnuCommands [] = {"set yrange[0:1]","set xlabel\"Split Ratio training:testing\"","set ylabel\"Error Probability\"","set title\"Error Probability chart\"","plot 'data.tmp'using 1:2:xticlabels(1) title 'Training Points' ,'data.tmp'using 1:3:xticlabels(1) title 'Testing Points' ,'data.tmp' using 1:2 title 'Training' with lines lc rgb '#00008B',\'data.tmp' using 1:3 title 'Testing' with lines lc rgb 'red'"};

    //set file pointer to data.tmp and command line
    fp = fopen("data.tmp","w");
    gnupipe = _popen("gnuplot -persistent","w" );

    //print Error probability values to temporay file data.tmp
    fprintf(fp,"Ratio Training Testing\n");

    for(int i=0; i <5;i++)
    {
        float y1 = EPtraining[i];
        float y2 = EPtesting[i];
        fprintf(fp,"%s %f %f\n",x[i],y1,y2);

        
    }

    //print commands to command line to run gnuplot
    for(int i = 0; i<5 ; i++)
    {
        fprintf(gnupipe,"%s\n",GnuCommands[i]);
    }

}