/*
Exercício 2 Escreva um programa em C no qual o processo pai cria 4 pro-
cessos filhos. Os processos filhos deverão imprimir na tela “Processo filho
XX”, onde XX é o PID do processo. Dica: utilize a função getpid() para
retornar o PID do processo.
*/
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main() {
  fork();
  printf("Novo processo criado!\n");
}