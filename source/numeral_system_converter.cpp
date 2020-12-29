/*
 * C++ interface for the numeral system converter program.
 */

#include <vector>

#include "numeral_system_converter.h"

namespace nsc {

    template<class T, class A1, class ...AN> static constexpr
    T try_get_else_cast(const std::variant<A1, AN...> &val)
    {
        if(const T* p = std::get_if<T>(&val))
        {
            return *p;
        }

        return static_cast<T>(*std::get_if<double>(&val)); // TODO: temporary solution.
    }

    number_t::number_t(std::string_view num, int base)
    {
       nsc_number_t t;
       t.buf = new std::remove_pointer_t<decltype (nsc_number_t::buf)>[num.length()];
       nsc_parse(&num.front(), &t);
       m_val = nsc_convert_fromi(base, t);
       delete[] t.buf;
    }

    number_t::number_t(int num): m_val(num) {  }

    number_t::operator int() const
    {
        return try_get_else_cast<int>(m_val);
    }

    std::string number_t::to_base(int base) const
    {
        auto t = nsc_convert_toi(base, try_get_else_cast<int>(m_val));
        char* buf = new char[t.length];
        auto result = nsc_to_string(t, buf);
        delete[] buf;
        free(t.buf);

        return result;
    }

} // namespace nsc
