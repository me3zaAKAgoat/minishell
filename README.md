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

- how to handle error codes to color prompt
- implement a dynamic tmp file for heredoc
- should cleanup cmds and heredoc when they're not longer needed
- lexing
  - handle env expansions
  - handle unclosed quotes
  - handle pipes at the end of the input
- handle cd when directories are removed
- have cd handle PWD and OLDPWD
- have echo handle its arguments in a fluent manner (-nnnnn -nnnnss -ss) etc
- have the lexer raise syntax errors for when heredoc append trunc and inputredir are not followed by strings/ when pipe is an end token/ when quotes are unclosed
- have the pre parser/ lexer expand environment variables
- store pids of all forks somewhere for them to get killed by CTRL-C
- have builtins run inside forks aswell
- find an elegant way to manage pipes
- make a dict function that returns the value of a key
- update global exit status
- handle export without arguments
- **when checking with strncmp which of the s1 and s2 strings should I take the length of, it seems to be the lengthier string but I'm not sure !**
- get_cmd and get_path_env are extremely vulnerable and untested functions!!
