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
