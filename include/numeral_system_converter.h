/* 
 * Author: AndreyNiemand, https://github.com/AndreyNiemand. 2020. 
 *
 * The API allows to convert a number from any numeral system defiend in integers, 
 * reals and complexes fields to decimal view.
 * 
 * If you want more functionality, please, send a letter to lafortaviro@gmail.com,
 * Also you may change and copy it partly or fully. 
 * 
*/

#ifndef NUMERAL_SYSTEM_CONVERTER_H
#define NUMERAL_SYSTEM_CONVERTER_H

#include <complex.h>
#include <stdbool.h>

typedef struct nsc_number_t {
	unsigned* buf;
	unsigned point_pos;
	unsigned length;
	bool sign; // plus - false, minus - true;
} nsc_number_t;

/* Converts a number from 'base' numerical system. */
int            nsc_convert_fromi (int        base,  nsc_number_t);
double         nsc_convert_fromd (double     base,  nsc_number_t);
_Dcomplex      nsc_convert_fromdc( _Dcomplex base,  nsc_number_t);

/* Converts 'num' to 'base' numerical system. */
nsc_number_t     nsc_convert_toi (int    base,    int num);
nsc_number_t     nsc_convert_toid(int    base, double num);

/* 
    * Return converted 'str' from 'base' numerical system if appropriate to 'base' and 'digits_count' in out-argument 'result'.
    *   Otherwise false.
    * 
    * Conditions:
    *   str != NULL && str[last] == '\0',
    *   result != NULL.
*/
bool nsc_try_convert_fromi (      int base, const char* str, unsigned digits_count,       int* result);
bool nsc_try_convert_fromd (   double base, const char* str, unsigned digits_count,    double* result);
bool nsc_try_convert_fromdc(_Dcomplex base, const char* str, unsigned digits_count, _Dcomplex* result);

/* 
    * Checks 'str' could be converted. 
    * A..Z are used after 0..9. Other digits are not used.
    * 
    * Conditions:
    *   str != NULL && str[last] == '\0',
    *   str = reg: "^[+-]?[0-9A-Z]+$".
*/
bool nsc_check(const char* str, unsigned digits_count);

/* 
    * Pasres a real number only with '+' (optional) or '-' sign ahead.
    * 
    * Conditions:
    *   str != NULL && str[last] == '\0',
    *   num != NULL && num->buf != NULL.
    *   num->length >= count of parsable charachters,
*/
bool nsc_parse(const char* str, nsc_number_t* num);

#endif NUMERAL_SYSTEM_CONVERTER_H