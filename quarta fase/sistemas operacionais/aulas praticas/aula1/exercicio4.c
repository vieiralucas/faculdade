/*
Exercício 4 Escreva um programa em C onde o processo pai cria um processo
filho o qual estabelece um pipe de comunicação com ele. O processo pai
deverá enviar 3 números inteiros ao processo filho através do pipe. O
processo filho deverá imprimir os números recebidos na tela.
*/
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main() {
  
  int a, b, c;
  int p[2];
  pipe(p);
  pid_t pid = fork();

  if(pid == 0) {
    close(p[1]);
    read(p[0], &a, sizeof(a));
    read(p[0], &b, sizeof(b));
    read(p[0], &c, sizeof(c));
    printf("Inteiros recebidos: %i - %i - %i\n", a, b, c);
  } else {
    close(p[0]);
    a = 1, b = 2,  c = 3;
    write(p[1], &a, sizeof(a));
    write(p[1], &b, sizeof(b));
    write(p[1], &c, sizeof(c));
  }

}