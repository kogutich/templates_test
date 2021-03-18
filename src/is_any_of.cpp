#pragma once

#include <type_traits>
#include <string>

namespace mp
{
	template <typename T, typename U>
	struct is_same : std::false_type
	{
	};

	template <typename T>
	struct is_same<T, T> : std::true_type
	{
	};

	template <typename T>
	struct is_any_of
	{
		template <typename ...Args>
		using among = std::disjunction<is_same<T, Args>...>;
	};
}

// usage
static_assert( !mp::is_any_of<std::string>::among<int>::value );
static_assert( mp::is_any_of<bool>::among<bool>::value );
static_assert( !mp::is_any_of<int>::among<double, bool>::value );
static_assert( mp::is_any_of<char>::among<double, int, char, float>::value );

int main()
{
}