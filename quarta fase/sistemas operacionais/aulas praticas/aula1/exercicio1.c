/*
Exercício 1 Escreva um programa em C que cria um processo utilizando a
chamada de sistema fork(). Ambos os processos pai e filho deverão impri-
mir na tela a frase "Novo processo criado!". Você deverá  utilizar apenas
um priintf().
*/
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main() {
  fork();
  printf("Novo processo criado!\n");
}
