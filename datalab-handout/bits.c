/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  // 德摩根律公式
  return ~(~x & ~y) & ~(x & y);
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  // 32 位 int 最大小值为 1000 0000 0000 0000 0000 0000 0000 0000
  return 1 << 31;

}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  /* 
   * 解法 1：
   * 这种 true or false 的函数，就是要把输入化为某种 bool 值。
   * C 语言里零为 false，非零为 true 
   * 如果 Tmax 满足某种运算变成 0，而 x 也满足这种运算，我们就说 x is Tmax
   * ~((Tmax+1)+Tmax) == 0，要排除 -1(0xFFFF) 的例外
   */
  int a = x + 1;
  int b = a + x;
  int c = ~b;
  return !(c) & !!(a^0);


  /* 
   * 解法 2：
   * Tmax+1 再取反等于其本身，如果 x 满足这个性质说明 x 是 Tmax
   * -1 是特例，需要利用 !!(x+1) 额外判断 
   *  return !(~(x + 1) ^ x) & !!(x+1);
   *  如果能用 << ，还可以用 &0x8000 判断 x+1 符号位 return !!((x+1) & (0x80 << 16));
   */
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  /*
   * 一个奇数位全 1 的数 & 0xAAAAAAAA 结果为 0xAAAAAAAA
   * 代码中最大只能用 0xAA，需要用一些二进制技巧把 0xAAAAAAAA 构造出来
   */
  int a = 0xAA << 8; // 0xAA00
  int b = a | 0xAA; // 0xAAAA
  int mask = b << 16 | b; // 0xAAAAAAAA 
  return !((x & mask) ^ (mask));
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  /*
   * x + ~x = -1 且 x + negate(x) = 0
   * 可得 negate(x) = ~x + 1
   */
   return ~x + 1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  /*
   * 0x30 = 0011 0000, 0x39 = 0011 1001
   * 所有 AsciiDigit 都要满足前 4 位等于 0x3
   * 后四位范围是 0-9，与 -0xA 之和应为负数
   */
  int a = !((x >> 4) ^ 0x3);
  int b = x & 0xf; // 取 x 的后 4 位
  int sum = b + (~0xA + 1);
  int is_neg = !!(sum & (1 << 4)); // 判断 c 是否为负
  return a & is_neg;
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  /*
   * 根据 x 的布尔值转换为全 0 或全 1
   */
  int x_to_bool = !!(x); // 获得 x 的布尔值
  int mask = ~x_to_bool + 1; // 获得 0x0 或 0xffff。negative(0) = 0，negative(1) = 0xffff
  //int y1 = (~y+1)&~mask; // x 非零，y1 为 0；x 为零，y1 为 -y
  //int z1 = (~z+1)&mask;  // x 非零，z1 为 -z；x 为零，z1 为 0
  //return y + y1 + z + z1;
  return (mask&y) | (~mask&z);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  /*
   * 三种情况 x <= y：
   * 1. x 为负，y 非负
   * 2. x，y 为负且 y - x > 0
   * 3. x, y 非负且 y - x > 0
   * */
  int x_is_neg = !!(x >> 31);
  int y_is_not_neg = !(y >> 31);
  int minus_x = ~x+1;
  int sub = y + minus_x;
  int sub_is_not_neg = !(sub >> 31);

  return  (x_is_neg & y_is_not_neg) | (!x_is_neg & y_is_not_neg & sub_is_not_neg) | (x_is_neg & !y_is_not_neg & sub_is_not_neg);
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  /*
   * 如果 x 为非零，其相反数与本身按位或一定得到一个负数，右移 31 位得到 -1
   * 如果 x 为零，其相反数与本身按位或一定为 0，右移 31 位还是 0
   */
  return ((x | (~x+1)) >> 31) + 1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  /* 
   * x 非负时，其最简二进制表示为 0(符号位) + 第一个 1 出现的低位部分
   * 如 12 = 0000 0000 0000 1100，最简二进制表示为 0 1100
   *
   * x 为负时，其最简二进制表示为 1(符号位) + 第一个 0 出现的低位部分
   * 如 -5 = 1111 1111 1111 1011，最简二进制表示为 1011
   *
   * 查找第一个 1 的过程类似于二分查找
  */
  int b16, b8, b4, b2, b1, b0;
  int sign = x >> 31;
  x = (~sign & x) | (sign & ~x); // 非负数不变，负数取反码。这样把负数的处理逻辑统一到非负数处理上来
  b16 = !!(x >> 16) << 4;	 // 判断 x 的高 16 位是否有 1，如果有说明表示 x 至少需要 16 位
  x = x >> b16;			 // x 的高 16 位有 1 就往高 24 位进一步查找第一个 1 的位置；否则往高 8 位找 1
  b8 = !!(x >> 8) << 3;
  x = x >> b8;
  b4 = !!(x >> 4) << 2;
  x = x >> b4;
  b2 = !!(x >> 2) << 1;
  x = x >> b2;
  b1 = !!(x >> 1);
  x = x >> b1;
  b0 = !!(x);

  return 1 + b16 + b8 + b4 + b2 + b1 + b0; // x 的最简二进制表示中，第一个 1 前面还有一个额外的符号位 
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  unsigned sign = uf >> 31;
  unsigned exponent = ((uf & 0x7f800000) >> 23);
  unsigned significand = 0x7fffff & uf;
  // NaN and Infinity
  if (exponent == 0xff) return uf;
  // unnomarlized
  if (exponent == 0) {
  	return (sign << 31) + (significand << 1);
  }

  return (sign << 31) + ((exponent + 1) << 23) + significand;
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  unsigned exponent = ((uf & 0x7f800000) >> 23);
  unsigned significand = 0x7fffff & uf;
  unsigned bias = 1;
  int E = exponent - ((1 << 7) - 1);
  int mask = ~(uf >> 31) + 1;
  if (exponent == 0xff) return 0x80000000u;
  if (exponent == 0 || E < 0) return 0;
  while (E > 0) {
	bias = (bias << 1) | !!(significand & 0x400000);
	significand = significand << 1;
	bias = bias << 1;
	--E;
  }
  // 处理溢出
  if (bias == 0) {
  	return 0x80000000u;
  }
  return ((mask & -1) | (~mask & 1)) * bias; 
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
    /*
     * 2.0 = 1.0 * 2.0^1，同理 2.0^x = 1.0 * 2.0^x
     * 也就是说 2.0^x 与 2.0 有相同的符号位（皆为 0）、尾数位（皆为 1.0-1），唯一的区别在于指数位
     * 在 2.0 中，指数位为 1+127；在 2.0^x 中，指数位为 x+127
     * */
    int exponent = x + 127; // 127 是 float 的指数 bias，E = exponent - 127
    if (exponent >= 255) return 0xff << 23; // 指数位越过上界，返回正无穷
    if (exponent <= 0) return 0; // 指数位越过下界，返回 0
    return exponent << 23;
}
