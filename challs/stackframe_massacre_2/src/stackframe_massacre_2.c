#include <stdio.h> // setbuf stdout stdin stderr printf gets
#include <unistd.h> // getuid setuid
#include <fcntl.h> // open close O_RDONLY

#define nobody 65534

void exploit_me() {
  char stuff[128];
  printf("Hey (once again)! Write some stuff to %p\n", &stuff);
  gets(stuff);
}

int main () {
  // Disable buffering
  setbuf(stdout, NULL);
  setbuf(stdin, NULL);
  setbuf(stderr, NULL);

  if (getuid() != 0) {
    printf("This program should be run as root\n");
    return 1;
  }

  char eh[] = "Test!";
  char flag[1024];

  int flag_fd = open("./flag.txt", O_RDONLY);

  size_t read_size = read(flag_fd, flag, 1024);

  flag[read_size] = 0;

  close(flag_fd);

  setgid(nobody);
  setuid(nobody);

  exploit_me();

  printf("Did you massacre the stack?\n");

  return 0;
}
