#include "stdafx.h"
#include "CppUnitTest.h"

#include "../../sha2.hpp"

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

namespace UnitTest
{	
	TEST_CLASS(Sha2Test)
	{
	public:
		
		TEST_METHOD(Sha224)
		{
            Assert::AreEqual(
                sha2::sha224(from_string("")), 
                { 
                    0xd14a028c,
                    0x2a3a2bc9,
                    0x476102bb,
                    0x288234c4, 
                    0x15a2b01f,
                    0x828ea62a,
                    0xc5b3e42f
                });
            Assert::AreEqual(
                sha2::sha224(from_string(
                    "The quick brown fox jumps over the lazy dog")),
                {
                    0x730e109b,
                    0xd7a8a32b,
                    0x1cb9d9a0,
                    0x9aa2325d,
                    0x2430587d,
                    0xdbc0c38b,
                    0xad911525
                });
            Assert::AreEqual(
                sha2::sha224(from_string(
                    "The quick brown fox jumps over the lazy dog.")),
                {
                    0x619cba8e,
                    0x8e05826e,
                    0x9b8c519c,
                    0x0a5c68f4,
                    0xfb653e8a,
                    0x3d8aa04b,
                    0xb2c8cd4c
                });
		}

        TEST_METHOD(Sha256)
        {
            Assert::AreEqual(
                sha2::sha256(from_string("")),
                {
                    0xe3b0c442,
                    0x98fc1c14,
                    0x9afbf4c8,
                    0x996fb924,
                    0x27ae41e4,
                    0x649b934c,
                    0xa495991b,
                    0x7852b855
                });
            Assert::AreEqual(
                sha2::sha256(from_string(
                    "The quick brown fox jumps over the lazy dog")),
                {
                    0xd7a8fbb3,
                    0x07d78094,
                    0x69ca9abc,
                    0xb0082e4f,
                    0x8d5651e4,
                    0x6d3cdb76,
                    0x2d02d0bf,
                    0x37c9e592
                });
            Assert::AreEqual(
                sha2::sha256(from_string(
                    "The quick brown fox jumps over the lazy dog.")),
                {
                    0xef537f25,
                    0xc895bfa7,
                    0x82526529,
                    0xa9b63d97,
                    0xaa631564,
                    0xd5d789c2,
                    0xb765448c,
                    0x8635fb6c
                });
        }

        TEST_METHOD(Sha512)
        {
            Assert::AreEqual(
                sha2::sha512(from_string("")),
                {
                    0xcf83e1357eefb8bd,
                    0xf1542850d66d8007,
                    0xd620e4050b5715dc,
                    0x83f4a921d36ce9ce,
                    0x47d0d13c5d85f2b0,
                    0xff8318d2877eec2f,
                    0x63b931bd47417a81,
                    0xa538327af927da3e,
                });
        }
	};
}