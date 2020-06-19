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
   if (Num==0)
   {
      qntd_divisores = 0;
      printf("O número %ld não é primo\n",Num);
   } else if (Num==1)
   {
      qntd_divisores = 0;
      printf("O número %ld não é primo\n", Num);
   } else 
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
            printf("O número %ld é primo\n", Num);
            div++;
         } else
         {
            printf("O número %ld não é primo\n", Num);
            qntd_divisores = 0;      
         }
   } 
      return div;
}

int main() {

   pid_t filho[QNTD_PROCESSOS];	
   int numeros = 0, cont = 0, j =0; //Variáveis auxiliares
   char c; //Variável que auxilia na leitura dos números
   unsigned long int numb[N_NUMBERS]; //Vetor que armazena os números que serão analisados
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
      c = scanf("%ld",&numb[numeros]);
      numeros++;
   } 
   
   for (j=0; j < (numeros - 1); j++)
   {
      ver_primo(numb[j]);
   }
   
   
/*   //Processos filhos
   for (cont = 0; cont < QNTD_PROCESSOS; cont++)
   {
      filho[cont] = fork();

      if (filho[cont] ==0)
      {
         printf("Estou no processo filho %d\n", cont);
         exit(0);
      } else 
      {
         printf("O PID do processo filho %d é %d,",i,filho[i]);
      }    
   }
*/
   
  return 0;
}
