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
/*
 * x ^ y
 * = ~(x & y) & (x | y)
 * = (~(x & y) & x) | ((~(x & y) & y))
 * = ~(~(~(x & y) & x) & ~(~(x & y) & y))
 */
  return ~(~(~(x & y) & x) & ~(~(x & y) & y));
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
/* 
 * tmin = 0x10000000 = 1 << 31
 */
  return 0x1 << 31;

}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise is
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
/*
 * tmax = 0x7fffffff, tmax + 1 = 0x80000000
 * Compare tmax with tmax + 1,
 * 1.tmax + 1 equals to the reversed tmax, that is ~tmax,
 *   (tmax + 1) ^ (~tmax) = 0
 * 2.0xffffffff should be excluded.
 */
  return !((~x) ^ (x + 1)) & !!(~x);
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
 * 0xAA = 1010 1010
 * 1.Shift 0xAA to get a pattern with all odd-numbered bits set to 1.
 * 2.(pattern & x) ^ pattern = 0 if all odd-numbered bits of x set to 1
 */
  int pattern = 0xAA;
  pattern = pattern | (pattern << 8) | (pattern << 16) | (pattern << 24);
  return !((pattern & x) ^ pattern);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
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
 * 1.0x30 >> 4 = 0x3, so !((x >> 4) ^ 0x3) = 1 if the highest 28 bits is the same as 0x30,
 *   which means x >= 0x30.
 * 2.Then consider the lowest 4 bits, 
 *   2.1 The highest bit is 0, !(x & 0x8) = 1 indicates that x may be 0 to 7.
 *   2.2 The highest bit is 1, !(x & 0x6) = 1 indicates that x may be 8 or 9.
 *   2.3 Or x > 0x39
 */
  return (!((x >> 4) ^ 0x3)) & (!(x & 0x8) | !(x & 0x6));
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
 * 1.!x = 1 if x = 0 else 0
 * 2.(0 << 31) >> 31 = 0x00000000, (1 << 31) >> 31 = 0xffffffff
 * 3.Suppose n as any integer, n | 0x00000000 = n, n | 0xffffffff = 0xffffffff,
 *   and n & 0x11111111 = n.
 * 4.So (x | y) & (~x | z) equals to x ? y : z.
 */
  x = (!x << 31) >> 31;
  return (x | y) & (~x | z);
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
 * If x <= y, there are two cases.
 * 1.x and y have the different sign, and x is negative.
 * 2.x and y have the same sign, y - x = y + ~(x + 1) >= 0.
 */
  int signx = !(x >> 31);
  int signy = !(y >> 31);
  int case1 = (signx ^ signy) & !signx;
  int case2 = !(signx ^ signy) & !((y + (~x + 1)) >> 31);
  return case1 | case2;
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
 * 1.Compute OR of all bits in the lowest bit of x.
 * 2.(x & 0x1) ^ 0x1 = 1 if all bits are 0 else 1
 */
  x = x | (x >> 1);
  x = x | (x >> 2);
  x = x | (x >> 4);
  x = x | (x >> 8);
  x = x | (x >> 16);
  return (x & 0x1) ^ 0x1;
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
 * Apply binary search for bit counting.
 */
  int res = 1;
  int mask1 = 0x1 << 1;
  int mask2 = 0x3 << 2;
  int mask4 = 0xf << 4;
  int mask8 = 0xff << 8;
  int mask16 = (0xff | mask8) << 16;
  int bitCount = 0;
  
  // Cast the number to positive with the same bits result.
  x = x ^ (x >> 31);
  
  // Check the highest 16 bits. 
  // If there is at least one bit of 1, then bitCount is 16.
  bitCount = (!!(x & mask16)) << 4;
  res += bitCount;
  x = x >> bitCount;
  
  // 8 or 0
  bitCount = (!!(x & mask8)) << 3;
  res += bitCount;
  x = x >> bitCount;
  
  // 4 0r 0
  bitCount = (!!(x & mask4)) << 2;
  res += bitCount;
  x = x >> bitCount;
  
  // 2 or 0
  bitCount = (!!(x & mask2)) << 1;
  res += bitCount;
  x = x >> bitCount;
  
  // 1 or 0
  bitCount = (!!(x & mask1));
  res += bitCount;
  x = x >> bitCount;
  
  // Consider the lowest bit.
  return res + (x & 0x1);
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
  int E = (uf >> 23) & 0xff;
  // uf = +-0
  if(uf == 0 || uf == 0x80000000) return uf;
  // uf = NaN or Infinity
  if(E == 0xff) return uf;
  // uf = Denormalized value
  if(E == 0) return (uf & (1 << 31)) | (uf << 1);
  // uf = Normalized value
  return uf + (1 << 23);
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
  int S = (uf >> 31) & 0x1;
  int E = (uf >> 23) & 0xff;
  // Normalized M
  int M = (uf & 0x007fffff) | 0x00800000;
  // uf = +-0
  if(uf == 0 || uf == 0x80000000) return 0;
  // uf = NaN or Infinity
  if(E == 0xff) return 0x80000000u;
  // uf = Denormalized value
  if(E == 0) return 0;
  
  // uf = Normalized value
  // Minus bias
  E -= 127;
  // Result < 1
  if(E < 0) return 0;
  // Result = NaN or Infinity
  if(E > 30) return 0x80000000u;
  // Right Shift
  if(E < 23) M = M >> (23 - E);
  // Left Shift
  if(E > 23) M = M << (E - 23);
  // Negative
  if(S == 1) M = ~M + 1;
  return M;
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
  int exp = x + 127;
  // Too small to be represented as a denorm
  if(exp <= 0) return 0;
  // Too large, return +INF
  if(exp >= 255) return 0xff << 23;
  return exp << 23;
}
