#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
  int i, bits = 0;
  FILE * addressFile;
  char * line = NULL;
  char control[33];
  char counter[33];
  for(i = 0; i < 32; i++) {
    counter[i] = '0';
  } // zero out the counter
  counter[32] = '\0';
  size_t len = 0;
  ssize_t read;
  if (argc != 2) {
    printf("usage: %s addressFile\n", argv[0]);
  } // if the program is not executed with the right number of parameters
  addressFile = fopen(argv[1], "r");
  if (addressFile == NULL) {
    exit(-1);
  } // if file cannot be read

  if ((read = getline(&line, &len, addressFile)) != -1) {
    strncpy(control, line, 32);
    control[32] = '\0';
    while ((read = getline(&line, &len, addressFile)) != -1) {
      for(i = 0; i < 32; i++) {
        if (control[i] != line[i]) {
          counter[i] = '1';
        } // set to 1 each bit that changes from the control bitmap
      } // read each character on the line
    } // read each line in the file
    counter[32] = '\0';
  } // if the file contains a line

  fclose(addressFile);
  printf("%s\n", counter); // print out which bits change

  for(i = 0; i < 32; i++) {
    if (counter[i] == '1') {
      bits++;
    } // this bit varies
  } // count the number of bits that changed

  printf("%d bits of entropy\n", bits);

  return 0;
} // main()
