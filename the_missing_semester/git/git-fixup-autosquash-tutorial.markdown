# Tutorial: Fixing a Commit with `git commit --fixup` and `git rebase --autosquash`

This tutorial explains how to fix a spelling error in a file (e.g., `README`) from a past commit using Git's `fixup` and `autosquash` features. We'll use `git commit --fixup` to create a correction commit and `git rebase --autosquash --interactive` to combine it with the original commit.

## Prerequisites
- A Git repository with a commit history.
- A specific commit (e.g., `0a75e8e` with message "Add documentation") that contains a file with a spelling error.
- Familiarity with basic Git commands and a text editor (e.g., Vim, Nano).

## Example Scenario
You have the following commit history (`git log --oneline`):
```
b442a9e (HEAD -> master) Test for feature hello world
57e013f Add Unrelated stuff feature
0a75e8e Add documentation
98fcbb8 Hello World feature
d4bf722 (tag: v0.0) Initial commit
```
You want to fix a spelling error in the `README` file introduced in commit `0a75e8e`.

## Steps

1. **Edit the File**
   - Open the `README` file in your editor (e.g., `nano README` or `code README`).
   - Fix the spelling error.
   - Save and exit.

2. **Stage and Create a Fixup Commit**
   - Stage the modified file:
     ```bash
     git add README
     ```
   - Create a `fixup` commit targeting the original commit (`0a75e8e`):
     ```bash
     git commit --fixup=0a75e8e
     ```
   - This creates a new commit with a message like `fixup! Add documentation`.

3. **Start an Interactive Rebase with Autosquash**
   - Run an interactive rebase starting from the commit before `0a75e8e` (or use the `v0.0` tag for all commits):
     ```bash
     git rebase --autosquash --interactive v0.0
     ```
   - The editor opens with preconfigured instructions, e.g.:
     ```
     pick 98fcbb8 Hello World feature
     pick 0a75e8e Add documentation
     fixup abc1234 fixup! Add documentation
     pick 57e013f Add Unrelated stuff feature
     pick b442a9e Test for feature hello world
     ```
   - The `fixup` commit is automatically placed after `0a75e8e` with the `fixup` action, thanks to `--autosquash`.
   - Save and exit the editor (e.g., `:wq` in Vim, or `Ctrl+O`, `Enter`, `Ctrl+X` in Nano).

4. **Complete the Rebase**
   - Git combines the `fixup` commit’s changes into `0a75e8e`, keeping the original message ("Add documentation").
   - If conflicts occur (e.g., later commits modified `README`):
     - Edit `README` to resolve conflicts.
     - Stage the resolved file: `git add README`.
     - Continue the rebase: `git rebase --continue`.

5. **Verify the Changes**
   - Check the updated commit history:
     ```bash
     git log --oneline
     ```
     Expected output (hashes will differ):
     ```
     def5678 (HEAD -> master) Test for feature hello world
     ghi9012 Add Unrelated stuff feature
     jkl3456 Add documentation
     98fcbb8 Hello World feature
     d4bf722 (tag: v0.0) Initial commit
     ```
   - Verify the `README` file:
     ```bash
     cat README
     ```
     Ensure the spelling error is fixed.

6. **Push Changes (if applicable)**
   - If the branch was pushed to a remote repository, force-push the rewritten history:
     ```bash
     git push --force
     ```
   - **Caution**: Coordinate with collaborators, as force-pushing overwrites remote history.

## Tips
- **Backup**: Before rebasing, create a backup branch:
  ```bash
  git branch backup-master
  ```
- **Conflicts**: Resolve conflicts by editing files, staging them, and continuing the rebase.
- **Editor**: Use `git config --global core.editor <editor>` to set your preferred editor (e.g., `nano`, `vim`).
- **Fixup vs. Squash**: `fixup` keeps the original commit message; `squash` prompts for a new message.

## Why Use This Method?
- `git commit --fixup` simplifies creating a correction commit.
- `git rebase --autosquash` automates reordering and marking the `fixup` commit, reducing manual editing.