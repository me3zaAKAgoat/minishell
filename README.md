# **References**

## general

- https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html
- https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf
- https://faculty.cs.niu.edu/~hutchins/csci480/signals.htm
- https://www.gnu.org/software/bash/manual/bash.html

## parsing

- https://www.oilshell.org/blog/2019/02/07.html
- https://www.geeksforgeeks.org/developing-linux-based-shell/
- https://hal.science/hal-01890044/file/main.pdf
- http://savage.net.au/Ron/html/graphviz2.marpa/Lexing.and.Parsing.Overview.html
- https://mukulrathi.com/create-your-own-programming-language/parsing-ocamllex-menhir/
- https://tomassetti.me/guide-parsing-algorithms-terminology/

# **concerns**

- lexing
  - handle unclosed quotes
- handle cd when directories are removed
- fix wildcard \*
- handle exit status of shell builtins 0 success 1 failure 2 invalid options
- handle += in export
- handle delim of heredoc being inside of quotes -> dont expand (maybe have two types of delim tokens)
- pipeline should stop if a command fails
  this would mean that I might have to change the way things are being waited for, not sure tho
- redirections might have to get moved up to parsing and have the command structure only return a file descriptor
- handle cases where a string is : "hello"world
  it should not become hello world
- if an env expansion amounts to NULL dont concatenate it/ pop the token
- export xd="" should work like export xd=
- add append in export

- description of redirections
  > redirections should happen at parsing stage, when creating the command structure, the files should get opened and the file descriptors for these opened files should be saved as output and input files.
  > if there are two redirections the previous file descriptor should be closed and then replaced by the newer one
  > what happens if an input redirection fails??
