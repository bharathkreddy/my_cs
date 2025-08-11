[Book](https://tldp.org/LDP/abs/html/index.html)
Tools installed

- [tldr](https://github.com/tldr-pages/tldr/wiki/Clients): try tldr <command> ex `tldr tar`

0. use `#! /usr/bin/env sh` instead of hardcoding `#! /bin/sh`, this allows better portability.
1. Shell knows how to run programs (ex. Date, Which, echo etc), by looking at env variable called PATH.
   `echo $PATH`
2. `which echo` gives where a program is located.
3. `pwd` print current working directory.
4. `rmdir` removes dir only if its empty
5. `rm -r` rm to remove dir add -r to do it recursive.
6. `ctr+l` clear and move to top
7. STREAMS: Every program has 2 default streams - input and output. We can re-wire these.
   - `<` input stream ex: `cat < hello.txt`
   - `>` output stream ex: `echo hello > hello.txt`
   - we can use both ex. ` cat < hello.txt > hello2.txt`
   - `>>` is append instead of overwrite
   - `|` take output stream of previous and give it to input stream to next.
8. `tee` writes to a file and output stream.
9. `sudo su` : gets me shell as root.
10. `open` on mac `xdg-open` will open a file with default tool.
11. `echo $SHELL` tells which shell is open.
12. functions
    - Create a file `myfunc.sh`
    - write a function (should be same name as file)
    - `source myfunc.sh` -> will register the function.
    - `myfunc.sh test`
13. Commands return output using `STDOUT` and errors thorugh `STDERR` and a `Return Code`
    - `$?` gives return code of previous command
    - `$_` last argument from the last command
    - `$$` PID for current script
    - `!!` Entire last command (press enter after !!)
14. Short-circuiting operators
    - `false || echo "oops"` # will print oops
    - `true || echo "will not be printed"`
    - `true && echo "will be printed"`
    - `false && echo "will not be printed"`
    - `true ; echo "this will allways run"`
    - `false ; echo "this will also allways run"`
15. Expansions
    - command substituion `$(CMD)` will execute CMD and get the output of CMD and substitute it in place.
    - usecase for above `diff < (ls foo) < (ls bar)` whill show diff in files of foo and bar dirs.
    - `mkdir -p foo{1,2}/{1,2,3}.sh` will create foo1, foo2 and all sh files inside these dirs.
    - `cp project{1,2}`
    - `mkdir {foo}/{a...c}`
    - `mkdir -p {foo,bar}/{1..9}`
    - `rm -rf {foo,bar}`
16. finding stuff
    - tldr find to see good usecases, to execute a command for files found etc.
    - `fd` is alternative to `find`
    - `locate` is faster as it runs on indexed data. `updatedb` to update index.
    - `rg` is faster alternative to `grep` and is recursive.
    - `ack` is regex for developers and faster alternative to it is `ag`.
    - `fzf` fuzzy finder, interactive lookup.
    - `ctrl + r` reverse lookup.
    - `broot` file navigator.
17. shell script
    - `tree recursive` gives folder strcuture of the experiment.`./recursivegrep.sh recursive/fooa/fooa.txt recursive/fooa/foob.txt recursive/fooa/fooc.txt`
    - marco.sh dumps current working dir path to marco.txt and polo.sh cds us to that path regardless wherever we are.
    - crash.sh runs a code 100 times and simulates random crash. Idea is to redirect STDERR to a file and STDIO to the terminal.
