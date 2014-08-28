/*
Exercício 3 Tendo como base a solução para o exercício anterior, crie uma
variável global do tipo inteiro inicialmente contendo o valor 0 (int conta-
dor_global = 0;). Remova o printf da função executada pelas threads. Mo-
difique a função executada pelas threads para que cada thread realize 100
operações de incremento nesta variável global (contador_global++)
com o uso de um for. Após o término da execução das threads, a main
thread deverá imprimir o valor armazenado na variável contador_global.
Em uma execução correta, o valor impresso deverá ser igual a
100 vezes o número de threads criadas, ou seja contador_global =
100 * MAX_THREADS. Execute várias vezes este programa com 2, 4, 8,
32 e 128 threads e observe o valor impresso a cada vez. O que acontece?
*/

#include <stdio.h>
#include <pthread.h>

#define MAX_THREADS 128

void *PrintTID(void *arg);

int contador_global = 0;

int main() {
  pthread_t thread[MAX_THREADS];
  for(int i = 0; i < MAX_THREADS; i++) {
    pthread_create(&thread[i], NULL, PrintTID, (void *) NULL);
  }
  for(int i = 0; i < MAX_THREADS; i++) {
    pthread_join(thread[i], NULL);
  }
  printf("Valor do contador global: %d\n", contador_global);
  pthread_exit(NULL);  
}

void *PrintTID(void *arg) {
  pthread_t tid = pthread_self();
  for(int i = 0; i < 100; i++) {
    contador_global++;
  }
  pthread_exit(NULL);
}