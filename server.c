#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#define DEBUG 0

socklen_t clilen;
unsigned int address;
struct sockaddr_in serv_addr, cli_addr;
unsigned char atkStr[256], buffer[256], *sendStr, countString[10],
              progress[4] = {'/', '-', '\\', '|'};
int i, j, *k, n, count, sockfd, newsockfd, portno = 54321, parent,
    pid, status, *finished, *yes, *sendCount, *loop, *readInput;

void daemonize(void);
void signalHandler(int signalValue);

/*
void fluffCodeNegative5(void) {
  int x = 14;
  int y = 28;
  
  x = (x * y) - (3 * y);
  if (DEBUG) {
    perror("you shouldn't have been able to get here\n");
  }
  exit(0);
} // fluffCodeNegative5()

void fluffCodeNegative4(void) {
  int x = 14;
  int y = 28;
  
  x = (x * y) - (3 * y);
  if (DEBUG) {
    perror("you shouldn't have been able to get here\n");
  }
  exit(0);
} // fluffCodeNegative4()

void fluffCodeNegative3(void) {
  int x = 14;
  int y = 28;
  
  x = (x * y) - (3 * y);
  if (DEBUG) {
    perror("you shouldn't have been able to get here\n");
  }
  exit(0);
} // fluffCodeNegative3()

void fluffCodeNegative2(void) {
  int x = 14;
  int y = 28;
  
  x = (x * y) - (3 * y);
  if (DEBUG) {
    perror("you shouldn't have been able to get here\n");
  }
  exit(0);
} // fluffCodeNegative2()

void fluffCodeNegative1(void) {
  int x = 14;
  int y = 28;

  x = (x * y) - (3 * y);
  if (DEBUG) {
    perror("you shouldn't have been able to get here\n");
  }
  exit(0);
} // fluffCodeNegative1()
*/

void hidden(void) {
  while (printf("\rHow did you get here...?\n") &&
         write(newsockfd, "hidden", 6) < 0);
} // hidden()

void getstr(void) {
  if (DEBUG) {
    printf("in getstr\n");
  }
  if (*readInput == 0) {
    exit(-1);
  }
  *readInput = 0;
  unsigned char buf[12];
  for (i = 0; i < count; i++) {
    buf[i] = atkStr[i];
  }
} // getstr()

void fluffCode1(void) {
  int x = 14;
  int y = 28;
  
  x = (x * y) - (3 * y);
  if (DEBUG) {
    perror("you shouldn't have been able to get here\n");
  }
  exit(0);
} // fluffCode1()

/*
void fluffCode2(void) {
  int x = 14;
  int y = 28;
  
  x = (x * y) - (3 * y);
  if (DEBUG) {
    perror("you shouldn't have been able to get here\n");
  }
  exit(0);
} // fluffCode2()

void fluffCode3(void) {
  int x = 14;
  int y = 28;
  
  x = (x * y) - (3 * y);
  if (DEBUG) {
    perror("you shouldn't have been able to get here\n");
  }
  exit(0);
} // fluffCode3()

void fluffCode4(void) {
  int x = 14;
  int y = 28;
  
  x = (x * y) - (3 * y);
  if (DEBUG) {
    perror("you shouldn't have been able to get here\n");
  }
  exit(0);
} // fluffCode4()
*/

int main(void) {
/*
  address = (unsigned int) hidden;
  printf("hidden at [%u][%u][%u][%u]\n", ((address & 0xFF000000) >> 24), ((address & 0x00FF0000) >> 16), ((address & 0x0000FF00) >> 8), (address & 0x000000FF));
  address = (unsigned int) main;
  printf("main at [%u][%u][%u][%u]\n", ((address & 0xFF000000) >> 24), ((address & 0x00FF0000) >> 16), ((address & 0x0000FF00) >> 8), (address & 0x000000FF));
  address = (unsigned int) signalHandler;
  printf("signalHandler at [%u][%u][%u][%u]\n", ((address & 0xFF000000) >> 24), ((address & 0x00FF0000) >> 16), ((address & 0x0000FF00) >> 8), (address & 0x000000FF));
  address = (unsigned int) daemonize;
  printf("daemonize at [%u][%u][%u][%u]\n", ((address & 0xFF000000) >> 24), ((address & 0x00FF0000) >> 16), ((address & 0x0000FF00) >> 8), (address & 0x000000FF));
  address = (unsigned int) fluffCodeNegative1;
  printf("fluffCodeNegative1 at [%u][%u][%u][%u]\n", ((address & 0xFF000000) >> 24), ((address & 0x00FF0000) >> 16), ((address & 0x0000FF00) >> 8), (address & 0x000000FF));
  address = (unsigned int) getstr;
  printf("getstr at [%u][%u][%u][%u]\n", ((address & 0xFF000000) >> 24), ((address & 0x00FF0000) >> 16), ((address & 0x0000FF00) >> 8), (address & 0x000000FF));
*/
  if (DEBUG) {
    printf("in main\n");
  }
  k = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  sendStr = mmap(NULL, (sizeof(char) * 256), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  sendCount = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  finished = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  loop = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  readInput = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);
  if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    if (DEBUG) {
      perror("ERROR on binding");
    }
    exit(0);
  }
  listen(sockfd, 5);
  clilen = sizeof(cli_addr);
  newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
  signal(SIGTERM, SIG_IGN);
  *k = 0;
  parent = getpid();

  while (1) {
    if (DEBUG) {
      printf("in while\n");
    }
    if (DEBUG) {
      printf("1. pid: %d\n", getpid());
    }
    ualarm(80000, 0);
    if (DEBUG) {
      printf("daemonizing\n");
    }
    *loop = 0;
    daemonize();
    waitpid(pid, &status, 0);
    if (getpid() == parent) {
      if (DEBUG) {
        printf("daemonize done\n");
      }
      if (*finished == 0) {
        n = write(newsockfd, sendStr, *sendCount);
        if (n < 0) {
          if (DEBUG) {
            perror("ERROR writing to socket");
          }
          exit(0);
        }
        if (DEBUG) {
          printf("%s sent\n", sendStr);
        }
      }
      usleep(800);
    }
  } // loop forever
  close(newsockfd);
  close(sockfd);
  if (DEBUG) {
    printf("exiting\n");
  }
  return 0;
} // main()

