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

/* Convert a number to numerical system using base. */
int            nsc_converti (nsc_number_t, int base);
double         nsc_convertd (nsc_number_t, double base);
_Dcomplex      nsc_convertdc(nsc_number_t, _Dcomplex base);

/* 
    * Return converted 'str' if appropriate to 'base' and 'digits_count' in out argument 'result'.
    * Otherwise return false.
    * 
    * Conditions:
    *   str != NULL && str[last] == '\0',
    *   result != NULL.
*/
bool nsc_try_converti (const char* str, int base, unsigned digits_count, int* result);
bool nsc_try_convertd (const char* str, double base, unsigned digits_count, double* result);
bool nsc_try_convertdc(const char* str, _Dcomplex base, unsigned digits_count, _Dcomplex* result);

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