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

constexpr uint32_t change_char_order(uint32_t v)
{
	return (v << 24) | ((v << 8) & 0xFF0000) | ((v >> 8) & 0xFF00) | ((v >> 24) & 0xFF);
}

constexpr uint64_t change_char_order(uint64_t v)
{
	return 
		 (v << 56) |
		((v << 40) & 0xFF000000000000ull) |
		((v << 24) & 0x00FF0000000000ull) |
		((v <<  8) & 0x0000FF00000000ull) | 
		((v >>  8) & 0x000000FF000000ull) |
		((v >> 24) & 0x00000000FF0000ull) |
		((v << 40) & 0x0000000000FF00ull) |
		((v >> 56) & 0x000000000000FFull);
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
	return with_remainder(
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

template<size_t S>
auto from_string64(char const (&s)[S])
{
	return from_string2<uint64_t>(s);
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
    reference operator *() const
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

template<class T>
constexpr T fill(uint8_t value)
{
	return static_cast<T>(0x0101010101010101ull) * static_cast<T>(value);
}

template<class T, uint8_t value, uint64_t size>
class nrange8_t: 
	public nrange_t<T, fill<T>(value), size / sizeof(T)>
{
public:
	static constexpr int remainder_size() { return (size % sizeof(T)) * CHAR_BIT; }
	static constexpr T remainder() { return fill<T>(value) << (sizeof(T) * CHAR_BIT - remainder_size()); }
};

template<uint8_t value, uint64_t size>
nrange8_t<uint32_t, value, size> nrange32()
{
	return nrange8_t<uint32_t, value, size>();
}

template<uint8_t value, uint64_t size>
nrange8_t<uint64_t, value, size> nrange64()
{
	return nrange8_t<uint64_t, value, size>();
}

template<class I>
class with_remainder_t
{
public:
	typedef typename ::std::iterator_traits<I>::value_type value_type;
private:
	I _begin;
	I _end;
	value_type const _remainder;
	int const _remainder_size;
public:
	with_remainder_t(
		I const &begin,
		I const &end,
		value_type remainder,
		int remainder_size) :
		_begin(begin),
		_end(end),
		_remainder(remainder),
		_remainder_size(remainder_size)
	{
	}
	I begin() const { return _begin; }
	I end() const { return _end; }
	value_type remainder() const { return _remainder; }
	int remainder_size() const { return _remainder_size; }
};

template<class I, class V>
auto with_remainder(
I const &begin, I const &end, V remainder, int remainder_size)
{
	return with_remainder_t<I>(begin, end, remainder, remainder_size);
}

template<class I>
auto no_remainder(I const &begin, I const &end)
{
	return with_remainder(begin, end, 0, 0);
}

template<class C>
auto no_remainder(C const &c)
{
	return no_remainder(::std::begin(c), ::std::end(c));
}