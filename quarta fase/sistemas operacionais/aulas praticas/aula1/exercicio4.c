#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

  /*
    posicao 0 eh o receptor e 1 eh o enviador
  */

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