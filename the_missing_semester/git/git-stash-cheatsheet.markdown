# Git Stash Cheatsheet

This cheatsheet covers all essential `git stash` commands and concepts, explaining what each does and when to use it. Git stash temporarily saves uncommitted changes (staged, unstaged, and optionally untracked/ignored files) to allow context switching without committing.

## Core Concepts

- **Purpose**: Save incomplete changes to revert the working directory to a clean state (matching HEAD) without committing.
- **What it saves**:
  - Staged changes (files added with `git add`).
  - Unstaged changes (modified tracked files).
  - Untracked files (with `--include-untracked` or `-u`).
  - Ignored files (with `--all` or `-a`).
- **Storage**: Stashes are stored as commit-like objects in `.git/refs/stash`, organized as a stack (last in, first out).
- **When to use**: Short-term context switching (e.g., switching branches, pulling changes, or testing ideas).
- **Limitations**: Stashes are local (not pushed to remotes), can cause conflicts when applied, and are not a substitute for commits.

## Commands and Their Functions

| Command | Description | Use Case |
|---------|-------------|----------|
| `git stash` | Saves staged and unstaged changes with a default message ("WIP on <branch>: <hash> <message>"). Resets working directory to HEAD. | Quick save when switching tasks (e.g., to review a PR). |
| `git stash save "message"` | Saves changes with a custom message for clarity. | Organize stashes for later reference (e.g., `git stash save "WIP on login feature"`). |
| `git stash --include-untracked` (or `-u`) | Includes untracked files in the stash. | Save new files not yet added to Git (e.g., new scripts or assets). |
| `git stash --all` (or `-a`) | Includes untracked and ignored files. | Save everything, including `.gitignore`-excluded files (e.g., build artifacts). |
| `git stash list` | Lists all stashes with their indices and messages (e.g., `stash@{0}: WIP on main`). | Review saved stashes to decide which to apply or drop. |
| `git stash apply` | Reapplies the latest stash (`stash@{0}`) to the working directory without removing it from the stash list. | Reapply changes to test or merge with current work. |
| `git stash apply stash@{n}` | Applies a specific stash (e.g., `stash@{1}`). | Reapply an older stash without affecting newer ones. |
| `git stash pop` | Applies the latest stash and removes it from the stash list if successful. | Resume work on the most recent stash and clean up. |
| `git stash pop stash@{n}` | Applies and removes a specific stash. | Resume and clean up a specific stash. |
| `git stash drop` | Removes the latest stash (`stash@{0}`) without applying it. | Discard unwanted recent changes. |
| `git stash drop stash@{n}` | Removes a specific stash. | Clean up a specific stash no longer needed. |
| `git stash clear` | Deletes all stashes in the repository. | Reset the stash list when all stashes are obsolete. |
| `git stash show` | Shows a summary of changes in the latest stash. | Check what changes a stash contains before applying. |
| `git stash show -p` | Shows the full diff of the latest stash. | Inspect detailed changes for debugging or review. |
| `git stash show stash@{n}` | Shows changes for a specific stash. | Review a specific stash’s contents. |
| `git stash branch <branch-name>` | Creates a new branch and applies the latest stash, dropping it from the stash list. | Turn a stash into a proper branch for long-term work. |
| `git stash branch <branch-name> stash@{n}` | Creates a branch from a specific stash. | Start a branch from an older stash (e.g., for a forgotten task). |

## Common Scenarios and Commands

1. **Switching Branches with Uncommitted Changes**
   - **Problem**: You're editing `app.js` on `main` but need to switch to `dev` for a hotfix.
   - **Solution**:
     ```bash
     git stash --include-untracked  # Save changes, including new files
     git checkout dev
     # Work on hotfix
     git checkout main
     git stash pop  # Resume work
     ```

2. **Pulling Remote Changes with Local Conflicts**
   - **Problem**: `git pull` fails because you modified `config.yaml`, which was updated remotely.
   - **Solution**:
     ```bash
     git stash
     git pull
     git stash pop  # Resolve conflicts if needed
     git add config.yaml
     git commit -m "Update config with fixes"
     ```

3. **Pausing Work for a Bug Fix**
   - **Problem**: Halfway through a feature on `feature/ui`, you need to fix a bug on `main`.
   - **Solution**:
     ```bash
     git stash save "WIP on UI feature"
     git checkout main
     git checkout -b bugfix/crash
     # Fix bug, commit, push
     git checkout feature/ui
     git stash pop
     ```

4. **Testing an Idea Without Committing**
   - **Problem**: You're tweaking `style.css` but want to try a different approach without losing your current changes.
   - **Solution**:
     ```bash
     git stash
     # Try new changes
     git restore style.css  # Discard new attempt
     git stash pop  # Restore original changes
     ```

5. **Managing Multiple Stashes**
   - **Problem**: You have several stashes and need to organize them.
   - **Solution**:
     ```bash
     git stash list  # View stashes
     git stash show stash@{1}  # Inspect specific stash
     git stash branch old-task stash@{1}  # Move stash to a branch
     git stash clear  # Clear remaining stashes
     ```

## Best Practices
- **Descriptive Messages**: Use `git stash save "message"` for clarity (e.g., "Login form tweaks").
- **Short-Term Use**: Stashes are for temporary storage; commit to branches for long-term work.
- **Check Before Dropping**: Use `git stash show -p` to avoid losing important changes.
- **Backup**: Stashes are local—back up critical work with commits or branches.
- **Combine with Branches**: Use `git stash branch` to convert stashes into proper branches.

## Pitfalls
- **Forgotten Stashes**: Regularly check `git stash list` to avoid losing track.
- **Conflicts**: Applying stashes can cause merge conflicts—resolve like merges.
- **No Remote Sync**: Stashes don’t push to remotes; use branches for collaboration.
- **Accidental Drops**: `git stash drop` and `clear` are irreversible—verify first.

## Quick Alias Tip
Add a stash alias to your `~/.gitconfig` for convenience:
```bash
git config --global alias.stl "stash list"
```