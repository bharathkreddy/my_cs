# Git Clean — Mini Cheat Sheet

## What `git clean` Does
Removes **untracked** stuff from your working tree.
- Won’t touch tracked or staged files.
- Destructive → always dry-run first.

## Core Options
- `-n` / `--dry-run` → **preview** what would be deleted.
- `-f` / `--force` → actually delete (required).
- `-d` → also remove **untracked directories**.
- `-x` → include files **ignored by .gitignore** (delete everything untracked).
- `-X` → delete **only ignored** files (keep other untracked files).
- `-i` → interactive (pick what to delete).
- `-e <pattern>` → **exclude** pattern from deletion (even if untracked).

## Common Recipes
- Preview untracked files to be removed:
  ```bash
  git clean -n
  ```
- Preview including untracked **directories**:
  ```bash
  git clean -n -d
  ```
- Delete untracked files (keep dirs):
  ```bash
  git clean -f
  ```
- Delete untracked files **and directories**:
  ```bash
  git clean -f -d
  ```
- Delete **ignored** files/folders only (e.g., build outputs):
  ```bash
  git clean -f -X
  ```
- Nuke **all** untracked (even those not ignored):
  ```bash
  git clean -f -x
  ```
- Interactive choose-what-to-remove:
  ```bash
  git clean -i
  ```
- Keep certain paths while cleaning:
  ```bash
  git clean -f -d -e "!keep-me/**" -e "notes.txt"
  ```

## Safety Checklist (Do These First)
1. **Preview**: `git clean -n` or `git clean -n -d`
2. **Check status**: `git status` (make sure nothing needed is “untracked”)
3. **Consider a safety net**:
   - Save untracked work: `git stash -u` (later `git stash pop`)
   - Or move important files out temporarily

## Related Gotchas & Tips
- `git reset --hard` **does not** remove untracked files; use `git clean`.
- If something shows as “untracked” but you want Git to track it:
  ```bash
  git add <path> && git commit -m "Track this"
  ```
- If Git is tracking a file you want treated as build output:
  ```bash
  echo "build/" >> .gitignore
  git rm -r --cached build/
  ```
- CI-like cleanup (wipe workspace):
  ```bash
  git reset --hard
  git clean -fdx
  ```
