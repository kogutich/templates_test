#pragma once

#include "common.hpp"
#include <type_traits>

namespace mp
{
	// default, for any type
	template <typename T, typename = void>
	struct partial
	{
		inline static constexpr size_t value = 1;
	};

	// for double and float
	template <typename T>
	struct partial<T, std::enable_if_t<is_any_of<T>:: template among<double, float>::value>>
	{
		inline static constexpr size_t value = 2;
	};

	// for int and char
	template <typename T>
	struct partial<T, std::enable_if_t<is_any_of<T>:: template among<int, char>::value>>
	{
		inline static constexpr size_t value = 3;
	};
}

// usage
static_assert( mp::partial<bool>::value == 1 );
static_assert( mp::partial<double>::value == 2 );
static_assert( mp::partial<float>::value == 2 );
static_assert( mp::partial<int>::value == 3 );
static_assert( mp::partial<char>::value == 3 );

int main()
{
}
