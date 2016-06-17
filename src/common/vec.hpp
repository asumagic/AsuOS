#include <stddef.h>
#include <stdint.h>

template<typename T>
struct vec2
{
	T x, y;
};

/// Signed types

// int
typedef vec2<int> vec2i;
typedef vec2<unsigned int> vec2u;

// short
typedef vec2<short> vec2s;
typedef vec2<unsigned short> vec2us;

// char
typedef vec2<char> vec2c;
typedef vec2<char> vec2uc;
