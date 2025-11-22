1. What is the difference between git merge and git rebase?

Merge combines changes from one branch into another, creating a merge commit that keeps both histories.
Rebase moves or “replays” commits from one branch onto another, creating a linear history.

🧩 Tip: Use merge for shared branches, and rebase for private or local cleanup.

2. How do you resolve a merge conflict?

When Git can’t automatically merge changes, it marks conflict areas in files.
You resolve it manually by editing the file, keeping the correct content, then:

git add <file>
git commit


to complete the merge.

3. How do you revert a specific commit?

Use:

git revert <commit_id>


This creates a new commit that undoes the changes from the selected commit — it’s safe for shared repositories because it doesn’t rewrite history.

4. What does git cherry-pick do?

git cherry-pick <commit_id> applies a single commit from one branch to another.

🔧 Example use: if a fix on develop is needed in release, you can cherry-pick that commit without merging the whole branch.

5. Explain the difference between git reset --soft, --mixed, and --hard.
Command	Effect on Staging	Effect on Working Directory	Use Case
--soft	Keeps staged changes	Keeps local edits	Undo last commit but keep all changes staged
--mixed	Unstages files	Keeps local edits	Undo commit and unstage changes
--hard	Clears everything	Discards all local changes	Reset repo completely to a previous commit
6. What’s the purpose of git reflog?

git reflog records every action in your local Git repo — commits, checkouts, resets, etc.

It’s mainly used to recover lost commits or branches that may not appear in git log.

7. How do you recover a deleted branch or commit?

You can restore it using the reflog:

git reflog
git checkout -b <branch_name> <commit_id>


This recreates the deleted branch from the commit reference.

8. What is a tag in Git, and when do you use it?

A tag marks a specific point in history, usually for version releases.

git tag v1.0
git push origin v1.0


Tags help identify stable or release-ready versions of the code.

9. How do you handle versioning in large projects with multiple developers?

We use a branching strategy (like Git Flow):

main → production-ready code

develop → integration branch

feature/* → new features

release/* → pre-production

hotfix/* → urgent fixes

Pull requests and code reviews ensure stable version control.

10. What’s your Git branching strategy in your team?

We follow a feature-branch workflow.
Each developer creates a branch for a feature, pushes to remote, and merges it via pull request into develop.
After testing, develop is merged into main for stable releases.


==============
GIT COMMANDS
==============

🧭 Basic Setup

git config → Set user name, email, or other config settings.

git init → Create a new Git repository.

git clone <url> → Copy an existing repository.


📂 Working with Files

git status → Show changed files in working directory.

git add <file> → Stage file(s) for commit.

git add . → Stage all modified files.

git rm <file> → Remove file from repo.

git mv <old> <new> → Rename or move a file.


💾 Committing Changes

git commit -m "message" → Save staged changes with a message.

git commit -am "message" → Add + commit all tracked files.

git log → Show commit history.

git show <commit> → Show details of a commit.


🔁 Branches

git branch → List branches.

git branch <name> → Create a new branch.

git checkout <branch> → Switch to another branch.

git checkout -b <branch> → Create and switch to new branch.

git merge <branch> → Merge branch into current branch.

git branch -d <branch> → Delete a branch.

🌐 Remote Repositories


git remote -v → Show remote URLs.

git remote add origin <url> → Link local repo to remote.

git push origin <branch> → Upload commits to remote.

git pull → Fetch + merge from remote repo.

git fetch → Download updates from remote (no merge).

git clone <url> → Copy remote repo locally.


🧹 Undo / Reset

git reset <file> → Unstage file (keep changes).

git reset --hard <commit> → Reset to commit and discard changes.

git revert <commit> → Undo commit by creating a new one.

git clean -fd → Remove untracked files/folders.

git stash → Temporarily save uncommitted work.

git stash pop → Reapply stashed changes.


🧠 Others

git diff → Show differences between changes.

git tag <name> → Create a tag (for version marking).

git blame <file> → Show who last modified each line.

git reflog → Show all local Git operations (useful for recovery)