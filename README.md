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

## API

```C++
namespace sha2
{
    template<class T>
    auto sha256(T const &input);
    
    template<class T>
    auto sha224(T const &input);
    
    template<class T>
    auto sha384(T const &input);
    
    template<class T>
    auto sha512(T const &input);
    
    template<class T>
    auto sha512_256(T const &input);
    
    template<class T>
    auto sha512_224(T const &input);
}
```

## Download

- [NuGet](https://www.nuget.org/packages/sha2/)

## Example

- [UnitTest/Example/main.cpp](UnitTest/Example/main.cpp)
