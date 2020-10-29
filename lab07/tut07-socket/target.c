#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <err.h>

/* http://man7.org/tlpi/code/online/book/sockets/read_line.c.html */
ssize_t read_line(int fd, void *buffer, size_t n)
{
  ssize_t numRead;                    /* # of bytes fetched by last read() */
  size_t totRead;                     /* Total bytes read so far */
  char *buf;
  char ch;

  if (n <= 0 || buffer == NULL) {
    errno = EINVAL;
    return -1;
  }

  buf = buffer;                       /* No pointer arithmetic on "void *" */

  totRead = 0;
  for (;;) {
    numRead = read(fd, &ch, 1);
    if (numRead == -1) {
      if (errno == EINTR)             /* Interrupted --> restart read() */
        continue;
      else
        return -1;                    /* Some other error */
    } else if (numRead == 0) {        /* EOF */
      if (totRead == 0)               /* No bytes read; return 0 */
        return 0;
      else                            /* Some bytes read; add '\0' */
        break;
    } else {                          /* 'numRead' must be 1 if we get here */
      if (ch == '\n')
        break;
      if (totRead < n - 1) {          /* Discard > (n - 1) bytes */
        totRead++;
        *buf++ = ch;
      }
    }
  }

  *buf = '\0';
  return totRead;
}

void dump_flag(int fd) {
  char buf[1024];

  FILE *fp = fopen("/proc/flag", "r");
  if (!fp)
    err(1, "Please insert your kflag.ko to get the flag!");

  while (1) {
    size_t len = fread(buf, 1, sizeof(buf)-1, fp);
    buf[len] = '\0';
    write(fd, buf, strlen(buf));
    if (len < sizeof(buf)-1)
      break;
  }
  write(fd, "\n", 1);

  fclose(fp);
}


int convert_to_int(char *input) {
  char *maps[] = {"rock", "paper", "scissors"};
  for (int i = 0; i < 3; i ++) {
    if (!strcmp(maps[i], input)) {
      return i;
    }
  }
  return -1;
}

void start(int fd) {

  write(fd, "Let's play rock, paper, scissors!\nYour name> ", 44);

  char name[0x200];
  if (read_line(fd, name, sizeof(name) - 1) <= 0) {
    return;
  }

  srand(*(unsigned int*)name + time(NULL));

  int iter;
  for (iter = 0; iter < 5; iter ++) {

    write(fd, "Your turn> ", 11);
    
    char input[10];
    if (read_line(fd, input, sizeof(input) - 1) <= 0) {
      return;
    }

    int yours = convert_to_int(input);
    if (yours == -1) {
      write(fd, "Not recognized! You lost!\n", 26);
      return;
    }

    int r = rand();
    int result = yours - r % 3;
    if (result == 0) {
      write(fd, "Tie, try again!\n", 16);
      iter --;
      continue;
    }
    if (result == 1 || result == -2) {
      write(fd, "You win! try again!\n", 20);
    } else {
      write(fd, "You lose! Game over\n", 20);
      return;
    }
  }

  write(fd, "YOU WIN!\n", 9);
  dump_flag(fd);
}

int main(int argc, char *argv[])
{
  int port = 10700;
  int server_sockfd, client_sockfd;
  socklen_t server_len, client_len;
  struct sockaddr_in server_address;
  struct sockaddr_in client_address;

  if (argc == 2) {
    port = atoi(argv[1]);
  }

  server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
  int yes = 1;
  if (setsockopt(server_sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) < 0) {
    perror("setsockopt");
    exit(-1);
  }

  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = htonl(INADDR_ANY);
  server_address.sin_port = htons(port);
  server_len = sizeof(server_address);

  if (bind(server_sockfd, (struct sockaddr *)&server_address,server_len) < 0) {
    perror("bind");
    exit(-1);
  }

  /* Create a connection queue, ignore child exit details and wait for
     clients. */

  listen(server_sockfd, 5);
  signal(SIGCHLD, SIG_IGN);

  while(1) {
    /* Accept connection. */

    client_len = sizeof(client_address);
    client_sockfd = accept(server_sockfd,\
                           (struct sockaddr *)&client_address, &client_len);

    /* Fork to create a process for this client and perform a test to see
       whether we're the parent or the child. */

    if (fork() == 0) {

      /* If we're the child, we can now read/write to the client on
         client_sockfd.
         The five second delay is just for this demonstration. */

      start(client_sockfd);

      close(server_sockfd);
      close(client_sockfd);
      return 0;
    }

    /* Otherwise, we must be the parent and our work for this client is
       finished. */

    else {
      close(client_sockfd);
    }
  }
}
