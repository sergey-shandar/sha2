[![Build status](https://ci.appveyor.com/api/projects/status/3inr5ejtnldgc9b0/branch/master?svg=true)](https://ci.appveyor.com/project/sergey-shandar/sha2/branch/master)

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

## Download

- [NuGet](https://www.nuget.org/packages/sha2/)

## Example

- [UnitTest/Example/main.cpp](UnitTest/Example/main.cpp)
