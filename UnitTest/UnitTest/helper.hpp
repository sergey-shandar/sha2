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

template<class T, T value>
class fill_iterator_t
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
	explicit fill_iterator_t(uint64_t index) : _index(index) {}
	bool operator==(fill_iterator_t const &i) const
	{
		return _index == i._index;
	}
	bool operator!=(fill_iterator_t const &i) const
	{
		return !operator==(i);
	}
	fill_iterator_t &operator++()
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
class fill_t
{
public:
	typedef fill_iterator_t<T, value> iterator_t;
	static iterator_t begin() { return iterator_t(0); }
	static iterator_t end() { return iterator_t(size); }
};

template<class T>
constexpr T fill(uint8_t value)
{
	return static_cast<T>(0x0101010101010101ull) * static_cast<T>(value);
}

template<class T, uint8_t value, uint64_t size>
class nrange8_t :
	public fill_t<T, fill<T>(value), size / sizeof(T)>
{
public:
	static constexpr int remainder_size()
	{
		return (size % sizeof(T)) * CHAR_BIT;
	}
	static constexpr T remainder()
	{
		return fill<T>(value) << (sizeof(T) * CHAR_BIT - remainder_size());
	}
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
