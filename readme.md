# readline-cli
*status: not yet ready*

executable for getting user input with simple line-editing.
like readline for the shell, yet based on [linenoise](https://github.com/antirez/linenoise).

* up or down to navigate input history
* left or right to move over characters
* ctrl+left or ctrl+right to move over words

example for getting a line from the user in a shell script:
~~~
input = $(readline)
echo $input
~~~

# setup
~~~
./exe/compile
~~~

the provided compile script uses gcc and musl-libc or glibc. it creates a statically compiled binary at ``exe/readline``.
it can be run directly from the project directory with ``./exe/readline``. alternatively, it can be linked or copied anywhere else. it can be copied into one of the directories listed in the $PATH environment variable to be available as a shell command.

# license
bsd-2

# other
special thanks to user c-cube and [https://github.com/ocaml-community/ocaml-linenoise](ocaml-linenoise) for the ctrl+left and ctrl+right word-navigation solution.

# similar projects
* [input](https://github.com/nmeum/input)
* [rlwrap](https://github.com/hanslub42/rlwrap)