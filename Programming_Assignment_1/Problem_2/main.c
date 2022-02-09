/*
** This program converts DOS commands into their unix equivalent commands
** DOS  Commands: cd, dir, type, del, ren, copy
** UNIX Commands: cd,  ls,  cat,  rm,  mv,   cp
**
*/
#include "headers.h"

// send a system command i is system("command string here");
int main() {
  // assign variables
  char line[1024];
  char delim[] = " \t\n\r";
  char catchall[] = "\n\r";
  char *command, *arg1, *arg2, *combine;

  // assign memory to strings
  command = malloc(1024 * sizeof(char));
  arg1 = malloc(1024 * sizeof(char));
  arg2 = malloc(1024 * sizeof(char));
  combine = malloc(1024 * sizeof(char));

  // prompt
  printf("\nDOS command interpreter for Linux\n");

  while (1) {
    printf("\nType Ctrl-C to exit\n> ");
    fflush(stdout);

    memset(line, '\0', 1024);

    fgets(line, 1024, stdin); // get the whole input
    // printf("\nread input");
    command = strtok(line, delim);
    switch (command[0]) {
    case 'c':
      if (command[1] == 'd' && command[2] == '\0') {
        arg1 = strtok(NULL, catchall);
        int err = chdir(arg1);
        if (err == -1) {
          printf("Invalid argument(s)\n");
        }
      } else if (strcmp("copy", command) == 0) {
        arg1 = strtok(NULL, delim);
        arg2 = strtok(NULL, catchall);
        sprintf(combine, "cp %s %s", arg1, arg2);
        system(combine);
      } else
        printf("Invalid Command\n");
      break;
    case 'd':
      if (strcmp("dir", command) == 0) {
        arg1 = strtok(NULL, catchall);
        if (arg1 != NULL) {
          sprintf(combine, "ls %s", arg1);
        } else
          sprintf(combine, "ls");
        system(combine);
      } else if (strcmp("del", command) == 0) {
        arg1 = strtok(NULL, catchall);
        sprintf(combine, "rm %s", arg1);
        system(combine);
      } else
        printf("Invalid Command\n");
      break;
    case 'r':
      if (strcmp("ren", command) == 0) {
        arg1 = strtok(NULL, delim);
        arg2 = strtok(NULL, catchall);
        sprintf(combine, "mv %s %s", arg1, arg2);
        system(combine);
      } else
        printf("Invalid Command\n");
      break;
    case 't':
      if (strcmp("type", command) == 0) {
        arg1 = strtok(NULL, catchall);
        sprintf(combine, "cat %s", arg1);
        system(combine);
      } else
        printf("Invalid Command\n");
      break;
    default:
      printf("Invalid Command\n");
      break;
    }
  }
  return 0;
}
