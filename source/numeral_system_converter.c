
#include "numeral_system_converter.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <assert.h>

#ifdef WIN32
    #if NSC_SHARED_LIBRARY
		#define NSC_IMPLEMENT __declspec(dllexport)
	#endif
#endif

#ifndef NSC_IMPLEMENT
#define NSC_IMPLEMENT
#endif

NSC_IMPLEMENT nsc_number_t nsc_convert_toi(int base, int num)
{
	assert(base != 1 && base != -1);

	nsc_number_t r = {.sign = (num < 0)};

	unsigned buf[sizeof(num) * 8U - 1U];
	unsigned i = 0;

	num = abs(num);

	do {
		buf[i++] = num % base;
	} while ((num /= base));
	
	r.length = i;
	r.point_pos = i;
	r.buf = calloc(i, sizeof(*r.buf));

	for (i = 0; i*2 < r.length; ++i)
	{
		const unsigned j = r.length - (i+1U);
		r.buf[i] = buf[j];
		r.buf[j] = buf[i];
	}

	return r;
}

NSC_IMPLEMENT nsc_number_t nsc_convert_toid(const int base, double num)
{
	nsc_number_t r = { .buf = NULL };
	if (base == 0)
	{
		return r;
	}

	const double epsilon = 1e-7;

	if (base > 0)
	{
		if((r.sign = (num < 0)))
		{
			num = -num;
		}

		unsigned whole;
		double 	 fract;
		{
			double  temp;
			fract = modf(num, &temp);
			whole = (unsigned) fabs(temp);
		}

		unsigned buf[sizeof(num) * 8U - 1U];

		unsigned i = 0;
		do {
			buf[i++] = whole % base;
			assert(i < sizeof(buf)/sizeof(*buf));
		} while ((whole /= base));
		
		r.point_pos = i;

		for(; i < sizeof(buf)/sizeof(*buf) && fabs(fract) > epsilon; i++) 
		{
			double temp;
			fract = modf(fract * base, &temp);
			buf[i] = (unsigned)temp;

			assert(temp > 0 || fabs(temp) < epsilon);
		}

		r.length = i;
		r.buf = calloc(r.length, sizeof(*r.buf));

		for (unsigned i = 0; i < r.point_pos; ++i)
		{
			const unsigned j = r.point_pos - (i+1U);
			r.buf[i] = buf[j];
			r.buf[j] = buf[i];
		}

		for (unsigned i = r.point_pos; i < r.length; ++i)
		{
			r.buf[i] = buf[i];
		}
	}
	else if (base < 0)
	{
		double num_whole, num_fract = modf(num, &num_whole);

		unsigned i = 0, buf [sizeof(num_whole) * 8U - 1U];
		for (double whole = num_whole; (i < sizeof(num_whole) * 8U - 1U) && fabs(whole) > epsilon; ++i)
		{
			double fract = modf(whole / base, &whole);

			if(fract > 0)
			{	
				whole++;
				fract--;
			}

			assert(round(base * fract) > 0.0 || fabs(round(base * fract)) < epsilon);
			buf[i] = (unsigned) round(base * fract);
		}

		r.point_pos = i;

		for (double whole, fract = num_fract; (i < sizeof(num_fract) * 8U - 1U) && fabs(fract) > epsilon; ++i)
		{
			fract = modf(fract * base, &whole);

			if (fract > 0)
			{
				whole++;
				fract--;
			}

			assert(whole > 0.0 || fabs(whole) < epsilon);
			buf[i] = (unsigned) whole;
		}

		r.length = i;
		r.buf = calloc(r.length, sizeof(*r.buf));

		for (i = 0; i < r.point_pos; ++i)
		{
			const unsigned j = r.point_pos - (i+1U);
			r.buf[i] = buf[j];
			r.buf[j] = buf[i];
		}

		for (i = r.point_pos; i < r.length; ++i)
		{
			r.buf[i] = buf[i];
		}
	}

	return r;
}

NSC_IMPLEMENT int nsc_convert_fromi(int base, nsc_number_t num)
{
	assert(num.buf != NULL);

	int result = 0;

	for (unsigned i = 0; i < num.length; ++i)
	{
		unsigned power = num.length - (i + 1U);
		result += (int)pow(base, power) * num.buf[i];
	}	

	return result * (num.sign ? -1 : 1);
}

NSC_IMPLEMENT double nsc_convert_fromd(double base, nsc_number_t num)
{
	assert(num.buf != NULL);

	double result = 0;

	for (unsigned i = 0; i < num.length; ++i)
	{
		int power = (int)num.point_pos - (int)(i + 1U);
		result += pow(base, power) * num.buf[i];
	}	

	return result * (num.sign ? -1.0 : 1.0);
}

NSC_IMPLEMENT _Dcomplex nsc_convert_fromdc(_Dcomplex base, nsc_number_t num)
{
	assert(num.buf != NULL);

	_Dcomplex result = {._Val = {0, 0}};

	for (unsigned i = 0; i < num.length; ++i)
	{
		int power = (int)num.point_pos - (int)(i + 1U);
		
		_Dcomplex temp = _Cmulcr(cpow(base,_Cbuild(power, 0)), 
								 num.buf[i]);			 
		result._Val[0] += temp._Val[0];
		result._Val[1] += temp._Val[1];
	}	

	if (num.sign)
		return _Cmulcr(result, -1.0);

	return result;
}

static bool nsc_pasre_char(unsigned x, char* result)
{
	assert(result != NULL);

	if (0 <= x && x <= 9)
	{
		*result = (char)x + '0';
		return true;
	}
	
	if (0xA <= x && x <= 0xA + (int)('Z' - 'A'))
	{
		*result = 'A' + (x - 0xA);
		return true;
	}
	
	return false;
}

