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
0100 ^ 0101 = 0001
异或门即1^1 0^0=0，1^0 0^1=1
xy相同必有x&y=1 | 0
不同必有 x&y=0;
情况1：x和y不都为0
都为1时x&y=1，否则为0，按位取反
情况2：x和y都为0
x&y=0
但会和情况1混淆
先取反~x&~y=1
再取反为0
两者取&
*/

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
分有0没0两种情况
没0因为int是32位，直接取第31位看是否^
有0再分两种，全0或者1个0
全0示例给的1，所以取反后&&操作为1
一个0分x和y再取
*/

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
算2进制对数向下取整
实际上在找最高的1所在位
二分查找，16+8+4+2+1=31
*/

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
将第m和第n字节互换
取第m和n字节，将对应位置清空，再互换m、n
*/

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
颠倒二进制串
unsigned有8byte，设为12345678
先交换相邻21 43 65 87=abcd
继续相邻交换ba dc(4321 8765)
最后交换为87654321
*/

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
正数直接右移
负数算术右移和逻辑右移不同，要把1去掉
构造掩码，最后n位为0，其余都是1
*/

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int count = 0;
    int inv = ~x;
    int t;
    t = !(inv >> 16); count += t << 4; inv <<= t << 4;
    t = !(inv >> 24); count += t << 3; inv <<= t << 3;
    t = !(inv >> 28); count += t << 2; inv <<= t << 2;
    t = !(inv >> 30); count += t << 1; inv <<= t << 1;
    t = !(inv >> 31); count += t;      inv <<= t;
    return count + !inv;
}
/*
int是32位
统计连续的1个数
和logtwo一个思想用二分
前16位开始 如果全1那么处理后变为全0 t=1
若t=1 那么知r>=16
再把inv左移看后16位
以此类推
若前16位不是连续1 则按照上述思想再看前8位 4 2 1
以此类推直到最后一步防止全1被阴
*/

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
先处理0和符号:x为0直接返回0;否则取绝对值abs,若x为负,符号位记为1,用~x+1求绝对值;若正,符号位为0
接着找abs的最高位1,若当前最高位为0就左移1位,使最高位1最终落在第31位，累计左移位数可以视作shift
然后算阶码:真实指数应该是31-shift（最开始在k位，有k+shift=31）,加上偏置127,得exp=158-shift
提取尾数:此时第31位是隐含的1,第30~8位是尾数(因为浮点数规格化后小数点前是1),所以把abs右移8位,再与0x7FFFFF取低23位,得到frac
四舍五入:取被舍掉的低8位abs&0xFF加上尾数最低位frac&1,若大于0x80就进位,frac加一;若进位导致frac溢出到第23位,则frac清0,exp加一
最后把符号位、exp<<23、frac三部分按位或,拼成最终float
*/

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
把uf拆成符号位sign、阶码exp、尾数frac三部分
如果阶码全1(exp==0xFF),说明是NaN或无穷大,乘以2不变,直接返回uf
如果阶码为0(exp==0),说明是非规格化数,没有隐含的1,乘以2等价于尾数左移1位
非规格化数左移时,如果尾数溢出到第23位(frac&0x400000为真),说明要进位到阶码,于是把exp设为1,尾数只保留低23位
如果尾数没有溢出,只把尾数左移1位,exp保持0
如果阶码在1~254之间,说明是规格化数,乘以2就是阶码加1
阶码加1后如果变成255,说明溢出成无穷大,要把尾数清0
最后把符号位、阶码、尾数三部分按位或拼回32位
*/

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
先把64位浮点数拆成三部分:符号位是uf2的第31位,阶码是uf2的第30~20位,尾数是uf2的低20位加上uf1的32位
如果阶码全1(exponent>=0x7FF),说明是NaN或无穷大,返回溢出值0x80000000
如果阶码小于1023,说明实际数值小于1,小数点前为0(真实指数e=exponent-1023)
如果e>=31,说明超出int范围,返回溢出值0x80000000
把隐含的1(1<<20)和mant_high拼成21位的高位部分high_word
计算需要右移的总位数sh=52-e
如果sh>=32,说明低32位不需要,只把high_word右移sh-32位得到整数部分
否则把high_word和mant_low拼接后右移sh位得到整数部分
如果符号位为1,返回负值;否则返回正值
*/

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
/*
计算2的x次方的单精度浮点表示
如果x<-149,太小了,非规格化数都表示不了,返回0
如果-149<=x<-126,属于非规格化数范围,阶码为0,尾数是1左移(x+149)位
如果-126<=x<=127,属于规格化数范围,阶码是x+127,直接左移23位
如果x>127,太大了,返回无穷大0x7F800000
*/