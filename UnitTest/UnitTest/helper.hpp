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
			static std::wstring ToString(long long x)
			{
				RETURN_WIDE_STRING(x);
			}
        }
    }
}

template<size_t S>
::boost::iterator_range<char const *> from_string(char const (&x)[S])
{
    return ::boost::make_iterator_range_n(x, S - 1);
}

inline uint32_t change_char_order(uint32_t v)
{
	return (v << 24) | ((v << 8) & 0xFF0000) | ((v >> 8) & 0xFF00) | ((v >> 24) & 0xFF);
}

template<class V>
class iterator_t
{
private:
	V const *_i;
public:
	typedef ::std::random_access_iterator_tag iterator_category;
	typedef V const value_type;
	typedef int64_t difference_type;
	typedef value_type *pointer;
	typedef value_type &reference;
	explicit iterator_t(V const *i) : _i(i) {}
	V operator*() const { return change_char_order(*_i); }
	difference_type operator-(iterator_t const x) const { return _i - x._i; }
	bool operator!=(iterator_t const x) const { return _i != x._i; }
	iterator_t &operator++() { ++_i; return *this; }
};

template<class V>
auto iterator(V const *i)
{
	return iterator_t<V>(i);
}

template<class V, size_t S>
auto from_string2(char const (&s)[S])
{
	typedef V const *iterator_t;
	auto const char_size = S - 1;
	auto const size = char_size / sizeof(V);
	auto const remainder_size = char_size % sizeof(V);
	auto const remainder_offset = sizeof(V) - remainder_size;
	auto const begin = reinterpret_cast<iterator_t>(s);
	auto const end = begin + size;
	char char_remainder[sizeof(V)] = {};
	auto const remainder_begin = reinterpret_cast<char const *>(end);
	auto const remainder_end = remainder_begin + remainder_size;
	auto j = char_remainder;
	for (auto i = remainder_begin; i != remainder_end; ++i, ++j)
	{
		*j = *i;
	}
	return sha2::with_remainder(
		iterator(begin),
		iterator(end),
		change_char_order(*reinterpret_cast<V const *>(char_remainder)),
		remainder_size * CHAR_BIT);
}

template<size_t S>
auto from_string32(char const (&s)[S])
{
	return from_string2<uint32_t>(s);
}

template<class T, T value>
class n_iterator_t
{
private:
    static T const _value = value;
    uint64_t _index;
public:
    typedef ::std::random_access_iterator_tag iterator_category;
    typedef T const value_type;
    typedef int64_t difference_type;
    typedef value_type *pointer;
    typedef value_type &reference;
    explicit n_iterator_t(uint64_t index) : _index(index) {}
    bool operator==(n_iterator_t const &i) const { return _index == i._index; }
    bool operator!=(n_iterator_t const &i) const { return !operator==(i); }
    n_iterator_t &operator++()
    {
        ++_index;
        return *this;
    }
    reference operator *()
    {
        return _value;
    }
};

template<class T, T value, uint64_t size>
class nrange_t
{
public:
    typedef n_iterator_t<T, value> iterator_t;
    static iterator_t begin() { return iterator_t(0); }
    static iterator_t end() { return iterator_t(size); }
};

template<uint8_t value, uint64_t size>
using n_range_t = nrange_t<uint8_t, value, size>;
