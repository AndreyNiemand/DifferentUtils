/* Author: AndreQ. 2020.

 * This program has been written to understand how floating-point numbers work.
 * Abilities:
    - Transform dec -> hex, oct or bin; also bin -> dec but the interface makes it implicity.
    - Show located value in the memory,
    - Calculate a mistake at a binary transfer.

 * If you want more functional, send a letter to lafortaviro@gmail.com
 * Or you may change and besides copy it. Use the full code anyway as you want.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void reverse(char s[])
{
    int ibegin = 0;
    int iend = (int)strlen(s);
    int c;

    while (ibegin < iend) {
        c = s[ibegin];
        s[ibegin++] = s[--iend];
        s[iend] = (char)c;
    }
}

char to_hex_char(unsigned x) // 0 < x < 16, else return 0;
{
    if (x < 10)
        return '0' + (char)x;
    else if (10 <= x && x < 16)
        return 'A' + (char)(x-10);

    return 0;
}

_Bool is_integral(float f)
{
    return fabs((f - (int)f)) < 0.0000001F;
}

float bin_to_dec(const char *bin)
{
    const int len = (int)strlen(bin);
    if (bin == 0 || len == 0) return 0;

    const _Bool hasMinus = bin[0] == '-';

    int pointPos;
    _Bool hasPoint = 0;

    for (int i = 0; i < len; i++)
    {
        if (bin[i] == '.') { hasPoint = 1; pointPos = i; break; }
    }

    // "101.101"; point's postion is 3 but the first power must be 2 cause needs
    pointPos--;

    float result = 0;
    for (int i = 0; i < len; i++, pointPos--)
    {
        if (bin[i] == '.')
        {
            continue;
        }

        if (bin[i] == '1')
            if (hasPoint)
                result += powf(2U, pointPos);
            else
                result += powf(2U, (len-i)-1);
    }
    return result * (hasMinus ? -1 : 1);
}

char* dec_to_base(float f, unsigned base, char* const out_buf) // correct for 2 and 16.
{
    char* buf = out_buf;

    if (f < 0)
    {
        f = -f;
        buf[0] = '-';
        buf++;
    }

    unsigned d = (unsigned)f;
    float m = f - (float)d;
    int i = 0;

    do
    {
        buf[i++] = to_hex_char(d % base);
    }
    while (d /= base);
    buf[i] = 0;

    reverse(buf);
    if (!is_integral(m))
    {
        buf[i++] = '.';

        float temp = m * base;
        for (;; temp = (temp - (float)(int)temp)*base, i++)
        {
            buf[i] = to_hex_char(((unsigned)temp) % base);
            if (is_integral(temp)) break;
        }

        buf[i+1] = 0;
    }
    return out_buf;
}

char* bits_in_memory(float f, char* out_buf)
{
    char buf [32];
    dec_to_base(*(unsigned*)&f, 2, buf);

    _Bool isFinishedBorder = 0;

    int j = 0;
    for(int i = 0; i < 32; j++)
    {
        if((j+1) % 5 == 0)
        {
            out_buf[j] = ' ';
        }
        else {
            if (buf[i] == 0) isFinishedBorder = 1;
            out_buf[j] = isFinishedBorder ? '0' : buf[i];

            i++;
        }
    }
    out_buf [32+8+1] = 0;

    return out_buf;
}

#define examples_count 4
static
float examples[examples_count] = {
                      124,
                     -87,
                      23.176F,
                     -99.321F,
                    };

void print(float f, _Bool withDec)
{
    char buf[100];

    printf("Hex: %s\n", dec_to_base(f, 16, buf));
    if (withDec) printf("Dec: %s\n", dec_to_base(f, 10, buf));
    printf("Oct: %s\n", dec_to_base(f,  8, buf));
    printf("Bin: %s\n", dec_to_base(f,  2, buf));

    printf("Bin (in memory): %s\n", bits_in_memory(f, buf));

    const double mistake = (double)f - (double)bin_to_dec(dec_to_base(f,  2, buf));
    if (fabs((double)mistake) > 0.00000)
        printf("Mistake at binary transfer: %.6f, (%.2f%%)\n", mistake, mistake * 100. / (double)f);

}

int main()
{
    printf("Hello!\nThe program helps to undestand how a 32-bit floating-point number looks in other base systems. "
           "It can process decimal -> hexadecimal, octal or binary bases only and also shows "
           "how its value is located in the memory (in binary only) and what mistake occurs at the binary transfer. "
           "Thanks for using Andrey's program.\nBefore you start, please pay to get a full functional revision or consider the examples:\n\n");

    for (int i = 0; i < examples_count; i++)
    {
        print(examples[i], 1);
        printf("\n");
    }

    float f;
    while(1)
    {
        printf("Dec: ");
        int _ = scanf("%f", &f); (void)_;
        print(f, 0);
        printf("\n");
    }

    return 0;
}
