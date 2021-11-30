#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "naiveBayes.h"


// void getPlot(double *EPtraining,double *EPtesting)
// {

//     //float x[] = {50.50f,60.40f,70.30f,80.30f,90.30f};
//     const char *x[5];
//     x[0] = "50:50";
//     x[1] = "60:40";
//     x[2] = "70:30";
//     x[3] = "80:20";
//     x[4] = "90:10";
//     FILE *fp = NULL;
//     FILE *gnupipe = NULL;
//     char *GnuCommands [] = {"set yrange[0:1]","set xlabel\"Split Ratio training:testing\"","set ylabel\"Error Probability\"","set title\"Error probability chart\"","plot 'data.tmp'using 1:2:xticlabels(1) title 'Training Points','data.tmp'using 1:3:xticlabels(1) title 'Testing Points' ,'data.tmp' using 1:2 title 'Training' with lines lc rgb '#00008B',\'data.tmp' using 1:3 title 'Testing' with lines lc rgb 'red'"};

//     fp = fopen("data.tmp","w");
//     gnupipe = _popen("gnuplot -persistent","w" );

//     fprintf(fp,"Ratio Training Testing\n");

//     for(int i=0; i <5;i++)
//     {
//         float y1 = EPtraining[i];
//         float y2 = EPtesting[i];
//         fprintf(fp,"%s %f %f\n",x[i],y1,y2);
//         //printf("errorprob: %lf\n",y);

        
//     }

//     for(int i = 0; i<5 ; i++)
//     {
//         fprintf(gnupipe,"%s\n",GnuCommands[i]);
//     }

// }