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

#ifdef __cplusplus
    #include <string_view>
    #include <string>
    #include <cstdlib>
    #include <variant>

    #define EXTERN extern "C"
    #define NSC_NAMESPACE_BEGIN namespace nsc {
    #define NSC_NAMESPACE_END   }
#else
    #include <complex.h>
    #include <stdbool.h>

    #define EXTERN extern
    #define NSC_NAMESPACE_BEGIN
    #define NSC_NAMESPACE_END
#endif

#ifdef WIN32
    #ifdef NSC_SHARED_LIBRARY
        #define NSC_DECLARE(result_t, name, ...)                          \
          EXTERN __declspec(dllexport) result_t   name     (__VA_ARGS__)

    #elif !defined(NSC_STATIC_LIBRARY) && !defined(NSC_EXECUTABLE)
        #define NSC_DECLARE(result_t, name, ...)                          \
          EXTERN __declspec(dllimport) result_t   name     (__VA_ARGS__); \
                typedef               result_t (*name##_t)(__VA_ARGS__)
    #endif 
#endif

#ifndef NSC_DECLARE
#define NSC_DECLARE(result_t, name, ...) EXTERN result_t name (__VA_ARGS__)
#endif 

NSC_NAMESPACE_BEGIN

typedef struct nsc_number_t
{
    unsigned*      buf;
    unsigned point_pos;
    unsigned    length;
    bool          sign; // plus - false, minus - true;
} nsc_number_t;

/* Converts a number from 'base' numerical system. */
NSC_DECLARE(int      , nsc_convert_fromi , int        base, nsc_number_t);
NSC_DECLARE(double   , nsc_convert_fromd , double     base, nsc_number_t);
//NSC_DECLARE(_Dcomplex, nsc_convert_fromdc,  _Dcomplex base, NSC(number_t));

/* Converts 'num' to 'base' numerical system. */
NSC_DECLARE(nsc_number_t, nsc_convert_toi , int base,    int num);
NSC_DECLARE(nsc_number_t, nsc_convert_toid, int base, double num);

/* 
    * Return converted 'str' from 'base' numerical system if appropriate to 'base' and 'digits_count' in out-argument 'result'.
    *   Otherwise false.
    * 
    * Conditions:
    *   str != NULL && str[last] == '\0',
    *   result != NULL.
*/
NSC_DECLARE(bool, nsc_try_convert_fromi ,       int base, const char* str, unsigned digits_count,       int* result);
NSC_DECLARE(bool, nsc_try_convert_fromd ,    double base, const char* str, unsigned digits_count,    double* result);
//NSC_DECLARE(bool, nsc_try_convert_fromdc, _Dcomplex base, const char* str, unsigned digits_count, _Dcomplex* result);

/* 
    * Checks 'str' could be converted. 
    * A..Z are used after 0..9. Other digits are not used.
    * 
    * Conditions:
    *   str != NULL && str[last] == '\0',
    *   str = reg: "^[+-]?[0-9A-Z]+$".
*/
NSC_DECLARE(bool, nsc_check, const char* str, unsigned digits_count);

/* 
    * Pasres a real number only with '+' (optional) or '-' sign ahead.
    * 
    * Conditions:
    *   str != NULL && str[last] == '\0',
    *   num != NULL && num->buf != NULL.
    *   num->length >= count of parsable charachters,
*/
NSC_DECLARE(bool, nsc_parse, const char* str, nsc_number_t* num);

/*
    * Converts number into string using and returning 'buf' with finish character '\0'.
    * 
    * Conditions:
    *   buf != NULL,
    *   number.buf != NULL,
    *   number.length + (1 if number has point) + (1 if number has sign) < buf.length.
*/
NSC_DECLARE(char*, nsc_to_string, nsc_number_t, char *buf);

#ifdef __cplusplus

class number_t
{
public:
    number_t() = default;
   ~number_t() = default;

    number_t(number_t&&) = default;
    number_t(const number_t&) = default;

    number_t& operator=(number_t&&) = default;
    number_t& operator=(const number_t&) = default;

    explicit number_t(std::string_view num, int base);
    number_t(int num);

    std::string to_base (int base) const;
    operator int() const;

private:
    std::variant<int, double> m_val;
};

#endif // __cplusplus

NSC_NAMESPACE_END

#endif //NUMERAL_SYSTEM_CONVERTER_H
