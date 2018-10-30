//
//  main.c
//  TreeParityMachineSync
//
//  Created by micha
//

//global sizers
#define L 3 //abs(weight range)
#define N 5 //weights per hidden neuron (range {-L..L})
#define K 5 //hidden neurons

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//prototypes
int p_run(int machine,int perceptron,int *in);
void p_learn(int machine, int perceptron,int *in,int tau);
int t_run(int machine,int **in);
void t_learn(int machine,int **in,int tau);
int diff(int machine1, int machine2);
void printweights(int machine);
int **geninput(void);

// dynamic allocation
int ***weights; //weights[2 machines][K perceptrons][N weights]
int **input;    //input[K perceptrons][N weights] (range {-1,1})

int main(int argc, const char * argv[])
{
    int i,j;
    int tau1,tau2,runs;
    
    // dynamic allocation
    weights=(int***)malloc(sizeof(int**)*2);    // 2 machines
    weights[0]=(int**)malloc(sizeof(int*)*K);   // K perceptrons per machine
    weights[1]=(int**)malloc(sizeof(int*)*K);
    input=(int**)malloc(sizeof(int*)*K);        // K perceptrons per random input
    for(i=0;i<K;i++)
    {
        weights[0][i]=(int*)malloc(sizeof(int)*N);  //N weights per perceptron
        weights[1][i]=(int*)malloc(sizeof(int)*N);
        input[i]=(int*)malloc(sizeof(int)*N);       //N weights per random input
    }
    
    //randomize 2x K vectors with N weights each in range {-L..L}
    srand(2); // STATIC SEED: change me
    
    for(i=0;i<K;i++)
        for(j=0;j<N;j++)
        {
            weights[0][i][j]=rand()%((2*L)+1)-L;
            weights[1][i][j]=rand()%((2*L)+1)-L;
        }

    for(runs=0;runs<10000;runs++)
    {
        geninput(); //gen random input
        
        tau1=t_run(0,input); //feed input into machine 0
        tau2=t_run(1,input); //feed input into machine 1
        
        if(tau1==tau2) //output parity equal?
        {
            t_learn(0,input,tau1); //learn input on machine 0
            t_learn(1,input,tau1); //learn input on machine 1
        }
        
        if(diff(0,1)==0) //done?
        {
            printweights(0);
            printweights(1);
            printf("--- %d %d ---\n",tau1,tau2);
            
            printf("%d iterations.\n",runs);
            break;
        }
    }

    printf("%d\n",1!=1);
    puts("ok.");
    return 0;
}



//tree parity machine functions
int t_run(int machine,int **in)
{
    int perceptron,o=1;
    
    for(perceptron=0;perceptron<K;perceptron++)
    {
        int t=p_run(machine,perceptron,in[perceptron]);
        o=o*t;
    }
    
    return o;
}

void t_learn(int machine,int **in,int tau)
{
    int perceptron;
    for(perceptron=0;perceptron<K;perceptron++)
    {
        p_learn(machine,perceptron,in[perceptron],tau);
    }
}

//perceptron functions
int p_run(int machine,int perceptron,int *in)
{
    int weight,t,o=1;
    for(weight=0;weight<N;weight++)
    {
        t=weights[machine][perceptron][weight] * in[weight];
        o=o+t;
    }
    
    return o>0 ? 1 : -1; //return signum (parity in our notion)
}

void p_learn(int machine, int perceptron,int *in,int tau)
{
    int weight;
    int o=p_run(machine,perceptron,in);
    
    if(o==tau)
        for(weight=0;weight<N;weight++)
        {
            weights[machine][perceptron][weight]=weights[machine][perceptron][weight] + (in[weight]) * tau;
            
            if(weights[machine][perceptron][weight]>L)
                weights[machine][perceptron][weight]=L;
            
            if(weights[machine][perceptron][weight]<(-L))
                weights[machine][perceptron][weight]=(-L);
        }
}

//main loop helpers
int diff(int machine1, int machine2)
{
    int perceptron,weight,d=0;
    
    for(perceptron=0;perceptron<K;perceptron++)
        for(weight=0;weight<N;weight++)
        {
            d+=abs(weights[machine1][perceptron][weight]-weights[machine2][perceptron][weight]);
        }
    
    return d;
}

void printweights(int machine)
{
    int perceptron,weight;
    
    for(perceptron=0;perceptron<K;perceptron++)
        for(weight=0;weight<N;weight++)
            printf("%s%1d ",weights[machine][perceptron][weight]>0?"+":"",weights[machine][perceptron][weight]);
    puts("");
}

int **geninput(void)
{
    int perceptron,weight;
    for(perceptron=0;perceptron<K;perceptron++)
        for(weight=0;weight<N;weight++)
        {
            input[perceptron][weight]=rand()%2==0?1:-1;
            input[perceptron][weight]=rand()%2==0?1:-1;
        }
    return input;
}
