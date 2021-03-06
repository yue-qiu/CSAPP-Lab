## attacklab

实验分为 5 个 phases，详细说明见 CMU 提供的[文档](http://csapp.cs.cmu.edu/3e/attacklab.pdf)，还会经常用到 [gdb](http://csapp.cs.cmu.edu/2e/docs/gdbnotes-x86-64.pdf) 作为调试工具。前三个实验基于 `ctarget` 程序，后两个基于 `rtarget` 程序。`hex2raw` 是用来进行十六进制向二进制串转换的工具，如地址高位为 0x80 时，ASCII 对应的字符是不可通过键盘输入的，可使用 hex2raw 进行转换。hex2raw 读取输入文件中的十六进制串(每两个十六进制数用空格隔开)，将其转换为对应的二进制序列。

前三个实验基于同一个函数展开：

```C
void test() {
    int val;
    val = getbuf();
    printf("No exploit. Getbuf return 0x%x\n", val);
}

void getbuf() {
	char buf[BUFFER_SIZE];
	Gets(buf);
	return 1;
}
```

`ctarget` 程序每次通过 `test()` 调用 `getbuf()`，从 shell 读入一行字符串并**不加检测地**保存到 `getbuf()` 的栈帧上，这意味可能会发生缓冲区溢出，攻击者可以通过构造合适的输入使保存在栈中的 `test()` 返回地址被覆盖，最后的表现就是 `getbuf()` 结束后程序崩溃或跳到别处而不是回到 `test()` 继续执行。在前三个 phases 中，我们的任务就是通过构造合适的输入分别使程序在 `getbuf()` 结束后转去执行 `touch1()`、`touch2()` 和 `touch3()`。

### phase 1

利用缓冲区溢出，把栈里保存的 `test()` 返回地址覆盖为 `touch1()` 的起始地址就行。

```C
void touch1() {
    vlevel = 1; /* Part of validation protocol */
    printf("Touch1!: You called touch1()\n");
    validate(1);
    exit(0);
}
```

执行如下命令过关：

```bash
./hex2raw < phase1.txt | ./ctarget -q
```

### phase2

`touch2()` 要求我们传递一个与 cookie 相等的参数。根据规范第一个参数是通过 `%rdi` 传递的，所以我们需要自己编写几条指令完成传参。利用缓冲区溢出让程序从 `getbuf()` 转移到自定义指令处完成准备工作，再通过 `ret` 指令把控制权转移给 `touch2()`。

```C
void touch2(unsigned val) {
    vlevel = 2; /* Part of validation protocol */
    if (val == cookie) {
        printf("Touch2!: You called touch2(0x%.8x)\n", val);
        validate(2);
    } else {
        printf("Misfire: You called touch2(0x%.8x)\n", val);
        fail(2);
    }
    exit(0);
}
```

需要注入的指令保存在 `phase2.d` 中，执行如下命令过关：

```bash
./hex2raw < phase2.txt | ./ctarget -q
```

### phase3

`touch3()` 使用一个字符串指针作为参数，调用 `hexmatch()` 方法检查这个指针指向的字符串是否与 cookie 字面字符串相等（cookie 前导 0x 不计入内）。我们的注入代码需要完成三个任务：

1. 保存 cookie 字面字符串到一个安全的位置
2. 得到 1 的指针作为 `touch3()` 入参
3. 控制权转移给 `touch3()`

```C
/* Compare string to hex represention of unsigned value */
int hexmatch(unsigned val, char *sval) {
    char cbuf[110];
    /* Make position of check string unpredictable */
    char *s = cbuf + random() % 100;
    sprintf(s, "%.8x", val);
    return strncmp(sval, s, 9) == 0;
}

/*
You must make it appear to touch3 as if you have passed a string representation of your cookie as its argument
*/
void touch3(char *sval) {
    vlevel = 3; /* Part of validation protocol */
    if (hexmatch(cookie, sval)) {
        printf("Touch3!: You called touch3(\"%s\")\n", sval);
        validate(3);
    } else {
        printf("Misfire: You called touch3(\"%s\")\n", sval);
        fail(3);
    }
    exit(0);
}
```

需要注入的指令保存在 `phase3.d` 中，执行如下命令过关：

```bash
./hex2raw < phase3.txt | ./ctarget -q
```

### phase4

phase4 基于是 `rtarget` 程序，使用了栈随机化和内存标记位技术，使我们无法像以前那样往栈里注入自己编写的代码并执行。这就用到 Return-Oriented Program(ROP) 技术了。我们从程序单条指令中截取一部分，称为 `gadget`，使其被 CPU 解释为另一种指令来完成攻击，这些 `gadget` 往往由 `ret` 指令结尾，因为我们需要 `ret` 来完成程序控制权的转移。

我们在栈顶注入一系列 gadget 的地址，`ret` 指令保证了各个 gadget 组成了一个 chain，每次执行 `ret` 就是跳转到另一个 `gedget` 里继续我们的攻击。

执行如下命令过关：

```bash
./hex2raw < phase4.txt | ./rtarget -q
```

### phase5

实验做到这里就能拿 95 分了，剩下这个算是选做题。因为这部分内容对实际工作用处不是很大，暂时就跳过了。

