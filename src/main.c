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

unsigned long int ver_primo(unsigned long int Num) //Essa função retorna o número 1 se o número é primo, e 0 caso contrário
{
   int qntd_divisores = 0, div = 0;
   if (Num==0) qntd_divisores = 0;
   else if (Num==1) qntd_divisores = 0;
   else 
   {
      for (unsigned int j = 2; j <= Num/2; j++) //Laço que verifica se cada número é primo.
      {
         if (Num%j==0)
         {
            qntd_divisores++;
            break;
         }  
      }
      if (qntd_divisores==0)
         {
            div++;
         } else
         {
            //printf("O número %ld não é primo\n", Num);
            qntd_divisores = 0;      
         }
   } 
      return div;
}

int main() {

   pid_t filho[QNTD_PROCESSOS];	
   int numeros = 0, cont = 0, j =0,qntd_primos=0; //Variáveis auxiliares
   char c; //Variável que auxilia na leitura dos números
   unsigned int numb[N_NUMBERS]; //Vetor que armazena os números que serão analisados

   //Definição de flags para proteção e visibilidade de memória 
   int protection = PROT_READ | PROT_WRITE ;
   int visibility = MAP_SHARED | MAP_ANON ;
   
   int *numPrimos; // Ponteiro que será o vetor de armazenamento se há ou não números primos
   numPrimos = (int *) mmap(NULL,sizeof(int)*64,protection,visibility,0,0); 

   for(cont=0;cont<N_NUMBERS;cont++) //Laço que inicializa o vetor com o caracter '\0' para não ler lixo
   {
      numb[cont] = '\0';
      numPrimos[cont] = '\0';
   }
    //Laço de leitura e armazenamento da entrada
   while ((c!='\n') && (c!=EOF)) 
   {
      c = scanf("%u",&numb[numeros]);
      numeros++;
   } 
   //Processos paralelos que armazenam a quantidade de números primos
   for (cont = 0; cont < QNTD_PROCESSOS; cont++)
   {
      filho[cont] = fork();
      if (filho[cont] ==0)
      {   
         for(int k = 0; cont+k < numeros-1; k += QNTD_PROCESSOS)
         {
            numPrimos[cont] +=ver_primo(numb[cont+k]);
         }
         exit(0);       
      }  
   }
   //Laço que finaliza os processos iniciados
   for(cont=0;cont<QNTD_PROCESSOS;cont++) waitpid(filho[cont],NULL,0);
  
   for (j = 0; j < numeros-1; j++) qntd_primos+=numPrimos[j];
    
   printf("%d\n",qntd_primos);
   
  return 0;
}
