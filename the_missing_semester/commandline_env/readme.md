# Command-Line Environment

1. Job Control
2. Terminal Multiplexers (tmux)
3. [Dotfiles](https://dotfiles.github.io/utilities/)

   - a common pattern is to create a dotfiles folder and version control it via git.
   - ~
     |-- .bashrc (simlink to file in dotfiles folder)
     |-- .vimrc
     |--dotfiles (vcs, with below files in it.)
     |- .bashrc (ln -s : simlink)
     |- .vimrc

4. Remote machines

### Job Control

1. check man signal
2. SIGTSTP pauses a process, in the terminal Ctrl+Z will prompt shell to send SIGTSTP signal (signal Termial stop)
3. We can continue the paused job in the foreground or in the background using `fg` or `bg` respectively.
4. `jobs ` command lists the unfinished jobs associated with current terminal session. These jobs can be refered to by their `pid` (process id).
5. `&` suffix in a command will run the command in the background, giving the prompt back, althought it will still use the shells STDOUT, which can be annoying.
6. closing the terminal sends `SIGHUP` (signal hangup) to all the childern process of the terminal. to prevent this from happening run the program with `nohup` or `disown` the process if already started before X ing the terminal or use tmux.
7. `SIGKILL` cant be captured by the process and it allways terminates the process immediately. However it leave children processes orphaned and running leaving the system in weird state with bad side-effects.
8. Run these
   a. sleep 1000
   b. ctrl+z (suspends the job)
   c. jobs (shows all jobs)
   d. bg %1 (starts the 1st suspended job)
   e. kill -STOP %1 (suspends again)
   f. kill -SIGHUP %1 (kills the process)
   g. nohup sleep 1000 & (runs a background job)
   h. kill -SIGHUP %1 (cant kill a nohup process via hangup)
   i. kill %2 (kills the process)
   j. ps aux : shows all processes
   k. ps aux | pgrep <process_name>
   l. pkill <process_name> kills all process which match process_name.
