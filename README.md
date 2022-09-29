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