void signalHandler(int signalValue) {
  signal(signalValue, SIG_IGN);
  usleep(800);
  if (DEBUG) {
    printf("signal: %d\n", signalValue);
  }
  if (signalValue == 4) {
    strcpy((char*) sendStr, "increment");
    *sendCount = 9;
  } // Illegal Instruction
  else if (signalValue == 11) {
    if (*finished == 1) {
      strcpy((char*) sendStr, "finished");
      *sendCount = 8;
    } else {
      strcpy((char*) sendStr, "increment");
      *sendCount = 9;
    }
  } // Segmentation fault
  else if (signalValue == 13) {
    strcpy((char*) sendStr, "increment");
    *sendCount = 9;
  } // Broken pipe
  else if (signalValue == 14) {
    if (*finished == 1) {
      strcpy((char*) sendStr, "finished");
      *sendCount = 8;
    } else {
      strcpy((char*) sendStr, "increment");
      *sendCount = 9;
    }
    kill(pid, SIGTERM);
    if (getpid() != parent) {
      write(newsockfd, "again", 5);
      if (DEBUG) {
        printf("again sent\n");
      }
      kill(getpid(), SIGTERM);
      exit(0);
    } else {
      write(newsockfd, sendStr, *sendCount);
    } // send a message back to the client
  } // Alarm
  if (*finished == 1) {
    strcpy((char*) sendStr, "finished");
    *sendCount = 8;
  }
} // signalHandler()

void daemonize(void) {
  if (DEBUG) {
    printf("in daemonize\n");
  }
  
  for (i = 3; i < 32; i++) {
    if (i != 9 && i != 15 && i != 17 && i != 28) {
      signal(i, signalHandler);
    }
  } // catch a bunch of signals

  if (parent == getpid()) {
    pid = fork();
    return;
  }
  if (pid < 0) {
    if (DEBUG) {
      printf("fork error\n");
    }
    exit(1);
  }
  // child (daemon) continues
  
  bzero(buffer, 256);
  if (DEBUG) {
    printf("waiting for string\n");
  }
  *readInput = 1;
  n = read(newsockfd, buffer, 255);
  for (i = 0; (buffer[i] >= '0') && (buffer[i] <= '9'); i++) {
    countString[i] = buffer[i];
  }
  count = atoi((char*) countString);
  for (j = 0; j < count; j++) {
    atkStr[j] = buffer[++i];
    if (DEBUG) {
      printf("[%u]", atkStr[j]);
    }
  }
  if (DEBUG) {
    printf("\n");
  }
  
  *finished = 0;
  if (!DEBUG) {
    if (0 == atkStr[count]) {
      printf("                      \r%c", progress[(*k)++ % 4]);
      fflush(stdout);
      if (*k > 3) {
        *k = 0;
      }
    }
  }
  if (DEBUG) {
    printf("getting str\n");
    printf("2. pid: %d\n", getpid());
  }
  (*loop)++;
  if (*loop > 5) {
    kill(getpid(), SIGTERM);
  } // stuck in a loop
  getstr();
  if (DEBUG) {
    printf("getstr done\n");
  }
  strcpy((char*) sendStr, "finished");
  *sendCount = 8;
  
  n = write(newsockfd, sendStr, *sendCount);
  if (n < 0) {
    if (DEBUG) {
      perror("ERROR writing to socket");
    }
    exit(0);
  }
  if (DEBUG) {
    printf("%s sent\n", sendStr);
  }
  *finished = 1;
  return;
} // daemonize()
