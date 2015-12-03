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

// whether to print out debug information
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

// a bunch of unnecessary functions to change the location of hidden()

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

// the function to buffer overflow into

void hidden(void) {
  while (printf("\rHow did you get here...?\n") &&
         write(newsockfd, "hidden", 6) < 0);
  // send a response indicating that hidden() has been reached
} // hidden()

// buffer overflow vulnerable function

void getstr(void) {
  if (DEBUG) {
    printf("in getstr\n");
  }
  if (*readInput == 0) {
    exit(-1);
  } // this helps prevent more than one forked process from executing
  *readInput = 0;
  unsigned char buf[12];
  for (i = 0; i < count; i++) {
    buf[i] = atkStr[i];
  } // no bounds checking
} // getstr()

// more unnecessary functions to change the location of hidden()

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

// a bunch of assembly calls to look at memory addresses

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

  // open a socket and listen for connections

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
  signal(SIGTERM, SIG_IGN); // ignore SIGTERM (ctrl+c) to prevent hanging
  *k = 0;
  parent = getpid(); // identify the parent process

  while (1) {
    if (DEBUG) {
      printf("in while\n");
      printf("1. pid: %d\n", getpid());
    }
    ualarm(80000, 0); // timeout after 80ms
    if (DEBUG) {
      printf("daemonizing\n");
    }
    *loop = 0;
    daemonize(); // for a child process (do not execute)
    waitpid(pid, &status, 0); // wait for child process to terminate
    if (getpid() == parent) {
      if (DEBUG) {
        printf("daemonize done\n");
      }
      if (*finished == 0) {
        // send response back to client
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
  close(sockfd); // close the connection to the client
  if (DEBUG) {
    printf("exiting\n");
  }
  return 0;
} // main()

void signalHandler(int signalValue) {
  signal(signalValue, SIG_IGN); // prevent further signal handling
  usleep(800);
  if (DEBUG) {
    printf("signal: %d\n", signalValue);
  }
  if (signalValue == 4) {
    // prepare response to increment client string
    strcpy((char*) sendStr, "increment");
    *sendCount = 9;
  } // Illegal Instruction
  else if (signalValue == 11) {
    if (*finished == 1) {
      // prepare response that server finished successfully
      strcpy((char*) sendStr, "finished");
      *sendCount = 8;
    } else {
      // prepare response to increment client string
      strcpy((char*) sendStr, "increment");
      *sendCount = 9;
    }
  } // Segmentation fault
  else if (signalValue == 13) {
    // prepare response to increment client string
    strcpy((char*) sendStr, "increment");
    *sendCount = 9;
  } // Broken pipe
  else if (signalValue == 14) {
    if (*finished == 1) {
      // prepare response that server finished successfully
      strcpy((char*) sendStr, "finished");
      *sendCount = 8;
    } else {
      // prepare response to increment client string
      strcpy((char*) sendStr, "increment");
      *sendCount = 9;
    }
    kill(pid, SIGTERM); // terminate the child process
    if (getpid() != parent) {
      // tell client to resend previous string
      write(newsockfd, "again", 5);
      if (DEBUG) {
        printf("again sent\n");
      }
      kill(getpid(), SIGTERM); // terminate the child process
      exit(0);
    } else {
      // write prepared response to socket within timeout handler
      write(newsockfd, sendStr, *sendCount);
    } // send a message back to the client
  } // Alarm
  if (*finished == 1) {
    // prepare response that server finished successfully
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
    } // these particular signals will be handled
      // by the program's signalHandler()
  } // catch a bunch of signals

  if (parent == getpid()) {
    pid = fork();
    return;
  } // if the current process is the parent process, fork a child process
  if (pid < 0) {
    if (DEBUG) {
      printf("fork error\n");
    }
    exit(1);
  } // terminate if the pid doesn't make sense
  // child (daemon) continues
  
  bzero(buffer, 256); // zero out the buffer
  if (DEBUG) {
    printf("waiting for string\n");
  }
  *readInput = 1;
  n = read(newsockfd, buffer, 255); // get the client string
  for (i = 0; (buffer[i] >= '0') && (buffer[i] <= '9'); i++) {
    countString[i] = buffer[i];
  } // determine the number of characters in the string
  count = atoi((char*) countString);
  for (j = 0; j < count; j++) {
    atkStr[j] = buffer[++i];
    if (DEBUG) {
      printf("[%u]", atkStr[j]);
    }
  } // copy the client's request to variable atkStr
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
    } // print a character indicating that progress is being made
  }
  if (DEBUG) {
    printf("getting str\n");
    printf("2. pid: %d\n", getpid());
  }
  (*loop)++;
  if (*loop > 5) {
    kill(getpid(), SIGTERM); // terminate the current process
  } // stuck in a loop
  getstr(); // use atkStr in buffer overflow vulnerable function
  if (DEBUG) {
    printf("getstr done\n");
  }
  strcpy((char*) sendStr, "finished");
  *sendCount = 8;

  // send response to client indicating that process finished successfully
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
