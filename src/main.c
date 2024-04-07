#include "foreign/linenoise.h"
#include "foreign/linenoise-with-word-navigation.c"

int main() {
  char* line = linenoise("");
  if (line) {
    write(1, line, strlen(line));
    linenoiseHistoryAdd(line);
    free(line);
  }
  return 0;
}
