/* Contador de Números primos
 *
 * Este programa receberá uma série de entradas cujo objetivo
 * é contar a quantidade de números primos ,utilizando até 4 
 * processos diferentes, sendo, portanto, finalizada ao receber
 * o caractere '\n'.
 */

#include <stdio.h>
#include <stdlib.h> //exit()
#include <sys/types.h> //Define pid_t
#include <unistd.h> //Fork
#include <sys/mman.h> //Memory map
#include <sys/wait.h> //Waitpid
#define QNTD_PROCESSOS 4
#define N_NUMBERS 64

int main() {

   pid_t filho[QNTD_PROCESSOS];	
   int qntd_divisores=0, numeros = 0, cont = 0,i =0;
   int c; //Variável que auxilia na leitura dos números
   unsigned long int numb[N_NUMBERS]; //Vetor que armazena os números que serão analisados

   for(cont=0;cont<N_NUMBERS;cont++) //Laço que inicializa o vetor com o caracter '\0' para não ler lixo
   {
      numb[cont] = '\0';
   }

   while (c!='\n' && c!=EOF) //Laço de leitura e armazenamento da entrada
   {
      c = scanf("%ld",&numb[numeros]);
      numeros++;
   } 
   
/*
   //Processos filhos
   for (cont = 0; cont < QNTD_PROCESSOS; cont++)
   {
      filho[cont] = fork();

      if (filho[cont] ==0)
      {
         printf("Estou no processo filho %d\n", cont);
         exit(0);
      }    
   }*/
   for (i = 0; i < numeros-1; i++)
   {
      printf("Os números inseridos são %ld\n",numb[i]);
   }
   

  //scanf("%d %d\n", &x, &y);
  //printf("%d\n", x + 200);
  return 0;
}
