/*

**************************************

* Aluno: 
Felipe Jimenez Clauzet - TIA: 41924711


* Exercicio:  Paralelismo e arrays
1)  Crie um programa em C que multiplica todos os elementos de um array por 4 ou por um valor fornecido pelo usuário;

**************************************

*/
#include "stdio.h"
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<ctype.h>
#include<string.h>
#include<sys/shm.h>
#include<signal.h>

int main(void) {

  int mem_compartilhada_id =shmget(IPC_PRIVATE, 10*sizeof(int), IPC_CREAT | 0666); //cria memoria compartilhada
  int* vetor_compartilhado = (int*)shmat(mem_compartilhada_id, NULL, 0);
  vetor_compartilhado[0] =2;
  vetor_compartilhado[1] =86;
  vetor_compartilhado[2] =1;
  vetor_compartilhado[3] =7;
  vetor_compartilhado[4] =4;
  vetor_compartilhado[5] =12;

  printf("array: ");
  printf("%d, ", vetor_compartilhado[0]);
  printf("%d, ", vetor_compartilhado[1]);
  printf("%d, ", vetor_compartilhado[2]);
  printf("%d, ", vetor_compartilhado[3]);
  printf("%d  \n", vetor_compartilhado[4]);

  
  pid_t processo_filho = fork();
  
  if(processo_filho==0){
    vetor_compartilhado[0] *=4;
    vetor_compartilhado[1] *=4;
    vetor_compartilhado[2] *=4;
    exit(0);
  }
  else{
    while(!SIGCHLD);   
    sleep(1);
    vetor_compartilhado[3] *=4;
    vetor_compartilhado[4] *=4;
    }
  
  printf("array apos a multiplicacao: ");
  printf("%d, ", vetor_compartilhado[0]);
  printf("%d, ", vetor_compartilhado[1]);
  printf("%d, ", vetor_compartilhado[2]);
  printf("%d, ", vetor_compartilhado[3]);
  printf("%d ", vetor_compartilhado[4]);
return 0;
}
