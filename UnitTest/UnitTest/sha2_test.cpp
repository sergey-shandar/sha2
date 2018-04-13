#include "stdafx.h"
#include "CppUnitTest.h"

#include "../../src/sha2.hpp"

#include <boost/range.hpp>

#include "helper.hpp"

namespace UnitTest
{    
    TEST_CLASS(Sha2Test)
    {
    public:
        
        /*
        // 32 GB 
        // old: ~ 5 min
        // new: ~ 4 min
        TEST_METHOD(Sha256Length)
        {
            auto const x = sha2::sha256(nrange32<0, 0x800000000>());
        }
        */

        /*
        // 32 GB
        // new: ~ 3 min
        TEST_METHOD(Sha512Length)
        {
            Assert::AreEqual(
                sha2::sha512_256(sha2::fill8<64, 0, 0x800000000ull * 8>()),
                {
                    0x309cd2dd4484d3e1,
                    0x02c54254cc3a26a2,
                    0x378480115d27168f,
                    0x36cea299bfce6765,
                });
        }
        */

        TEST_METHOD(Sha224)
        {
            Assert::AreEqual(
                sha2::sha224(sha2::from_string<32>("")),
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
                sha2::sha224(sha2::from_string<32>(
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
                sha2::sha224(sha2::from_string<32>(
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

        TEST_METHOD(Sha256U)
        {
            Assert::AreEqual(
                sha2::sha256(sha2::bit_sequence(
                    ::boost::make_iterator_range<uint32_t const *>(nullptr, nullptr))),
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
                sha2::sha256(sha2::from_string<32>("")),
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
                sha2::sha256(sha2::from_string<32>(
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
            //                           0123012301230123012301230123012301230123012
            auto const x = sha2::from_string<32>("The quick brown fox jumps over the lazy dog");
            Assert::AreEqual(x.end() - x.begin(), 10LL);
            Assert::AreEqual(x.remainder_size(), 24);
            char const m[] = "\0god";
            Assert::AreEqual(x.remainder(), *reinterpret_cast<uint32_t const *>(m));
            //                                 d o g
            Assert::AreEqual(x.remainder(), 0x646F6700u);
            Assert::AreEqual(
                sha2::sha256(x),
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
        }

        TEST_METHOD(Sha512)
        {
            Assert::AreEqual(
                sha2::sha512(sha2::from_string<64>("")),
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

        TEST_METHOD(Sha384)
        {
            Assert::AreEqual(
                sha2::sha384(sha2::from_string<64>("")),
                {
                    0x38b060a751ac9638,
                    0x4cd9327eb1b1e36a,
                    0x21fdb71114be0743,
                    0x4c0cc7bf63f6e1da,
                    0x274edebfe76f65fb,
                    0xd51ad2f14898b95b,
                });
        }

        TEST_METHOD(Sha512t256)
        {
            Assert::AreEqual(
                sha2::sha512_256(sha2::from_string<64>("")),
                {
                    0xc672b8d1ef56ed28,
                    0xab87c3622c511406,
                    0x9bdd3ad7b8f97374,
                    0x98d0c01ecef0967a,
                });
        }

        TEST_METHOD(Sha512t224)
        {
            Assert::AreEqual(
                sha2::sha512_224(sha2::from_string<64>("")),
                {
                    0x6ed0dd02806fa89e,
                    0x25de060c19d3ac86,
                    0xcabb87d6a0ddd05c,
                    0x333b84f400000000,
                });
        }
    };
}