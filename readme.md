# readline-cli
executable for getting user input with simple line-editing.
like readline for the shell, yet based on [linenoise](https://github.com/antirez/linenoise).

* left or right to move over characters
* ctrl+left or ctrl+right to move over words
* up or down to navigate input history

command-line interface:
~~~
usage: readline [options] [prompt] [historyfile]
description
  read a line of user input with basic text editing.
examples
  readline
  readline "> "
  readline "" /tmp/history
options
  --help, -h
  --version, -v
~~~

getting a line from the user in a shell script:
~~~
input = $(readline)
echo $input
~~~

# dependencies
* c 2011 standard library (for example musl-libc or glibc)
* posix 2008 features (for example linux or freebsd)
* for the provided compile script: shell, gcc

# setup
~~~
./exe/compile
~~~

the provided compile script uses gcc and [musl-libc](https://musl.libc.org/) or glibc. it creates a statically compiled binary at ``exe/readline``.
it can be run directly from the project directory with ``./exe/readline``. alternatively, it can be linked or copied anywhere else. it can be copied into one of the directories listed in the $PATH environment variable to be available as a shell command.

# license
bsd-2

# thanks
* [multibyte character support by yhirose](https://github.com/yhirose/linenoise)
* [word-navigation by c-cube](https://github.com/ocaml-community/ocaml-linenoise)

# similar projects
* [input](https://github.com/nmeum/input)
* [rlwrap](https://github.com/hanslub42/rlwrap)
