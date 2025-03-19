---
title: Hexo博客编写
date: 2022-01-29 20:25:33
tags:
- linux
- hexo
categories:
- 新的入门
- Hexo
---

1、Create a new blog

`hexo n post "name"`n表示new，**post**文章作为默认layout，（不加即为post）还有**draft**草稿，**page**页面,运行结果如下：

```bash
[ljk@leejk myBlog]$ hexo n post "Hexo博客编写"
INFO  Validating config
INFO  Created: ~/myBlog/source/_posts/Hexo博客编写.md
```

在这之前需要先初始化一个文件夹存放hexo配置文件和其他文件，使用命令`hexo init myBlog` or `mkdir myBlog;cd myBlog;hexo init`，这个命令会下载一些东西，需要等待。。。

在hexo init的目录下，有一个source文件夹，用于存放用户文件资源，在该文件夹下可以找到_posts文件夹，里面存放了name.md文件，不同布局存放的文件夹不同。

2、Edit the Front-matter

编辑前言，这个地方写文章的基本信息，包含标题，创建时间，分类等等。。。

```bash
[ljk@leejk ~]$ cat ~/myBlog/source/_posts/Hexo博客编写.md  
---
title: Hexo博客编写` 
date: 2022-01-29 20:25:33` 
tags:
---
```

要在文章第一行使用`---`和结束处使用其隔开，下面列出几个常用，具体请参考[hexo官方文档](https://hexo.bootcss.com/docs/front-matter.html)

| 参数        | 含义                 |
| ----------- | -------------------- |
| title       | 标题                 |
| categoreies | 分类（后文细述）     |
| tags        | 标签                 |
| comments    | 评论功能，默认为true |

为文章添加标签和分类

本文标签为：linux,blog,hexo

本文分类为：新的入门>Hexo博客

```yaml
categories:
- 新的入门（第一层级）
- Hexo博客（第二层级）
tags:
- linux
- blog
- hexo
```

