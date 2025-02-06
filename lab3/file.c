#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define LENGTH 5

int main() {

  char *history[LENGTH];
  char *buff = NULL;
  size_t count = 0;
  int num_input = 0;
  int array_length = 5;

  while (1) {
    printf("Enter input = ");
    if (getline(&buff, &count, stdin) == -1) {
      printf("Error reading input .\n");
      free(buff);
    }
    // replace \n by \0
    for (size_t i = 0; i < count; i++) {
      if (buff[i] == '\n') {
        buff[i] = '\0';
        break;
      }
    }

    // if history is full
    if (num_input == LENGTH) {
      free(history[0]);
      for (int i = 0; i < LENGTH - 1; i++) {
        history[i] = history[i + 1];
      }
      num_input--;
    }
    // store in history
    history[num_input % LENGTH] = malloc(strlen(buff) + 1);
    if (history[num_input] != NULL) {
      strcpy(history[num_input], buff);
    }
    num_input++;
    else {
      perror("allocation failed");
    }

    // check print
    if (strcmp(buff, "print") == 0) {
      for (size_t i = 0; i < num_input; i++) {
        printf("%s\n", history[i]);
      }
    }
  }
  // freeing memory
  for (int i = 0; i < LENGTH; i++) {
    free(history[i]);
  }
}
