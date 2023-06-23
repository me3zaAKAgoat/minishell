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
- have cd handle PWD and OLDPWD
- have the lexer raise syntax errors for when heredoc append trunc and inputredir are not followed by strings/ when pipe is an end token/ when quotes are unclosed
- update global exit status
- echo builtin is missing
- fix wildcard \*
- handle exit status of shell builtins 0 success 1 failure 2 invalid options
- handle += in export
- handle delim of heredoc being inside of quotes -> dont expand (maybe have two types of delim tokens)
- does the fucking lexer and parser remove quotes or is that handle execution level
