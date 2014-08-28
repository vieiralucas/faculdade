/* 
Para compilar
gcc -o meu_programa meu_programa.c -lpthread

Exercício 1 Escreva um programa em C que cria uma worker thread usando
PThreads. A thread criada deverá imprimir na tela a frase “Nova thread
criada. TID = XX!”, onde XX é o identificador da thread. A main thread
deverá aguardar que a thread criada imprima a frase na tela antes de
terminar. Dica: use a função pthread_self() para retornar o ID da thread.

*/

#include <stdio.h>
#include <pthread.h>

void *PrintTID(void *arg);

int main() {
  pthread_t thread;
  pthread_create(&thread, NULL, PrintTID, (void *) NULL);
  pthread_join(thread, NULL);
  pthread_exit(NULL);
}

void *PrintTID(void *arg) {
  pthread_t tid = pthread_self();
  printf("Nova thread criada. TID= %ld\n", (long int)tid);
  pthread_exit(NULL);
}