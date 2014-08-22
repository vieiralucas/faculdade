#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

  /*
    posicao 0 eh o receptor e 1 eh o enviador
  */

int main() {
  
  int a, b, c;
  int p1[2], p2[2];
  pipe(p1);
  pipe(p2);
  pid_t pid = fork();

  if(pid == 0) {
    close(p1[1]);
    close(p2[0]);
    read(p1[0], &a, sizeof(a));
    read(p1[0], &b, sizeof(b));
    read(p1[0], &c, sizeof(c));
    printf("Inteiros recebidos: %i - %i - %i\n", a, b, c);
    a += 10, b += 10, c += 10;
    write(p2[1], &a, sizeof(a));
    write(p2[1], &b, sizeof(b));
    write(p2[1], &c, sizeof(c));
  } else {
    close(p1[0]);
    close(p2[1]);
    a = 1, b = 2,  c = 3;
    write(p1[1], &a, sizeof(a));
    write(p1[1], &b, sizeof(b));
    write(p1[1], &c, sizeof(c));
    read(p2[0], &a, sizeof(a));
    read(p2[0], &b, sizeof(b));
    read(p2[0], &c, sizeof(c));
    printf("Inteiros somados com 10: %i - %i - %i\n", a, b, c);
  }

}