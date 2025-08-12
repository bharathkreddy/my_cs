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
