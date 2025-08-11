# VIM EDITOR

[Vim cheatsheet](https://missing.csail.mit.edu/2020/editors/)
[vim game](https://vim-adventures.com/)
[Vim MasterClass](https://nt.udemy.com/course/vim-commands-cheat-sheet/learn/lecture/6452606#content)

NOTES:

1. Modes in VIM

   - `i`: insert mode
   - `r`: replace mode
   - `v`: visual mode
   - `⇧ v`: line visual
   - `⌃ v`: block visual
   - `:` : command-line mode
   - `esc` : get back to usual model.
     ⌘,⌥,⌃, ⇧

2. Normal mode - movements in normal mode

   - `hjkl` movements - takes a number at front ex 4j.
   - `w b` word by word forward and backward
   - `^ $` start and end of line
   - `⌃D ^U` up down by page.
   - `G gg` all the way down and all the way up.
   - `f{char} t{char}` find-a-char or to-a-char in same line
   - `o` opens a line and switches to insert mode.
   - `d` deletes and goes with motion commands. takes a number at front.
   - `X x` deleting previous char and next char
   - `u` undo (the last change made)
   - `^ r` redo
   - `y p` yank and paste and takes motion commands
   - `/` search and 'enter' to go to the word. `n` next find.

3. ## Insert mode
