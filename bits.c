/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x | ~y);
}
/*
0100 & 0101 = 0100
与门即1&1=0，1&0 0&1 0&0=0
前三种情况或操作均取1，第四种情况是0
反过来可以令前三种为0，最后为1（x、y取反即可）
有~x | ~y
最后再取反得到真正0-1
*/

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(x & y) & ~(~x & ~y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */

int samesign(int x, int y) {
    int x_zero = !x;
    int y_zero = !y;
    if (x_zero && y_zero) return 1;
    if (x_zero && !y_zero) return 0;
    if (!x_zero && y_zero) return 0;
    return !((x ^ y) >> 31);
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int r = 0, t;
    t = (v > 0xFFFF) << 4;
    r |= t;
    v >>= t;
    t = (v > 0xFF) << 3;
    r |= t;
    v >>= t;
    t = (v > 0xF) << 2;
    r |= t;
    v >>= t;
    t = (v > 0x3) << 1;
    r |= t;
    v >>= t;
    r |= v >> 1;
    return r;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int m_=m<<3;
    int n_=n<<3;
    int n_x=(x>>n_)&0xFF;
    int m_x=(x>>m_)&0xFF;
    x = x & ~(0xFF << n_) & ~(0xFF << m_);
    x = x | (n_x << m_) | (m_x << n_);
    return x;
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    v = ((v >> 1) & 0x55555555) | ((v & 0x55555555) << 1);
    v = ((v >> 2) & 0x33333333) | ((v & 0x33333333) << 2);
    v = ((v >> 4) & 0x0F0F0F0F) | ((v & 0x0F0F0F0F) << 4);
    v = ((v >> 8) & 0x00FF00FF) | ((v & 0x00FF00FF) << 8);
    v = (v >> 16) | (v << 16);
    return v;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int y = ~(((1<<31 ) >> n) << 1);
    return (x>>n)&y;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int r = 0;
    int t;
    t = !(~x >> 16);
    r += t << 4;
    x <<= t << 4;
    t = !(~x >> 24);
    r += t << 3;
    x <<= t << 3;
    t = !(~x >> 28);
    r += t << 2;
    x <<= t << 2;
    t = !(~x >> 30);
    r += t << 1;
    x <<= t << 1;
    t = !(~x >> 31);
    r += t;
    x <<= t;
    
    r += (x >> 31) & 1;
    return r;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    if (!x) return 0;
    unsigned abs = x;
    if (x < 0) abs = -x;
    int exp = 158;
    while (!(abs & 0x80000000)) {
        abs = abs << 1;
        exp = exp - 1;
    }
    unsigned frac = (abs >> 8) & 0x7FFFFF;
    if ((abs & 0xFF) + (frac & 1) > 0x80) {
        frac = frac + 1;
        if (frac == 0x800000) {
            frac = 0;
            exp = exp + 1;
        }
    }
    return (x & 0x80000000) | (exp << 23) | frac;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned sign = uf & 0x80000000;
    unsigned exp = (uf >> 23) & 0xFF;
    unsigned frac = uf & 0x7FFFFF;
    if (exp == 0xFF) return uf;
    if (exp == 0) {
        if (frac & 0x400000) {
            exp = 1;
            frac = (frac << 1) & 0x7FFFFF;
        } else {
            frac = (frac << 1) & 0x7FFFFF;
        }
    } else {
        exp = exp + 1;
        if (exp == 0xFF) frac = 0;
    }
    return sign | (exp << 23) | frac;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    unsigned sign = uf2 >> 31;
    unsigned exponent = (uf2 >> 20) & 0x7FF;
    unsigned mant_high = uf2 & 0xFFFFF;
    unsigned mant_low = uf1;
    int e;
    unsigned sh;
    unsigned high_word;
    unsigned abs_val;
    if (exponent >= 0x7FF) return 0x80000000;
    if (exponent < 1023) return 0;
    e = exponent - 1023;
    if (e >= 31) return 0x80000000;
    sh = 52 - e;
    high_word = (1 << 20) | mant_high;
    if (sh >= 32) {
        abs_val = high_word >> (sh - 32);
    } else {
        abs_val = (high_word << (32 - sh)) | (mant_low >> sh);
    }
    if (sign) return -abs_val;
    return abs_val;
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
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if (x < -149) return 0;
    else if (x < -126) {
        unsigned frac = 1 << (x + 149);
        return frac;
    } else if (x <= 127) {
        unsigned exp = x + 127;
        return exp << 23;
    } else return 0x7F800000;
}