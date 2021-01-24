## CSAPP-Lab

CSAPP 作为一本公认的神书，其优秀程度毋庸多言。本人在大学期间断断续续读过两三遍，但每次都是浅尝辄止，只挑了其中一些章节来看。荣升大四狗之后有了不少自由时间，于是打算系统性地刷一遍此书，并至少完成几个个人比较感兴趣的 Lab。目前进度：

- [datalab(100%)](#datalab)
- [bomblab(%85)](#bomblab)

### datalab

作为该系列的第一个 Lab，本实验的主要目的在于加深学生对不同类型数据在计算机内部的表示形式的理解，并介绍几种有趣的位运算技巧。

下面放一张运行成功的截图：

![datalab成功截图](https://i.loli.net/2021/01/23/8Rx2Um9iSztdyF3.png)

### bomblab

bomblab 可谓是“举世闻名”了，无数大佬谈起它都赞不绝口。本实验对应书本第三章。需要用到 gdb 对汇编代码进行分析。炸弹运行的每个阶段要求你输入一个特定的字符串，若你的输入符合程序预期的输入，该阶段的炸弹就被“拆除”，否则炸弹“爆炸”并打印输出 "BOOM!!!"字样。
