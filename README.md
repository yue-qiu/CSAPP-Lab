## CSAPP-Lab

CSAPP 作为一本公认的神书，其优秀程度毋庸多言。本人在大学期间断断续续读过两三遍，但每次都是浅尝辄止，只挑了其中一些章节来看。荣升大四狗之后有了不少自由时间，于是打算系统性地刷一遍此书，并至少完成几个个人比较感兴趣的 Lab。目前进度：

- [datalab(100%)](#datalab)
- [bomblab(%100)](#bomblab)
- [attacklab(100%)](#attacklab)
- [cachelab(100%)](#cachelab)

### datalab

作为该系列的第一个 Lab，本实验的主要目的在于加深学生对不同类型数据在计算机内部的表示形式的理解，并介绍几种有趣的位运算技巧。

下面放一张运行成功的截图：

![datalab成功截图](https://i.loli.net/2021/01/23/8Rx2Um9iSztdyF3.png)

### bomblab

bomblab 可谓是“举世闻名”了，无数大佬谈起它都赞不绝口。本实验对应书本第三章。需要用到 gdb 对汇编代码进行分析。炸弹运行的每个阶段要求你输入一个特定的字符串，若你的输入符合程序预期的输入，该阶段的炸弹就被“拆除”，否则炸弹“爆炸”并打印输出 "BOOM!!!"字样。

下面放出成功拆除炸弹的截图，那一瞬间还是很有成就感的：

![bomblab](https://i.loli.net/2021/01/26/xOFLfN7YQbwhE4p.png)

### attacklab

本实验对应书本第三章：程序的机器级表示中，缓冲区溢出攻击的内容。目标是通过代码注入攻击（Code Injection Attack）和返回导向编程（Return Oriented Programming）两种攻击方式，分别修改具有缓冲区溢出漏洞的两个x86_64可执行文件的行为。主要目的是加深学生对于栈规则的理解，以及说明缓冲区溢出可能造成的后果。

### cachelab

本实验让学生模拟实现一个全相联缓存模型与优化矩阵转置缓存不命中率，加深学生对缓存替换过程的理解，锻炼编写高性能代码的能力。 

这个实验 partB 没拿到满分，个人认为掌握“化整为零”的思想，懂得把大数据分割成多个小数据，提高程序的空间局部性以尽量利用高速缓存的思想就可以了，所以没有做更细致的优化：

![cachelab](https://i.loli.net/2021/02/06/nd5MINRpwUx4YoQ.png)

