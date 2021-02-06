## cachelab

实验分为两部分。在 partA 中，您将实现一个缓存模拟器。在 partB 中，您将编写一个矩阵针对高速缓存性能优化的转置功能
实验目录的 `traces` 子目录包含参考跟踪文件的集合，我们将用于评估您在 partA 中编写的缓存模拟器的正确性。跟踪文件是由 `valgrind` 程序产生的。

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

### partA

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

### partB

我们需要修改 `trans.c`文件中的 `transpose_submit` 函数，使得矩阵转置时的不命中次数尽可能小。分别对 32* 32、64 * 64、61*67 的矩阵进行实验。高速缓存的架构为 `s=5, E=1, b=5`

实验要求：
- 最多使用 12 个 int 局部变量
- 不能使用递归函数
- 不能对原始的矩阵 A 进行修改
- 不能通过 malloc 申请空间

评分标准：

- 32*32: 8 points if misses < 300, 0 points if misses > 600
- 64*64: 8 points if misses < 1300, 0 points if misses > 2000
- 61*67: 10 points if misses < 2000, 0 points if misses > 3000

经过计算发现 cache 容量是小于矩阵大小的，而”转置“这个动作可以通过分块矩阵完成，同时如果分块后矩阵小于 cache，那么整个小矩阵都可以被储存到 cache 里，对单个小矩阵而言不命中率就大大降低了。

具体到题目，可以发现 32\*32 矩阵如果被分割为 16 个 8\*8 小矩阵，每个小矩阵都可以被完全放进 cache 里。同理 64\*64 也可以被分割为多个 4\*4 小矩阵，并且经过实验可知选择 4\*4 效果优于 8\*8。61\*67 矩阵不是方阵，但一样可以分块，经过实验发现 17\*17 是一个比较合适的值
