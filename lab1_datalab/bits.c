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
#include "bits.h"


//P1
/* 
 * bitNor - ~(x|y) using only ~ and & 
 *   Example: bitNor(4, 5) = -6, bitNor(-1,-2) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitNor(int x, int y) {
	return (~x)&(~y);
}

//P2
/* 
 * tmax - return maximum two's complement integer (0x7fffffff)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmax(void) {
	return ~(1 << 31);
}

//P3
/*
 * isTmin - returns 1 if x is the minimum two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmin(int x) {
	return !((x^(~x + 1))|(!x));
}

//P4
/*
 * minusOne - return a value of -1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int minusOne(void){
	return ~0;
}

//P5
/*
 * absVal - return the absolute value of x
 *   Examples: absVal(-10) = 10
 *			   absVal(5) = 5
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int absVal(int x){
    int flag = x >> 31;
    return ((~flag)&x)|(flag&((~x) + 1));
}

//P6 
/*
 * leastBitPos - return a mask that marks the position of the least significant 1 bit.
 *   Examples: leastBitPos(12) = 4
 *			       leastBitPos(-2) = 2
 *             leastBitPos(0)  = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int leastBitPos(int x) {
	return ((~x) + 1)&(x);
}

//P7
/*
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 20
 *  Rating: 2
 */
int byteSwap(int x, int n, int m){
        int xn = (x >> (n << 3)) << (m << 3), xm = (x >> (m << 3)) << (n << 3), npl = 0xff << (n << 3), mpl = 0xff << (m << 3);
        xn = (xn) & (mpl);
        xm = (xm) & (npl);
        x = x & ~(mpl);
        x = x & ~(npl);
        x = x | xn;
        x = x | xm;
	return x;
}

//P8
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
        int move = ~(((~0) << (32 + ~n)) << 1);
        x = x >> n;
        x = x & move;
        return x;
}

//P9
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  int flag = ((y + (~x) + 1) >> 31), xf = x >> 31, yf = y >> 31;
  return ((!!!flag)&(!(!xf & !!yf)))|(!!xf & !yf);
}

//P10 
/* 
 * multFiveEighths - return floor(x*5/8), for 0 <= x, x is an integer 
 *   Example: multFiveEighths(10) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */
int multFiveEighths(int x) {
  int x1 = x & 7, x2 = x & ~7;
  x1 = (x1 + (x1 << 2)) >> 3;
  x2 = (x2 >> 3) + (x2 >> 1);
  return x1 + x2;
}

//P11
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  int find1 = 0x55 + (0x55 << 8), find2 = 0x33 + (0x33 << 8), find3 = 0x0f + (0x0f << 8), find4 = 0xff + (0xff << 16), find5 = 0xff + (0xff << 8);
  find1 = find1 + (find1 << 16);
  find2 = find2 + (find2 << 16);
  find3 = find3 + (find3 << 16);
  x = (x & find1) + ((x >> 1) & find1);
  x = (x & find2) + ((x >> 2) & find2);
  x = (x & find3) + ((x >> 4) & find3);
  x = (x & find4) + ((x >> 8) & find4);
  x = (x & find5) + ((x >> 16) & find5);
  return x;
}

//P12
/*
 * greatestBitPos - return a mask that marks the position of the greatest significant 1 bit.
 *   Example: greatestBitPos(12) = 8
 *            greatestBitPos(-2) = -2147483648
 *            greatestBitPos(0)  = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 60
 *   Rating: 4
 */
int greatestBitPos(int x) {
  int n;
  n = (!!(x >> 16)) << 4;
  n = n + ((!!(x >> (n + 8))) << 3);
  n = n + ((!!(x >> (n + 4))) << 2);
  n = n + ((!!(x >> (n + 2))) << 1);
  n = n + !!(x >> (n + 1));
  return (~(!x)) & (1 << n);
}

//P13
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
  return ((x >> 31) | ((x + ~(1 << 31)) >> 31)) + 1;	
}

//P14
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Max ops: 40
 *   Rating: 4
 */
int bitReverse(int x){
  int find1 = 0x55 + (0x55 << 8), find2 = 0x33 + (0x33 << 8), find3 = 0x0f + (0x0f << 8), find4 = 0xff + (0xff << 16), find5 = 0xff + (0xff << 8);
  find1 = find1 + (find1 << 16);
  find2 = find2 + (find2 << 16);
  find3 = find3 + (find3 << 16);
  x = ((x & find1) << 1) + ((x >> 1) & find1);
  x = ((x & find2) << 2) + ((x >> 2) & find2);
  x = ((x & find3) << 4) + ((x >> 4) & find3);
  x = ((x & find4) << 8) + ((x >> 8) & find4);
  x = (x << 16) + ((x >> 16) & find5);
  return x;
}

//P15
/*
 * mod3 - calculate x mod 3 without using %.
 *   Example: mod3(100) = 1
 *            mod3(-100) = -1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int mod3(int x){
  int sign = x & (1 << 31), find2 = 0x33 + (0x33 << 8), find3 = 0x0f + (0x0f << 8), find4 = 0xff + (0xff << 16), find5 = 0xff + (0xff << 8);
  find2 = find2 + (find2 << 16);
  find3 = find3 + (find3 << 16);
  x = ((sign >> 31) & ((~x) + 1)) + ((~(sign >> 31)) & x);
  x = (x & find2) + ((x >> 2) & find2);
  x = (x & find3) + ((x >> 4) & find3);
  x = (x & find4) + ((x >> 8) & find4);
  x = (x & find5) + ((x >> 16) & find5);
  x = (x & find2) + ((x >> 2) & find2);
  x = (x & find3) + ((x >> 4) & find3);
  x = (x & find2) + ((x >> 2) & find2);
  x = (x & find2) + ((x >> 2) & find2);
  x = ((!!(3 ^ x)) + ((!!(3 ^ x)) << 1)) & x;
  return ((sign >> 31) & ((~x) + 1)) + ((~(sign >> 31)) & x);
}

//P16
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
  int y, z, findx = 1 << 31, findy = 0xff << 22, findz;
  findz = ~(findx + findy);
  y = uf & findy;
  z = uf & findz;
  if((y == findy) && (findz != 0))
  {
    return uf;
  }
  else
  {
    return uf ^ findx;
  }
}

//P17
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  int c = 1 << 31, d = 1 << 7, sign, i = 0;
  if(x);
  else
  {
    return 0;
  }
  if(x == c)
  {
    return c + (158 << 23);
  }
  sign = x & c;
  if(sign)
  {
    x = -x;
  }
  while((x & (1 << 30)) == 0)
  {
    x = x << 1;
    i++;
  }
  if((x & 0x7f) > 0x40)
  {
    x += d;
  }
  else if((x & 0x7f) == 0x40)
  {
    if(x & d)
    {
      x += d;
    }
  }
  if(x & c)
  {
    x = 1 << 30;
    i--;
  }
  return ((x >> 7) & ~(0xff << 23)) | ((157 - i) << 23) | sign;
}

//P18
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  int c = 0xff << 23;
  if((uf == 0) || (uf == (1 << 31)))
  {
    return uf;
  }
  if((uf & c) == c)
  {
    return uf;
  }
  else if((uf & c) == 0)
  {
     uf = (uf << 1) + (uf & (1 << 31));
     return uf;
  }
  else
  {
    return (uf - (uf & c)) | ((uf & c) + (1 << 23));
  }
}
