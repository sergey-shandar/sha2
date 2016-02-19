#pragma once

#include <boost/range.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

template<class T, size_t S>
::std::wostream &operator<<(
    ::std::wostream &stream, ::std::array<T, S> const &array)
{
    for each (auto const &var in array)
    {
        stream.width(sizeof(T) * 2);
        stream.fill(L'0');
        stream << ::std::hex << var << L" ";
    }
    return stream;
}

namespace Microsoft {
    namespace VisualStudio {
        namespace CppUnitTestFramework {
            template<class T, size_t S>
            static std::wstring ToString(::std::array<T, S> const &t)
            {
                RETURN_WIDE_STRING(t);
            }
        }
    }
}

template<size_t S>
::boost::iterator_range<char const *> from_string(char const (&x)[S])
{
    return ::boost::make_iterator_range_n(x, S - 1);
}

template<uint8_t value>
class n_iterator_t
{
private:
    static uint8_t const _value = value;
    uint64_t _index;
public:
    typedef ::std::random_access_iterator_tag iterator_category;
    typedef uint8_t const value_type;
    typedef int64_t difference_type;
    typedef value_type *pointer;
    typedef value_type &reference;
    explicit n_iterator_t(uint64_t index) : _index(index) {}
    bool operator==(n_iterator_t const &i) const { return _index == i._index; }
    bool operator!=(n_iterator_t const &i) const { return !operator==(i); }
    n_iterator_t &operator++()
    {
        _index++;
        return *this;
    }
    reference operator *()
    {
        return _value;
    }
};

template<uint8_t value, uint64_t size>
class n_range_t
{
public:
    typedef n_iterator_t<value> iterator_t;
    iterator_t begin() const { return iterator_t(0); }
    iterator_t end() const { return iterator_t(size); }
};
