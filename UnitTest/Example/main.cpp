#include "../../src/sha2.hpp"

int main()
{
    auto const sha512 = sha2::sha512(sha2::from_string<64>("Hello world!"));
    return 0;
}