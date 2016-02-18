#include "stdafx.h"
#include "CppUnitTest.h"

#include "../../src/sha2.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
    TEST_CLASS(Sha2LinkerTest)
    {
    public:

        TEST_METHOD(Linker32)
        {
            Assert::AreEqual(sha2::parameters_t<uint32_t, void>::k[0], 0x428a2f98u);
        }

        TEST_METHOD(Linker64)
        {
            Assert::AreEqual(sha2::parameters_t<uint64_t, void>::k[0], 0x428a2f98d728ae22ul);
        }
    };
}