#pragma once

#include <array>
#include <cstddef>

namespace mp
{
	template <typename ...Ts>
	struct is_unique : std::true_type
	{
	};

	template <typename T, typename ...Ts>
	struct is_unique<T, Ts...> : std::bool_constant<!std::disjunction_v<std::is_same<T, Ts>...>&& is_unique<Ts...>::value>
	{
	};

	template <typename ...Ts>
	inline static constexpr bool is_unique_v = is_unique<Ts...>::value;
}

// usage
static_assert( mp::is_unique_v<> );
static_assert( mp::is_unique_v<int> );
static_assert( !mp::is_unique_v<int, int> );
static_assert( mp::is_unique_v<int, double> );
static_assert( !mp::is_unique_v<int, double, char, int, void> );
static_assert( mp::is_unique_v<int, double, char, void> );
static_assert( !mp::is_unique_v<int, void, void> );

int main()
{
}