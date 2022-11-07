#include <stdio.h> // scanf printf
#include <unistd.h> // read write sleep ssize_t STDOUT_FILENO
#include <fcntl.h> // open close O_RDONLY O_WRONLY
#include <string.h> // strlen
#include <stddef.h> // ssize_t

#define BUFFER_MAX_SIZE 1024
#define MESSAGE_MAX_SIZE 255

#define MIN(a,b) (((a)<(b))?(a):(b))

int main () {
  // Disable buffering
  setbuf(stdout, NULL);
  setbuf(stdin, NULL);
  setbuf(stderr, NULL);

  int void_of_nothingness_fd = open("/dev/null", O_WRONLY);
  int flag_fd = open("./flag.txt", O_RDONLY);

  if (flag_fd < 0) {
    printf("Seems that our flag.txt might is missing, or it's unreadable. Is it stolen? Please report this to the police.\n");
    return 1;
  }
  if (void_of_nothingness_fd < 0) {
    printf("Wait, we can't write to /dev/null? Wtf?");
    return 1;
  }

  char message[MESSAGE_MAX_SIZE];

  printf("Let us both write our deepest secrets to the deep void of nothingness. You go first: ");
  scanf("%s", message);

  // Your turn
  write(void_of_nothingness_fd, message, MIN(strlen(message), MESSAGE_MAX_SIZE));
  write(void_of_nothingness_fd, "\n", 1); // Add a nice newline between your message and my message

  printf("And now my turn...\n");
  sleep(1);

  // My turn
  char read_buf[BUFFER_MAX_SIZE];
  ssize_t buf_size;
  while ((buf_size = read(flag_fd, read_buf, BUFFER_MAX_SIZE))) {
    write(void_of_nothingness_fd, read_buf, buf_size);
  }

  printf("\nThe deed is done. Let's hope no one ever finds out...\n");

  close(flag_fd);
  close(void_of_nothingness_fd);
  return 0;
}
