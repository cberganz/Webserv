# Webserv

## Branching process:

from main:
```
git branch myBranch
```
```
git checkout myBranch
```
From myBranch once changes are done:
```
git add .
```
```
git commit -m "message"
```
```
git push -u origin myBranch
```
-> You can stop the process here if you just want to save your files. You can get it back later with `git checkout myBranch` from anywhere.
```
git checkout main
```
Then, from main branch:
```
git pull
```
```
git merge myBranch
```
-> Then resolv conflicts if needed
```
git push
```

Once everything is good, delete the branch:
```
git branch -d myBranch
```
