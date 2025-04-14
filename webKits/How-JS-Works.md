## TypeScript / JavaScript 是如何工作的，从源码到运行过程

### 从ts源码出发，它是如何变成二进制可执行机器码的

- 经过tsc编译为JavaScript
- Node.js运行JavaScript

### 什么是JavaScript, Node.js, 它们是怎么工作的

#### JavaScript

JavaScript (JS) is a lightweight interpreted (or just-in-time compiled) programming language with first-class functions. While it is most well-known as the scripting language for Web pages, many non-browser environments also use it, such as Node.js, Apache CouchDB and Adobe Acrobat. JavaScript is a prototype-based, multi-paradigm, single-threaded, dynamic language, supporting object-oriented, imperative, and declarative (e.g., functional programming) styles.

- JavaScript 是一种运行时解释的脚本语言，最初被设计用于网页交互（如点击、弹窗等）
- JavaScript 本身不具备文件 I/O、网络、数据库等系统级能力，这些功能由运行时环境（如浏览器的 V8 + DOM API、Node.js）提供支持。

#### Node.js

As an asynchronous event-driven JavaScript runtime, Node.js is designed to build scalable network applications.   

Node.js 是一个基于 `Chrome V8` 引擎 构建的 JavaScript 运行环境，主要用于开发服务器端应用程序。它的核心特点是`事件驱动`、`非阻塞 I/O（异步 I/O）` 和`单线程模型`。

```
        +--------------------------+
        |      JavaScript 程序     |
        +-----------+--------------+
                    |
            调用异步API，如 fs.readFile
                    |
             +------v------+
             |   Event Loop |
             +------+-------+
                    |
         +----------v----------+
         |       libuv         |
         +----------+----------+
                    |
     +--------------v-------------+
     |  系统内核线程池/异步IO等    |
     +----------------------------+

当 I/O 完成后，回调返回 -> 事件队列 -> Event Loop 调度执行

```
上图展示了当 JavaScript 程序在 Node.js 中调用异步 API（如 fs.readFile）时，任务被传给 libuv，最终由线程池或系统调用处理，完成后通过回调函数返回事件队列，由 Event Loop 调度执行。

#### Chrome 内核（Chromium）
通常说的`Chrome 内核`是指开源的浏览器项目 Chromium，它也包括两大块：

- Blink（网页渲染引擎）
- V8（JavaScript 引擎）

所以浏览器能运行 JS，是因为它集成了 V8 引擎和一整套浏览器提供的 Web API（如 DOM、BOM、网络等）。

##### JavaScript 在浏览器中运行时，发生了什么？
当你打开一个网页：

```html
<html>
  <script>
    alert("Hello from JS!");
  </script>
</html>
```
浏览器的流程如下：

- Blink 渲染 HTML 页面

- 看到 `<script>` 标签，调用内置的 V8 引擎

- V8 解释执行 JS 代码

- 浏览器提供了很多 JS 能用的 API，比如：

```
alert()
document.querySelector()
fetch()
window.setTimeout()
```

这些 API 是浏览器提供的，不是 JavaScript 标准语法！


#### Node.js和Chromium总结比较

| 环境        | 引擎         | 提供API示例             | 应用方向      |
| ----------- | ----------- | ---------------------- | ----------- |
| 浏览器	   | V8	         | alert, document, fetch |	前端交互      |
| Node.js	  |V8           |	fs, http, process	 | 后端/CLI 工具 |