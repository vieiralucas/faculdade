/*
Exercício 2 Transforme o código do exercício anterior em um código gené-
rico que cria n threads. Da mesma forma que o exercício anterior, a
main thread deverá aguardar a finalização de todas as worker threads
antes de terminar. O número de threads deverá ser definido no código
em uma constante chamada MAX_THREADS. Por exemplo, deverão ser
criadas 5 threads se a constante for definida da seguinte forma: #define
MAX_THREADS 5.
*/

#include <stdio.h>
#include <pthread.h>

#define MAX_THREADS 666

void *PrintTID(void *arg);

int main() {
  pthread_t thread[MAX_THREADS];
  for(int i = 0; i < MAX_THREADS; i++) {
    pthread_create(&thread[i], NULL, PrintTID, (void *) NULL);
  }
  for(int i = 0; i < MAX_THREADS; i++) {
    pthread_join(thread[i], NULL);
  }
  pthread_exit(NULL);  
}

void *PrintTID(void *arg) {
  pthread_t tid = pthread_self();
  printf("Nova thread criada. TID= %ld\n", (long int)tid);
  pthread_exit(NULL);
}