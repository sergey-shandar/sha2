[![Build status](https://ci.appveyor.com/api/projects/status/3inr5ejtnldgc9b0/branch/master?svg=true)](https://ci.appveyor.com/project/sergey-shandar/sha2/branch/master)

[![NuGet version](https://badge.fury.io/nu/sha2.svg)](https://badge.fury.io/nu/sha2).

C++ implementation of SHA-2:
- SHA-224
- SHA-256
- SHA-384
- SHA-512
- SHA-512/224
- SHA-512/256

## Supported Compilers

- Visual C++ 14.0 (Visual Studio 2015)
- CLang 3.7

## Bit Sequence Concept

```C++
template<class ValueType>
class IteratorConcept
{
public:
    ValueType *operator() const;
    IteratorConcept operator++() const;
    bool operator==(IteratorConcept const &) const;
    bool operator!=(IteratorConcept const &) const;
};

template<size_t ValueSize>
class BitSequenceConcept
{
public:
    
    typedef uint_t<ValueSize> value_type;
    
    typedef IteratorConcept<value_type const> const_iterator;
    
    const_iterator begin() const;
    
    const_iterator end() const;

    value_type remainder() const;

    /**
     * A remainder size in bits. 
     */
    size_t remainder_size() const;
};
```

## API

### SHA2 Functions

```C++
namespace sha2
{
    /**
     * T is BitSequenceConcept<32>
     */
    template<class T>
    ::std::array<uint32_t, 8> sha256(T const &input);
    
    /**
     * T is BitSequenceConcept<32>
     */
    template<class T>
    ::std::array<uint32_t, 7> sha224(T const &input);
    
    /**
     * T is BitSequenceConcept<64>
     */
    template<class T>
    ::std::array<uint64_t, 6> sha384(T const &input);
    
    /**
     * T is BitSequenceConcept<64>
     */
    template<class T>
    ::std::array<uint64_t, 8> sha512(T const &input);
    
    /**
     * T is BitSequenceConcept<64>
     */
    template<class T>
    ::std::array<uint64_t, 4> sha512_256(T const &input);
    
    /**
     * T is BitSequenceConcept<64>
     */
    template<class T>
    ::std::array<uint64_t, 4> sha512_224(T const &input);
}
```

### Bit Sequence

```C++
namespace sha2
{
    /**
     * Implements BitSequence<sizeof(typename Iterator::value_type) * CHAR_BIT>.
     */
    template<class Iterator>
    class bit_sequence_t
    {
    public:
        typedef typename ::std::iterator_traits<I>::value_type value_type;
        bit_sequence_t(Iterator begin, Iterator end, value_type remainder, size_t remainder_size);
        Iterator begin() const;
        Iterator end() const;
        value_type remainder() const;
        size_t remainder_size() const;
    };
    
    template<class I, class V>
    bit_sequence_t<I> bit_sequence(I begin, I end, V remainder, size_t remainder_size);

    template<class I>
    bit_sequence_t<I> bit_sequence(I begin, I end);

    template<class C>
    bit_sequence_t<typename C::const_iterator> bit_sequence(C const &c);
    
    template<size_t ValueBitSize>
    bit_sequence_t<uint_t<ValueBitSize> const *> bit_sequence(uint8_t const *begin, uint8_t const *end);
}
```

### Fill Bit Sequence With Value

```C++
namespace sha2
{
    /**
     * Implements BitSequence<sizeof(T) * CHAR_BIT>.
     */
    template<class T, T value, uint64_t size, size_t remainder_size_ = 0>
    class fill_t
    {
    public:
        typedef ... const_iterator;
        static const_iterator begin();
        static const_iterator end();
        static size_t remainder_size();
        static T remainder();
    };

    /**
     * Returns BitSequence<output_size>.
     */
    template<size_t output_size, uint8_t value, uint64_t size>
    auto fill8();
}
```

## Example

- [UnitTest/Example/main.cpp](UnitTest/Example/main.cpp)
