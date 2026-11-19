#include <stdio.h>
#include <string.h>
#include <unistd.h>

void clearTerminal() {
  printf("\033[2J\033[H");
};

void printError() {
  printf("\n  Erro: selecione uma opção valida\n");
  usleep(1500000);
};

void formatInput(char *input) {
  int loc = strcspn(input, "\n");

  input[loc] = '\0';
};
