## attacklab

实验分为 5 个 phases，详细说明见 CMU 提供的[文档](http://csapp.cs.cmu.edu/3e/attacklab.pdf)。前三个实验基于 `ctarget` 程序，后两个基于 `rtarget` 程序。`hex2raw` 是用来进行十六进制向二进制串转换的工具，如地址高位为 0x80 时，ASCII 对应的字符是不可通过键盘输入的，可使用 hex2raw 进行转换。hex2raw 读取输入文件中的十六进制串(每两个十六进制数用空格隔开)，将其转换为对应的二进制序列。

前三个实验基于同一个函数展开：

```C
void test() {
    int val;
    val = getbuf();
    printf("No exploit. Getbuf return 0x%x\n", val);
}
```

`ctarget` 程序每次通过 `test()` 调用 `getbuf()`，从 shell 读入一行字符串并**不加检测地**保存到 `getbuf()` 的栈帧上，这意味可能会发生缓冲区溢出，攻击者可以通过构造合适的输入使保存在栈中的 `test()` 返回地址被覆盖，最后的表现就是 `getbuf()` 结束后程序崩溃或跳到别处而不是回到 `test()` 继续执行。在前三个 phases 中，我们的任务就是通过构造合适的输入分别使程序在 `getbuf()` 结束后转去执行 `touch1()`、`touch2()` 和 `touch3()`。

```C
void touch1() {
    vlevel = 1; /* Part of validation protocol */
    printf("Touch1!: You called touch1()\n");
    validate(1);
    exit(0);
}

void touch2() {
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


### phase 1

执行如下命令过关：

```bash
./hex2raw < phase1.txt | ./ctarget -q
```

### phase2

执行如下命令过关：

```bash
./hex2raw < phase2.txt | ./ctarget -q
```

