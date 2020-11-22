
#include "numeral_system_converter.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <assert.h>

nsc_number_t nsc_convert_toi(int base, int num)
{
	assert(base != 1 && base != -1);

	nsc_number_t r = {.sign = (num < 0)};

	unsigned buf[sizeof(num) * 8U - 1U];
	unsigned i = 0;

	do {
		buf[i++] = num % base;
	} while ((num /= base));
	
	r.length = i;
	r.buf = calloc(i, sizeof(*r.buf));

	for (i = 0; i*2 < r.length; ++i)
	{
		const unsigned j = r.length - (i+1U);
		r.buf[i] = buf[j];
		r.buf[j] = buf[i];
	}

	return r;
}

nsc_number_t nsc_convert_toid(const int base, const double num)
{
	nsc_number_t r = { .buf = NULL };
	if (base == 0)
	{
		return r;
	}

	const double epsilon = 1e-7;

	if (base > 0)
	{
		r.sign = (num < 0);

		unsigned whole;
		double 	 fract;
		{
			double  whole_temp;
					fract = modf(num, &whole_temp);
					whole = (unsigned) fabs(whole_temp);
		}

		unsigned whole_buf [sizeof(whole) * 8U - 1U];
		unsigned fract_buf [sizeof(fract) * 8U - 1U];

		unsigned whole_i = 0;
		do {
			whole_buf[whole_i++] = whole % base;
		} while ((whole /= base));

		unsigned fract_i;
		for(fract_i = 0; fract_i < sizeof(fract) * 8U - 1U && fabs(fract) > epsilon; fract_i++) 
		{
			double temp;
			fract = modf(fract * base, &temp);
			fract_buf[fract_i] = (unsigned)temp;
		}

		r.point_pos = whole_i;
		r.length = whole_i + fract_i;
		r.buf = calloc(r.length, sizeof(*r.buf));

		for (unsigned i = 0; i*2 < whole_i; ++i)
		{
			const unsigned j = r.point_pos - (i+1U);
			r.buf[i] = whole_buf[j];
			r.buf[j] = whole_buf[i];
		}

		for (unsigned i = whole_i; i < fract_i; ++i)
		{
			r.buf[i] = fract_buf[i - whole_i];
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

int nsc_convert_fromi(int base, nsc_number_t num)
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

double nsc_convert_fromd(double base, nsc_number_t num)
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

_Dcomplex nsc_convert_fromdc(_Dcomplex base, nsc_number_t num)
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
	
	if (0xA <= x && x <= 0xA + (int)'Z')
	{
		*result = (char)x + 'A';
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

bool nsc_try_convert_fromi(int base, const char* str, unsigned digits_count, int* result)
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

bool nsc_try_convert_fromd (double base, const char* str, unsigned digits_count, double* result)
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

bool nsc_try_convert_fromdc(_Dcomplex base, const char* str, unsigned digits_count, _Dcomplex* result)
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

bool nsc_check(const char* str, unsigned digits_count)
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

bool nsc_parse(const char* str, nsc_number_t* number)
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