- execl.c
- call_by_exec.c

用 execl() 运行程序的示例。

- execv.c
- call_by_exec.c

用 execv() 运行程序的示例。
这个例子在 Ubuntu 22.04 环境中执行，会返回 Bad Address，不知道为什么。

- daemon.c

编写守护进程。

- exit.c

退出进程的几种方式。

- for_job.c

用于查看前台进程（组）和后台进程（组）。

- for_proc.c

死循环，用于查看进程的 /proc 目录里的内容。

- for_pstree.c

用于 pstree 查看进程组。

- for_zombie.c

构造僵尸进程。

- fork.c

用 fork() 创建进程。

- fork_separate_memory.c

fork() 父子进程的内存资源是隔离的。

- nice.c

通过 nice() 改变进程的优先级。

- pid_and_ppid.c

进程 id 和父进程 id。

- pgid.c

使用 getpgid() 获取进程组 id。

- rlimit.c

使用 getrlimit() 获取和 setrlimit() 修改进程的资源限制。

- vfork.c

用 vfork() 创建进程。

- vfork_share_memory.c

vfork() 子进程和父进程共享内存。

- wait.c

父进程用 wait() 回收子进程。

- waitpid_macros.c

父进程用 waitpid() 回收子进程，然后用宏函数 WEXITSTATUS 判断子进程的退出状态。
