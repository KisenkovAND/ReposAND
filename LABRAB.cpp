#include <iostream>
#include <stdio.h>
double lr (const double *input, const unsigned int n, const double *coefsA ,const unsigned int m, unsigned int  outputNumb, unsigned short& error, const double *Conds, const bool initCond=1 , const bool overLims=1)
{
    unsigned int buffSize=(++outputNumb)<m?m:outputNumb;
    if (!initCond && outputNumb<m) { error=1; return 0; }
    if (!overLims && outputNumb>n) { error=2; return 0; }
    double *x=new double [buffSize]; double y=0;
    if (initCond) for (unsigned int i=0; i<m-1 ;i++) x[i]=Conds[i];
    for (unsigned int i=0; i<outputNumb; i++)
    {
        for(int j=static_cast<int>(buffSize)-1; j>=0; j--) x[j]=x[j-1];
        if (i<n) x[0]=input[i]; else x[0]=0;
    }
    for(unsigned int j=0; j<m; j++) y+=coefsA[j]*x[j];
    return y;
}
int main()
{
    unsigned short error=0;
    const bool initCond=0; const bool overLims=0; //значения 1 или 0 как тру или фолс включаем или выключаем условия иск ситуации
    const unsigned int n=6; const unsigned int m=4;
    double *input=new double [n]; input[0]=2; input[1]=7; input[2]=4; input[3]=2; input[4]=5; input[5]=6;
    double *coefsA=new double [m]; coefsA[0]=7; coefsA[1]=-2; coefsA[2]=8; coefsA[3]=-5;
    double *Conds=new double [m-1]; Conds[0]=0.2; Conds[1]=4; Conds[2]=0.9;
    const unsigned int outputNumb=7;
    printf ("\nResult: %5.2f", lr(input, n, coefsA, m, outputNumb, error, Conds ,initCond, overLims));
    if (error==1) printf("\nIncorrect initial conditionals");// неверные начальные условия
    if (error==2) printf("\nInput is too small");// входное значение мало
    return 0;
}
