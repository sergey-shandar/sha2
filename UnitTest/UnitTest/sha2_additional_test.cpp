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

        TEST_METHOD(A256)
        {
            Assert::AreEqual(
                sha2::sha256(from_string("\xbd")),
                {
                    0x68325720, 0xaabd7c82, 0xf30f554b, 0x313d0570, 0xc95accbb, 0x7dc4b5aa, 0xe11204c0, 0x8ffe732b
                });
            Assert::AreEqual(
                sha2::sha256(from_string("\xc9\x8c\x8e\x55")),
                {
                    0x7abc22c0, 0xae5af26c, 0xe93dbb94, 0x433a0e0b, 0x2e119d01, 0x4f8e7f65, 0xbd56c61c, 0xcccd9504
                });
            Assert::AreEqual(
                sha2::sha256(n_range_t<0, 55>()),
                {
                    0x02779466, 0xcdec1638, 0x11d07881, 0x5c633f21, 0x90141308, 0x1449002f, 0x24aa3e80, 0xf0b88ef7
                });
            Assert::AreEqual(
                sha2::sha256(n_range_t<0, 56>()),
                {
                    0xd4817aa5, 0x497628e7, 0xc77e6b60, 0x6107042b, 0xbba31308, 0x88c5f47a, 0x375e6179, 0xbe789fbb
                });
            Assert::AreEqual(
                sha2::sha256(n_range_t<0, 57>()),
                {
                    0x65a16cb7, 0x861335d5, 0xace3c607, 0x18b5052e, 0x44660726, 0xda4cd13b, 0xb745381b, 0x235a1785
                });
            Assert::AreEqual(
                sha2::sha256(n_range_t<0, 64>()),
                {
                    0xf5a5fd42, 0xd16a2030, 0x2798ef6e, 0xd309979b, 0x43003d23, 0x20d9f0e8, 0xea9831a9, 0x2759fb4b
                });
            Assert::AreEqual(
                sha2::sha256(n_range_t<0, 1000>()),
                {
                    0x541b3e9d, 0xaa09b20b, 0xf85fa273, 0xe5cbd3e8, 0x0185aa4e, 0xc298e765, 0xdb87742b, 0x70138a53
                });
                /*
                #8) 1000 bytes of 0x41 ‘A’
                c2e68682 3489ced2 017f6059 b8b23931 8b6364f6 dcd835d0 a519105a 1eadd6e4

                #9) 1005 bytes of 0x55 ‘U’
                f4d62dde c0f3dd90 ea1380fa 16a5ff8d c4c54b21 740650f2 4afc4120 903552b0

                #10) 1000000 bytes of zeros
                d29751f2 649b32ff 572b5e0a 9f541ea6 60a50f94 ff0beedf b0b692b9 24cc8025

                #11) 0x20000000 (536870912) bytes of 0x5a ‘Z’
                15a1868c 12cc5395 1e182344 277447cd 0979536b adcc512a d24c67e9 b2d4f3dd

                #12) 0x41000000 (1090519040) bytes of zeros
                461c19a9 3bd4344f 9215f5ec 64357090 342bc66b 15a14831 7d276e31 cbc20b53

                #13) 0x6000003e (1610612798) bytes of 0x42 ‘B’
                c23ce8a7 895f4b21 ec0daf37 920ac0a2 62a22004 5a03eb2d fed48ef9 b05aabea
                */
        }
    };
}