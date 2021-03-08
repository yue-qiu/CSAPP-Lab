## shell lab

先放出实验的[说明文档](http://csapp.cs.cmu.edu/3e/shlab.pdf)。我们的任务是补全 `tsh.c` 中如下函数的代码：

- `void eval(char *cmdline)`：解析并执行命令。
- `int builtin_cmd(char **argv)`：检测命令是否为内置命令 quit、fg、bg、jobs。
- `void do_bgfg(char **argv)`：实现 bg、fg 命令。
- `void waitfg(pid_t pid)`：等待前台命令执行完成。
- `void sigchld_handler(int sig)`：处理 SIGCHLD 信号，即子进程停止或终止。
- `void sigint_handler(int sig)`：处理 SIGINT 信号，即来自键盘的中断 ctrl-c。
- `void sigtstp_handler(int sig)`：处理 SIGTSTP 信号，即终端停止信号 ctrl-z。

每次修改代码后都要重新编译再运行：

```shell
make
./tsh
```

### 辅助函数

官方已经实现了一些可能会用到的辅助函数，我们编码的时候直接调用即可：

- `int parseline(const char *cmdline,char **argv)`：获取参数列表 char **argv，返回是否为后台运行命令（true）。
- `void clearjob(struct job_t *job)`：清除 job 结构。
- `void initjobs(struct job_t *jobs)`：初始化 jobs 链表。
- `void maxjid(struct job_t *jobs)`：返回 jobs 链表中最大的 jid 号。
- `int addjob(struct job_t *jobs,pid_t pid,int state,char *cmdline)`：在 jobs 链表中添加 job
- `int deletejob(struct job_t *jobs,pid_t pid)`：在 jobs 链表中删除 pid 的 job。
- `pid_t fgpid(struct job_t *jobs)`：返回当前前台运行 job 的 pid 号。
- `struct job_t *getjobpid(struct job_t *jobs,pid_t pid)`：返回 pid 号的 job。
- `struct job_t *getjobjid(struct job_t *jobs,int jid)`：返回 jid 号的 job。
- `int pid2jid(pid_t pid)`：将 pid 号转化为 jid。
- `void listjobs(struct job_t *jobs)`：打印 jobs。
- `void sigquit_handler(int sig)`：处理 SIGQUIT 信号。

### 注意事项

- tsh 的提示符为 tsh>
- 用户的输入分为第一个的 name 和后面的参数，之间以一个或多个空格隔开。如果 name 是一个 tsh 内置的命令，那么tsh应该马上处理这个命令然后等待下一个输入。否则，tsh 应该假设 name 是一个路径上的可执行文件，并在一个子进程中运行这个文件（这也称为一个工作/job）
- tsh 不需要支持管道和重定向
- 如果用户输入 ctrl-c/ctrl-z)，那么SIGINT/SIGTSTP 信号应该被送给每一个在前台进程组中的进程，如果没有进程，那么这两个信号应该不起作用。
- 如果一个命令以 & 结尾，那么tsh应该将它们放在后台运行，否则就放在前台运行（并等待它的结束）
- 每一个工作（job）都有一个正整数 PID 或者 job ID（JID）。JID 通过 % 前缀标识符表示，例如， %5 表示 JID 为 5 的工作，而 5 代表 PID 为 5 的进程。
- tsh 应该回收（reap）所有僵尸进程，如果一个工作是因为收到了一个它没有捕获的（没有按照信号处理函数）而终止的，那么 tsh 应该输出这个工作的 PID 和这个信号的相关描述。
- tsh 支持如下内置命令：
```
quit: 退出当前shell

jobs: 列出所有后台运行的工作

bg <job>: 这个命令将会向 <job> 代表的工作发送 SIGCONT 信号并放在后台运行，<job> 可以是一个 PID 也可以是一个 JID。

fg <job>: 这个命令会向 <job> 代表的工作发送 SIGCONT 信号并放在前台运行，<job> 可以是一个 PID 也可以是一个 JID。
```

