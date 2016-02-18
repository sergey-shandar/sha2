#include <sha2.hpp>

template<size_t S>
::boost::iterator_range<char const *> from_string(char const (&x)[S])
{
    return ::boost::make_iterator_range_n(x, S - 1);
}

int main()
{
    auto const sha512 = sha2::sha512(from_string("Hello world!"));
    return 0;
}