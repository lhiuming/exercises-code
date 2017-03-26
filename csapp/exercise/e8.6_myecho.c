// printing all command-line arguments and environment variables:
#include <stdio.h>

void print_with_prefix(const char *pfx, int i, char *content) {
  printf("%s[%2i]: %s\n", pfx, i, content);
}

int main(int argc, char **argv, char**envp) {
  int i;
  /* command-line arguments */
  printf("Command-line arguments: \n");
  for (i = 0; i < argc; i++) {
    printf("    ");
    print_with_prefix("argv", i, argv[i]);
  }

  /* environment variable */
  printf("Environment Variables: \n");
  for (i = 0; envp[i] != NULL; i++) {
    printf("    ");
    print_with_prefix("envp", i, envp[i]);
  }

  return 0;
}
