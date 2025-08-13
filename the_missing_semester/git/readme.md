[ohShitGit](https://ohshitgit.com/)
[the git boot](https://git-scm.com/book/en/v2)
[High Level](https://jwiegley.github.io/git-from-the-bottom-up)

# Git Developer Cheat Sheet

> BRKs cheat sheet
>
> 1. [ohShitGit](https://ohshitgit.com/)
> 2. [the git boot](https://git-scm.com/book/en/v2)
> 3. [High Level](https://jwiegley.github.io/git-from-the-bottom-up)

---

## 1. Setup \& Configuration

1. **Install Git (macOS/Linux)**

```bash
brew install git          # Homebrew
sudo apt-get install git  # Debian/Ubuntu
```

2. **Global identity**

```bash
git config --global user.name  "Alice"
git config --global user.email "alice@example.com"
```

3. **Editor \& diff tool**

```bash
git config --global core.editor "code --wait"
git config --global diff.tool   "vimdiff"
```

4. **Enable colored output \& helpful aliases**

```bash
git config --global color.ui auto
git config --global alias.lg "log --oneline --graph --decorate --all"
```

## 2. Creating or Getting a Repository

1. **Start a new repo in the current folder**

```bash
git init
```

2. **Clone an existing repo**

```bash
git clone https://github.com/user/project.git
# --branch main  # Optional: select branch
```

## 3. Snapshotting Your Work

1. **Check status \& differences**

```bash
git status
git diff                 # unstaged →
git diff --staged        # staged   →
git diff branch1 branch2 # diff FROM branch1 TO branch2
```

2. **Stage \& commit**

```bash
git add README.md
git add .                # stage all modified/added files
git commit -m "Add README"
git commit -am "Quick commit"   # add *and* commit tracked files
```

3. **Amend the last commit**

_we can add changes to last commit, just stage the changes and do git commit --ammend and this would include all these staged changes in prior commit._
Logs of changes along with changes can be seen by `git log -p`

```bash
git commit --amend -m "Better message"
```

## 4. Working with Remotes

1. **Add, view, remove**

```bash
git remote add origin git@github.com:user/repo.git
git remote -v
git remote remove origin
```

2. **Push \& pull**
   _git pull is essentially shorthand for a git fetch followed by a merge of whatever branch was just fetched with the branch where HEAD is at_

```bash
git push origin main           # first push may need -u
git pull --rebase origin main  # avoid merge bubbles
```

3. **Fetch without merging**

```bash
git fetch origin
```

## 5. Branching \& Merging

1. **Create, list, switch**

```bash
git branch feature/login   # create branch (no switch)
git switch feature/login   # modern way to switch
git branch -a              # local + remote branches
```

2. **Merge another branch into current**

```bash
git merge feature/login          # fast-forward or 3-way
git merge --no-ff feature/login  # force merge commit
```

3. **Delete a branch**

```bash
git branch -d feature/login    # safe
git branch -D feature/login    # force
```

## 6. Moving Around the Repository Tree

1. **Checkout any revision**

```bash
git checkout 2f4e3c8        # detached HEAD
git checkout v2.0.0         # tag
git checkout main           # back to branch
```

2. **Navigate files from past revisions**

```bash
git show HEAD~2:src/main.c
git restore --source=HEAD~1 package.json   # modern restore
```

## 7. Manipulating Pointers (HEAD, Branches, Tags)

1. **Move a branch pointer (fast-forward)**
   _usecase: Bug found, add a commit with all print statements and loggers, add a commit with bugFix, now move only bugFix commit to main (you can use cherry-pick for this as well.)_

```bash
git branch -f main 2f4e3c8   # moves the pointer of main to commit with hash 2f42...
git push -f origin main       # rewrite remote
```

2. **Move HEAD backward/forward**

Mental model: three areas
HEAD → which commit your branch points to.
Index (staging area) → what will be in your next commit.
Working tree → files on disk.

Different reset modes change different parts:

| Command                         | Moves HEAD | Resets Index | Resets Working Tree |
| ------------------------------- | ---------- | ------------ | ------------------- |
| `git reset --soft X`            | ✅         | ❌           | ❌                  |
| `git reset --mixed X` (default) | ✅         | ✅           | ❌                  |
| `git reset --hard X`            | ✅         | ✅           | ✅ (tracked only)   |

**TL;DR of the behaviors**
`--soft`: rewinds branch pointer only; leaves your staged+working files as-is → previous commit’s changes become staged.

`--mixed`: also resets the index → previous staged changes become unstaged/untracked if they don’t exist in the new target commit; working tree still carries the files on disk.

`--hard`: also resets the working tree → tracked files are overwritten to match the target commit; untracked files remain.

```bash
git reset --hard HEAD~3     # dangerous! resets index & WD
git reset --soft HEAD~1     # keep changes staged
```

3. **Create \& manage tags**
   _branches move around tags are anchors, like bookmarks, we cant checkout tags and edit the commits_

```bash
git tag v2.1.0 [optional commit]       # lightweight
git tag -a v2.1.0 -m "Release 2.1.0"  # annotated
git push origin --tags
```

## 8. `git reflog` – Your Safety Net

1. **View every HEAD movement (90 days by default)**

```bash
git reflog
```

_downloads remote commits and moves only origin/main[branch] pointers to the new commits, local main[branches] point as is to local commits._

2. **Recover lost work**

```bash
git checkout <reflog-hash>
# or
git reset --hard <reflog-hash>   # move branch back
```

## 9. Rebase Workflows

1. **Interactive rebase (squash, edit, reorder)**

```bash
git rebase -i HEAD~5
# pick 1a2b3c4 Fix bug
# squash 3d4e5f Minor typo
```

2. **Update a feature branch onto latest main**

```bash
git switch feature/login
git fetch origin
git rebase origin/main
```

3. **Abort or continue**

```bash
git rebase --abort
git rebase --continue
```

#### full rebase premier

The `git rebase -i` (interactive rebase) command opens an editor with a list of commits, allowing you to modify the commit history of your branch. The editor displays the commits in the order they will be applied (oldest at the top, newest at the bottom), along with instructions for actions like `pick`, `reword`, `edit`, `squash`, `fixup`, and `drop`. Each action you specify in the editor instructs Git on how to handle the corresponding commit during the rebase process.

Your `git rebase -i` editor shows a series of commits, and you want to perform the following actions:

1. For `cdd7198`: Use the commit but edit its commit message ("Helo Volrd feature").
2. For `11cabb7`: Use the commit but stop to amend it (e.g., modify its contents or message).
3. For `cce9b90`, `73fd3aa`, `c97a407`: Meld (combine) these into a single commit, keeping `c97a407`’s message ("Add doc - step 3").
4. For `ad78bfd`: Drop the commit ("Really made the thingy done").

Below, I’ll explain how to achieve each of these goals, including the mechanism behind each action in the interactive rebase process.

---

### Step-by-Step Guide to Modify the Rebase Instructions

1. **Understand the Interactive Rebase Editor**

   - When you run `git rebase -i <base>`, Git opens an editor (e.g., Vim, Nano) with a list of commits starting from the commit after `<base>` up to the current HEAD.
   - Each line starts with a command (e.g., `pick`), followed by the commit hash and message.
   - You modify the commands (e.g., change `pick` to `reword`, `edit`, `squash`, or `drop`) or reorder the lines to instruct Git how to rewrite the history.
   - After saving and closing the editor, Git processes the commits in the order listed, applying each according to the specified command.

2. **Modify the Rebase Instructions**
   Open the interactive rebase editor (as shown in your input). Modify the lines to achieve your goals as follows:

   ```plaintext
   reword cdd7198 Helo Volrd feature
   edit 11cabb7 Finished HW feature
   drop ad78bfd Really made the thingy done
   pick ffcecb9 debugging
   pick a3cc5b9 important secret
   squash cce9b90 Add doc - step 1
   squash 73fd3aa Add doc - step 2
   pick c97a407 Add doc - step 3
   pick 3dcd6f3 Test for feature hello world
   pick 3e44e95 I forgot a semicolon
   ```

   Let’s break down each change and the mechanism behind it:

---

### 1. For `cdd7198`: Use Commit, but Edit the Commit Message

- **Action**: Change `pick cdd7198 Helo Volrd feature` to `reword cdd7198 Helo Volrd feature`.
- **Mechanism**:
  - The `reword` command tells Git to use the commit (`cdd7198`) as is (keeping its changes) but pause during the rebase to allow you to edit its commit message.
  - When Git processes this commit, it will open your editor again, showing the current message ("Helo Volrd feature"). You can modify it (e.g., fix the typo to "Hello World feature").
  - After you save and close the editor, Git applies the commit with the new message and continues the rebase.
- **Steps in the Editor**:
  - Replace `pick` with `reword` for the line with `cdd7198`.
  - Save and exit the editor (e.g., in Vim, type `:wq` and press Enter).
  - When Git pauses for `reword`, the editor will open with "Helo Volrd feature". Edit it (e.g., to "Hello World feature"), save, and exit.

---

### 2. For `11cabb7`: Use Commit, but Stop for Amending

- **Action**: Change `pick 11cabb7 Finished HW feature` to `edit 11cabb7 Finished HW feature`.
- **Mechanism**:
  - The `edit` command tells Git to apply the commit (`11cabb7`) but pause the rebase process immediately after applying it.
  - During this pause, you can amend the commit by:
    - Modifying files in the working directory (e.g., add or edit files).
    - Running `git commit --amend` to update the commit’s contents and/or message.
    - Resuming the rebase with `git rebase --continue`.
  - This is useful for fixing mistakes in a commit (e.g., adding missing changes or updating the commit message).
- **Steps in the Editor**:
  - Replace `pick` with `edit` for the line with `11cabb7`.
  - Save and exit the editor.
  - When Git pauses (after applying `11cabb7`), you’ll see a message like `Stopped at 11cabb7... Finished HW feature`.
  - Make changes (e.g., edit files, add new files with `git add`), then run:
    ```bash
    git commit --amend
    ```
    - This opens the editor to modify the commit message (if desired) and includes any new changes staged with `git add`.
  - Resume the rebase:
    ```bash
    git rebase --continue
    ```

---

### 3. For `cce9b90`, `73fd3aa`, `c97a407`: Meld into `c97a407`

- **Action**:
  - Keep `pick c97a407 Add doc - step 3`.
  - Change `pick cce9b90 Add doc - step 1` to `squash cce9b90 Add doc - step 1`.
  - Change `pick 73fd3aa Add doc - step 2` to `squash 73fd3aa Add doc - step 2`.
- **Mechanism**:
  - The `squash` command combines the specified commit (e.g., `cce9b90` or `73fd3aa`) with the previous `pick` or `squash` commit (in this case, `c97a407`).
  - Git merges the changes from `cce9b90`, `73fd3aa`, and `c97a407` into a single commit, keeping the commit message of the `pick` commit (`c97a407`: "Add doc - step 3") by default.
  - After saving the rebase instructions, Git will open the editor to let you edit the combined commit message. You can keep "Add doc - step 3" or write a new message (e.g., "Add documentation for steps 1, 2, and 3").
  - The resulting commit will include all changes from `cce9b90`, `73fd3aa`, and `c97a407` under a single commit hash with the message you choose.
- **Steps in the Editor**:
  - For `cce9b90` and `73fd3aa`, replace `pick` with `squash`.
  - Ensure `c97a407` remains `pick` (it’s the target commit for the squash).
  - The order matters: `squash` commits are combined into the nearest preceding `pick` commit, so keep `c97a407` after `cce9b90` and `73fd3aa`.
  - Save and exit the editor.
  - When Git pauses for the combined commit message, the editor will show the messages of all three commits (`cce9b90`, `73fd3aa`, `c97a407`). Edit to something like "Add documentation for steps 1, 2, and 3" or keep "Add doc - step 3", then save and exit.

---

### 4. For `ad78bfd`: Drop the Commit

- **Action**: Change `pick ad78bfd Really made the thingy done` to `drop ad78bfd Really made the thingy done`.
- **Mechanism**:
  - The `drop` command tells Git to exclude the commit (`ad78bfd`) from the rebase process, effectively removing it from the branch’s history.
  - The changes introduced by `ad78bfd` will be discarded, and the commit will no longer appear in the branch’s log.
  - Alternatively, you can simply delete the line for `ad78bfd` in the editor, which has the same effect as `drop`.
- **Steps in the Editor**:
  - Replace `pick` with `drop` for the line with `ad78bfd`, or delete the line entirely.
  - Save and exit the editor.
  - Git will skip `ad78bfd` during the rebase, removing it from the history.

---

### Final Rebase Instructions

Your modified rebase editor should look like this:

```plaintext
reword cdd7198 Helo Volrd feature
edit 11cabb7 Finished HW feature
drop ad78bfd Really made the thingy done
pick ffcecb9 debugging
pick a3cc5b9 important secret
squash cce9b90 Add doc - step 1
squash 73fd3aa Add doc - step 2
pick c97a407 Add doc - step 3
pick 3dcd6f3 Test for feature hello world
pick 3e44e95 I forgot a semicolon
```

### What Happens During the Rebase

1. **For `cdd7198`**:

   - Git applies the commit and pauses to let you edit the message (e.g., change "Helo Volrd feature" to "Hello World feature").
   - Save and exit to continue.

2. **For `11cabb7`**:

   - Git applies the commit and pauses (`Stopped at 11cabb7...`).
   - You can modify files, stage them with `git add`, and run `git commit --amend`.
   - Run `git rebase --continue` to proceed.

3. **For `ad78bfd`**:

   - Git skips this commit, removing it from the history.

4. **For `cce9b90`, `73fd3aa`, `c97a407`**:

   - Git combines these into a single commit with the changes from all three.
   - The editor opens to edit the combined commit message. Keep "Add doc - step 3" or write a new one, then save and exit.

5. **For the remaining commits** (`ffcecb9`, `a3cc5b9`, `3dcd6f3`, `3e44e95`):
   - Git applies them as is (`pick` means keep the commit unchanged).

### After Saving the Rebase Instructions

- Save and exit the editor (e.g., `:wq` in Vim).
- Git will process the commits in order, pausing for:
  - `reword` (to edit the message for `cdd7198`).
  - `edit` (to amend `11cabb7`).
  - `squash` (to combine the documentation commits and edit the message).
- If conflicts occur (e.g., if changes in `ad78bfd` overlap with others), Git will pause and prompt you to resolve them. Run `git rebase --continue` after resolving conflicts.

### Post-Rebase Verification

After the rebase completes:

- Check the new commit history:
  ```bash
  git log --oneline --graph --all
  ```
  - You should see:
    - `cdd7198` with the updated message (e.g., "Hello World feature").
    - `11cabb7` with any amendments you made.
    - `ad78bfd` gone (dropped).
    - A single commit combining `cce9b90`, `73fd3aa`, and `c97a407` (with the message you chose).
    - The remaining commits (`ffcecb9`, `a3cc5b9`, `3dcd6f3`, `3e44e95`) unchanged.
- Verify the files in the branch:
  ```bash
  git ls-tree -r HEAD --name-only
  ```
  - Ensure the expected files (e.g., `file3`, `file5` from your `bugFix` branch context) are present and `file4` is not (since you want it only in `main`).

### Important Notes

- **Backup Before Rebase**: Rebasing rewrites history, which can be destructive. Before starting, create a backup of your branch:
  ```bash
  git branch backup-bugFix
  ```
  If something goes wrong, you can restore with `git checkout backup-bugFix`.
- **Conflicts**: If dropping `ad78bfd` or squashing commits causes conflicts (e.g., overlapping changes), Git will pause and show the conflicts. Resolve them by editing the files, staging with `git add`, and running `git rebase --continue`.
- **Pushing Changes**: If the `bugFix` branch was already pushed to a remote repository (e.g., GitHub), you’ll need to force-push after rebasing:
  ```bash
  git push --force
  ```
  Be cautious, as this rewrites the remote history and can affect collaborators.
- **Editor Usage**: If you’re unfamiliar with the editor (e.g., Vim), let me know which editor you’re using, and I can provide specific save/exit instructions (e.g., `:wq` for Vim, `Ctrl+O, Ctrl+X` for Nano).
- **Context with `bugFix` Branch**: Your earlier context indicates you’re on the `bugFix` branch with `file3` and `file5`, and `file4` should stay in `main`. The rebase doesn’t directly affect these files unless they were modified in the listed commits. Ensure `file4` isn’t added during the `edit` step for `11cabb7`.

If you encounter conflicts, errors, or need help with specific steps (e.g., resolving conflicts or amending `11cabb7`), share the output or details, and I’ll guide you further!

## 10. Cherry-Picking

1. **Apply a single commit onto current HEAD**

```bash
git cherry-pick 1a2b3c4     # adds commit with hash 1a2... to current HEAD
```

2. **Pick a range (inclusive)**

```bash
git cherry-pick a1b2c3d^..d4e5f6g
```

3. **Resolve conflicts, then**

```bash
git cherry-pick --continue
git cherry-pick --abort
```

## 11. Reset vs. Revert

1. **`reset` (rewrite history)**

```bash
git reset --hard HEAD~1
```

2. **`revert` (safe, new commit)**

```bash
git revert HEAD~1
```

## 12. Stashing Work-in-Progress

1. **Save \& list stashes**

```bash
git stash push -m "wip: ui tweak"
git stash list
```

2. **Apply \& drop**

```bash
git stash apply stash@{2}
git stash drop  stash@{2}
git stash pop   # apply + drop latest
```

## 13. History \& Searching

1. **Logs**

```bash
git log --oneline --graph --decorate --all
git log -p --follow README.md
```

2. **Search**

```bash
git grep "TODO"
git log -S'initDatabase(' --source --all
```

## 14. Bisecting Bugs

1. **Binary search for offending commit**

```bash
git bisect start
git bisect bad                # current commit bad
git bisect good v2.0.0        # known good tag
git bisect run npm test       # automate
git bisect reset              # back to original HEAD
```

## 15. Submodules \& Subtrees

1. **Add, update, remove submodule**

```bash
git submodule add https://github.com/lib/libxyz.git vendor/libxyz
git submodule update --remote
git submodule deinit -f vendor/libxyz
rm -rf .git/modules/vendor/libxyz
git rm -f vendor/libxyz
```

## 16. Cleaning the Working Directory

1. **Remove untracked files**

```bash
git clean -fdx      # *irrevocable* (add -n to preview)
```

## 17. Signing \& Verification

1. **Sign a commit or tag**

```bash
git commit -S -m "Signed commit"
git tag -s v2.2.0 -m "Signed release"
```

## 18. Multi-Remote Collaboration

1. **Track upstream fork**

```bash
git remote add upstream https://github.com/parent/project.git
git fetch upstream
git rebase upstream/main
```

## 19. Performance \& Maintenance

1. **Prune unreachable objects \& optimize**

```bash
git gc --prune=now --aggressive
git repack -ad
```

## 20. Helpful One-Liners

1. **List files changed between two refs**

```bash
git diff --name-only v1.0.0..v2.0.0
```

2. **Find commits by author since last month**

```bash
git log --author="alice" --since="1 month ago" --pretty=oneline
```

3. **Show remote URL for the current branch**

```bash
git remote get-url origin
```

---

### Quick Legend

- **HEAD** – pointer to _current_ commit.
- **Index / Staging Area** – snapshot slated for the next commit.
- **Working Directory (WD)** – your actual files on disk.
- **Origin** – default name for the primary remote.

### Anatomy of git files

I start with this below state

```bash
$ ls -lah
total 20K
drwxrwxr-x 4 reddybharath_k reddybharath_k 4.0K Aug 12 18:38 .
drwxrwxr-x 3 reddybharath_k reddybharath_k 4.0K Aug 12 18:38 ..
drwxrwxr-x 8 reddybharath_k reddybharath_k 4.0K Aug 12 18:38 .git
drwxrwxr-x 3 reddybharath_k reddybharath_k 4.0K Aug 12 18:38 src
-rw-rw-r-- 1 reddybharath_k reddybharath_k   29 Aug 12 18:38 test.md

$ git log --oneline
0b36626 (HEAD -> master) Fill test.md
4083bcc Put data in main.h
62b73d1 Add folders
fb0e2b3 add test.md
```

- Lets grab the Commit SHA at HEAD. We use that to see what type it is and contents of it. _git cat-file_ `-t` flag show object type (one of 'blob', 'tree', 'commit', 'tag', ...). This is a commit (commit object envelops tree object, tree can contain other trees or blobs.)

```bash
$ git rev-parse HEAD
0b366266812385a4546d0f2edb874d77d2f3ef53
# see this matches the git log

$ git cat-file -t $(git rev-parse HEAD)
commit  # type of object

$ git cat-file -p $(git rev-parse HEAD)
tree fed4d7381b37c4b1e1cf925f5de0b992272d6b5e
parent 4083bcc005a6c2499183b8d4e32baaa94b4069db   # see git log
author badex <test@test.com> 1755023891 +0000
committer badex <test@test.com> 1755023891 +0000

Fill test.md
```

- lets check the contents of the tree recusively (-t : recusrive, -l give size)

```bash
$ git ls-tree -t -l fed4d7381b37c4b1e1cf925f5de0b992272d6b5e
040000 tree 68ebdecef990e7a93b49666c59e237f7b961403a       -    src
100644 blob 3e01ae02c5a70d3a92fada56dc20457a6e4deb52      29    test.md
```

- from here on we can keep tracking parents and for each parent expand the tree and inspect the blob with below commands

```bash
TREE=<a tree sha>
git ls-tree -t $TREE

BLOB=<a blob sha>
git cat-file -s $BLOB        # size
git cat-file -p $BLOB        # contents
git cat-file -t $BLOB        # type (blob)
```
