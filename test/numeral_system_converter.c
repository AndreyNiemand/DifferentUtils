
#include "numeral_system_converter.h"

#include <stdio.h>
#include <float.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

typedef struct test_t {
    const char *in; 
    union { 
        int base_i;
        double base_d;
        _Dcomplex base_dc;
    };
    unsigned digits_count;
    union { 
        int out_i;
        double out_d;
        _Dcomplex  out_dc;
    };
   enum Type { Int, Double, DComplex } type;
} test_t;

static bool try_get_type(const char* str, enum Type* type)
{
    if(strcmp("Int", str) == 0)
    {
        *type = Int;
        return true;
    }
    if (strcmp("Double", str) == 0)
    {
        *type = Double;
        return true;
    }
    if (strcmp("DComplex", str) == 0)
    {
        *type = DComplex;
        return true;
    }
    
    return false;
}

int main(int argc, const char** argv)
{
    if (argc != 6 && argc != 8)
    {
        printf("Input must have 5 arguments for real numbers: in, {Int, Double, DComplex}, base, out, digits_count;\n");
        printf("and 7 arguments for complex: in, {Int, Double, DComplex}, base_real, base_img, out_real, out_img, digits_count.\n\n");
        printf("Example: %s 2.34 Double 10 2.34 10\n", argv[0]);
        printf("Example: %s 23 Complex 0 1 3 2 10\n", argv[0]);
        return -1;
    }

    enum Type type;
    if (!try_get_type(argv[2], &type))
    {
        printf("Error: the second argument can be one of the set {Int, Double, DComplex}.\n");
        printf("Example: %s 2.34 Double 10 2.34 10", argv[0]);
        return -1;
    }

    test_t test = {.in = argv[1], .type = type};
    switch(type)
    {
        case Int: {
            test.base_i = atoi(argv[3]);
            test.out_i  = atoi(argv[4]);
            test.digits_count = (unsigned)atol(argv[5]);
        } break;
        case Double: {
            test.base_d = atof(argv[3]);
            test.out_d  = atof(argv[4]);
            test.digits_count = (unsigned)atol(argv[5]);
        } break;
        case DComplex: {
            test.base_dc._Val[0] = atof(argv[3]);
            test.base_dc._Val[1] = atof(argv[4]);
            test.out_dc._Val[0]  = atoi(argv[5]);
            test.out_dc._Val[1]  = atoi(argv[6]);
            test.digits_count = (unsigned)atol(argv[7]);
        } break;
    }

    const double epsilon = 0.1e-7;

    switch(test.type)
    {
        case Int: 
        {
            int out;
            if (NS_try_converti(test.in, test.base_i, test.digits_count, &out))
            {
                //printf("%s(%d) -> %d(10): ", test.in, test.base_i, out);
                if (out == test.out_i)
                    printf("1");
                else 
                    printf("0");
            }
            else 
            {
                printf("%s(%d) could be converted.\n", test.in, test.base_i);
            }
        } break;
        case Double:
        {
            double out;
            if (NS_try_convertd(test.in, test.base_d, test.digits_count, &out))
            {
                //printf("%s(%.2lf) -> %.2lf(10): ", test.in, test.base_d, out);
                if (fabs(out - test.out_d) < epsilon)
                    printf("1");
                else 
                    printf("0");
            }
            else 
            {
                printf("%s(%.2lf) could be converted.\n", test.in, test.base_d);
            }
        } break;
        case DComplex:
        {
            _Dcomplex out;
            if (NS_try_convertdc(test.in, test.base_dc, test.digits_count, &out))
            {
                //printf("%s(%.2lf%+.2lfi) -> (%.2lf%+.2lfi)(10): ", test.in, creal(test.base_dc), cimag(test.base_dc), creal(out), cimag(out));

                if (   fabs(out._Val[0] - test.out_dc._Val[0]) < epsilon 
                    && fabs(out._Val[1] - test.out_dc._Val[1]) < epsilon)
                    printf("1");
                else 
                    printf("0");
            }
            else 
            {
                printf("%s(%.2lf%+.2lfi) could be converted.", test.in, creal(test.base_dc), cimag(test.base_dc));
            }   
        } break;
    }
    
    return 0;
}