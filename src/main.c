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

void cli(int argc, char** argv, char** historyfile, char** prompt) {
  int opt;
  struct option longopts[3] = {{"help", no_argument, 0, 'h'}, {"version", no_argument, 0, 'v'}, {0}};
  while (!(-1 == (opt = getopt_long(argc, argv, "hv", longopts, 0)))) {
    if ('h' == opt) {
      display_help();
      exit(0);
    } if ('v' == opt) {
      printf("v0.1\n");
      exit(0);
    };
  };
  *prompt = argc > optind ? argv[optind] : "";
  *historyfile = argc > optind + 1 ? argv[optind + 1] : 0;
}

int main(int argc, char** argv) {
  char* historyfile;
  char* prompt;
  char* line;
  cli(argc, argv, &historyfile, &prompt);
  if (historyfile) linenoiseHistorySetMaxLen(linenoiseHistoryLoad(historyfile) ? 0 : 100);
  // setup output file descriptor. important when called in a subshell
	if (!isatty(1)) {
    linenoise_stdout = fopen(tty_dev_path, "w");
    if (!linenoise_stdout) exit(errno);
  }
  // if prompt is not set in linenoise, linenoise clears it
  line = linenoise(prompt);
  if (line) {
    write(1, line, strlen(line));
    free(line);
  }
  return 0;
}
