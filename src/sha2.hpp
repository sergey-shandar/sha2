#pragma once

#include <array>

namespace sha2
{
    template<class T>
    constexpr T right_rotate(T v, int n)
    {
        return (v >> n) | (v << (sizeof(T) * CHAR_BIT - n));
    }

    template<class T, class Dummy = void>
    class parameters_t {};

    template<class Dummy>
    class parameters_t<uint32_t, Dummy>
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

        typedef uint32_t const k_t[size];

        static k_t k;
    };

    // Initialize array of round constants :
    // (first 32 bits of the fractional parts of the cube roots of the first 64 primes 2..311) :
    template<class Dummy>
    typename parameters_t<uint32_t, Dummy>::k_t parameters_t<uint32_t, Dummy>::k = 
    {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2,
    };

    template<class Dummy>
    class parameters_t<uint64_t, Dummy>
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

        typedef uint64_t const k_t[size];

        static k_t k;
    };

    template<class Dummy>
    typename parameters_t<uint64_t, Dummy>::k_t parameters_t<uint64_t, Dummy>::k =
    {
        0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc, 0x3956c25bf348b538,
        0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118, 0xd807aa98a3030242, 0x12835b0145706fbe,
        0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2, 0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235,
        0xc19bf174cf692694, 0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
        0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5, 0x983e5152ee66dfab,
        0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4, 0xc6e00bf33da88fc2, 0xd5a79147930aa725,
        0x06ca6351e003826f, 0x142929670a0e6e70, 0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed,
        0x53380d139d95b3df, 0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b,
        0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30, 0xd192e819d6ef5218,
        0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8, 0x19a4c116b8d2d0c8, 0x1e376c085141ab53,
        0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8, 0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373,
        0x682e6ff3d6b2b8a3, 0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
        0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b, 0xca273eceea26619c,
        0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178, 0x06f067aa72176fba, 0x0a637dc5a2c898a6,
        0x113f9804bef90dae, 0x1b710b35131c471b, 0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc,
        0x431d67c49c100d4c, 0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817
    };

    template<class T>
    class state_t: parameters_t<T>
    {
    public:

        typedef parameters_t<T> p_t;

        ::std::array<T, 8> result;

        T w[p_t::size];

        state_t(::std::array<T, 8> const &initial) : result(initial) {}

        void process()
        {
            // Extend the first 16 words into the remaining 48/66 words w[16..63/79] 
            // of the message schedule array:
            for (auto i = 16; i < p_t::size; ++i)
            {
                auto const w15 = w[i - 15];
                auto const w2 = w[i - 2];

                auto const s0 =
                    right_rotate(w15, p_t::s00) ^
                    right_rotate(w15, p_t::s01) ^
                    (w15 >> p_t::s02);
                auto const s1 =
                    right_rotate(w2, p_t::s10) ^
                    right_rotate(w2, p_t::s11) ^
                    (w2 >> p_t::s12);

                w[i] = w[i - 16] + s0 + w[i - 7] + s1;
            }

            // Initialize working variables to current hash value :
            T a = result[0];
            T b = result[1];
            T c = result[2];
            T d = result[3];
            T e = result[4];
            T f = result[5];
            T g = result[6];
            T h = result[7];

            // Compression function main loop :
            for (auto i = 0; i < p_t::size; ++i)
            {
                auto const s1 =
                    right_rotate(e, p_t::e0) ^
                    right_rotate(e, p_t::e1) ^
                    right_rotate(e, p_t::e2);
                auto const ch = (e & f) ^ ((~e) & g);
                auto const temp1 = h + s1 + ch + p_t::k[i] + w[i];

                auto const s0 =
                    right_rotate(a, p_t::a0) ^
                    right_rotate(a, p_t::a1) ^
                    right_rotate(a, p_t::a2);
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

    template<class I>
    class bit_sequence_t
    {
    private:
        I _begin;
        I _end;
    public:

        typedef typename std::iterator_traits<I>::value_type value_type;

        bit_sequence_t(I begin, I end) : _begin(begin), _end(end) { }

        value_type operator()(uint32_t &size)
        {
            if (_begin == _end)
            {
                size = 0;
                return 0;
            }
            else
            {
                size = sizeof(value_type) * CHAR_BIT;
                value_type const result = *_begin;
                ++_begin;
                return result;
            }
        }
    };

    template<class C>
    auto bit_sequence(C &c)
    {
        typedef typename decltype(::std::begin(c)) iterator_t;
        return bit_sequence_t<iterator_t>(::std::begin(c), ::std::end(c));
    }

    template<class T>
    auto make_unsigned(T v)
    {
        return static_cast<::std::make_unsigned_t<T>>(v);
    }

    // input requirements:
    // - iterator begin() const;
    // - iterator end() const;
    // - T remainder_value()
    // - size_t remainder_size() - it should be in the range [0, sizeof(T)).
    template<class T, class I>
    ::std::array<T, 8> process(::std::array<T, 8> const &initial, I const &input)
    {
        static_assert(
            sizeof(*input.begin()) == sizeof(T),
            "sizeof(*input.begin()) != sizeof(T)");
        static_assert(
            sizeof(input.remainder()) == sizeof(T),
            "sizeof(input.remainder()) != sizeof(T)");

        static int const uint_size = sizeof(T) * CHAR_BIT;

        T size_hi = 0;
        state_t<T> state(initial);
        static const auto i_max = 
            ::std::numeric_limits<T>::max() / uint_size + 1;
        T i = 0;

        for (auto const value: input)
        {
            auto const index = i % 16;
            state.w[index] = value;
            i = (i + 1) % i_max;
            if (index == 15)
            {
                state.process();
                if (i == 0)
                {
                    ++size_hi;
                }
            }
        }

        // remainder and 1 bit at the end.
        {
            // size < unit_size always.
            auto index = i % 16;
            auto const size = input.remainder_size();
            state.w[index] =
                input.remainder() | 
                (static_cast<T>(1) << ((uint_size - 1) - size));

            //
            ++index;
            if (index > 14)
            {
                for (; index < 16; ++index)
                {
                    state.w[index] = 0;
                }
                state.process();
                index = 0;
            }
            for (; index < 14; ++index)
            {
                state.w[index] = 0;
            }
            state.w[14] = size_hi;
            state.w[15] = i * uint_size + size;
            state.process();
        }

        return state.result;
    }

	// old process
    template<class T, class B>
    ::std::array<T, 8> process_bit_sequence(
        ::std::array<T, 8> const &initial,
        B const &bytes)
    {
        static int const uint_size = sizeof(T) * CHAR_BIT;

        auto bits = bit_sequence(bytes);

        T size_lo = 0;
        T size_hi = 0;
        state_t<T> state(initial);
        T value = 0;

        while(true)
        {
            uint32_t b_size;
            auto const b = bits(b_size);
            if (b_size == 0)
            {
                break;
            }
            auto const value_offset = (uint_size - b_size) - size_lo % uint_size;
            value |= static_cast<T>(make_unsigned(b)) << value_offset;
            if (value_offset == 0)
            {
                auto const i = (size_lo / uint_size) % 16;
                state.w[i] = value;
                value = 0;
                if (i == 15)
                {
                    state.process();
                    if (size_lo == std::numeric_limits<T>::max() - (b_size - 1))
                    {
                        ++size_hi;
                    }
                }
            }
            size_lo += b_size;
        }

        // 1 bit at the end.
        {
            auto i = (size_lo / uint_size) % 16;
            state.w[i] =
                value | static_cast<T>(1) << ((uint_size - 1) - size_lo % uint_size);
            ++i;
            if (i > 14)
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
            state.w[14] = size_hi;
            state.w[15] = size_lo;
            state.process();
        }

        return state.result;
    }

    // bytes is a function wich returns optional(bitloads, size)
    template<class T, class Bytes>
    ::std::array<T, 8> process_old(
        ::std::array<T, 8> const &initial,
        Bytes const &bytes)
    {
        return process_bit_sequence(initial, bytes);
    }

    // 256 bits = 32 bytes = 16 uint16 = 8 uint32 = 4 uint64
    typedef ::std::array<uint32_t, 8> sha256_t;

    template<class I>
    class with_remainder_t
    {
    public:
        typedef typename ::std::iterator_traits<I>::value_type value_type;
    private:
        I _begin;
        I _end;
        value_type const _remainder;
        int const _remainder_size;
    public:
        with_remainder_t(
            I const &begin,
            I const &end,
            value_type remainder,
            int remainder_size):
            _begin(begin),
            _end(end),
            _remainder(remainder),
            _remainder_size(remainder_size)
        {
        }
        I begin() const { return _begin; }
        I end() const { return _end; }
        value_type remainder() const { return _remainder; }
        int remainder_size() const { return _remainder_size; }
    };

	template<class I, class V>
	auto with_remainder(
		I const &begin, I const &end, V remainder, int remainder_size)
	{
		return with_remainder_t<I>(begin, end, remainder, remainder_size);
	}

    template<class I>
    auto no_remainder(I const &begin, I const &end)
    {
        return with_remainder(begin, end, 0, 0);
    }

    template<class C>
    auto no_remainder(C const &c)
    {
        return no_remainder(::std::begin(c), ::std::end(c));
    }

    template<class Input>
    sha256_t sha256(Input const &input)
    {
        return process<uint32_t>(
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
            input);
    }

    typedef ::std::array<uint32_t, 7> sha224_t;

    template<class Input>
    sha224_t sha224(Input const &input)
    {
        // SHA - 224 initial hash values(in big endian) :
        // (The second 32 bits of the fractional parts of the square roots of 
        // the 9th through 16th primes 23..53)
        auto const result = process<uint32_t>(
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
            input);
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

    typedef ::std::array<uint64_t, 8> sha512_t;

    template<class Input>
    sha512_t sha512(Input const &input)
    {
        return process<uint64_t>(
            {
                {
                    0x6a09e667f3bcc908,
                    0xbb67ae8584caa73b,
                    0x3c6ef372fe94f82b,
                    0xa54ff53a5f1d36f1,
                    0x510e527fade682d1,
                    0x9b05688c2b3e6c1f,
                    0x1f83d9abfb41bd6b,
                    0x5be0cd19137e2179,
                }
            },
            input);
    }

    typedef ::std::array<uint64_t, 6> sha384_t;

    template<class Input>
    sha384_t sha384(Input const &input)
    {
        auto const result = process<uint64_t>(
            {
                {
                    0xcbbb9d5dc1059ed8,
                    0x629a292a367cd507,
                    0x9159015a3070dd17,
                    0x152fecd8f70e5939,
                    0x67332667ffc00b31,
                    0x8eb44a8768581511,
                    0xdb0c2e0d64f98fa7,
                    0x47b5481dbefa4fa4,
                }
            },
            input);
        return 
            {
                {
                    result[0],
                    result[1],
                    result[2],
                    result[3],
                    result[4],
                    result[5],
                }
            };
    }

    typedef ::std::array<uint64_t, 4> sha512t256_t;

    template<class Input>
    sha512t256_t sha512t256(Input const &input)
    {
        auto const result = process<uint64_t>(
            {
                {
                    0x22312194FC2BF72C,
                    0x9F555FA3C84C64C2,
                    0x2393B86B6F53B151,
                    0x963877195940EABD,
                    0x96283EE2A88EFFE3,
                    0xBE5E1E2553863992,
                    0x2B0199FC2C85B8AA,
                    0x0EB72DDC81C52CA2
                }
            },
            input);
        return
            {
                {
                    result[0],
                    result[1],
                    result[2],
                    result[3],
                }
            };
    }

    template<class Input>
    sha512t256_t sha512t224(Input const input)
    {
        auto const result = process<uint64_t>(
            {
                {
                    0x8C3D37C819544DA2,
                    0x73E1996689DCD4D6,
                    0x1DFAB7AE32FF9C82,
                    0x679DD514582F9FCF,
                    0x0F6D2B697BD44DA8,
                    0x77E36F7304C48942,
                    0x3F9D85A86A1D36C8,
                    0x1112E6AD91D692A1,
                }
            },
            input);
        return
            {
                {
                    result[0],
                    result[1],
                    result[2],
                    result[3] & 0xFFFFFFFF00000000,
                }
            };
    }
}
