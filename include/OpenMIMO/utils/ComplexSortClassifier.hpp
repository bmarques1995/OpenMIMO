#include <complex>

namespace OpenMIMO
{
    template<typename T>
    inline bool ComplexGreater(const std::complex<T>& a, const std::complex<T>& b)
    {
        return((std::norm(a) > std::norm(b)) && (std::real(a) > std::real(b)) && (std::imag(a) > std::imag(b)) );
    }

    template<typename T>
    inline bool ComplexLess(const std::complex<T>& a, const std::complex<T>& b)
    {
        //return ((a.real < b.real) || (a.imag < b.imag));
        return( (std::norm(a) > std::norm(b)) && (std::real(a) < std::real(b)) && (std::imag(a) < std::imag(b)) );
    }

    template<typename T>
    inline bool ComplexEqual(const std::complex<T>& a, const std::complex<T>& b)
    {
        return( (std::real(a) == std::real(b)) && (std::imag(a) == std::imag(b)) );
    }

    template<typename T>
    inline bool ComplexGreaterEqual(const std::complex<T>& a, const std::complex<T>& b)
    {
        return !ComplexLess(a,b);
    }

    template<typename T>
    inline bool ComplexLessEqual(const std::complex<T>& a, const std::complex<T>& b)
    {
        return !ComplexGreater(a,b);
    }
}
