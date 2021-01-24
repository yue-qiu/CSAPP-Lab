## bomblab

本实验共有 6 关和 1 个彩蛋，需要阅读汇编代码 bomb.s 搞清楚每关对应的拆弹字符串才能过关。bomb.s 通过对可执行文件 bomb 反编译得到：

```shell
objdump -d bomb > bomb.s
```