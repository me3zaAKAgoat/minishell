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
- implement a heredoc that dosent need a file or just a dynamic better way of simulating a heredoc
- should cleanup cmds and heredoc when they're not longer needed
- lexing
  - handle env expansions
  - handle unclosed quotes
  - handle pipes at the end of the input
