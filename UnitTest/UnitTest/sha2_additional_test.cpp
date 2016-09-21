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

        TEST_METHOD(A224Size)
        {
            uint32_t const x4[] = { 0xe5e09924 };
            Assert::AreEqual(
                sha2::sha224(sha2::no_remainder(x4)),
                {
                    0xfd19e746, 0x90d29146, 0x7ce59f07, 0x7df31163, 0x8f1c3a46, 0xe510d0e4, 0x9a67062d
                });
        }

        TEST_METHOD(A256SizeU)
        {
            uint32_t const x4[] = { 0xc98c8e55 };
            Assert::AreEqual(
                sha2::sha256(sha2::no_remainder(x4)),
                {
                    0x7abc22c0, 0xae5af26c, 0xe93dbb94, 0x433a0e0b, 0x2e119d01, 0x4f8e7f65, 0xbd56c61c, 0xcccd9504
                });
        }

        TEST_METHOD(A224)
        {
            Assert::AreEqual(
                sha2::sha224(from_string32("\xFF")), 
                {
                    0xe33f9d75, 0xe6ae1369, 0xdbabf81b, 0x96b4591a, 0xe46bba30, 0xb591a6b6, 0xc62542b5
                });
            Assert::AreEqual(
                sha2::sha224(from_string32("\xe5\xe0\x99\x24")),
                {
                    0xfd19e746, 0x90d29146, 0x7ce59f07, 0x7df31163, 0x8f1c3a46, 0xe510d0e4, 0x9a67062d
                });
            Assert::AreEqual(
                sha2::sha224(nrange32<0, 56>()),
                {
                    0x5c3e25b6, 0x9d0ea26f, 0x260cfae8, 0x7e23759e, 0x1eca9d1e, 0xcc9fbf3c, 0x62266804
                });
            Assert::AreEqual(
                sha2::sha224(nrange32<0x51, 1000>()),
                {
                    0x3706197f, 0x66890a41, 0x779dc879, 0x1670522e, 0x136fafa2, 0x48746857, 0x15bd0a8a
                });
            Assert::AreEqual(
                sha2::sha224(nrange32<0x41, 1000>()),
                {
                    0xa8d0c66b, 0x5c6fdfd8, 0x36eb3c6d, 0x04d32dfe, 0x66c3b1f1, 0x68b488bf, 0x4c9c66ce
                });
            Assert::AreEqual(
                sha2::sha224(nrange32<0x99, 1005>()),
                {
                    0xcb00ecd0, 0x3788bf6c, 0x0908401e, 0x0eb053ac, 0x61f35e7e, 0x20a2cfd7, 0xbd96d640
                });
            Assert::AreEqual(
                sha2::sha224(nrange32<0, 1000000>()),
                {
                    0x3a5d74b6, 0x8f14f3a4, 0xb2be9289, 0xb8d37067, 0x2d0b3d2f, 0x53bc303c, 0x59032df3
                });
            Assert::AreEqual(
                sha2::sha224(nrange32<0x41, 0x20000000>()),
                {
                    0xc4250083, 0xcf8230bf, 0x21065b30, 0x14baaaf9, 0xf76fecef, 0xc21f91cf, 0x237dedc9
                });
            Assert::AreEqual(
                sha2::sha224(nrange32<0, 0x41000000>()),
                {
                    0x014674ab, 0xc5cb9801, 0x99935695, 0xaf22fab6, 0x83748f42, 0x61d4c649, 0x2b77c543
                });
            Assert::AreEqual(
                sha2::sha224(nrange32<0x84, 0x6000003f>()),
                {
                    0xa654b50b, 0x767a8323, 0xc5b519f4, 0x67d86698, 0x37142881, 0xdc7ad368, 0xa7d5ef8f
                });
        }

        TEST_METHOD(A256FromString1)
        {
            Assert::AreEqual(
                sha2::sha256(from_string32("\xbd")),
                {
                    0x68325720, 0xaabd7c82, 0xf30f554b, 0x313d0570, 0xc95accbb, 0x7dc4b5aa, 0xe11204c0, 0x8ffe732b
                });
        }

        TEST_METHOD(A256FromString4)
        {
            Assert::AreEqual(
                sha2::sha256(from_string32("\xc9\x8c\x8e\x55")),
                {
                    0x7abc22c0, 0xae5af26c, 0xe93dbb94, 0x433a0e0b, 0x2e119d01, 0x4f8e7f65, 0xbd56c61c, 0xcccd9504
                });
        }

        TEST_METHOD(A256SmallU)
        {
            Assert::AreEqual(
                sha2::sha256(sha2::no_remainder(nrange_t<uint32_t, 0, 14>())),
                {
                    0xd4817aa5, 0x497628e7, 0xc77e6b60, 0x6107042b, 0xbba31308, 0x88c5f47a, 0x375e6179, 0xbe789fbb
                });
            Assert::AreEqual(
                sha2::sha256(sha2::no_remainder(nrange_t<uint32_t, 0, 16>())),
                {
                    0xf5a5fd42, 0xd16a2030, 0x2798ef6e, 0xd309979b, 0x43003d23, 0x20d9f0e8, 0xea9831a9, 0x2759fb4b
                });
            Assert::AreEqual(
                sha2::sha256(sha2::no_remainder(nrange_t<uint32_t, 0, 250>())),
                {
                    0x541b3e9d, 0xaa09b20b, 0xf85fa273, 0xe5cbd3e8, 0x0185aa4e, 0xc298e765, 0xdb87742b, 0x70138a53
                });
        }

		/*
        TEST_METHOD(A256Small)
        {
            Assert::AreEqual(
                sha2::sha256u(sha2::no_remainder(n_range_t<0, 55>())),
                {
                    0x02779466, 0xcdec1638, 0x11d07881, 0x5c633f21, 0x90141308, 0x1449002f, 0x24aa3e80, 0xf0b88ef7
                });
            Assert::AreEqual(
                sha2::sha256u(sha2::no_remainder(n_range_t<0, 56>())),
                {
                    0xd4817aa5, 0x497628e7, 0xc77e6b60, 0x6107042b, 0xbba31308, 0x88c5f47a, 0x375e6179, 0xbe789fbb
                });
            Assert::AreEqual(
                sha2::sha256u(sha2::no_remainder(n_range_t<0, 57>())),
                {
                    0x65a16cb7, 0x861335d5, 0xace3c607, 0x18b5052e, 0x44660726, 0xda4cd13b, 0xb745381b, 0x235a1785
                });
            Assert::AreEqual(
                sha2::sha256u(sha2::no_remainder(n_range_t<0, 64>())),
                {
                    0xf5a5fd42, 0xd16a2030, 0x2798ef6e, 0xd309979b, 0x43003d23, 0x20d9f0e8, 0xea9831a9, 0x2759fb4b
                });
            Assert::AreEqual(
                sha2::sha256u(sha2::no_remainder(n_range_t<0, 1000>())),
                {
                    0x541b3e9d, 0xaa09b20b, 0xf85fa273, 0xe5cbd3e8, 0x0185aa4e, 0xc298e765, 0xdb87742b, 0x70138a53
                });
            Assert::AreEqual(
                sha2::sha256u(sha2::no_remainder(n_range_t<0x41, 1000>())),
                {
                    0xc2e68682, 0x3489ced2, 0x017f6059, 0xb8b23931, 0x8b6364f6, 0xdcd835d0, 0xa519105a, 0x1eadd6e4
                });
            Assert::AreEqual(
                sha2::sha256u(sha2::no_remainder(n_range_t<0x55, 1005>())),
                {
                    0xf4d62dde, 0xc0f3dd90, 0xea1380fa, 0x16a5ff8d, 0xc4c54b21, 0x740650f2, 0x4afc4120, 0x903552b0
                });
        }
		*/

        TEST_METHOD(A256Big0U)
        {
            Assert::AreEqual(
                sha2::sha256(sha2::no_remainder(nrange_t<uint32_t, 0, 250000>())),
                {
                    0xd29751f2, 0x649b32ff, 0x572b5e0a, 0x9f541ea6, 0x60a50f94, 0xff0beedf, 0xb0b692b9, 0x24cc8025
                });
        }

        TEST_METHOD(A256Big1U)
        {
            Assert::AreEqual(
                sha2::sha256(sha2::no_remainder(nrange_t<uint32_t, 0x5a5a5a5a, 0x8000000>())),
                {
                    0x15a1868c, 0x12cc5395, 0x1e182344, 0x277447cd, 0x0979536b, 0xadcc512a, 0xd24c67e9, 0xb2d4f3dd
                });
        }

        TEST_METHOD(A256Big2U)
        {
            Assert::AreEqual(
                sha2::sha256(sha2::no_remainder(nrange_t<uint32_t, 0, 0x10400000>())),
                {
                    0x461c19a9, 0x3bd4344f, 0x9215f5ec, 0x64357090, 0x342bc66b, 0x15a14831, 0x7d276e31, 0xcbc20b53
                });
        }

        TEST_METHOD(A256Big0)
        {
            Assert::AreEqual(
                sha2::sha256(nrange32<0, 1000000>()),
                {
                    0xd29751f2, 0x649b32ff, 0x572b5e0a, 0x9f541ea6, 0x60a50f94, 0xff0beedf, 0xb0b692b9, 0x24cc8025
                });
        }

        TEST_METHOD(A256Big1)
        {
            Assert::AreEqual(
                sha2::sha256(nrange32<0x5a, 0x20000000>()),
                {
                    0x15a1868c, 0x12cc5395, 0x1e182344, 0x277447cd, 0x0979536b, 0xadcc512a, 0xd24c67e9, 0xb2d4f3dd
                });
        }

        TEST_METHOD(A256Big2)
        {
            Assert::AreEqual(
                sha2::sha256(nrange32<0, 0x41000000>()),
                {
                    0x461c19a9, 0x3bd4344f, 0x9215f5ec, 0x64357090, 0x342bc66b, 0x15a14831, 0x7d276e31, 0xcbc20b53
                });
        }

        TEST_METHOD(A256Huge)
        {
            Assert::AreEqual(
                sha2::sha256(nrange32<0x42, 0x6000003e>()),
                {
                    0xc23ce8a7, 0x895f4b21, 0xec0daf37, 0x920ac0a2, 0x62a22004, 0x5a03eb2d, 0xfed48ef9, 0xb05aabea
                });
        }

        TEST_METHOD(A384)
        {
            Assert::AreEqual(
                sha2::sha384(from_string("")),
                {
                    0x38b060a751ac9638, 0x4cd9327eb1b1e36a, 0x21fdb71114be0743,
                    0x4c0cc7bf63f6e1da, 0x274edebfe76f65fb, 0xd51ad2f14898b95b
                });
            Assert::AreEqual(
                sha2::sha384(n_range_t<0, 111>()),
                {
                    0x435770712c611be7, 0x293a66dd0dc8d145, 0x0dc7ff7337bfe115,
                    0xbf058ef2eb9bed09, 0xcee85c26963a5bcc, 0x0905dc2df7cc6a76
                });
            Assert::AreEqual(
                sha2::sha384(n_range_t<0, 112>()),
                {
                    0x3e0cbf3aee0e3aa7, 0x0415beae1bd12dd7, 0xdb821efa446440f1,
                    0x2132edffce76f635, 0xe53526a111491e75, 0xee8e27b9700eec20
                });
            Assert::AreEqual(
                sha2::sha384(n_range_t<0, 113>()),
                {
                    0x6be9af2cf3cd5dd1, 0x2c8d9399ec2b34e6, 0x6034fbd699d4e022,
                    0x1d39074172a38065, 0x6089caafe8f39963, 0xf94cc7c0a07e3d21
                });
            Assert::AreEqual(
                sha2::sha384(n_range_t<0, 122>()),
                {
                    0x12a72ae4972776b0, 0xdb7d73d160a15ef0, 0xd19645ec96c7f816,
                    0x411ab780c794aa49, 0x6a22909d941fe671, 0xed3f3caee900bdd5
                });

            Assert::AreEqual(
                sha2::sha384(n_range_t<0, 1000>()),
                {
                    0xaae017d4ae5b6346, 0xdd60a19d52130fb5, 0x5194b6327dd40b89,
                    0xc11efc8222292de8, 0x1e1a23c9b59f9f58, 0xb7f6ad463fa108ca
                });
            Assert::AreEqual(
                sha2::sha384(n_range_t<0x41, 1000>()),
                {
                    0x7df01148677b7f18, 0x617eee3a23104f0e, 0xed6bb8c90a6046f7,
                    0x15c9445ff43c30d6, 0x9e9e7082de39c345, 0x2fd1d3afd9ba0689
                });
            Assert::AreEqual(
                sha2::sha384(n_range_t<0x55, 1005>()),
                {
                    0x1bb8e256da4a0d1e, 0x87453528254f223b, 0x4cb7e49c4420dbfa,
                    0x766bba4adba44eec, 0xa392ff6a9f565bc3, 0x47158cc970ce44ec
                });
            Assert::AreEqual(
                sha2::sha384(n_range_t<0, 1000000>()),
                {
                    0x8a1979f9049b3fff, 0x15ea3a43a4cf84c6, 0x34fd14acad1c333f,
                    0xecb72c588b68868b, 0x66a994386dc0cd16, 0x87b9ee2e34983b81
                });
            Assert::AreEqual(
                sha2::sha384(n_range_t<0x5a, 0x20000000>()),
                {
                    0x18aded227cc6b562, 0xcc7fb259e8f40454, 0x9e52914531aa1c5d,
                    0x85167897c779cc4b, 0x25d0425fd1590e40, 0xbd763ec3f4311c1a
                });
            Assert::AreEqual(
                sha2::sha384(n_range_t<0, 0x41000000>()),
                {
                    0x83ab05ca483abe3f, 0xaa597ad524d31291, 0xae827c5be2b3efcb,
                    0x6391bfed31ccd937, 0xb6135e0378c6c7f5, 0x98857a7c516f207a
                });
            Assert::AreEqual(
                sha2::sha384(n_range_t<0x42, 0x6000003e>()),
                {
                    0xcf852304f8d80209, 0x351b37ce69ca7dcf, 0x34972b4edb781702,
                    0x8ec55ab67ad3bc96, 0xeecb8241734258a8, 0x5d2afce65d4571e2
                });
        }

        TEST_METHOD(A512)
        {
            Assert::AreEqual(
                sha2::sha512(from_string64("")),
                {
                    0xcf83e1357eefb8bd, 0xf1542850d66d8007, 0xd620e4050b5715dc, 0x83f4a921d36ce9ce,
                    0x47d0d13c5d85f2b0, 0xff8318d2877eec2f, 0x63b931bd47417a81, 0xa538327af927da3e
                });
            Assert::AreEqual(
                sha2::sha512(nrange64<0, 111>()),
                {
                    0x77ddd3a542e530fd, 0x047b8977c657ba6c, 0xe72f1492e360b2b2, 0x212cd264e75ec038,
                    0x82e4ff0525517ab4, 0x207d14c70c2259ba, 0x88d4d335ee0e7e20, 0x543d22102ab1788c
                });
            Assert::AreEqual(
                sha2::sha512(nrange64<0, 112>()),
                {
                    0x2be2e788c8a8adea, 0xa9c89a7f78904cac, 0xea6e39297d75e057, 0x3a73c756234534d6,
                    0x627ab4156b48a665, 0x7b29ab8beb733340, 0x40ad39ead81446bb, 0x09c70704ec707952
                });
            Assert::AreEqual(
                sha2::sha512(nrange64<0, 113>()),
                {
                    0x0e67910bcf0f9ccd, 0xe5464c63b9c850a1, 0x2a759227d16b040d, 0x98986d54253f9f34,
                    0x322318e56b8feb86, 0xc5fb2270ed87f312, 0x52f7f68493ee7597, 0x43909bd75e4bb544
                });
            Assert::AreEqual(
                sha2::sha512(nrange64<0, 122>()),
                {
                    0x4f3f095d015be4a7, 0xa7cc0b8c04da4aa0, 0x9e74351e3a97651f, 0x744c23716ebd9b3e,
                    0x822e5077a01baa5c, 0xc0ed45b9249e88ab, 0x343d4333539df21e, 0xd229da6f4a514e0f
                });
            Assert::AreEqual(
                sha2::sha512(nrange64<0, 1000>()),
                {
                    0xca3dff61bb23477a, 0xa6087b27508264a6, 0xf9126ee3a004f53c, 0xb8db942ed345f2f2,
                    0xd229b4b59c859220, 0xa1cf1913f34248e3, 0x803bab650e849a3d, 0x9a709edc09ae4a76
                });
            Assert::AreEqual(
                sha2::sha512(nrange64<0x41, 1000>()),
                {
                    0x329c52ac62d1fe73, 0x1151f2b895a00475, 0x445ef74f50b979c6, 0xf7bb7cae349328c1,
                    0xd4cb4f7261a0ab43, 0xf936a24b000651d4, 0xa824fcdd577f211a, 0xef8f806b16afe8af
                });
            Assert::AreEqual(
                sha2::sha512(nrange64<0x55, 1005>()),
                {
                    0x59f5e54fe299c6a8, 0x764c6b199e44924a, 0x37f59e2b56c3ebad, 0x939b7289210dc8e4,
                    0xc21b9720165b0f4d, 0x4374c90f1bf4fb4a, 0x5ace17a116179801, 0x5052893a48c3d161
                });
            Assert::AreEqual(
                sha2::sha512(nrange64<0, 1000000>()),
                {
                    0xce044bc9fd43269d, 0x5bbc946cbebc3bb7, 0x11341115cc4abdf2, 0xedbc3ff2c57ad4b1,
                    0x5deb699bda257fea, 0x5aef9c6e55fcf4cf, 0x9dc25a8c3ce25f2e, 0xfe90908379bff7ed
                });
            Assert::AreEqual(
                sha2::sha512(nrange64<0x5a, 0x20000000>()),
                {
                    0xda172279f3ebbda9, 0x5f6b6e1e5f0ebec6, 0x82c25d3d93561a16, 0x24c2fa9009d64c7e,
                    0x9923f3b46bcaf11d, 0x39a531f43297992b, 0xa4155c7e827bd0f1, 0xe194ae7ed6de4cac
                });
            Assert::AreEqual(
                sha2::sha512(nrange64<0, 0x41000000>()),
                {
                    0x14b1be901cb43549, 0xb4d831e61e5f9df1, 0xc791c85b50e85f9d, 0x6bc64135804ad43c,
                    0xe8402750edbe4e5c, 0x0fc170b99cf78b9f, 0x4ecb9c7e02a15791, 0x1d1bd1832d76784f,
                });
            Assert::AreEqual(
                sha2::sha512(nrange64<0x42, 0x6000003e>()),
                {
                    0xfd05e13eb771f051, 0x90bd97d62647157e, 0xa8f1f6949a52bb6d, 0xaaedbad5f578ec59,
                    0xb1b8d6c4a7ecb2fe, 0xca6892b4dc138771, 0x670a0f3bd577eea3, 0x26aed40ab7dd58b1
                });
        }
    };
}