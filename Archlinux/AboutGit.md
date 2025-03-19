# All this pages are about how to use __git__, a code manager.
## clone a repo or project
```shell
git clone <Git repo URL>
```
## Something should be customized before
- who are you?
```shell
git config --global user.name leejkee
git config --global user.email leejykee@yeah.net
```
- the default branch for git init
```
git config --global init.defaultBranch main
```
## Quick Start for my github
- step 1: create a new repository in your github
- step 2: select your directory your want to upload
```shell
# initilize your dir
git init
# add all your new files
git add .
# commit your changes
git commit -m "<message about this commit>"

# push your changes t remote repo 
# firstly
git remote add origin <your repo url>
git push -u origin main
# normally
git push origin main
```
## Using for ssh-keygen
what is ssh-keygen?  
Ssh-keygen is a tool for __creating new authentication key pairs for SSH__ . Such key pairs are used for automating logins, single sign-on, and for authenticating hosts.
- a example
```shell
ssh-keygen -t rsa -b 4096 -C <your email or others>
```
Something details are shown in [SSH Website](https://www.ssh.com/academy/ssh/keygen).
Then, upload your public key to your github.

## 合并冲突
- 本地修改可以放弃
```shell
git reset --hard
git pull origin main
```
- 本地修改需要保留
```shell
git stash             # 暂存本地修改
git pull origin main  # 拉取远程更新
git stash pop         # 取回本地修改
```