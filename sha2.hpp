#pragma once

#include <array>

namespace sha2
{
    // 256 bits = 32 bytes = 16 uint16 = 8 uint32 = 4 uint64
    typedef ::std::array<uint32_t, 8> sha256_t;

    template<int n, class T>
    T right_rotate(T v)
    {
        return (v >> n) | (v << (sizeof(T) * CHAR_BIT - n));
    }

    template<class T>
    class parameters_t {};

    template<>
    class parameters_t<uint32_t>
    {
    public:
        static const size_t size = 64;

        static const size_t s00 = 7;
        static const size_t s01 = 18;
        static const size_t s02 = 3;

        static const size_t s10 = 17;
        static const size_t s11 = 19;
        static const size_t s12 = 10;

        static const size_t a0 = 2;
        static const size_t a1 = 13;
        static const size_t a2 = 22;

        static const size_t e0 = 6;
        static const size_t e1 = 11;
        static const size_t e2 = 25;
    };

    template<>
    class parameters_t<uint64_t>
    {
    public:
        static const size_t size = 80;

        static const size_t s00 = 1;
        static const size_t s01 = 8;
        static const size_t s02 = 7;

        static const size_t s10 = 19;
        static const size_t s11 = 61;
        static const size_t s12 = 6;

        static const size_t a0 = 28;
        static const size_t a1 = 34;
        static const size_t a2 = 39;

        static const size_t e0 = 14;
        static const size_t e1 = 18;
        static const size_t e2 = 41;
    };

    template<class T>
    class state_t
    {
    public:

        typedef parameters_t<T> p_t;

        T const (&k)[p_t::size];

        ::std::array<T, 8> result;

        T w[p_t::size];

        state_t(T const (&k)[p_t::size], ::std::array<T, 8> const &initial) :
            k(k), result(initial)
        {
        }

        void process()
        {
            // Extend the first 16 words into the remaining 48 words w[16..63] 
            // of the message schedule array:
            for (auto i = 16; i < p_t::size; ++i)
            {
                auto const w15 = w[i - 15];
                auto const w2 = w[i - 2];

                auto const s0 =
                    right_rotate<p_t::s00>(w15) ^
                    right_rotate<p_t::s01>(w15) ^
                    (w15 >> p_t::s02);
                auto const s1 =
                    right_rotate<p_t::s10>(w2) ^
                    right_rotate<p_t::s11>(w2) ^
                    (w2 >> p_t::s12);

                w[i] = w[i - 16] + s0 + w[i - 7] + s1;
            }

            // Initialize working variables to current hash value :
            uint32_t a = result[0];
            uint32_t b = result[1];
            uint32_t c = result[2];
            uint32_t d = result[3];
            uint32_t e = result[4];
            uint32_t f = result[5];
            uint32_t g = result[6];
            uint32_t h = result[7];

            // Compression function main loop :
            for (auto i = 0; i < p_t::size; ++i)
            {
                auto const s1 =
                    right_rotate<p_t::e0>(e) ^
                    right_rotate<p_t::e1>(e) ^
                    right_rotate<p_t::e2>(e);
                auto const ch = (e & f) ^ ((~e) & g);
                auto const temp1 = h + s1 + ch + k[i] + w[i];

                auto const s0 =
                    right_rotate<p_t::a0>(a) ^
                    right_rotate<p_t::a1>(a) ^
                    right_rotate<p_t::a2>(a);
                auto const maj = (a & b) ^ (a & c) ^ (b & c);
                auto const temp2 = s0 + maj;

                h = g;
                g = f;
                f = e;
                e = d + temp1;
                d = c;
                c = b;
                b = a;
                a = temp1 + temp2;
            }

            // Add the compressed chunk to the current hash value :
            result[0] += a;
            result[1] += b;
            result[2] += c;
            result[3] += d;
            result[4] += e;
            result[5] += f;
            result[6] += g;
            result[7] += h;
        }
    };

    // Initialize array of round constants :
    // (first 32 bits of the fractional parts of the cube roots of the first 64 primes 2..311) :
    uint32_t const kk[] = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2,
    };

    template<class Bytes>
    sha256_t process(sha256_t const &initial, Bytes const &bytes)
    {
        uint64_t size = 0;
        state_t<uint32_t> state(kk, initial);
        uint32_t value = 0;
        for each (auto const v in bytes)
        {
            auto const value_offset = size % 32;
            value |= v << (24 - value_offset);
            if (value_offset == 24)
            {
                auto const i = (size / 32) % 16;
                state.w[i] = value;
                value = 0;
                if (i == 15)
                {
                    state.process();
                }
            }
            size += 8;
        }
        // 1 bit at the end.
        {
            auto const value_offset = size % 32;
            value |= 0x80 << (24 - value_offset);
            auto i = (size / 32) % 16;
            state.w[i] = value;
            ++i;
            if (i >= 14)
            {
                for (; i < 16; ++i)
                {
                    state.w[i] = 0;
                }
                state.process();
                i = 0;
            }
            for (; i < 14; ++i)
            {
                state.w[i] = 0;
            }
            state.w[14] = static_cast<uint32_t>(size >> 32);
            state.w[15] = static_cast<uint32_t>(size);
            state.process();
        }
        return state.result;
    }

    template<class Bytes>
    sha256_t sha256(Bytes const &bytes)
    {
        // Initialize hash values :
        // (first 32 bits of the fractional parts of the square roots of the
        // first 8 primes 2..19) :
        return process(
            {
                {
                    0x6a09e667,
                    0xbb67ae85,
                    0x3c6ef372,
                    0xa54ff53a,
                    0x510e527f,
                    0x9b05688c,
                    0x1f83d9ab,
                    0x5be0cd19,
                }
            },
            bytes);
    }

    typedef ::std::array<uint32_t, 7> sha224_t;

    template<class Bytes>
    sha224_t sha224(Bytes const &bytes)
    {
        // SHA - 224 initial hash values(in big endian) :
        // (The second 32 bits of the fractional parts of the square roots of 
        // the 9th through 16th primes 23..53)
        auto const result = process(
            {
                {
                    0xc1059ed8,
                    0x367cd507,
                    0x3070dd17,
                    0xf70e5939,
                    0xffc00b31,
                    0x68581511,
                    0x64f98fa7,
                    0xbefa4fa4,
                }
            },
            bytes);
        return
        {
            {
                result[0],
                result[1],
                result[2],
                result[3],
                result[4],
                result[5],
                result[6],
            }
        };
    }
}
