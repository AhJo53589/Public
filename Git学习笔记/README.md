# Git学习笔记

---
## 在 Git 中 Checkout 历史版本
### 从某个历史版本创建新的分支
在 Git 中从当前分支创建并检出新分支的命令是  
```
git checkout -b name-of-new-branch
```

这个命令实际上是  
```
git checkout -b name-of-new-branch current-branch
```
的简写形式。也就是说，当我们不指定 checkout 起点时，Git 默认从当前活动分支开始创建新的分支。

### 将某个文件的历史版本 checkout 到工作区
大多数时候，我们可能只需要对某一个文件做细小的修补，因此只 checkout 该文件就行了，并不需要操作整个 commit 或分支。

上一节我们介绍了如何将某个历史版本完整地 checkout 到工作区。实际上，我们只需要在上一节的命令之后加上需要 checkout 的文件即可。

```
git checkout <sha1-of-a-commit> </path/to/your/file>
```

当然，有时候你需要将某个文件的历史版本 checkout 出来，并以一个新的名字保存。这时候可以这么做：
```
git show <sha1-of-a-commit>:</path/to/your/file> > </new/name/of/the/file>
```