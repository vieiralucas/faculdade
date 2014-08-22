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
/*
          PAI

      FILHO FILHO
  FILHO

  fork
  fork
  if pid != 0
    fork*/