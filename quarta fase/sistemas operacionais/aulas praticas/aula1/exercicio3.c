/*
Exercício 3 Escreva um programa em C no qual o processo pai cria 2 processos
filhos e cada um dos processos filhos cria mais 2 processos filhos.
*/
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main() {
  pid_t pid = fork();
  if(pid == 0) {
    pid_t pid = fork();  
    if(pid == 0) {
      pid_t pid = fork();  
      if(pid > 0) {
        fork();
      }
    }
  } else {
    pid_t pid = fork();
    if(pid == 0) {
      pid_t pid = fork();  
      if(pid > 0) {
        fork();
      }
    }
  }
}