static bool nsc_pasre_digit(char x, unsigned* result)
{	
	assert(result != NULL);	

	if (result == NULL)
		return false;

	if ('A' <= x && x <= 'Z')
	{
		*result = x - 'A' + 10;
		return true;
	}
	
	if ('0' <= x && x <= '9')
	{
		*result = x - '0';
		return true;
	}
	
	return false;
}

NSC_IMPLEMENT bool nsc_try_convert_fromi(int base, const char* str, unsigned digits_count, int* result)
{
	assert(result != NULL);
	assert(str != NULL);
	assert(str[strnlen_s(str, 1024U)] == '\0');

	if (nsc_check(str, digits_count))
	{
		const size_t len = strlen(str);
		nsc_number_t num = {.buf = calloc(len, sizeof(*num.buf))};

		if(nsc_parse(str, &num))
		{
			*result = nsc_convert_fromi(base, num);

			free(num.buf);
			return true;
		}
		free(num.buf);
	}

	return false;
}

NSC_IMPLEMENT bool nsc_try_convert_fromd (double base, const char* str, unsigned digits_count, double* result)
{
	assert(result != NULL);
	assert(str != NULL);
	assert(str[strnlen_s(str, 1024U)] == '\0');	

	if (nsc_check(str, digits_count))
	{
		const size_t len = strlen(str);
		nsc_number_t num = {.buf = calloc(len, sizeof(*num.buf))};

		if (nsc_parse(str, &num))
		{
			*result = nsc_convert_fromd(base, num);

			free(num.buf);
			return true;
		}
		free(num.buf);
	}

	return false;
}

NSC_IMPLEMENT bool nsc_try_convert_fromdc(_Dcomplex base, const char* str, unsigned digits_count, _Dcomplex* result)
{
	assert(result != NULL);
	assert(str != NULL);
	assert(str[strnlen_s(str, 1024U)] == '\0');

	if (nsc_check(str, digits_count))
	{
		const size_t len = strlen(str);
		nsc_number_t num = {.buf = calloc(len, sizeof(*num.buf))};

		if (nsc_parse(str, &num))
		{
			*result = nsc_convert_fromdc(base, num);

			free(num.buf);
			return true;
		}
		free(num.buf);
	}

	return false;
}

NSC_IMPLEMENT bool nsc_check(const char* str, unsigned digits_count)
{
	assert(str != NULL);

	unsigned i = 0;
	switch(str[i])
	{
		case '+':  
		case '-': i++; break;
	}

	bool foundPoint = false;
	for (unsigned j = 0; str[i] != 0; ++i)
	{
		unsigned val;
		if (!foundPoint && str[i] == '.')
		{
			foundPoint = true;
		} 
		else if (!nsc_pasre_digit(str[i], &val) || val >= digits_count)
		{
			return false;
		}
	}
	return true;
}

NSC_IMPLEMENT bool nsc_parse(const char* str, nsc_number_t* number)
{	
	assert(str != NULL);
	assert(str[strnlen_s(str, 1024U)] == '\0');
	assert(number != NULL);
	assert(number->buf != NULL);

	unsigned i = 0;
	bool found_point = false;

	if (str[i] != 0)
		switch(str[i])
		{
			case '+': number->sign = false; i++; break;
			case '-': number->sign =  true; i++; break;
		}
	
	unsigned j = 0;
	for (; str[i] != 0; ++i)
	{
		unsigned digit;
		if (str[i] == '.')
		{
			found_point = true;
			number->point_pos = j;
		}
		else if (nsc_pasre_digit(str[i], &digit))
		{
			number->buf[j++] = digit;
		}
		else return false;
	}

	number->length = j;

	if(!found_point) 
		number->point_pos = number->length;

	return true;
}

NSC_IMPLEMENT char* nsc_to_string(nsc_number_t num, char *buf)
{
	assert(buf != NULL);
	assert(num.buf != NULL);
	
	unsigned i = 0;

	if (num.sign)
	{
		buf[i++] = '-';
		num.point_pos++;
	}

	for (unsigned j = 0; j < num.length; ++i)
	{
		if (i == num.point_pos)
		{
			buf[i] = '.';
		}
		else 
		{
			char r;
			bool is_parsed = nsc_pasre_char(num.buf[j++], &r);
			assert(is_parsed);
			buf[i] = r;
		}
	}

	buf[i] = '\0';
	
	return buf;
}

#ifdef NSC_EXECUTABLE

#include <stdio.h>

int main(int argc, char** argv)
{
	const double epsilon = 1e-7;

	if(argc != 4)
	{
		fprintf(stderr, "Error: there must be 3 arguments: \n%s number:Double from_radix:Double to_radix:Int\n", argv[0]);
		return EXIT_FAILURE;
	}

	const char* const in_num = argv[1];
	const double from_radix  = atof(argv[2]);
	const int    to_radix    = atoi(argv[3]);

	if (fabs(from_radix) < epsilon)
	{
		fprintf(stderr, "Error: the base radix '%f' is so little.", from_radix);
		return EXIT_FAILURE;
	}
	if (to_radix == 0)
	{
		fprintf(stderr, "Error: the radix '%d' must be not 0.", to_radix);
		return EXIT_FAILURE;
	}

	double result; 

	double _, fract = fabs(modf(from_radix, &_)) + fabs(modf(to_radix, &_));
	unsigned digits_count = fabs(fract) < epsilon ? (unsigned) fabs(from_radix) : 10U;

	nsc_try_convert_fromd(from_radix, in_num, digits_count, &result);
	nsc_number_t n = nsc_convert_toid(to_radix, result);
				
	char buf[1024];
	printf("%s", nsc_to_string(n, buf));
	free(n.buf);

	return EXIT_SUCCESS;
}

#endif