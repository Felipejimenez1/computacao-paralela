#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS    20

void *inicializa(void *p);
pthread_mutex_t valor = PTHREAD_MUTEX_INITIALIZER;
double pi=0,p16=1;int k=0;
float sumvalue=0,sum=0;

void *funcao_pi(void * p){
    int rc;
    int k=(int)p;
    sumvalue += 1.0/p16 * (4.0/(8* k + 1) - 2.0/(8*k + 4) - 1.0/(8*k + 5) - 1.0/(8*k+6));
    pthread_mutex_lock( &valor );
    p16 *=16;
    rc=pthread_mutex_unlock( &valor );
    pthread_exit(&sumvalue); 
}


int main()
{
    pthread_t threads[NUM_THREADS];
    int i1;  
    int i;
    pthread_mutex_init(&valor, NULL);

    for(i=0;i<NUM_THREADS;i++){
        i1= pthread_create(&threads[i],NULL,funcao_pi,(int *) i);
        }

    for(i=0;i<NUM_THREADS;i++){
        i1=pthread_join(threads[i],&sumvalue);
        pi=pi+sumvalue;

    }

    printf("O valor de pi é  : %f\n",pi);

    exit(0);
}

