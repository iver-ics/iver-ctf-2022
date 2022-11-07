#include <stdio.h> // setbuf stdout stdin stderr printf gets

#define BUFFER_MAX_SIZE 128

void exploit_me() {
  char stuff[BUFFER_MAX_SIZE];
  printf("Hey, write some stuff to %p\n", &stuff);
  gets(stuff);
}

int main () {
  // Disable buffering
  setbuf(stdout, NULL);
  setbuf(stdin, NULL);
  setbuf(stderr, NULL);

  exploit_me();

  printf("Did you massacre the stack?\n");

  return 0;
}
