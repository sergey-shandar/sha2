// CLangLibExample.cpp : Defines the exported functions for the static library.
//

#include "CLangLibExample.h"

#include <sha2.hpp>

// This is an example of an exported variable
int nCLangLibExample=0;

// This is an example of an exported function.
int fnCLangLibExample(void)
{
    uint8_t const x[] = { 0x48 };
    auto const r = sha2::sha512(x);
    return r[0];
}

// This is the constructor of a class that has been exported.
// see CLangLibExample.h for the class definition
CCLangLibExample::CCLangLibExample()
{
    return;
}
