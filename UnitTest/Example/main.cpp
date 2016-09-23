#include "../../src/sha2.hpp"

#include <boost/range/iterator_range.hpp>

int main()
{
    auto const sha512 = sha2::sha512(sha2::from_string64("Hello world!"));
    return 0;
}