#include "stdafx.h"
#include "CppUnitTest.h"

#include "../../src/sha2.hpp"

#include "helper.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
    // From http://csrc.nist.gov/groups/ST/toolkit/documents/Examples/SHA2_Additional.pdf
    TEST_CLASS(Sha2AdditionalTest)
    {
    public:

        TEST_METHOD(A224)
        {
            Assert::AreEqual(
                sha2::sha224(from_string("\xFF")), 
                {
                    0xe33f9d75, 0xe6ae1369, 0xdbabf81b, 0x96b4591a, 0xe46bba30, 0xb591a6b6, 0xc62542b5
                });
            Assert::AreEqual(
                sha2::sha224(from_string("\xe5\xe0\x99\x24")),
                {
                    0xfd19e746, 0x90d29146, 0x7ce59f07, 0x7df31163, 0x8f1c3a46, 0xe510d0e4, 0x9a67062d
                });
            Assert::AreEqual(
                sha2::sha224(n_range_t<0, 56>()),
                {
                    0x5c3e25b6, 0x9d0ea26f, 0x260cfae8, 0x7e23759e, 0x1eca9d1e, 0xcc9fbf3c, 0x62266804
                });
            Assert::AreEqual(
                sha2::sha224(n_range_t<0x51, 1000>()),
                {
                    0x3706197f, 0x66890a41, 0x779dc879, 0x1670522e, 0x136fafa2, 0x48746857, 0x15bd0a8a
                });
            Assert::AreEqual(
                sha2::sha224(n_range_t<0x41, 1000>()),
                {
                    0xa8d0c66b, 0x5c6fdfd8, 0x36eb3c6d, 0x04d32dfe, 0x66c3b1f1, 0x68b488bf, 0x4c9c66ce
                });
            Assert::AreEqual(
                sha2::sha224(n_range_t<0x99, 1005>()),
                {
                    0xcb00ecd0, 0x3788bf6c, 0x0908401e, 0x0eb053ac, 0x61f35e7e, 0x20a2cfd7, 0xbd96d640
                });
            Assert::AreEqual(
                sha2::sha224(n_range_t<0, 1000000>()),
                {
                    0x3a5d74b6, 0x8f14f3a4, 0xb2be9289, 0xb8d37067, 0x2d0b3d2f, 0x53bc303c, 0x59032df3
                });
            Assert::AreEqual(
                sha2::sha224(n_range_t<0x41, 0x20000000>()),
                {
                    0xc4250083, 0xcf8230bf, 0x21065b30, 0x14baaaf9, 0xf76fecef, 0xc21f91cf, 0x237dedc9
                });
            Assert::AreEqual(
                sha2::sha224(n_range_t<0, 0x41000000>()),
                {
                    0x014674ab, 0xc5cb9801, 0x99935695, 0xaf22fab6, 0x83748f42, 0x61d4c649, 0x2b77c543
                });
            Assert::AreEqual(
                sha2::sha224(n_range_t<0x84, 0x6000003f>()),
                {
                    0xa654b50b, 0x767a8323, 0xc5b519f4, 0x67d86698, 0x37142881, 0xdc7ad368, 0xa7d5ef8f
                });
        }
    };
}