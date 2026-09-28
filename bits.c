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
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(~x & ~y) & ~(x & y);
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
    if (!x)
        return !y;
    if (!y)
        return 0;
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
    int r = 0;
    int s;
    s = ((v >> 16) > 0) << 4;
    r = r | s;
    v = v >> s;
    s = ((v >> 8) > 0) << 3;
    r = r | s;
    v = v >> s;
    s = ((v >> 4) > 0) << 2;
    r = r | s;
    v = v >> s;
    s = ((v >> 2) > 0) << 1;
    r = r | s;
    v = v >> s;
    r = r | ((v >> 1) > 0);
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
    int ns = n << 3;
    int ms = m << 3;
    int nb = (x >> ns) & 0xff;
    int mb = (x >> ms) & 0xff;
    int mask = (0xff << ns) | (0xff << ms);
    int cleared = x & ~mask;
    return cleared | (nb << ms) | (mb << ns);
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
    unsigned result = 0;
    int i = 32;
    while (i) {
        result = (result << 1) | (v & 1);
        v = v >> 1;
        i = i - 1;
    }
    return result;
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
    return (x >> n) & (0xffffffffu >> n);
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
    int y = ~x;
    int n = 0;
    int hz;
    hz = !(y >> 16);
    n = n + (hz << 4);
    y = (y >> ((!hz) << 4)) & 0xffff;
    hz = !(y >> 8);
    n = n + (hz << 3);
    y = (y >> ((!hz) << 3)) & 0xff;
    hz = !(y >> 4);
    n = n + (hz << 2);
    y = (y >> ((!hz) << 2)) & 0xf;
    hz = !(y >> 2);
    n = n + (hz << 1);
    y = (y >> ((!hz) << 1)) & 0x3;
    hz = !(y >> 1);
    n = n + hz;
    y = (y >> (!hz)) & 0x1;
    n = n + !y;
    return n;
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
    unsigned absx = x;
    unsigned sign = 0;
    unsigned exp;
    unsigned frac;
    unsigned rem;
    unsigned half;
    int e = 0;
    int shift;
    unsigned t;

    if (x < 0) {
        sign = 0x80000000u;
        absx = -absx;
    }
    if (absx == 0)
        return 0;

    t = absx;
    while (t > 1) {
        t = t >> 1;
        e = e + 1;
    }

    exp = e + 127;
    if (e < 24) {
        frac = absx << (23 - e);
    } else {
        shift = e - 23;
        frac = absx >> shift;
        rem = absx & ((1u << shift) - 1);
        half = 1u << (shift - 1);
        if (rem > half)
            frac = frac + 1;
        if (rem == half) {
            if (frac & 1)
                frac = frac + 1;
        }
        if (frac >> 24) {
            frac = frac >> 1;
            exp = exp + 1;
        }
    }
    return sign | (exp << 23) | (frac & 0x7fffff);
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
    unsigned exp = uf & 0x7f800000;
    unsigned frac = uf & 0x007fffff;
    if (exp == 0x7f800000)
        return uf;
    if (exp == 0) {
        if (frac == 0)
            return uf;
        return sign | (uf << 1);
    }
    return sign | (exp + 0x00800000) | frac;
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
    unsigned exp = (uf2 >> 20) & 0x7ff;
    unsigned val = 0x80000000u | ((uf2 & 0xfffff) << 11) | (uf1 >> 21);
    if (exp < 1023)
        return 0;
    if (exp > 1054)
        return 0x80000000u;
    val = val >> (1054 - exp);
    if (sign) {
        if (val > 0x80000000u)
            return 0x80000000u;
        return -val;
    } else {
        if (val > 0x7fffffffu)
            return 0x80000000u;
        return val;
    }
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
    if (x > 127)
        return 0x7f800000;
    if (x < -149)
        return 0;
    if (x < -126)
        return 1 << (x + 149);
    return (x + 127) << 23;
}
