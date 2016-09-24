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

template<class T, T v, int size>
class remainder_t
{
public:
	static const T value = v << (sizeof(T) * CHAR_BIT - size);
};

template<class T, T v>
class remainder_t<T, v, 0>
{
public:
	static const T value = 0;
};

template<class T, T value, uint64_t size, int remainder_size_ = 0>
class fill_t
{
public:
	typedef fill_iterator_t<T, value> iterator_t;
	static iterator_t begin() { return iterator_t(0); }
	static iterator_t end() { return iterator_t(size); }
	static constexpr int remainder_size()
	{
		return remainder_size_;
	}
	static constexpr T remainder()
	{
		return remainder_t<T, value, remainder_size_>::value;
	}
};

template<size_t size>
constexpr sha2::uint_t<size> fill(uint8_t value)
{
	typedef sha2::uint_t<size> output_t;
	return
		static_cast<output_t>(
			0x0101010101010101ull & ::std::numeric_limits<output_t>::max()) *
		static_cast<output_t>(value);
}

template<size_t output_size, uint8_t value, uint64_t size>
constexpr auto fill8()
{
	return fill_t<
		sha2::uint_t<output_size>,
		fill<output_size>(value),
		size / output_size,
		size % output_size>();
}
