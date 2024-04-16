#define _POSIX_C_SOURCE 1
#define tty_dev_path "/dev/tty"
#include "foreign/linenoise-extended.c"
#include <getopt.h>

void display_help() {
  printf("usage: readline [options] [prompt] [historyfile]\n"
   "description\n"
   "  read a line of user input with basic text editing.\n"
   "examples\n"
   "  readline\n"
   "  readline \"> \"\n"
   "  readline \"\" /tmp/history\n"
   "options\n"
   "  --help, -h\n"
   "  --version, -v\n");
}

void cli(int argc, char** argv, char** historyfile, char** prompt, unsigned char* loop) {
  int opt;
  struct option longopts[4] = {{"help", no_argument, 0, 'h'}, {"loop", no_argument, 0, 'l'}, {"version", no_argument, 0, 'v'}, {0}};
  while (!(-1 == (opt = getopt_long(argc, argv, "hlv", longopts, 0)))) {
    if ('h' == opt) {
      display_help();
      exit(0);
    }
    else if ('l' == opt) {
      *loop = 1;
    }
    else if ('v' == opt) {
      printf("v0.1\n");
      exit(0);
    }
  }
  *prompt = argc > optind ? argv[optind] : "";
  *historyfile = argc > optind + 1 ? argv[optind + 1] : 0;
}

int main(int argc, char** argv) {
  char buf[LINENOISE_MAX_LINE];
  char* historyfile;
  char* line;
  char* prompt;
  unsigned char loop = 0;
  cli(argc, argv, &historyfile, &prompt, &loop);
  linenoiseSetEncodingFunctions(linenoiseUtf8PrevCharLen, linenoiseUtf8NextCharLen, linenoiseUtf8ReadCode);
  if (historyfile) linenoiseHistorySetMaxLen(linenoiseHistoryLoad(historyfile) ? 0 : 100);
  // when called in a subshell then line editing output goes to parent terminal
  if (!isatty(1)) {
    linenoise_stdout = fopen(tty_dev_path, "w");
    if (!linenoise_stdout) exit(errno);
  }
  else linenoise_stdout = stdout;
  // using the loop option saves repeating all the setup above
  do {
    // if prompt were not set in linenoise, linenoise would clear it when editing
    line = linenoiseBlockingEdit(fileno(stdin), fileno(linenoise_stdout), buf, LINENOISE_MAX_LINE, prompt);
    if (line) {
      write(1, line, strlen(line));
      write(1, "\n", 1);
      free(line);
    }
    else break;
  } while (loop);
  return 0;
}
