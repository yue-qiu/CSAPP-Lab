## cachelab

实验分为两部分。在 phase1 中，您将实现一个缓存模拟器。在 phase2 中，您将编写一个矩阵针对高速缓存性能优化的转置功能
实验目录的 `traces` 子目录包含参考跟踪文件的集合，我们将用于评估您在 phase1 中编写的缓存模拟器的正确性。跟踪文件是由 `valgrind` 程序产生的。

Ubuntu 安装 valgrind：

```bash
sudo apt install valgrind
```

valgrind 利用 `traces` 目录中的文件作为输入，内容按照以下形式组织：

```
[space] operation address,size
``` 

operation 共有四种：I、M、L 与 S。I 表示指令读取，L 表示数据读取，S 表示数据储存，M 表示数据修改。其中只有当 operation 为 I 的时候前面没有空格 space。address 是一个 64 位 16 进制内存地址。size 表示操作数长度。i.g.

```
I 0400d7d4,8
 M 0421c7f0,4
 L 04f6b868,8
 S 7ff0005c8,8
```

### phase1

您将在 csim.c 中编写一个缓存模拟器，该模拟器将 valgrind 内存跟踪作为输入，模拟高速缓存存储器的命中/未命中行为，并输出命中，不命中和驱逐的总数目。

csim.c 应当支持以下命令行参数：

```
-s <s> -E <E> -b <b> -t <tracefile>
```

- -s: Number of set index bits(S=2^s is the number of sets)
- -E: Associatively(numer of lines per set)
- -b: Number of block bits(B=2^b is the block size)
- -t: Name of the valgrind tarce to replay

最后通过测试的截图：

![模拟高速缓存](https://i.loli.net/2021/02/05/TW6sLuCil5qZajr.png)
